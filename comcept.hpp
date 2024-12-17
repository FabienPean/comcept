#include <concepts>
#include <compare>

namespace ttfy
{
    #define COMCEPT_X_N(name)                                     \
        template<class... Args>                                 \
        struct name                                             \
        {                                                       \
            template<class T>                                   \
            static constexpr bool value = std::name<T,Args...>; \
        }

    #define COMCEPT_X_3(name)                                 \
        template<class U, class V>                          \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T,U,V>; \
        }  

    #define COMCEPT_X_2(name)                                 \
        template<class U>                                   \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T,U>;   \
        }                                                 

    #define COMCEPT_X_1(name)                                 \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T>;     \
        }

    // https://en.cppreference.com/w/cpp/concepts#Core_language_concepts
    COMCEPT_X_2(same_as);                
    COMCEPT_X_2(derived_from);            
    COMCEPT_X_2(convertible_to);       
    COMCEPT_X_2(common_reference_with);
    COMCEPT_X_2(common_with);  
    COMCEPT_X_2(assignable_from);
    COMCEPT_X_2(swappable_with);    
    COMCEPT_X_N(constructible_from);
    COMCEPT_X_1(integral);
    COMCEPT_X_1(signed_integral);
    COMCEPT_X_1(unsigned_integral);
    COMCEPT_X_1(floating_point);
    COMCEPT_X_1(swappable);
    COMCEPT_X_1(destructible);
    COMCEPT_X_1(default_initializable);
    COMCEPT_X_1(move_constructible);
    COMCEPT_X_1(copy_constructible);

    // https://en.cppreference.com/w/cpp/concepts#Comparison_concepts
    COMCEPT_X_2(equality_comparable_with);
    COMCEPT_X_2(totally_ordered_with);        
    COMCEPT_X_2(three_way_comparable_with);
    COMCEPT_X_1(equality_comparable);               
    COMCEPT_X_1(totally_ordered);        
    COMCEPT_X_1(three_way_comparable);

    // https://en.cppreference.com/w/cpp/concepts#Object_concepts
    COMCEPT_X_1(movable);   
    COMCEPT_X_1(copyable);
    COMCEPT_X_1(semiregular);
    COMCEPT_X_1(regular);

    // https://en.cppreference.com/w/cpp/concepts#Callable_concepts
    COMCEPT_X_N(invocable);
    COMCEPT_X_N(regular_invocable);
    COMCEPT_X_N(predicate);
    COMCEPT_X_3(relation);
    COMCEPT_X_3(equivalence_relation);
    COMCEPT_X_3(strict_weak_order);

    #undef COMCEPT_X_N
    #undef COMCEPT_X_3
    #undef COMCEPT_X_2
    #undef COMCEPT_X_1


}

#include <ranges>

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
