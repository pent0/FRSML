#ifndef FRSML_RECT_H
#define FRSML_RECT_H

#include "internal.h"

namespace frsml {

	struct point;

	struct FRS_MATH_API rect {
		float x, y;
		float width, height;

		rect();
		rect(float p_x, float p_y, float p_width, float p_height);

		bool contains(float p_x, float p_y) const;
		bool contains(point p_point) const;
		bool contains(rect p_rect) const;

		inline bool operator ==(rect p_rect);

		rect intersects(rect p_rect);

		void inflate(float p_inflate_width, float p_inflate_height);
		void offset(float p_new_x, float p_new_y);

		void offset(point p_point);
	};

}

#endif