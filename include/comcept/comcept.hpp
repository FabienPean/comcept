// SPDX-License-Identifier: MIT
#pragma once

#include <concepts>
#include <ranges>
#include <type_traits>

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
}
