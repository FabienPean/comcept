#pragma once 

#include <concepts>

#include "details/macros.hpp"

namespace comcept::trait
{
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
    COMCEPT_X_1(equality_comparable);               
    COMCEPT_X_1(totally_ordered);        

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
}