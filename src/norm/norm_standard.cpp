#include <cmath>

#include "norm_standard.h"

namespace frsml {
	namespace norm {
		float  _exp(float x) {
			return std::expf(x);
		}

		float  _log(float x) {
			return std::logf(x);
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
			return std::sinf(p_num);
		}

		float  _cos(float p_num) {
			return std::cosf(p_num);
		}

		float  _tan(float p_num) {
			return std::tanf(p_num);
		}

		float  _asin(float p_num) {
			return std::asinf(p_num);
		}

		float  _acos(float p_num) {
			return std::acosf(p_num);
		}

		float  _atan(float p_num) {
			return std::atanf(p_num);
		}

		float  _atan2(float p_x, float p_y) {
			return std::atan2f(p_y, p_x);
		}

		float  _sqrt(float p_num) {
			return std::sqrtf(p_num);
		}

		float  _fade(float p_num) {
			return pow(p_num, 3) * (p_num * (p_num * 6 - 15) + 10);
		}
	}
}