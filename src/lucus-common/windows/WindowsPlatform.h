
#pragma once

// from UE4

// Alignment.
#if defined(__clang__)
	#define GCC_PACK(n) __attribute__((packed,aligned(n)))
	#define GCC_ALIGN(n) __attribute__((aligned(n)))
	#if defined(_MSC_VER)
		#define MS_ALIGN(n) __declspec(align(n)) // With -fms-extensions, Clang will accept either alignment attribute
	#else
		#define MS_ALIGN(n)
	#endif
#else
	#define GCC_PACK(n)
	#define GCC_ALIGN(n)
	#define MS_ALIGN(n) __declspec(align(n))
#endif

// todo
#define FORCEINLINE inline