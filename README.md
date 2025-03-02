# Comcept [<img align="right" src="https://github.com/codespaces/badge.svg">](https://codespaces.new/FabienPean/comcept?quickstart=1)

![Linux](https://github.com/FabienPean/comcept/actions/workflows/linux.yml/badge.svg)
![Windows](https://github.com/FabienPean/comcept/actions/workflows/windows.yml/badge.svg)

No this is not a typo :smile: it is the contraction of _Composable Concepts_. After using C++20 and concepts for a while, have you ever wondered _"Dang, I really wish I could constrain the element type of this range"_, then you are at the right place ! This library reformulates concepts and type traits into a unified type trait interface that can be used to build higher-order concepts. Do not expect blazing compilation time, as the goal was a _pleasant_ interface. Currently, it has only a few of them, but their number is destined to increase, where it makes sense _and where it is possible_.

## Usage

```cpp
#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>

namespace ccpt = ::comcept;
namespace  trt = ::comcept::trait;
// A
auto foo(ccpt::range_of<trt::integral> auto&& R)
{
    std::print("foo(range_of<integral>)\n");
    for(auto&& e : R)
        std::print("{}\n",e)
}
// B
auto foo(ccpt::range_of<trt::floating_point> auto&& R)
{
    std::print("foo(range_of<floating_point>)\n");
    for(auto&& e : R)
        std::print("{}\n",e)
}
// C
auto foo(ccpt::range_of<trt::range_of<trt::integral>> auto&& R)
{
    std::print("foo(range_of<range_of<integral>>)\n");
    for(auto&& e : R)
        foo(e);
}

int main()
{
    foo(std::array{1UL,2UL,3UL});   // calls A
    foo(std::array{1.,2.,3.});      // calls B
    foo(std::array{std::array{11UL,12UL,13UL},
                   std::array{14UL,15UL,16UL}}
    ); // calls C
    return 0;
}
```

## Installation

The library is header-only and the content of include folder simply needs to be added on the include directory path of the compiler with the `-I` argument. Alternatively, this repository is CMake ready and provides a target name `comcept::comcept` to link your project to, via `add_subdirectory`, or `FetchContent`: 

```cmake
FetchContent_Declare(
  comcept
  GIT_REPOSITORY https://github.com/FabienPean/comcept.git
  GIT_TAG        main
  SYSTEM
  FIND_PACKAGE_ARGS # FIND_PACKAGE_ARGS can also be given with nothing after it, which indicates that find_package() can still be called if FETCHCONTENT_TRY_FIND_PACKAGE_MODE is set to OPT_IN, or is not set.
)
FetchContent_MakeAvailable(comcept)
```

and then linked to your target afterwards as such

```cmake
add_executable(main main.cpp)
target_link_libraries(main comcept::comcept)
```

## License

Copyright (c) 2025 Fabien Péan

This library is released under the [MIT license](LICENSE).
