#pragma once

// Arch
#if defined(__i386__) || defined(_M_IX86)
	#define LLCL_CPU_ARCH_X86
	#define LLCL_CPU_ADDRESS_BYTES 4
	#define LLCL_CPU_ADDRESS_BITS 32
	#define LLCL_CPU_CACHE_LINE_SIZE 64
#elif defined(__x86_64__) || defined(_M_X64)
	#define LLCL_CPU_ARCH_X64
	#define LLCL_CPU_ADDRESS_BYTES 8
	#define LLCL_CPU_ADDRESS_BITS 64
	#define LLCL_CPU_CACHE_LINE_SIZE 64
#elif defined(__arm__) || defined(_M_ARM)
	#define LLCL_CPU_ARCH_ARM32
	#define LLCL_CPU_ADDRESS_BYTES 4
	#define LLCL_CPU_ADDRESS_BITS 32
	#define LLCL_CPU_CACHE_LINE_SIZE 64
#elif defined(__aarch64__) || defined(_M_ARM64)
	#define LLCL_CPU_ARCH_ARM64
	#define LLCL_CPU_ADDRESS_BYTES 8
	#define LLCL_CPU_ADDRESS_BITS 64
	#define LLCL_CPU_CACHE_LINE_SIZE 64
#else
	#error Unknown cpu architecture
#endif
static_assert(LLCL_CPU_ADDRESS_BYTES * 8 == LLCL_CPU_ADDRESS_BITS);

// SIMD instruction sets
// AVX
#if defined(__AVX512F__) && defined(__AVX512VL__) && defined(__AVX512DQ__)
	#define LLCL_CPU_USE_AVX512
#endif

#if defined(__AVX2__) || defined(LLCL_CPU_USE_AVX512)
	#define LLCL_CPU_USE_AVX2
#endif

#if defined(__AVX__) || defined(LLCL_CPU_USE_AVX2)
	#define LLCL_CPU_USE_AVX
#endif

// Float16 Conversion to Float32
#if defined(__F16C__) || defined(LLCL_CPU_USE_AVX2)
	#define LLCL_CPU_USE_F16C
#endif

// Leading Zero CouNT
#if defined(__LZCNT__) || defined(LLCL_CPU_USE_AVX2)
	#define LLCL_CPU_USE_LZCNT
#endif

// Trailing Zero CouNT
#if defined(__BMI__) || defined(LLCL_CPU_USE_AVX2)
	#define LLCL_CPU_USE_TZCNT
#endif

// Fused Multiply Add
#if defined(LLCL_COMPILER_CLANG) || defined(LLCL_COMPILER_GCC) 
	#if defined(__FMA__)
		#define LLCL_CPU_USE_FMADD
	#endif
#elif defined(LLCL_COMPILER_MSVC)
	#if defined(LLCL_CPU_USE_AVX2)
		#define LLCL_CPU_USE_FMADD
	#endif
#endif

// SSE
#if defined(LLCL_CPU_ARCH_X86) || defined(LLCL_CPU_ARCH_X64)
	#define LLCL_CPU_USE_SSE
#endif

#if defined(__SSE4_2__)
	#define LLCL_CPU_USE_SSE4_2
#endif

#if defined(__SSE4_1__) || defined(LLCL_CPU_USE_SSE4_2)
	#define LLCL_CPU_USE_SSE4_1
#endif

// NEON
#if defined(LLCL_CPU_ARCH_ARM32) || defined(LLCL_CPU_ARCH_ARM64)
	#define LLCL_CPU_USE_NEON
#endif