#include <frsml/standard.h>

#include "sse/sse_standard.h"

namespace frsml {

	float exp(float x) {
		return _mm_cvtss_f32(nmmintrin::_exp(_mm_set1_ps(x)));
	}

	float log(float x) {
		return _mm_cvtss_f32(nmmintrin::_log(_mm_set1_ps(x)));
	}

	float log2(float x) {
		return _mm_cvtss_f32(
			_mm_div_ps(nmmintrin::_exp(_mm_set1_ps(x))
				, _mm_set1_ps(static_cast<float>(LOG2))));
	}

	float log(float x, float base) {
		return _mm_cvtss_f32(
			_mm_div_ps(nmmintrin::_exp(_mm_set1_ps(x))
				, nmmintrin::_log(_mm_set1_ps(base))));
	}

	float pow(float x, float y) {
		__m128 tmp = _mm_set_ss(x);
		__m128 tmp2 = _mm_set_ss(y);

		tmp = nmmintrin::_log(tmp);
		tmp2 = _mm_mul_ss(tmp, tmp2);

		tmp2 = nmmintrin::_exp(tmp2);

		return _mm_cvtss_f32(tmp2);
	}

	float abs(float p_num) {
		return (p_num < 0) ? (-p_num) : (p_num);
	}

	float clamp(float p_t1, float p_t2, float p_crrNumber) {
		return (p_t1 > p_crrNumber) ? (p_t1) :
			((p_t2 < p_crrNumber) ? (p_t2) : (p_crrNumber));
	}

	float lerp(float p_t, float p_a, float p_b) {
		return (1 - p_t) * p_a + p_t * p_b;
	}

	int sign(float p_num) {
		return (p_num < 0) ? -1 : ((p_num > 0) ? 1 : 0);
	}

	float sin(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_sin(_mm_set1_ps(p_num)));
	}

	float cos(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_cos(_mm_set1_ps(p_num)));
	}

	float tan(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_tan(_mm_set1_ps(p_num)));
	}

	float cot(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_cot(_mm_set1_ps(p_num)));
	}

	void sin_cos(float p_x, float* p_s, float* p_c) {
		__m128 t_both = _mm_set_ps(0, 0, p_x + PID2, p_x);
		__m128 t_sincos = nmmintrin::_sin(t_both);

		__m128 t_cos = _mm_shuffle_ps(t_sincos, t_sincos, _MM_SHUFFLE(0, 0, 0, 1));
		*p_s = _mm_cvtss_f32(t_sincos);
		*p_c = _mm_cvtss_f32(t_cos);
	}

	float asin(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_asin(_mm_set1_ps(p_num)));
	}

	float acos(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_acos(_mm_set1_ps(p_num)));
	}

	float atan(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_atan(_mm_set1_ps(p_num)));
	}

	float atan2(float p_y, float p_x) {
		return _mm_cvtss_f32(nmmintrin::_atan2(_mm_set1_ps(p_y), _mm_set1_ps(p_x)));
	}

	float maxf(float p_num, float p_num1) {
		return (p_num < p_num1) ? p_num1 : p_num;
	}

	float minf(float p_num, float p_num1) {
		return (p_num < p_num1) ? p_num : p_num1;
	}

	float sqrt(float p_num) {
		return _mm_cvtss_f32(nmmintrin::_sqrtf(_mm_set1_ps(p_num)));
	}

	vec2 abs(vec2 p_vec) {
		return vec2(abs(p_vec.x), abs(p_vec.y));
	}

	vec3 abs(vec3 p_vec) {
		return vec3(abs(p_vec.x), abs(p_vec.y),
			abs(p_vec.z));
	}

	vec4 abs(vec4 p_vec) {
		return vec4(abs(p_vec.x), abs(p_vec.y),
			abs(p_vec.z), abs(p_vec.w));
	}

	vec2 dot(vec2 p_vec, vec2 p_vec1) {
		return to_vec2(
			_mm_dp_ps(to_pack4(p_vec), to_pack4(p_vec1), 0x33));
	}

	vec3 dot(vec3 p_vec, vec3 p_vec1) {
		return to_vec3(
			_mm_dp_ps(to_pack4(p_vec), to_pack4(p_vec1), 0x77));
	}

	vec4 dot(vec4 p_vec, vec4 p_vec1) {
		return to_vec4(
			_mm_dp_ps(to_pack4(p_vec), to_pack4(p_vec1), 0xFF));
	}

	vec3 cross(vec3 p_vec, vec3 p_vec1) {
		__m128 t1 = to_pack4(p_vec);
		__m128 t2 = to_pack4(p_vec1);

		__m128 t3 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(3, 1, 0, 2));
		__m128 t4 = _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 t5 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 t6 = _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(3, 1, 0, 2));

		__m128 c1 = _mm_mul_ps(t3, t4);
		__m128 c2 = _mm_mul_ps(t5, t6);

		return to_vec3(_mm_sub_ps(c1, c2));
	}

	vec2 angle(vec2 p_vec, vec2 p_vec1) {
		vec2 _t1 = p_vec.normalize();
		vec2 _t2 = p_vec1.normalize();

		_t1 = dot(_t1, _t2);
		return to_vec2(nmmintrin::_acos(to_pack4(_t1)));
	}

	vec3 angle(vec3 p_vec, vec3 p_vec1) {
		vec3 _t1 = p_vec.normalize();
		vec3 _t2 = p_vec1.normalize();

		_t1 = dot(_t1, _t2);
		return to_vec3(nmmintrin::_acos(to_pack4(_t1)));
	}

	vec4 angle(vec4 p_vec, vec4 p_vec1) {
		vec4 _t1 = p_vec.normalize();
		vec4 _t2 = p_vec1.normalize();

		_t1 = dot(_t1, _t2);
		return to_vec4(nmmintrin::_acos(to_pack4(_t1)));
	}

	vec2 reflect(vec2 p_inDir, vec2 p_inNorm) {
		vec2 norm = p_inNorm.normalize();
		return p_inDir - (dot(p_inDir, norm))*norm * 2;
	}

	vec3 reflect(vec3 p_inDir, vec3 p_inNorm) {
		vec3 norm = p_inNorm.normalize();
		return p_inDir - (dot(p_inDir, norm))*norm * 2;
	}

	vec4 reflect(vec4 p_inDir, vec4 p_inNorm) {
		vec4 norm = p_inNorm.normalize();
		return p_inDir - (dot(p_inDir, norm))*norm * 2;
	}

	float distance(vec2 p_start, vec2 p_end) {
		return (p_end - p_start).length();
	}

	float distance(vec3 p_start, vec3 p_end) {
		return (p_end - p_start).length();
	}

	float distance(vec4 p_start, vec4 p_end) {
		return (p_end - p_start).length();
	}
}