// g++-11 -std=c++20 test_reconcept.cpp 

#include "reconcept.hpp"

#include <iostream>
#include <array>
#include <vector>

auto print(auto e)
{
    std::cout<<std::to_string(e)<<"\n";
}

auto print(std::ranges::range auto R)
{
    for(auto&& element : R)
        print(element);
}

auto foo(ccpt::range_of<ttfy::integral> auto R)
{
    for(auto&& element : R)
    std::cout<<std::to_string(element)<<"\n";
}

auto foo(ccpt::range_of<ttfy::range_of<ttfy::integral>> auto R)
{
    for(auto&& element : R)
        print(element);
}

auto foo(ccpt::range_of<ttfy::range_of<ttfy::range_of<ttfy::integral>>> auto R)
{
    for(auto&& element : R)
        print(element);
}

static_assert(not ccpt::tuple_like<std::vector<double>>);
static_assert(    ccpt::tuple_like<std::tuple<double>>);
static_assert(    ccpt::tuple_like<std::array<double,2>>);

static_assert(ccpt::array_of<std::tuple<double>,ttfy::floating_point>);
static_assert(ccpt::array_of<std::tuple<double,double>,ttfy::floating_point>);
static_assert(not ccpt::array_of<std::tuple<double,double>,ttfy::floating_point,1>);
static_assert(    ccpt::array_of<std::tuple<double,double>,ttfy::floating_point,2>);
static_assert(not ccpt::array_of<std::tuple<double,double>,ttfy::floating_point,3>);

static_assert(    ccpt::tuple_of<std::tuple<double>,double>);
static_assert(    ccpt::tuple_of<std::tuple<double>,double>);
static_assert(not ccpt::tuple_of<std::tuple<double>,ttfy::integral>);



int main()
{
    foo(std::array{1,2,3});
    foo(std::array{1UL,2UL,3UL});
    foo(std::array{std::array{11UL,21UL,31UL},std::array{12UL,22UL,32UL}});
    foo(std::array{std::array{std::array{11,21,31}},std::array{std::array{12,22,32}}});
    
    
    return 0;
}