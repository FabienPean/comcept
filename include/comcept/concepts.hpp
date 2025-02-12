#pragma once 

#include <concepts>

#include "details/macros.hpp"

namespace comcept::trait
{
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
    COMCEPT_TRAITIFY_1(equality_comparable);               
    COMCEPT_TRAITIFY_1(totally_ordered);        

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
}