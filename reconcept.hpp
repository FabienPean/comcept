#include <concepts>
#include <compare>

namespace rccpt
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

namespace rccpt
{
    template<class Range, class Type_or_Trait , template<class...>class Element = std::ranges::range_value_t>
    concept range_of = std::ranges::range<Range> && 
        (std::same_as<Type_or_Trait,Element<Range>> || Type_or_Trait::template value<Element<Range>>);
}
