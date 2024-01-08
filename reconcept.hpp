#include <concepts>

// WIP implement all concepts as class https://en.cppreference.com/w/cpp/concepts
namespace reconcept
{
    template<class Type>
    class same_as 
    {
        template<class Source>
        inline static constexpr bool value = std::same_as<Source,Type>; 
    };

    template<class Base>
    class derived_from 
    {
        template<class Derived>
        inline static constexpr bool value = std::derived_from<Derived,Base>; 
    };

    template<class To>
    class convertible_to
    {
        template<class From>
        inline static constexpr bool value = std::convertible_to<From,To>; 
    };
}