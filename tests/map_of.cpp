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
