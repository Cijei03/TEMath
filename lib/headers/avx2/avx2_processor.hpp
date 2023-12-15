#pragma once

#ifndef TEM_AVX2_FMA3_SIMD
	#ifdef _MSC_VER
		#define TEM_AVX2_FMA3_SIMD
	#else
		#define TEM_AVX2_FMA3_SIMD [[gnu::target("avx2"), gnu::target("fma")]]
	#endif
#endif