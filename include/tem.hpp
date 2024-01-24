#pragma once

#ifndef TEM_64_BIT_ERROR
	#define TEM_64_BIT_ERROR "Library is not compatible with 32-bit systems!"
#endif

#if _WIN32
	#ifndef _M_X64
		#error TEM_64_BIT_ERROR
	#elif !_M_ARM64
	#endif
#elif __linux__
	#ifndef __LP64
		#error TEM_64_BIT_ERROR
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
