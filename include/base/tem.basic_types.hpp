#pragma once
#include <cstdint>
#include <concepts>
#include <type_traits>
#include <cstddef>

using tem_size = size_t;

using tem_i8 = int8_t;
using tem_i16 = int16_t;
using tem_i32 = int32_t;
using tem_i64 = int64_t;

using tem_ui8 = uint8_t;
using tem_ui16 = uint16_t;
using tem_ui32 = uint32_t;
using tem_ui64 = uint64_t;

using tem_f32 = float;
using tem_f64 = double;

namespace tem::intern
{
	template<typename T>
	concept temType =
		std::is_same_v<T, tem_i8> ||
		std::is_same_v<T, tem_i16> ||
		std::is_same_v<T, tem_i32> ||
		std::is_same_v<T, tem_i64> ||

		std::is_same_v<T, tem_ui8> ||
		std::is_same_v<T, tem_ui16> ||
		std::is_same_v<T, tem_ui32> ||
		std::is_same_v<T, tem_ui64> ||

		std::is_same_v<T, tem_f32> ||
		std::is_same_v<T, tem_f64>;
}
