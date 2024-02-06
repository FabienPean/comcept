#include "reconcept.hpp"

#include <iostream>
#include <format>

auto foo(rccpt::range_of<rccpt::integral> auto R)
{
    for(auto&& element : R)
    std::cout<<std::format("{}",element)<<"\n";
}

int main()
{
    foo(std::array{1,2,3});
    foo(std::array{1UL,2UL,3UL});
    return 0;
}