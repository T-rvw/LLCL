#pragma once

#include <cstddef>
#include <cstdint>

LLCL_NAMESPACE_BEGIN

using int8_t = std::int8_t;
using int16_t = std::int16_t;
using int32_t = std::int32_t;
using int64_t = std::int64_t;
using uint8_t = std::uint8_t;
using uint16_t = std::uint16_t;
using uint32_t = std::uint32_t;
using uint64_t = std::uint64_t;
using size_t = std::size_t;

static_assert(1 == sizeof(int8_t));
static_assert(2 == sizeof(int16_t));
static_assert(4 == sizeof(int32_t));
static_assert(8 == sizeof(int64_t));
static_assert(1 == sizeof(uint8_t));
static_assert(2 == sizeof(uint16_t));
static_assert(4 == sizeof(uint32_t));
static_assert(8 == sizeof(uint64_t));

static_assert(1 == sizeof(bool));

// TODO : Is it necessary to use std::char8_t to make ASCII/Unicode things safe?
static_assert(1 == sizeof(char));
static_assert(1 == sizeof(unsigned char));

// TODO : C++23 will add std::float32_t, std::float64_t, ...
static_assert(4 == sizeof(float));
static_assert(8 == sizeof(double));

static_assert(sizeof(void*) == (LLCL_CPU_ADDRESS_BITS / 8));

LLCL_NAMESPACE_END