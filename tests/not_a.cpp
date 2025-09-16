#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>
#include <comcept/trait/type_traits.hpp>

namespace trt = comcept::trait;

static_assert(true  == trt::not_a<trt::same_as<float>>::value<int>);
static_assert(false == trt::not_a<trt::same_as<float>>::value<float>);
static_assert(false == trt::not_a<trt::floating_point>::value<float>);
static_assert(true  == trt::not_a<trt::floating_point>::value<int>);

static_assert(true  == trt::none_of<trt::same_as<float>, trt::floating_point>::value<int>);
static_assert(false == trt::none_of<trt::same_as<float>, trt::floating_point>::value<float>);
static_assert(false == trt::none_of<trt::floating_point, trt::integral>::value<float>);
static_assert(true  == trt::none_of<trt::integral, trt::same_as<double>>::value<float>);
