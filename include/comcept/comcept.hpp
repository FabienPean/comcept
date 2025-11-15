// SPDX-License-Identifier: MIT
#pragma once

#include <concepts>
#include <ranges>
#include <type_traits>
#include <utility>
#include <variant>

namespace comcept
{
    /// Defines the core requirement that a type must fulfill to be used as argument in a composable concept
    /// It is not possible to verify the validity of a template variable for all possible instances (infinite possibilities),
    /// hence the need to query for a specific type _Type_ template argument.
    template<typename Type, typename Trait>
    concept composable = std::same_as<decltype(Trait::template value<Type>), const bool>;

    /// Verify that a type fulfills a constraint expressed via a composable trait, as defined by this library
    template<typename Type, typename Type_or_Trait>
    concept satisfy = std::same_as<Type,Type_or_Trait> || (composable<Type,Type_or_Trait> && Type_or_Trait::template value<Type>);

    /// Composable concept to verify that a type fulfills all given type or constraints
    template<typename T, typename... Traits>
    concept all_of = (satisfy<T,Traits> && ...);

    /// Composable concept to verify that a type fulfills any given type or constraints
    template<typename T,typename... Traits>
    concept any_of = (satisfy<T,Traits> || ...); 

    /// Composable concept to verify that a type fulfills all given type or constraints
    template<typename T, typename Trait>
    concept not_a = composable<T,Trait> && (Trait::template value<T> == false);
    template<typename T, typename... Traits>
    concept none_of = (not_a<T, Traits> && ...);
    
    /// Composable concept to constrain on the content of a range
    template<class Range, class Type_or_Trait, template<class...>class Element = std::ranges::range_value_t>
    concept range_of = std::ranges::range<Range> && satisfy<Element<Range>,Type_or_Trait>;

    /// Composable concept to constrain the end result of a call to `std::decay_t`
    template<typename T, typename Type_or_Trait>
    concept decays_to = satisfy<std::decay_t<T>,Type_or_Trait>;

    /// Composable concept to constrain the content of associative containers
    template<typename T, typename Key, typename Val>
    concept map_of = satisfy<typename T::key_type,Key> && satisfy<typename T::mapped_type,Val>;
    template<typename T, typename Key>
    concept set_of = satisfy<typename T::key_type,Key> && satisfy<typename T::value_type ,Key>;                

    /// Composable concept to constrain the possibilities of `std::variant`
    template <typename T, typename... Types>
    concept variant_of = 
    ([]<std::size_t... I, typename U>(std::index_sequence<I...>, std::type_identity<U>) 
    { 
        return (satisfy<std::variant_alternative_t<I,T>,U> || ...);
    } (std::make_index_sequence<std::variant_size_v<T>>{}, std::type_identity<Types>{}) && ... );

    /// Composable concept match qualified types and forward underlying type to the constraint
    template <typename T, typename Type_or_Trait>
    concept cvref_of = !std::same_as<T,std::remove_cvref_t<T>> && satisfy<std::remove_cvref_t<T>,Type_or_Trait>;
    
    template <typename T, typename Type_or_Trait>
    concept qualified = cvref_of<T,Type_or_Trait>;
    
    template <typename T, typename Type_or_Trait>
    concept unqualified = std::same_as<T,std::remove_cvref_t<T>> && satisfy<T,Type_or_Trait>;

    /// Concept checking that a type implements the _tuple protocol_
    template <typename T>
    concept tuple_like =
        requires
        {
            typename std::tuple_size<std::remove_cvref_t<T>>::type;
            requires std::same_as<decltype(std::tuple_size_v<std::remove_cvref_t<T>>), const std::size_t>;
        } 
        and 
        []<std::size_t... I>(std::index_sequence<I...>) 
        { 
            constexpr auto has_tuple_element = 
            []<std::size_t N>(){ return requires(T t) {
                typename std::tuple_element_t<N, std::remove_cvref_t<T>>;
                { get<N>(t) } -> decays_to<std::tuple_element_t<N, std::remove_cvref_t<T>>>;
            }; };
            return ( has_tuple_element.template operator()<I>() && ...);
        } (std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>{});

    template <typename T>
    concept pair_like = tuple_like<T> && std::tuple_size_v<T> == 2;

    /// Composable concept to constrain the content of a tuple like type
    template<typename T, typename... Type_or_Trait>
    concept tuple_of =
        comcept::tuple_like<T>
        and
        std::tuple_size_v<T> == sizeof...(Type_or_Trait) 
        and 
        // IIFE to input index sequence to process each element of the tuple
        []<std::size_t... I>(std::index_sequence<I...>) 
        {
            constexpr auto check_constraint = []<typename ToC, typename E>()
            {
                if constexpr (std::same_as<ToC, E>)
                    return true;
                if constexpr (requires { ToC::template value<E>; })
                    return ToC::template value<E>;
                else
                    return false;
            };
            // Element-wise check on input tuple
            return ((check_constraint.template operator()<Type_or_Trait, std::tuple_element_t<I, T>>()) && ...);
        }
        (std::make_index_sequence<sizeof...(Type_or_Trait)>{});

}

namespace comcept::trait
{
    /// Helper struct to enable composing the standard library type traits with this library
    template<template<typename...>typename TypeTrait, typename... Args>
    struct compose
    {
        template<typename T>
        static constexpr bool value = TypeTrait<T,Args...>::value;
    };

    /// Verify that a type fulfills all constraints expressed via composable traits
    template<typename... Traits>
    struct all_of 
    {
        template<typename T>
        static constexpr bool value = (comcept::satisfy<T,Traits> && ...);
    };

    /// Verify that a type fulfills any constraints expressed via composable traits
    template<typename... Traits>
    struct any_of 
    {
        template<typename T>
        static constexpr bool value = (comcept::satisfy<T,Traits> || ...);
    };

    /// Verify that a type does _not_ fulfill a constraint expressed via composable traits
    template<typename Trait>
    struct not_a 
    {
        template<typename T>
        static constexpr bool value = comcept::composable<T,Trait> && (Trait::template value<T> == false);
    };
    template<typename... Traits>
    struct none_of 
    {
        template<typename T>
        static constexpr bool value = (not_a<Traits>::template value<T> && ...);
    };

    /// Traitify the composable concept `range_of` to be reusable as an argument in a composable concept
    template<typename Type_or_Trait, template<class...> class E = std::ranges::range_value_t>
    struct range_of
    {
        template<typename R>
        static constexpr bool value = comcept::range_of<R, Type_or_Trait, E>;
    };

    /// Traitify the composable concept `decays_to` to be reusable as an argument in a composable concept
    template<typename Type_or_Trait>
    struct decays_to
    {
        template<typename T>
        static constexpr bool value = comcept::decays_to<T, Type_or_Trait>;
    };

    /// Traitify the composable concept `map_of` to be reusable as an argument in a composable concept
    template<typename Key, typename Value>
    struct map_of
    {
        template<typename T>
        static constexpr bool value = comcept::map_of<T, Key, Value>; 
    };

    /// Traitify the composable concept `set_of` to be reusable as an argument in a composable concept
    template<typename Key>
    struct set_of
    {
        template<typename T>
        static constexpr bool value = comcept::set_of<T, Key>; 
    };

    /// Traitify the composable concept `variant_of` to be reusable as an argument in a composable concept
    template<typename... Types>
    struct variant_of
    {
        template<typename T>
        static constexpr bool value = comcept::variant_of<T, Types...>;
    };

    /// Traitify the composable concept `cvref_of` to be reusable as an argument in a composable concept
    template<typename Type_or_Trait>
    struct cvref_of
    {
        template<typename T>
        static constexpr bool value = comcept::cvref_of<T, Type_or_Trait>;
    };
    template<typename Type_or_Trait>
    using qualified = cvref_of<Type_or_Trait>;
    
    /// Traitify the composable concept `unqualified` to be reusable as an argument in a composable concept
    template<typename Type_or_Trait>
    struct unqualified
    {
        template<typename T>
        static constexpr bool value = comcept::unqualified<T, Type_or_Trait>;
    };

    /// Traitify the composable concept `tuple_of` to be reusable as an argument in a composable concept
    template<typename... Type_or_Trait>
    struct tuple_of
    {
        template<typename T>
        static constexpr bool value = comcept::tuple_of<T, Type_or_Trait...>;
    };
}
