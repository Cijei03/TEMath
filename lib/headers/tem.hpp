#pragma once

#ifndef _M_X64
	#error Library is not compatible with 32-bit systems!
#elif !_M_ARM64
	
#endif

#ifndef __clang__
	//#error Library should be compiled with CLang compiler.
#else
	#if __clang_major__ < 16
		//#error Outdated CLang version. Minimal requires version is 16.0.
	#endif
#endif



#include "tem.basic_types.hpp"
#include "tem.vec2.hpp"
#include "tem.vec3.hpp"
#include "tem.vec4.hpp"
#include "tem.basic_math.hpp"
#include "tem.angle_units.hpp"
#include "tem.mat2.hpp"
#include "tem.mat3.hpp"
#include "tem.mat4.hpp"