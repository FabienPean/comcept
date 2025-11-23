#include <comcept/comcept.hpp>
#include <comcept/trait/concepts.hpp>
#include <type_traits>

namespace cpt = comcept;
namespace trt = comcept::trait;
struct Dummy {};

///====================================================================================================================
/// Compile-time
///====================================================================================================================

// concept satisfaction
static_assert(    cpt::cvref_of<const Dummy& , Dummy>);
static_assert(    cpt::cvref_of<volatile Dummy&& , Dummy>);
static_assert(    cpt::cvref_of<const volatile Dummy&, Dummy>);
static_assert(    cpt::cvref_of<const Dummy&, Dummy>);
static_assert(    cpt::cvref_of<const Dummy&&, Dummy>);
static_assert(    cpt::cvref_of<volatile Dummy&, Dummy>);
static_assert(    cpt::cvref_of<const volatile Dummy&&, Dummy>);

// concept composition
static_assert(    cpt::cvref_of<const Dummy&, trt::same_as<Dummy>>);
static_assert(    cpt::cvref_of<volatile Dummy&&, trt::same_as<Dummy>>);
static_assert(    cpt::cvref_of<const volatile Dummy&, trt::same_as<Dummy>>);
static_assert(    cpt::cvref_of<const Dummy&&, trt::same_as<Dummy>>);
static_assert(    cpt::cvref_of<volatile Dummy&, trt::same_as<Dummy>>);
static_assert(    cpt::cvref_of<const volatile Dummy&&, trt::same_as<Dummy>>);

// trait satisfaction
static_assert(    trt::cvref_of<Dummy>::value<const Dummy&>);
static_assert(    trt::cvref_of<Dummy>::value<volatile Dummy&&>);
static_assert(    trt::cvref_of<Dummy>::value<const volatile Dummy&>);
static_assert(    trt::cvref_of<Dummy>::value<const Dummy&&>);
static_assert(    trt::cvref_of<Dummy>::value<volatile Dummy&>);
static_assert(    trt::cvref_of<Dummy>::value<const volatile Dummy&&>);

// trait composition
static_assert(    trt::cvref_of<trt::same_as<Dummy>>::value<const Dummy&>);
static_assert(    trt::cvref_of<trt::same_as<Dummy>>::value<volatile Dummy&&>);
static_assert(    trt::cvref_of<trt::same_as<Dummy>>::value<const volatile Dummy&>);
static_assert(    trt::cvref_of<trt::same_as<Dummy>>::value<const Dummy&&>);
static_assert(    trt::cvref_of<trt::same_as<Dummy>>::value<volatile Dummy&>);
static_assert(    trt::cvref_of<trt::same_as<Dummy>>::value<const volatile Dummy&&>);

// negative cases
static_assert(not cpt::cvref_of<Dummy, Dummy>);
static_assert(not cpt::cvref_of<int&, Dummy>);
static_assert(not cpt::cvref_of<float&&, Dummy>);
static_assert(not trt::cvref_of<Dummy>::value<int&>);
static_assert(not trt::cvref_of<Dummy>::value<float&&>);

// unqualified concept satisfaction
static_assert(    cpt::unqualified<Dummy, Dummy>);
static_assert(    cpt::unqualified<int, int>);
static_assert(    cpt::unqualified<float, float>);
static_assert(    cpt::unqualified<Dummy, trt::same_as<Dummy>>);
static_assert(    cpt::unqualified<int, trt::same_as<int>>);
static_assert(    cpt::unqualified<float, trt::same_as<float>>);

// trait satisfaction
static_assert(    trt::unqualified<Dummy>::value<Dummy>);
static_assert(    trt::unqualified<int>::value<int>);
static_assert(    trt::unqualified<float>::value<float>);

// trait composition
static_assert(    trt::unqualified<trt::same_as<Dummy>>::value<Dummy>);
static_assert(    trt::unqualified<trt::same_as<int>>::value<int>);
static_assert(    trt::unqualified<trt::same_as<float>>::value<float>);

// negative cases
static_assert(not cpt::unqualified<const Dummy&, Dummy>);
static_assert(not cpt::unqualified<volatile Dummy&&, Dummy>);
static_assert(not cpt::unqualified<const Dummy&, trt::same_as<Dummy>>);
static_assert(not trt::unqualified<Dummy>::value<const Dummy&>);
static_assert(not trt::unqualified<Dummy>::value<volatile Dummy&&>);
static_assert(not trt::unqualified<trt::same_as<Dummy>>::value<const Dummy&>);

