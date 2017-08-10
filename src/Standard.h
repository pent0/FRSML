#pragma once

#include "math_internal.h"
#include "sse_extensions.h"

namespace frs {
	namespace nmmintrin {
		__m128i FRS_MATH_API _abs(__m128i p_para);
		__m128 FRS_MATH_API _absf(__m128 p_para);
		__m128 FRS_MATH_API _maxf(__m128 p_a, __m128 p_b);
		__m128 FRS_MATH_API _minf(__m128 p_a, __m128 p_b);
		__m128i FRS_MATH_API _max(__m128i p_a, __m128i p_b);
	    __m128i FRS_MATH_API _min(__m128i p_a, __m128i p_b);
		__m128 FRS_MATH_API _sqrtf(__m128 p_num);
		__m128i FRS_MATH_API _sqrt(__m128i p_num);
		__m128 FRS_MATH_API _signf(__m128 p_num);
		inline __m128 FRS_MATH_API balance_to_pi_distance(__m128 p_para);
		inline __m128 FRS_MATH_API _sin(__m128 p_para);
		inline __m128 FRS_MATH_API _cos(__m128 p_para);
		inline __m128 FRS_MATH_API _tan(__m128 p_para);
		inline __m128 FRS_MATH_API _cot(__m128 p_para);
		inline __m128 FRS_MATH_API _asin(__m128 p_para);
		inline __m128 FRS_MATH_API _acos(__m128 p_para);
		inline __m128 FRS_MATH_API _atan2(__m128 p_y, __m128 p_x);
		inline __m128 FRS_MATH_API _atan(__m128 p_x);
		inline __m128 FRS_MATH_API _pow(__m128 p_x, __m128 p_y);
		inline __m128 FRS_MATH_API _exp(__m128 p_para);
		inline __m128 FRS_MATH_API _log(__m128 p_para);
	}
}
