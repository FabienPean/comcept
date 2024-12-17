#pragma once

#include <concepts>
#include <cstdint>
#include <ranges>
#include <tuple>
#include <utility>


namespace comcept
{
    template<class Range, class Type_or_Trait , template<class...>class Element = std::ranges::range_value_t>
    concept range_of = std::ranges::range<Range> && 
        (std::same_as<Type_or_Trait,Element<Range>> || Type_or_Trait::template value<Element<Range>>);


    template <typename T, std::size_t N>
    concept is_tuple_element = 
        requires(T t) {
            typename std::tuple_element_t<N, std::remove_const_t<T>>;
            { get<N>(t) } -> std::convertible_to<std::tuple_element_t<N, T>&>;
        };

    template <typename T>
    concept tuple_like =
        not std::is_reference_v<T> 
        and 
        requires
        {
            typename std::tuple_size<T>::type;
            requires std::same_as<decltype(std::tuple_size_v<T>), const std::size_t>;
        } 
        and 
        []<std::size_t... I>(std::index_sequence<I...>) { return (is_tuple_element<T, I> && ...); }(std::make_index_sequence<std::tuple_size_v<T>>{});

    template <typename T>
    concept pair_like = tuple_like<T> && std::tuple_size_v<T> == 2;

    template<typename T, typename Type_or_Trait, std::size_t S = std::tuple_size_v<T>>
    concept array_of = 
        comcept::tuple_like<T> 
        and
        S == std::tuple_size_v<T>
        and 
        (
            // Content of tuple-like is same as given type 
            []<std::size_t... I>(std::index_sequence<I...>) { return (std::same_as<Type_or_Trait,std::tuple_element_t<I,T>> &&...); }(std::make_index_sequence<S>{})
            or 
            // Verify that all elements satisfy the given constraint
            []<std::size_t... I>(std::index_sequence<I...>) { return (Type_or_Trait::template value<std::tuple_element_t<I,T>> &&...); }(std::make_index_sequence<S>{})
        );

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
                if constexpr (std::same_as<ToC,E>)
                    return true;
                else if constexpr(requires {ToC::template value<E>;})
                    return ToC::template value<E>;
                else
                    return false;
            };
            // Element-wise check on input tuple
            return ((check_constraint.template operator()<Type_or_Trait,std::tuple_element_t<I,T>>()) &&...);
        }(std::make_index_sequence<sizeof...(Type_or_Trait)>{});

    template <typename T>
    concept optional_like = requires(T t) {std::same_as<decltype(t.value()),typename std::remove_cvref_t<T>::value_type>;};

    template<typename T, typename Type_or_Trait>
    concept optional_of = optional_like<T> && (std::same_as<Type_or_Trait,typename std::remove_cvref_t<T>::value_type> || Type_or_Trait::template value<typename std::remove_cvref_t<T>::value_type>);
}

namespace comcept::trait
{
    struct anything                                    
    {                                              
        template<class T>                          
        static constexpr bool value = true;
    };

    template<std::size_t N>
    struct size                                    
    {                                              
        template<class T>                          
        static constexpr bool value = (std::tuple_size_v<T> == N);
    };

    template<typename Type_or_Trait, template<class...> class E = std::ranges::range_value_t>
    struct range_of
    {
        template<typename R>
        static constexpr bool value = comcept::range_of<R, Type_or_Trait, E>;
    };

    template<typename Type_or_Trait, int size = -1>
    struct array_of
    {
        template<typename T>
        static constexpr bool value = comcept::array_of<T, Type_or_Trait, (size<0 ? std::tuple_size_v<T> : std::size_t(size))>;
    };

    template<typename... Type_or_Trait>
    struct tuple_of
    {
        template<typename T>
        static constexpr bool value = comcept::tuple_of<T, Type_or_Trait...>;
    };
  
}
