#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>
#include <comcept/trait/type_traits.hpp>

namespace trt = comcept::trait;

static_assert(true  == trt::any_of<trt::same_as<int>>::value<int>);
static_assert(true  == trt::any_of<trt::same_as<int>,trt::floating_point>::value<int>);
static_assert(false == trt::any_of<trt::same_as<int>,trt::floating_point>::value<unsigned>);
static_assert(true  == trt::any_of<trt::same_as<float>,trt::integral>::value<float>);
static_assert(false == trt::any_of<trt::same_as<float>,trt::integral>::value<float*>);
static_assert(true  == trt::any_of<trt::is_scalar,trt::floating_point>::value<float*>);
static_assert(false == trt::any_of<trt::is_scalar,trt::floating_point>::value<std::array<double,3>>);
