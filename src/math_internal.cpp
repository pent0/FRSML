#include <frsml/vector.h>

#include "math_internal.h"

namespace frsml {
	__m128 to_pack4(vec2 p_vec) {
		return _mm_set_ps(0, 0, p_vec.x, p_vec.y);
	}

	__m128 to_pack4(vec3 p_vec) {
		return _mm_set_ps(0, p_vec.x, p_vec.y, p_vec.z);
	}

	__m128 to_pack4(vec4 p_vec) {
		return _mm_set_ps(p_vec.x, p_vec.y, p_vec.z, p_vec.w);
	}

	vec2 to_vec2(__m128 p_vec) {
		__m128 t1 = _mm_shuffle_ps(p_vec, p_vec, MASK1);
		__m128 t2 = _mm_shuffle_ps(p_vec, p_vec, MASK0);

		return vec2(_mm_cvtss_f32(t1), _mm_cvtss_f32(t2));
	}

	vec3 to_vec3(__m128 p_vec) {
		__m128 t1 = _mm_shuffle_ps(p_vec, p_vec, MASK2);
		__m128 t2 = _mm_shuffle_ps(p_vec, p_vec, MASK1);
		__m128 t3 = _mm_shuffle_ps(p_vec, p_vec, MASK0);

		return vec3(_mm_cvtss_f32(t1), _mm_cvtss_f32(t2),
			_mm_cvtss_f32(t3));
	}

	vec4 to_vec4(__m128 p_vec) {
		__m128 t1 = _mm_shuffle_ps(p_vec, p_vec, MASK3);
		__m128 t2 = _mm_shuffle_ps(p_vec, p_vec, MASK2);
		__m128 t3 = _mm_shuffle_ps(p_vec, p_vec, MASK1);
		__m128 t4 = _mm_shuffle_ps(p_vec, p_vec, MASK0);

		return vec4(_mm_cvtss_f32(t1), _mm_cvtss_f32(t2),
			_mm_cvtss_f32(t3), _mm_cvtss_f32(t4));
	}
}