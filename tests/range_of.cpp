#include <comcept/comcept.hpp>
#include <comcept/concepts.hpp>
#include <iostream>

auto print(auto&& e)
{
    std::cout<<std::to_string(e)<<"\n";
}

auto print(std::ranges::range auto&& R)
{
    for(auto&& element : R)
        print(element);
}

auto foo(comcept::range_of<comcept::trait::integral> auto&& R)
{
    for(auto&& element : R)
        print(element);
}

int main()
{
    foo(std::array{1,2,3});
    return 0;
}