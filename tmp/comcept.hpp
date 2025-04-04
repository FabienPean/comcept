#include <concepts>
#include <compare>

namespace ttfy
{
    #define COMCEPT_TRAITIFY_N(name)                                     \
        template<class... Args>                                 \
        struct name                                             \
        {                                                       \
            template<class T>                                   \
            static constexpr bool value = std::name<T,Args...>; \
        }

    #define COMCEPT_TRAITIFY_3(name)                                 \
        template<class U, class V>                          \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T,U,V>; \
        }  

    #define COMCEPT_TRAITIFY_2(name)                                 \
        template<class U>                                   \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T,U>;   \
        }                                                 

    #define COMCEPT_TRAITIFY_1(name)                                 \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T>;     \
        }

    // https://en.cppreference.com/w/cpp/concepts#Core_language_concepts
    COMCEPT_TRAITIFY_2(same_as);                
    COMCEPT_TRAITIFY_2(derived_from);            
    COMCEPT_TRAITIFY_2(convertible_to);       
    COMCEPT_TRAITIFY_2(common_reference_with);
    COMCEPT_TRAITIFY_2(common_with);  
    COMCEPT_TRAITIFY_2(assignable_from);
    COMCEPT_TRAITIFY_2(swappable_with);    
    COMCEPT_TRAITIFY_N(constructible_from);
    COMCEPT_TRAITIFY_1(integral);
    COMCEPT_TRAITIFY_1(signed_integral);
    COMCEPT_TRAITIFY_1(unsigned_integral);
    COMCEPT_TRAITIFY_1(floating_point);
    COMCEPT_TRAITIFY_1(swappable);
    COMCEPT_TRAITIFY_1(destructible);
    COMCEPT_TRAITIFY_1(default_initializable);
    COMCEPT_TRAITIFY_1(move_constructible);
    COMCEPT_TRAITIFY_1(copy_constructible);

    // https://en.cppreference.com/w/cpp/concepts#Comparison_concepts
    COMCEPT_TRAITIFY_2(equality_comparable_with);
    COMCEPT_TRAITIFY_2(totally_ordered_with);        
    COMCEPT_TRAITIFY_2(three_way_comparable_with);
    COMCEPT_TRAITIFY_1(equality_comparable);               
    COMCEPT_TRAITIFY_1(totally_ordered);        
    COMCEPT_TRAITIFY_1(three_way_comparable);

    // https://en.cppreference.com/w/cpp/concepts#Object_concepts
    COMCEPT_TRAITIFY_1(movable);   
    COMCEPT_TRAITIFY_1(copyable);
    COMCEPT_TRAITIFY_1(semiregular);
    COMCEPT_TRAITIFY_1(regular);

    // https://en.cppreference.com/w/cpp/concepts#Callable_concepts
    COMCEPT_TRAITIFY_N(invocable);
    COMCEPT_TRAITIFY_N(regular_invocable);
    COMCEPT_TRAITIFY_N(predicate);
    COMCEPT_TRAITIFY_3(relation);
    COMCEPT_TRAITIFY_3(equivalence_relation);
    COMCEPT_TRAITIFY_3(strict_weak_order);

    #undef COMCEPT_TRAITIFY_N
    #undef COMCEPT_TRAITIFY_3
    #undef COMCEPT_TRAITIFY_2
    #undef COMCEPT_TRAITIFY_1


}

#include <ranges>

namespace comcept
{
    /// compose
    /// 
    /// Helper struct to enable composing the standard library type traits with this library
    template<template<typename...>typename TypeTrait, typename... Args>
    struct compose
    {
        template<typename T>
        static constexpr bool value = TypeTrait<T,Args...>::value;
    };
    
    /// composable
    /// 
    /// Verify that a trait can be composed according to this library requirement
    template<typename T, typename U>
    concept composable = std::same_as<decltype(T::template value<U>), bool>;

    /// has_tuple_element
    /// 
    /// Concept to check if element N exists and returns expected type from tuple T
    template <typename T, std::size_t N>
    concept has_tuple_element = 
        requires(T t) {
            typename std::tuple_element_t<N, std::remove_cvref_t<T>>;
            { get<N>(t) } -> std::convertible_to<std::tuple_element_t<N, std::remove_cvref_t<T>>&>;
        };

    /// tuple_like
    /// pair_like
    /// 
    /// Concept checking that a type implements the _tuple protocol_
    template <typename T>
    concept tuple_like =
        requires
        {
            typename std::tuple_size<std::remove_cvref_t<T>>::type;
            requires std::same_as<decltype(std::tuple_size_v<std::remove_cvref_t<T>>), const std::size_t>;
        } 
        and 
        []<std::size_t... I>(std::index_sequence<I...>) { return (has_tuple_element<std::remove_cvref_t<T>, I> && ...); }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>{});

    template <typename T>
    concept pair_like = tuple_like<T> && std::tuple_size_v<T> == 2;


    template<typename T, std::size_t N>
    concept size = tuple_like<T> && std::tuple_size_v<T> == N;

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

    template<typename T, typename Type_or_Trait, std::size_t S = 0>
    concept array_of = 
        comcept::tuple_like<T> 
        and
        (S==0 || S == std::tuple_size_v<T>)
        and 
        (
            // Content of tuple-like is same as given type 
            []<std::size_t... I>(std::index_sequence<I...>) { return (std::same_as<Type_or_Trait,std::tuple_element_t<I,T>> &&...); }(std::make_index_sequence<std::tuple_size_v<T>>{})
            or 
            // Verify that all elements satisfy the given constraint
            []<std::size_t... I>(std::index_sequence<I...>) { return (Type_or_Trait::template value<std::tuple_element_t<I,T>> &&...); }(std::make_index_sequence<std::tuple_size_v<T>>{})
        );

    template<class Range, class Type_or_Trait, template<class...>class Element = std::ranges::range_value_t>
    concept range_of = std::ranges::range<Range> && (std::same_as<Type_or_Trait,Element<Range>> || Type_or_Trait::template value<Element<Range>>);

    template <typename T>
    concept optional_like = requires(T t) {requires std::same_as<std::remove_cvref_t<decltype(t.value())>,typename std::remove_cvref_t<T>::value_type>;};

    template<typename T, typename Type_or_Trait>
    concept optional_of = optional_like<T> && (std::same_as<Type_or_Trait,typename std::remove_cvref_t<T>::value_type> || Type_or_Trait::template value<typename std::remove_cvref_t<T>::value_type>);

    template<typename T, typename Type_or_Trait>
    concept decays_to = std::same_as<Type_or_Trait,std::decay_t<T>> || Type_or_Trait::template value<std::decay_t<T>>;
}

#include <tuple>

namespace ttfy
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
        static constexpr bool value = comcept::size<T,N>;
    };

    template<typename... Args>
    struct And
    {
        template<typename T>
        static constexpr bool value = (Args::template value<T> &&...);
    };

    template<typename... Args>
    struct Or
    {
        template<typename T>
        static constexpr bool value = (Args::template value<T> ||...);
    };

    template<typename Type_or_Trait, template<class...> class E = std::ranges::range_value_t>
    struct range_of
    {
        template<typename R>
        static constexpr bool value = comcept::range_of<R, Type_or_Trait, E>;
    };

    template<typename Type_or_Trait, int size = 0>
    struct array_of
    {
        template<typename T>
        static constexpr bool value = comcept::array_of<T, Type_or_Trait, size>;
    };

    template<typename... Type_or_Trait>
    struct tuple_of
    {
        template<typename T>
        static constexpr bool value = comcept::tuple_of<T, Type_or_Trait...>;
    };
  
}
