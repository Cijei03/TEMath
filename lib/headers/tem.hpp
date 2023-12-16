#pragma once

#ifndef TEM_64_BIT_ERROR
	#define TEM_64_BIT_ERROR #error Library is not compatible with 32-bit systems!
#endif

#if _WIN32
	#ifndef _M_X64
		TEM_64_BIT_ERROR
	#elif !_M_ARM64
#elif __linux__
	#ifndef __LP64
		TEM_64_BIT_ERROR
	#endif
#endif
	
#endif

#include "base/tem.basic_types.hpp"
#include "base/tem.basic_math.hpp"
#include "base/tem.angle_units.hpp"
#include "basic/tem.vec2.hpp"
#include "basic/tem.vec3.hpp"
#include "basic/tem.vec4.hpp"
#include "basic/tem.mat2.hpp"
#include "basic/tem.mat3.hpp"
#include "basic/tem.mat4.hpp"

#include "avx/tem.vec2.hpp"
#include "avx/tem.vec3.hpp"
#include "avx/tem.vec4.hpp"
#include "avx/tem.mat2.hpp"
#include "avx/tem.mat3.hpp"
#include "avx/tem.mat4.hpp"

#include "avx2/tem.vec2.hpp"
#include "avx2/tem.vec3.hpp"
#include "avx2/tem.vec4.hpp"
#include "avx2/tem.mat2.hpp"
#include "avx2/tem.mat3.hpp"
#include "avx2/tem.mat4.hpp"


#ifdef _MSC_VER
	#pragma message("MSVC does not support partial code generation with advanced SIMD usage. Use GNU compiler.")
#endif
