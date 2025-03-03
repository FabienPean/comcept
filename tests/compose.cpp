#include <comcept/comcept.hpp>
#include <type_traits>

namespace trt = comcept::trait;

static_assert(    trt::compose<std::is_integral>::value<int>);
static_assert(not trt::compose<std::is_integral>::value<float>);

static_assert(    comcept::satisfy<  int,trt::compose<std::is_integral>>);
static_assert(not comcept::satisfy<float,trt::compose<std::is_integral>>);
