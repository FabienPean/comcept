#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>

#include <doctest/doctest.h>

#include <iostream>
#include <vector>
#include <array>

using namespace std::string_literals;
namespace trt = comcept::trait;


///====================================================================================================================
/// Compile-time
///====================================================================================================================

// concept satisfaction
static_assert(    comcept::range_of<std::vector<double>,double>);
static_assert(    comcept::range_of<std::vector<double>,comcept::trait::floating_point>);
static_assert(not comcept::range_of<std::vector<double>,comcept::trait::integral>);

static_assert(not comcept::range_of<std::vector<double>,double&>);
static_assert(    comcept::range_of<std::vector<double>,double&, std::ranges::range_reference_t>);

///====================================================================================================================
/// Run-time
///====================================================================================================================

// overload resolution
constexpr auto overload(comcept::range_of<trt::integral> auto&& R)
{
    return 11;
}
constexpr auto overload(comcept::range_of<trt::range_of<trt::integral>> auto&& R)
{
    return 101;
}

constexpr auto sum(comcept::range_of<comcept::trait::integral> auto&& range)
{
    std::ranges::range_value_t<decltype(range)> total = {};
    for(auto&& element : range)
        total += element;
    return total; 
}

constexpr auto sum(comcept::range_of<comcept::trait::floating_point> auto&& range)
{
    std::ranges::range_value_t<decltype(range)> total = {};
    for(auto&& element : range)
        total += element;
    return total; 
}

TEST_CASE("Testing composable concept `range_of`")
{
    CHECK( 11 == overload(std::array{1,2}));
    CHECK( 11 == overload(std::vector{1,2}));
    CHECK(101 == overload(std::array{std::array{1,2},std::array{2,3}}));
    CHECK(101 == overload(std::array{std::vector{1,2},std::vector{2,3}}));
    CHECK(sum(std::array{1,2,3}) == 6);
    CHECK(sum(std::array{-1.,1.,2.}) == 2.);
}
