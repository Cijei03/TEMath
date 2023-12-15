#pragma once

#ifndef TEM_AVX_SIMD
	#ifdef _MSC_VER
		#define TEM_AVX_SIMD
	#else
		#define TEM_AVX_SIMD [[gnu::target("avx")]]
	#endif
#endif