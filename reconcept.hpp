#include <concepts>
#include <compare>

namespace ttfy
{
    #define RCCPT_X_N(name)                                     \
        template<class... Args>                                 \
        struct name                                             \
        {                                                       \
            template<class T>                                   \
            static constexpr bool value = std::name<T,Args...>; \
        }

    #define RCCPT_X_3(name)                                 \
        template<class U, class V>                          \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T,U,V>; \
        }  

    #define RCCPT_X_2(name)                                 \
        template<class U>                                   \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T,U>;   \
        }                                                 

    #define RCCPT_X_1(name)                                 \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T>;     \
        }

    // https://en.cppreference.com/w/cpp/concepts#Core_language_concepts
    RCCPT_X_2(same_as);                
    RCCPT_X_2(derived_from);            
    RCCPT_X_2(convertible_to);       
    RCCPT_X_2(common_reference_with);
    RCCPT_X_2(common_with);  
    RCCPT_X_2(assignable_from);
    RCCPT_X_2(swappable_with);    
    RCCPT_X_N(constructible_from);
    RCCPT_X_1(integral);
    RCCPT_X_1(signed_integral);
    RCCPT_X_1(unsigned_integral);
    RCCPT_X_1(floating_point);
    RCCPT_X_1(swappable);
    RCCPT_X_1(destructible);
    RCCPT_X_1(default_initializable);
    RCCPT_X_1(move_constructible);
    RCCPT_X_1(copy_constructible);

    // https://en.cppreference.com/w/cpp/concepts#Comparison_concepts
    RCCPT_X_2(equality_comparable_with);
    RCCPT_X_2(totally_ordered_with);        
    RCCPT_X_2(three_way_comparable_with);
    RCCPT_X_1(equality_comparable);               
    RCCPT_X_1(totally_ordered);        
    RCCPT_X_1(three_way_comparable);

    // https://en.cppreference.com/w/cpp/concepts#Object_concepts
    RCCPT_X_1(movable);   
    RCCPT_X_1(copyable);
    RCCPT_X_1(semiregular);
    RCCPT_X_1(regular);

    // https://en.cppreference.com/w/cpp/concepts#Callable_concepts
    RCCPT_X_N(invocable);
    RCCPT_X_N(regular_invocable);
    RCCPT_X_N(predicate);
    RCCPT_X_3(relation);
    RCCPT_X_3(equivalence_relation);
    RCCPT_X_3(strict_weak_order);

    #undef RCCPT_X_N
    #undef RCCPT_X_3
    #undef RCCPT_X_2
    #undef RCCPT_X_1


}

#include <ranges>

namespace ccpt
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
        ccpt::tuple_like<T> 
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
        ccpt::tuple_like<T>
        and
        std::tuple_size_v<T> == sizeof...(Type_or_Trait)
        and 
        // IIFE to input index sequence
        []<std::size_t... I>(std::index_sequence<I...>) 
        {
            // Element-wise check on input tuple
            constexpr auto check_constraint = []<typename ToC, typename E>() 
            {
                if constexpr (std::same_as<ToC,E>)
                    return true;
                else
                    return ToC::template value<E>;
            };
            return ((check_constraint.template operator()<Type_or_Trait,std::tuple_element_t<I,T>>()) &&...);
        }(std::make_index_sequence<sizeof...(Type_or_Trait)>{});
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
        static constexpr bool value = (std::tuple_size_v<T> == N);
    };

    template<typename Type_or_Trait, template<class...> class E = std::ranges::range_value_t>
    struct range_of
    {
        template<typename R>
        static constexpr bool value = ccpt::range_of<R, Type_or_Trait, E>;
    };

    template<typename Type_or_Trait, int size = -1>
    struct array_of
    {
        template<typename T>
        static constexpr bool value = ccpt::array_of<T, Type_or_Trait, (size<0 ? std::tuple_size_v<T> : std::size_t(size))>;
    };

    template<typename... Type_or_Trait>
    struct tuple_of
    {
        template<typename T>
        static constexpr bool value = ccpt::tuple_of<T, Type_or_Trait...>;
    };
  
}
