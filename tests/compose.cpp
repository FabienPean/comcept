#include <comcept/comcept.hpp>
#include <type_traits>

///====================================================================================================================
/// Compile-time
///====================================================================================================================

static_assert(    comcept::compose<std::is_integral>::value<int>);
static_assert(not comcept::compose<std::is_integral>::value<float>);

static_assert(    comcept::satisfy<  int,comcept::compose<std::is_integral>>);
static_assert(not comcept::satisfy<float,comcept::compose<std::is_integral>>);
