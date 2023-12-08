#pragma once

#include <cstdint>

LLCL_NAMESPACE_BEGIN

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

static_assert(1 == sizeof(int8));
static_assert(2 == sizeof(int16));
static_assert(4 == sizeof(int32));
static_assert(8 == sizeof(int64));
static_assert(1 == sizeof(uint8));
static_assert(2 == sizeof(uint16));
static_assert(4 == sizeof(uint32));
static_assert(8 == sizeof(uint64));

static_assert(1 == sizeof(bool));

// TODO : Is it necessary to use std::char8_t to make ASCII/Unicode things safe?
static_assert(1 == sizeof(char));
static_assert(1 == sizeof(unsigned char));

// TODO : C++23 will add std::float32_t, std::float64_t, ...
static_assert(4 == sizeof(float));
static_assert(8 == sizeof(double));

static_assert(sizeof(void*) == (LLCL_CPU_ADDRESS_BITS / 8));

LLCL_NAMESPACE_END