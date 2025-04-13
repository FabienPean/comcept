#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>

using namespace std::string_literals;

namespace trt = comcept::trait;

///====================================================================================================================
/// Compile-time
///====================================================================================================================

static_assert(    comcept::set_of<std::set<double>,double>);
static_assert(    comcept::set_of<std::set<double>,trt::floating_point>);
static_assert(not comcept::set_of<std::set<double>,trt::integral>);
static_assert(    comcept::set_of<std::set<int>,int>);
static_assert(    comcept::set_of<std::set<int>,trt::integral>);
static_assert(not comcept::set_of<std::set<int>,trt::floating_point>);

static_assert(    trt::set_of<double>::value<std::set<double>>);
static_assert(    trt::set_of<trt::floating_point>::value<std::set<double>>);
static_assert(not trt::set_of<trt::integral>::value<std::set<double>>);
static_assert(    trt::set_of<int>::value<std::set<int>>);
static_assert(    trt::set_of<trt::integral>::value<std::set<int>>);
static_assert(not trt::set_of<trt::floating_point>::value<std::set<int>>);
