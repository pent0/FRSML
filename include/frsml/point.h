#ifndef FRSML_POINT_H
#define FRSML_POINT_H

#include "internal.h"

namespace frsml {
	struct FRS_MATH_API point {
		float x, y;

		point();
		point(float p_x, float p_y);

		inline bool operator == (point p_point);
		inline bool operator != (point p_point);
	};
}

#endif