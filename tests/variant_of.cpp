#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>
#include <comcept/trait/type_traits.hpp>

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

namespace trt = comcept::trait;

static_assert(    comcept::variant_of<std::variant<double, int>,double>);
static_assert(    comcept::variant_of<std::variant<double, int>,double,int>);
static_assert(    comcept::variant_of<std::variant<double, int>,int>);
static_assert(    comcept::variant_of<std::variant<double, int>,trt::floating_point>);
static_assert(    comcept::variant_of<std::variant<double, int>,trt::integral>);
static_assert(    comcept::variant_of<std::variant<double, int>,trt::floating_point,int>);
static_assert(not comcept::variant_of<std::variant<double, int>,trt::is_class>);
static_assert(    comcept::variant_of<std::variant<double, int>,trt::is_fundamental>);
static_assert(    comcept::variant_of<std::variant<std::vector<double>>,trt::is_class>);
static_assert(    comcept::variant_of<std::variant<std::vector<double>,int>,trt::is_class>);
static_assert(    comcept::variant_of<std::variant<std::vector<double>,int>,trt::integral,trt::is_class>);

static_assert(    trt::variant_of<double>::value<std::variant<double, int>>);
static_assert(    trt::variant_of<int,double>::value<std::variant<double, int>>);
static_assert(    trt::variant_of<int>::value<std::variant<double, int>>);
static_assert(    trt::variant_of<trt::floating_point>::value<std::variant<double, int>>);
static_assert(    trt::variant_of<trt::integral>::value<std::variant<double, int>>);
static_assert(    trt::variant_of<trt::floating_point,int>::value<std::variant<double, int>>);
static_assert(not trt::variant_of<trt::is_class>::value<std::variant<double, int>>);
static_assert(    trt::variant_of<trt::is_fundamental>::value<std::variant<double, int>>);
static_assert(    trt::variant_of<trt::is_class>::value<std::variant<std::vector<double>>>);
static_assert(    trt::variant_of<trt::is_class>::value<std::variant<std::vector<double>,int>>);
static_assert(    trt::variant_of<trt::integral,trt::is_class>::value<std::variant<std::vector<double>,int>>);