#pragma once

#include <iterator>

#include "details/macros.hpp"

namespace comcept::trait
{
    COMCEPT_TRAITIFY_1(indirectly_readable);
    COMCEPT_TRAITIFY_1(indirectly_writable);
    COMCEPT_TRAITIFY_1(weakly_incrementable);
    COMCEPT_TRAITIFY_1(incrementable);
    COMCEPT_TRAITIFY_1(input_or_output_iterator);
    COMCEPT_TRAITIFY_2(sentinel_for);
    COMCEPT_TRAITIFY_2(sized_sentinel_for);
    COMCEPT_TRAITIFY_2(disable_sized_sentinel_for);
    COMCEPT_TRAITIFY_1(input_iterator);
    COMCEPT_TRAITIFY_1(output_iterator);
    COMCEPT_TRAITIFY_1(forward_iterator);
    COMCEPT_TRAITIFY_1(bidirectional_iterator);
    COMCEPT_TRAITIFY_1(random_access_iterator);
    COMCEPT_TRAITIFY_1(contiguous_iterator);
}

