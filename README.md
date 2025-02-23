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

## Installation

The library is header-only and the content of include folder simply needs to be added on the include directory path of the compiler with the `-I` argument. Alternatively, this repository is CMake ready and provides a target name `comcept::comcept` to link your project to. For example with `FetchContent` tools. 

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

## Usage