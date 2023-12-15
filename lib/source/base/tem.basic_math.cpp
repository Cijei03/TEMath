#include "../../headers/base/tem.basic_math.hpp"

#define TEM_LOCAL_CLASS_TEMPLATE template<intern::temType T>

namespace tem
{
	template class BasicMath<tem_f32>;
	template class BasicMath<tem_f64>;

	template class BasicMath<tem_i8>;
	template class BasicMath<tem_i16>;
	template class BasicMath<tem_i32>;
	template class BasicMath<tem_i64>;

	template class BasicMath<tem_ui8>;
	template class BasicMath<tem_ui16>;
	template class BasicMath<tem_ui32>;
	template class BasicMath<tem_ui64>;
}