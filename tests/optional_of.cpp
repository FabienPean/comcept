#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>

#include <doctest/doctest.h>

#include <optional>
#include <variant>

namespace cpt = comcept;
namespace trt = comcept::trait;

static_assert(not cpt::optional_of<std::optional<double>,trt::integral>);
static_assert(not cpt::optional_of<std::optional<double>,double&>);
static_assert(not cpt::optional_of<std::optional<double>,float>);
static_assert(    cpt::optional_of<std::optional<double>,double>);
static_assert(    cpt::optional_of<std::optional<double>,trt::floating_point>);
static_assert(not cpt::optional_of<std::optional<int>   ,trt::floating_point>);
static_assert(not cpt::optional_of<std::variant<int>    ,trt::floating_point>);

#ifdef __cpp_lib_expected 
#include <expected>
static_assert(    comcept::optional_of<std::expected<float,int>,trt::floating_point>);
#endif