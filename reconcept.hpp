#include <concepts>

// WIP implement all concepts as class https://en.cppreference.com/w/cpp/concepts
namespace rccpt
{
    template<class Type>
    struct same_as
    {
        template<class Source>
        static constexpr bool value = std::same_as<Source,Type>; 
    };

    template<class Base>
    struct derived_from 
    {
        template<class Derived>
        static constexpr bool value = std::derived_from<Derived,Base>; 
    };

    template<class To>
    struct convertible_to
    {
        template<class From>
        static constexpr bool value = std::convertible_to<From,To>; 
    };

    template<class T>
    struct common_reference_with
    {
        template<class U>
        static constexpr bool value = std::common_reference_with<T,U>; 
    };

    template<class T>
    struct common_with
    {
        template<class U>
        static constexpr bool value = std::common_with<T,U>; 
    };

    template<class RHS>
    struct assignable_from
    {
        template<class LHS>
        static constexpr bool value = std::assignable_from<LHS,RHS>; 
    };

    template<class T>
    struct swappable_with
    {
        template<class U>
        static constexpr bool value = std::swappable_with<T,U>; 
    };

    template<class... From>
    struct constructible_from 
    {
        template<class T>
        static constexpr bool value = std::constructible_from<T,From...>; 
    };

    template<class U>
    struct equality_comparable_with
    {
        template<class T>
        static constexpr bool value = std::equality_comparable_with<T,U>; 
    };

    template<class T>
    struct totally_ordered_with
    {
        template<class U>
        static constexpr bool value = std::totally_ordered_with<T,U>; 
    };

    template<class... Args>
    struct invocable 
    {
        template<class Func>
        static constexpr bool value = std::invocable<Func,Args...>; 
    };

    template<class... Args>
    struct regular_invocable 
    {
        template<class Func>
        static constexpr bool value = std::invocable<Func,Args...>; 
    };

    template<class... Args>
    struct predicate 
    {
        template<class Func>
        static constexpr bool value = std::predicate<Func,Args...>; 
    };

    struct integral
    {
        template<class T>
        static constexpr bool value = std::integral<T>;
    };
}

#include <ranges>

namespace rccpt
{
    // range_of<double>, range_of<filesystem::path>,range_of<filesystem::path>, range_of<convertible_to<filesystemm::path>>
    // range_of<filesystemm::path,convertible_to>
    // template<class R, class Constraint , template<class...>class Selector = std::ranges::range_value_t>
    // concept range_of = std::ranges::range<R> && (std::same_as<Constraint,Selector<R>> || Constraint::template value<Selector<R>>);

    template<class Range, class Type_or_Constraint , template<class...>class Element = std::ranges::range_value_t>
    concept range_of = std::ranges::range<Range> && 
        (std::same_as<Type_or_Constraint,Element<Range>> || Type_or_Constraint::template value<Element<Range>>);
}
