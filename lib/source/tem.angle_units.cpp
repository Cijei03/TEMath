#include "../headers/tem.angle_units.hpp"

#define TEM_LOCAL_CLASS_TEMPLATE template<intern::temType T>

namespace tem
{
	template class Radian<tem_f32>;
	template class Radian<tem_f64>;

	template class Degree<tem_f32>;
	template class Degree<tem_f64>;
}