#include <cmath>

#include "norm_standard.h"

namespace frsml {
	namespace norm {
		float  _exp(float x) {
			return std::exp(x);
		}

		float  _log(float x) {
			return std::log(x);
		}

		float  _log2(float x) {
			return std::log2f(x);
		}

		float  _pow(float x, float y) {
			return std::pow(x, y);
		}

		float  _lerp(float p_t, float p_a, float p_b) {
			return p_a + p_t * (p_b - p_a);
		}

		float  _sin(float p_num) {
			return std::sin(p_num);
		}

		float  _cos(float p_num) {
			return std::cos(p_num);
		}

		float  _tan(float p_num) {
			return std::tan(p_num);
		}

		float  _asin(float p_num) {
			return std::asin(p_num);
		}

		float  _acos(float p_num) {
			return std::acos(p_num);
		}

		float  _atan(float p_num) {
			return std::atan(p_num);
		}

		float  _atan2(float p_y, float p_x) {
			return std::atan2(p_y, p_x);
		}

		float  _sqrt(float p_num) {
			return std::sqrt(p_num);
		}

		float  _fade(float p_num) {
			return pow(p_num, 3) * (p_num * (p_num * 6 - 15) + 10);
		}
	}
}