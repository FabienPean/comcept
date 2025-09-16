// SPDX-License-Identifier: MIT
#pragma once

#include <type_traits>
#include <version>

#include <comcept/comcept.hpp>

namespace comcept::trait
{
#if __cplusplus >= 201103L
using is_void = compose<std::is_void>;
#endif

#if __cplusplus >= 201103L
using is_null_pointer = compose<std::is_null_pointer>;
#endif

#if __cplusplus >= 201103L
using is_integral = compose<std::is_integral>;
#endif

#if __cplusplus >= 201103L
using is_floating_point = compose<std::is_floating_point>;
#endif

#if __cplusplus >= 201103L
using is_array = compose<std::is_array>;
#endif

#if __cplusplus >= 201103L
using is_enum = compose<std::is_enum>;
#endif

#if __cplusplus >= 201103L
using is_union = compose<std::is_union>;
#endif

#if __cplusplus >= 201103L
using is_class = compose<std::is_class>;
#endif

#if __cplusplus >= 201103L
using is_function = compose<std::is_function>;
#endif

#if __cplusplus >= 201103L
using is_pointer = compose<std::is_pointer>;
#endif

#if __cplusplus >= 201103L
using is_lvalue_reference = compose<std::is_lvalue_reference>;
#endif

#if __cplusplus >= 201103L
using is_rvalue_reference = compose<std::is_rvalue_reference>;
#endif

#if __cplusplus >= 201103L
using is_member_object_pointer = compose<std::is_member_object_pointer>;
#endif

#if __cplusplus >= 201103L
using is_member_function_pointer = compose<std::is_member_function_pointer>;
#endif

#if __cplusplus >= 201103L
using is_fundamental = compose<std::is_fundamental>;
#endif

#if __cplusplus >= 201103L
using is_arithmetic = compose<std::is_arithmetic>;
#endif

#if __cplusplus >= 201103L
using is_scalar = compose<std::is_scalar>;
#endif

#if __cplusplus >= 201103L
using is_object = compose<std::is_object>;
#endif

#if __cplusplus >= 201103L
using is_compound = compose<std::is_compound>;
#endif

#if __cplusplus >= 201103L
using is_reference = compose<std::is_reference>;
#endif

#if __cplusplus >= 201103L
using is_member_pointer = compose<std::is_member_pointer>;
#endif

#if __cplusplus >= 201103L
using is_const = compose<std::is_const>;
#endif

#if __cplusplus >= 201103L
using is_volatile = compose<std::is_volatile>;
#endif

#if __cplusplus >= 201103L
using is_trivial = compose<std::is_trivial>;
#endif

#if __cplusplus >= 201103L
using is_trivially_copyable = compose<std::is_trivially_copyable>;
#endif

#if __cplusplus >= 201103L
using is_standard_layout = compose<std::is_standard_layout>;
#endif

#if __cplusplus >= 201103L
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
using is_pod = compose<std::is_pod>;
#pragma GCC diagnostic push
#endif

#if __cplusplus >= 201103L && __cplusplus < 202002L
using is_literal_type = compose<std::is_literal_type>;
#endif

#if __cplusplus >= 201703L
using has_unique_object_representations = compose<std::has_unique_object_representations>;
#endif

#if __cplusplus >= 201103L
using is_empty = compose<std::is_empty>;
#endif

#if __cplusplus >= 201103L
using is_polymorphic = compose<std::is_polymorphic>;
#endif

#if __cplusplus >= 201103L
using is_abstract = compose<std::is_abstract>;
#endif

#if __cplusplus >= 201402L
using is_final = compose<std::is_final>;
#endif

#if __cplusplus >= 201703L
using is_aggregate = compose<std::is_aggregate>;
#endif

#if __cplusplus >= 202300L
#ifdef __cpp_lib_is_implicit_lifetime
using is_implicit_lifetime = compose<std::is_implicit_lifetime>;
#endif
#endif

#if __cplusplus >= 201103L
using is_signed = compose<std::is_signed>;
#endif

#if __cplusplus >= 201103L
using is_unsigned = compose<std::is_unsigned>;
#endif

#if __cplusplus >= 202002L
using is_bounded_array = compose<std::is_bounded_array>;
#endif

#if __cplusplus >= 202002L
using is_unbounded_array = compose<std::is_unbounded_array>;
#endif

#if __cplusplus >= 202300L
using is_scoped_enum = compose<std::is_scoped_enum>;
#endif

#if __cplusplus >= 201103L
template<typename... Args>
using is_constructible = compose<std::is_constructible, Args...>;
#endif

#if __cplusplus >= 201103L
template<typename... Args>
using is_trivially_constructible = compose<std::is_trivially_constructible, Args...>;
#endif

#if __cplusplus >= 201103L
template<typename... Args>
using is_nothrow_constructible = compose<std::is_nothrow_constructible, Args...>;
#endif

#if __cplusplus >= 201103L
using is_default_constructible = compose<std::is_default_constructible>;
#endif

#if __cplusplus >= 201103L
using is_trivially_default_constructible = compose<std::is_trivially_default_constructible>;
#endif

#if __cplusplus >= 201103L
using is_nothrow_default_constructible = compose<std::is_nothrow_default_constructible>;
#endif

#if __cplusplus >= 201103L
using is_copy_constructible = compose<std::is_copy_constructible>;
#endif

#if __cplusplus >= 201103L
using is_trivially_copy_constructible = compose<std::is_trivially_copy_constructible>;
#endif

#if __cplusplus >= 201103L
using is_nothrow_copy_constructible = compose<std::is_nothrow_copy_constructible>;
#endif

#if __cplusplus >= 201103L
using is_move_constructible = compose<std::is_move_constructible>;
#endif

#if __cplusplus >= 201103L
using is_trivially_move_constructible = compose<std::is_trivially_move_constructible>;
#endif

#if __cplusplus >= 201103L
using is_nothrow_move_constructible = compose<std::is_nothrow_move_constructible>;
#endif

#if __cplusplus >= 201103L
template<typename Arg>
using is_assignable = compose<std::is_assignable, Arg>;
#endif

#if __cplusplus >= 201103L
template<typename Arg>
using is_trivially_assignable = compose<std::is_trivially_assignable, Arg>;
#endif

#if __cplusplus >= 201103L
template<typename Arg>
using is_nothrow_assignable = compose<std::is_nothrow_assignable, Arg>;
#endif

#if __cplusplus >= 201103L
using is_copy_assignable = compose<std::is_copy_assignable>;
#endif

#if __cplusplus >= 201103L
using is_trivially_copy_assignable = compose<std::is_trivially_copy_assignable>;
#endif

#if __cplusplus >= 201103L
using is_nothrow_copy_assignable = compose<std::is_nothrow_copy_assignable>;
#endif

#if __cplusplus >= 201103L
using is_move_assignable = compose<std::is_move_assignable>;
#endif

#if __cplusplus >= 201103L
using is_trivially_move_assignable = compose<std::is_trivially_move_assignable>;
#endif

#if __cplusplus >= 201103L
using is_nothrow_move_assignable = compose<std::is_nothrow_move_assignable>;
#endif

#if __cplusplus >= 201103L
using is_destructible = compose<std::is_destructible>;
#endif

#if __cplusplus >= 201103L
using is_trivially_destructible = compose<std::is_trivially_destructible>;
#endif

#if __cplusplus >= 201103L
using is_nothrow_destructible = compose<std::is_nothrow_destructible>;
#endif

#if __cplusplus >= 201103L
using has_virtual_destructor = compose<std::has_virtual_destructor>;
#endif

#if __cplusplus >= 201703L
template<typename Arg>
using is_swappable_with = compose<std::is_swappable_with, Arg>;
#endif

#if __cplusplus >= 201703L
using is_swappable = compose<std::is_swappable>;
#endif

#if __cplusplus >= 201703L
template<typename Arg>
using is_nothrow_swappable_with = compose<std::is_nothrow_swappable_with, Arg>;
#endif

#if __cplusplus >= 201703L
using is_nothrow_swappable = compose<std::is_nothrow_swappable>;
#endif

#if __cplusplus >= 202300L
#ifdef __cpp_lib_reference_from_temporary
template<typename Arg>
using reference_constructs_from_temporary = compose<std::reference_constructs_from_temporary, Arg>;
template<typename Arg>
using reference_converts_from_temporary = compose<std::reference_converts_from_temporary, Arg>;
#endif
#endif

#if __cplusplus >= 201103L
template<typename Arg>
using is_same = compose<std::is_same, Arg>;
#endif

#if __cplusplus >= 201103L
template<typename Arg>
using is_base_of = compose<std::is_base_of, Arg>;
#endif

#if __cplusplus >= 202600L
template<typename Arg>
using is_virtual_base_of = compose<std::is_virtual_base_of, Arg>;
#endif

#if __cplusplus >= 201103L
template<typename Arg>
using is_convertible = compose<std::is_convertible, Arg>;
#endif

#if __cplusplus >= 202002L
template<typename Arg>
using is_nothrow_convertible = compose<std::is_nothrow_convertible, Arg>;
#endif

#if __cplusplus >= 202002L
#ifdef __cpp_lib_is_layout_compatible
template<typename Arg>
using is_layout_compatible = compose<std::is_layout_compatible, Arg>;
#endif
#endif

#if __cplusplus >= 202002L
#ifdef __cpp_lib_is_pointer_interconvertible
template<typename Arg>
using is_pointer_interconvertible_base_of = compose<std::is_pointer_interconvertible_base_of, Arg>;
#endif
#endif

#if __cplusplus >= 201703L
template<typename... Args>
using is_invocable = compose<std::is_invocable, Args...>;
#endif

#if __cplusplus >= 201703L
using is_nothrow_invocable = compose<std::is_nothrow_invocable>;
#endif

} // namespace comcept::trait
