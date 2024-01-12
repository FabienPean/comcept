#include <concepts>

// WIP implement all concepts as class https://en.cppreference.com/w/cpp/concepts
namespace reconcept
{
    template<class Type>
    class same_as 
    {
        template<class Source>
        static constexpr bool value = std::same_as<Source,Type>; 
    };

    template<class Base>
    class derived_from 
    {
        template<class Derived>
        static constexpr bool value = std::derived_from<Derived,Base>; 
    };

    template<class To>
    class convertible_to
    {
        template<class From>
        static constexpr bool value = std::convertible_to<From,To>; 
    };

    template<class T>
    class common_reference_with
    {
        template<class U>
        static constexpr bool value = std::common_reference_with<T,U>; 
    };

    template<class T>
    class common_with
    {
        template<class U>
        static constexpr bool value = std::common_with<T,U>; 
    };

    template<class LHS>
    class assignable_from
    {
        template<class RHS>
        static constexpr bool value = std::assignable_from<LHS,RHS>; 
    };

    template<class T>
    class swappable_with
    {
        template<class U>
        static constexpr bool value = std::swappable_with<T,U>; 
    };

    template<class... From>
    class constructible_from 
    {
        template<class T>
        static constexpr bool value = std::constructible_from<T,From...>; 
    };

    template<class T>
    class equality_comparable_with
    {
        template<class U>
        static constexpr bool value = std::equality_comparable_with<T,U>; 
    };

    template<class T>
    class totally_ordered_with
    {
        template<class U>
        static constexpr bool value = std::totally_ordered_with<T,U>; 
    };

    template<class... Args>
    class invocable 
    {
        template<class Func>
        static constexpr bool value = std::invocable<Func,Args...>; 
    };

    template<class... Args>
    class regular_invocable 
    {
        template<class Func>
        static constexpr bool value = std::invocable<Func,Args...>; 
    };

    template<class... Args>
    class predicate 
    {
        template<class Func>
        static constexpr bool value = std::predicate<Func,Args...>; 
    };
}