#include <comcept/comcept.hpp>
#include <comcept/concepts.hpp>
#include <iostream>
#include <vector>
#include <array>

using namespace std::string_literals;
namespace trt = comcept::trait;

///====================================================================================================================
/// Compile-time
///====================================================================================================================

// concept satisfaction
static_assert(    comcept::decays_to<double[5],double*>);
static_assert(    comcept::decays_to<double&&,double>);
static_assert(    comcept::decays_to<double&,double>);
static_assert(    comcept::decays_to<const double&,double>);
static_assert(    comcept::decays_to<const double[5][3], const double(*)[3]>);
static_assert(    comcept::decays_to<const double[5], const double*>);
// concept composition
static_assert(    comcept::decays_to<const double[5], trt::same_as<const double*>>);
static_assert(    comcept::decays_to<double[5],trt::same_as<double*>>);
static_assert(    comcept::decays_to<double&&,trt::same_as<double>>);
static_assert(    comcept::decays_to<double&,trt::same_as<double>>);
static_assert(    comcept::decays_to<const double&,trt::same_as<double>>);
static_assert(    comcept::decays_to<const double[5][3], trt::same_as<const double(*)[3]>>);
// end to end example
static_assert(not comcept::decays_to<int,float>);
static_assert(not comcept::decays_to<int,trt::same_as<float>>);
static_assert(not comcept::decays_to<int,trt::floating_point>);
static_assert(    comcept::decays_to<int,trt::convertible_to<float>>);
