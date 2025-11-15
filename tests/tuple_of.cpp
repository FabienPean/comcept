#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <complex>
#include <tuple>
#include <variant>

namespace cpt = comcept;
namespace trt = comcept::trait;

static_assert(cpt::tuple_like<std::tuple<double, int>>);
static_assert(cpt::tuple_like<std::pair<double, int>>);
static_assert(cpt::tuple_like<std::array<double, 2>>);
#if defined __cpp_lib_tuple_like
static_assert(comcept::tuple_like<std::complex<double>>);
#endif

static_assert(not cpt::tuple_of<std::tuple<double, int>,double,double>);
static_assert(    cpt::tuple_of<std::tuple<double, int>,double,int>);
static_assert(    cpt::tuple_of<std::tuple<double, int>,double,trt::integral>);
static_assert(    cpt::tuple_of<std::tuple<double, int>,trt::floating_point,trt::integral>);
static_assert(not cpt::tuple_of<std::tuple<double, int>,trt::integral,trt::floating_point>);
static_assert(not cpt::tuple_of<std::tuple<double, int>,trt::integral,trt::floating_point>);
static_assert(    cpt::tuple_of<std::pair<double, int>,double,int>);
static_assert(    cpt::tuple_of<std::array<double, 2>,double,double>);
#if defined __cpp_lib_tuple_like
static_assert(    cpt::tuple_of<std::complex<double>,double,double>);
#endif