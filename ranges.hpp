#pragma once

#include <ranges>

namespace ttfy
{
    #define RCCPT_X_1(name)                                 \
        struct name                                         \
        {                                                   \
            template<class T>                               \
            static constexpr bool value = std::name<T>;     \
        }

    RCCPT_X_1(range);
    RCCPT_X_1(borrowed_range);
    RCCPT_X_1(sized_range);
    RCCPT_X_1(view);
    RCCPT_X_1(input_range);
    RCCPT_X_1(output_range);
    RCCPT_X_1(forward_range);
    RCCPT_X_1(bidirectional_range);
    RCCPT_X_1(random_access_range);
    RCCPT_X_1(random_access_range);
    RCCPT_X_1(random_access_range);
    RCCPT_X_1(contiguous_range);
    RCCPT_X_1(common_range);
    RCCPT_X_1(viewable_range);
    RCCPT_X_1(constant_range);

    #undef RCCPT_X_1
}