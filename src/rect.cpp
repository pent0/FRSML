#include <frsml/rect.h>
#include <frsml/point.h>

#include "math_internal.h"

namespace frs {
	rect::rect() : x(0), y(0), width(0), height(0) {};

	rect::rect(float p_x, float p_y, float p_width, float p_height) :
		x(p_x), y(p_y), width(p_width), height(p_height) {};

	bool rect::contains(float p_x, float p_y) const {
		if ((x < p_x) && p_x < (x + width)
			&& (y < p_y) && p_y < (y + height)) {
			return true;
		}

		return false;
	}

	bool rect::contains(point p_point) const {
		return contains(p_point.x, p_point.y);
	}

	bool rect::contains(rect p_rect) const {
		if ((x < p_rect.x) && p_rect.x < (x + width)
			&& (y < p_rect.y) && p_rect.y < (y + height)) {
			return true;
		}

		return false;
	}

	inline bool rect::operator ==(rect p_rect) {
		return (p_rect.x == x) && (p_rect.y == y)
			&& (p_rect.width == width) && 
			(p_rect.height == height);
	}

	rect rect::intersects(rect p_rect) {
		rect t_intersects = rect::rect();

		t_intersects.width = abs(width - p_rect.width);
		t_intersects.height = abs(height - p_rect.height);
		t_intersects.x = maxf(x, p_rect.x);
		t_intersects.y = maxf(y, p_rect.y);

		return t_intersects;
	}

	void rect::inflate(float p_inflate_width, float p_inflate_height) {
		width += p_inflate_width;
		height += p_inflate_height;
	}

	void rect::offset(float p_new_x, float p_new_y) {
		x = p_new_x;
		y = p_new_y;
	}

	void rect::offset(point p_point) {
		x = p_point.x;
		y = p_point.y;
	}
}
