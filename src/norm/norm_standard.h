#ifndef FRSML_IMPL_NORM_NORM_STANDARD_H
#define FRSML_IMPL_NORM_NORM_STANDARD_H

#include "../math_internal.h"

namespace frsml {
	namespace norm {
		float  _exp(float x);
		float  _log(float x);
		float  _log2(float x);
		float  _log(float x, float base);
		float  _pow(float x, float y);

		float  _abs(float p_num);
		float  _clamp(float p_t1, float p_t2, float p_crrNumber);
		float  _lerp(float p_t, float p_a, float p_b);

		int  _sign(float p_num);

		float  _sin(float p_num);
		float  _cos(float p_num);
		float  _tan(float p_num);
		float  _cot(float p_num);

		void   _sin_cos(float p_x, float* p_s, float* p_c);

		float  _asin(float p_num);
		float  _acos(float p_num);
		float  _atan(float p_num);
		float  _atan2(float p_y, float p_x);
		float  _sqrt(float p_num);

		float  _fade(float p_num);
	}
}

#endif