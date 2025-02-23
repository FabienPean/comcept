# Comcept

No this is not a typo :smile: it is the contraction of _Composable Concepts_. The repository relies solely on C++20 to provide composable concept.

## Usage

```cpp
#include <comcept/comcept.hpp>
#include <comcept/concepts.hpp>

namespace ccpt = ::comcept;
namespace trt = ::comcept::trait;

auto foo(ccpt::range_of<trt::integral> auto&& R)
{
    std::print("foo(range_of<integral>)\n");
    for(auto&& e : R)
        std::print("{}\n",e)
}

auto foo(ccpt::range_of<trt::floating_point> auto&& R)
{
    std::print("foo(range_of<floating_point>)\n");
    for(auto&& e : R)
        std::print("{}\n",e)
}

auto foo(ccpt::range_of<ccpt::range_of<trt::floating_point>> auto&& R)
{
    std::print("foo(range_of<range_of<floating_point>>)\n");
    for(auto&& e : R)
        foo(e);
}

int main()
{
    foo(std::array{1UL,2UL,3UL});
    foo(std::array{1.,2.,3.});
    foo(std::array{std::array{11UL,12UL,13UL},std::array{14UL,15UL,16UL}});
    return 0;
}
```

## Principle

## Usage