# Comcept

No this is not a typo :smile: it is the contraction of _Composable Concepts_


```cpp
#include<comcept/comcept.hpp>

using namespace comcept;

void print(auto&& e)
{
    std::print("{}\n",e)
}

auto print(std::ranges::range auto&& R)
{
    for(auto&& e : R)
        std::print("{}\n",e)
}

auto foo(range_of<trait::integral> auto&& R)
{
    for(auto&& e : R)
        print(e);
}

auto foo(tuple_of<trait::range_of<trait::integral>> auto&& t)
{
    std::apply([](auto const& ...e) { (print(e), ...); }, t);
}

int main()
{
    foo(std::array{1,2,3});
    foo(std::array{1UL,2UL,3UL});
    foo(std::tuple{std::array{11UL,21UL,31UL},std::array{12.,22.,32.}});
    return 0;
}

```