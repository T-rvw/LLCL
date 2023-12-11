#pragma once

#include <LLCL/Namespace.h>

#include <climits>
#include <cmath>

LLCL_NAMESPACE_BEGIN

//
// Constant values can switch to arbitrary precision : float/double/...
//
namespace constants
{

template<typename T> inline constexpr T Min() { return std::numeric_limits<T>::min(); }
template<typename T> inline constexpr T Max() { return std::numeric_limits<T>::max(); }
template<typename T> inline constexpr T NaN() { return std::numeric_limits<T>::quiet_NaN(); }

template<typename T> inline constexpr T Zero() { return static_cast<T>(0.0); }
template<typename T> inline constexpr T Half() { return static_cast<T>(0.5); }
template<typename T> inline constexpr T One() { return static_cast<T>(1.0); }
template<typename T> inline constexpr T Two() { return static_cast<T>(2.0); }

template<typename T> inline constexpr T PI() { return static_cast<T>(3.141592653589793238462643383279502884e+00); }
template<typename T> inline constexpr T HalfPI() { return Half<T>() * PI<T>(); }
template<typename T> inline constexpr T TwoPI() { return Two<T>() * PI<T>(); }
template<typename T> inline constexpr T InversePI() { return One<T>() / PI<T>(); }

template<typename T> inline constexpr T RootTwo() { return static_cast<T>(1.414213562373095048801688724209698078e+00); }
template<typename T> inline constexpr T HalfRootTwo() { return Half<T>() * RootTwo<T>(); }
template<typename T> inline constexpr T InverseRootTwo() { return One<T>() / RootTwo<T>(); }

template<typename T> inline constexpr T RootThree() { return static_cast<T>(1.732050807568877293527446341505872366e+00); }
template<typename T> inline constexpr T HalfRootThree() { return Half<T>() * RootThree<T>(); }
template<typename T> inline constexpr T InverseRootThree() { return One<T>() / RootThree<T>(); }

template<typename T> inline constexpr T Degree() { return PI<T>() / static_cast<T>(180.0); }
template<typename T> inline constexpr T Radian() { return One<T>() / Degree<T>(); }

}

[[nodiscard]] template<typename T> constexpr T DegreeToRadian(T degree) { return degree * constants::Degree<T>(); }
[[nodiscard]] template<typename T> constexpr T RadianToDegree(T radian) { return radian * constants::Radian<T>(); }

LLCL_NAMESPACE_END