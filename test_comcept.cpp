// g++ -std=c++20 test_comcept.cpp 

#include "comcept.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <variant>

auto print(auto&& e)
{
    std::cout<<std::to_string(e)<<"\n";
}

auto print(std::ranges::range auto&& R)
{
    for(auto&& element : R)
        print(element);
}

/// This overload conflicts with 
/// auto foo(comcept::array_of<ttfy::range_of<ttfy::Or<ttfy::integral,ttfy::floating_point>>> auto&& t);
/// because array_of does not subsume range
// auto foo(std::ranges::range auto&& R) 
// {
//     for(auto&& element : R)
//         print(element);
// }

auto foo(comcept::range_of<ttfy::integral> auto&& R)
{
    for(auto&& element : R)
        print(element);
}

/// The following two `foo` overload are ambiguous overload with std::array
/// `std::array` is both a range and a tuple, but each constraint form a disjoint set
// auto foo(comcept::range_of<ttfy::range_of<ttfy::integral>> auto&& R)
// {
//     for(auto&& element : R)
//         print(element);
// }
// auto foo(comcept::array_of<ttfy::range_of<ttfy::Or<ttfy::integral,ttfy::floating_point>>> auto&& t)
// {
//     std::apply([](auto const& ...e) { (print(e), ...); }, t);
// }

auto foo(comcept::range_of<ttfy::range_of<ttfy::range_of<ttfy::integral>>> auto&& R)
{
    for(auto&& element : R)
        print(element);
}

auto foo(comcept::array_of<ttfy::range_of<ttfy::Or<ttfy::integral,ttfy::floating_point>>> auto&& t)
{
    std::apply([](auto const& ...e) { (print(e), ...); }, t);
}

static_assert(    comcept::range_of<std::vector<double>,comcept::compose<std::is_floating_point>>);
static_assert(not comcept::range_of<std::tuple<double> ,comcept::compose<std::is_floating_point>>);


static_assert(not comcept::tuple_like<std::vector<double>>);
static_assert(    comcept::tuple_like<std::tuple<double>>);
static_assert(    comcept::tuple_like<std::array<double,2>>);

static_assert(    comcept::array_of<std::tuple<double>       ,ttfy::floating_point  >);
static_assert(    comcept::array_of<std::tuple<double,double>,ttfy::floating_point  >);
static_assert(not comcept::array_of<std::tuple<double,double>,ttfy::floating_point,1>);
static_assert(    comcept::array_of<std::tuple<double,double>,ttfy::floating_point,2>);
static_assert(not comcept::array_of<std::tuple<double,double>,ttfy::floating_point,3>);
static_assert(not comcept::array_of<std::vector<double>,ttfy::floating_point,3>);
static_assert(not comcept::array_of<std::vector<double>,ttfy::floating_point>);



static_assert(    comcept::tuple_of<std::tuple<double>,double        >);
static_assert(    comcept::tuple_of<std::tuple<double>,double        >);
static_assert(not comcept::tuple_of<std::tuple<double>,double,double >);
static_assert(not comcept::tuple_of<std::tuple<double>,ttfy::integral>);

static_assert(not comcept::tuple_of<std::tuple<double, int>,double,double>);
static_assert(    comcept::tuple_of<std::tuple<double, int>,double,int>);
static_assert(    comcept::tuple_of<std::tuple<double, int>,double,ttfy::integral>);
static_assert(    comcept::tuple_of<std::tuple<double, int>,ttfy::floating_point,ttfy::integral>);
static_assert(not comcept::tuple_of<std::tuple<double, int>,ttfy::integral,ttfy::floating_point>);

static_assert(    comcept::optional_of<std::optional<double>,ttfy::floating_point>);
static_assert(not comcept::optional_of<std::optional<int>   ,ttfy::floating_point>);
static_assert(not comcept::optional_of<std::variant<int>    ,ttfy::floating_point>);


int main()
{
    foo(std::array{1,2,3});
    foo(std::array{1UL,2UL,3UL});
    foo(std::array{std::array{11UL,21UL,31UL},std::array{12UL,22UL,32UL}});
    foo(std::array{std::array{std::array{11,21,31}},std::array{std::array{12,22,32}}});
    foo(std::tuple{std::array{11UL,21UL,31UL},std::array{12.,22.,32.}});

    return 0;
}