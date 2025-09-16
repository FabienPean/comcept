#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>

namespace trt = comcept::trait;

static_assert(true  == trt::all_of<trt::same_as<int>>::value<int>);
static_assert(true  == trt::all_of<trt::same_as<int>,trt::integral>::value<int>);
static_assert(false == trt::all_of<trt::same_as<int>,trt::integral>::value<float>);
static_assert(false == trt::all_of<trt::same_as<float>,trt::integral>::value<float>);
static_assert(true  == trt::all_of<trt::same_as<float>,trt::floating_point>::value<float>);
static_assert(true  == trt::all_of<trt::floating_point,trt::same_as<float>>::value<float>);
