// SPDX-License-Identifier: MIT
#pragma once

#include <ranges>
#include <version>

#include <comcept/detail/macros.hpp>

namespace comcept::trait
{
    // https://en.cppreference.com/w/cpp/ranges#Range_concepts
    COMCEPT_TRAITIFY_1(range);
    COMCEPT_TRAITIFY_1(borrowed_range);
    COMCEPT_TRAITIFY_1(sized_range);
    COMCEPT_TRAITIFY_1(view);
    COMCEPT_TRAITIFY_1(input_range);
    COMCEPT_TRAITIFY_1(output_range);
    COMCEPT_TRAITIFY_1(forward_range);
    COMCEPT_TRAITIFY_1(bidirectional_range);
    COMCEPT_TRAITIFY_1(random_access_range);
    COMCEPT_TRAITIFY_1(random_access_range);
    COMCEPT_TRAITIFY_1(random_access_range);
    COMCEPT_TRAITIFY_1(contiguous_range);
    COMCEPT_TRAITIFY_1(common_range);
    COMCEPT_TRAITIFY_1(viewable_range);
#ifdef __cpp_lib_ranges_as_const
    COMCEPT_TRAITIFY_1(constant_range);
#endif
}