// SPDX-License-Identifier: MIT
#pragma once

#include <concepts>
#include <ranges>
#include <type_traits>

namespace comcept
{
    /// Defines the core requirement that a type must fulfill to be used as argument in a composable concept
    /// Note that it is not possible to verify the existence of a template,
    /// hence the need for a specific type _Type_ template argument.
    template<typename Trait, typename Type>
    concept composable = std::same_as<decltype(Trait::template value<Type>), const bool>;

    /// Verify that a type fulfills a constraint expressed via a composable trait, as defined by this library
    template<typename Type, typename Trait>
    concept satisfy = composable<Trait,Type> && (Trait::template value<Type> == true);

    /// Composable concept to constrain on the content of a range
    template<class Range, class Type_or_Trait, template<class...>class Element = std::ranges::range_value_t>
    concept range_of = std::ranges::range<Range> && (std::same_as<Type_or_Trait,Element<Range>> || satisfy<Element<Range>,Type_or_Trait>);

    /// Composable concept to constrain the end result of a call to `std::decay_t`
    template<typename T, typename Type_or_Trait>
    concept decays_to = std::same_as<Type_or_Trait,std::decay_t<T>> ||  satisfy<std::decay_t<T>,Type_or_Trait>;
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
}
