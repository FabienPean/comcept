#pragma once

#include <concepts>
#include <ranges>

namespace comcept
{
    /// composable
    /// 
    /// Verify that a trait can be composed according to this library requirement
    template<typename Trait, typename Type>
    concept composable = std::same_as<decltype(Trait::template value<Type>), const bool>;

    /// satisfy
    /// 
    /// Verify that a type fulfills a constraint expressed via a composable trait, as defined by this library
    template<typename Trait, typename Type>
    concept satisfy = composable<Trait,Type> && (Trait::template value<Type>) == true;

    /// range_of
    /// 
    /// Composable concept to constrain on the content of a range
    template<class Range, class Type_or_Trait, template<class...>class Element = std::ranges::range_value_t>
    concept range_of = std::ranges::range<Range> && (std::same_as<Type_or_Trait,Element<Range>> || satisfy<Type_or_Trait,Element<Range>>);
}

namespace comcept::trait
{
    /// range_of
    /// 
    /// Traitify the composable concept `range_of` to be reused in composed constraints
    template<typename Type_or_Trait, template<class...> class E = std::ranges::range_value_t>
    struct range_of
    {
        template<typename R>
        static constexpr bool value = comcept::range_of<R, Type_or_Trait, E>;
    };
}
