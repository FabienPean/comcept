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

static_assert(not comcept::map_of<std::vector<double>,double,double>);
static_assert(    comcept::map_of<std::map<int,double>,int,double>);
static_assert(    comcept::map_of<std::map<int,double>,trt::integral,trt::floating_point>);
static_assert(not comcept::map_of<std::map<int,int>,trt::floating_point,trt::floating_point>);
static_assert(    comcept::map_of<std::map<int,int>,trt::integral,int>);

static_assert(not trt::map_of<double,double>::value<std::vector<double>>);
static_assert(    trt::map_of<int,double>::value<std::map<int,double>>);
static_assert(    trt::map_of<trt::integral,trt::floating_point>::value<std::map<int,double>>);
static_assert(not trt::map_of<trt::floating_point,trt::floating_point>::value<std::map<int,int>>);
static_assert(    trt::map_of<trt::integral,int>::value<std::map<int,int>>);
