// SPDX-License-Identifier: MIT
#pragma once

#include <compare>

#include <comcept/detail/macros.hpp>

namespace comcept::trait
{
    // https://en.cppreference.com/w/cpp/header/compare#Concepts
    COMCEPT_TRAITIFY_1(three_way_comparable);
    COMCEPT_TRAITIFY_2(three_way_comparable_with);
}