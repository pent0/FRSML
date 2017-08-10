#include "math_internal.h"

namespace frs {
	point::point() : x(0), y(0) {};

	point::point(float p_x, float p_y) : x(p_x), y(p_y) {};

	inline bool point::operator == (point p_point) {
		return (x == p_point.x) && (y == p_point.y);
	}

	inline bool point::operator != (point p_point) {
		return !(*this == p_point);
	}
}
