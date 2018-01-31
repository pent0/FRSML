#include <frsml/standard.h>
#include <frsml/vector.h>

#ifdef FRSML_SSE
	#include "sse/sse_standard.h"
#else
	#include "norm/norm_standard.h"
#endif

namespace frsml {

	float exp(float x) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_exp(_mm_set1_ps(x)));
#else
		return norm::_exp(x);
#endif
	}

	float log(float x) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_log(_mm_set1_ps(x)));
#else
		return norm::_log(x);
#endif
	}

	float log2(float x) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(
			_mm_div_ps(nmmintrin::_exp(_mm_set1_ps(x))
				, _mm_set1_ps(static_cast<float>(LOG2))));
#else
		return norm::_log2(x);
#endif
	}

	float log(float x, float base) {
		return exp(x) / log(base);
	}

	float pow(float x, float y) {
#ifdef FRSML_SSE
		__m128 tmp = _mm_set_ss(x);
		__m128 tmp2 = _mm_set_ss(y);

		tmp = nmmintrin::_log(tmp);
		tmp2 = _mm_mul_ss(tmp, tmp2);

		tmp2 = nmmintrin::_exp(tmp2);

		return _mm_cvtss_f32(tmp2);
#else
		return norm::_pow(x, y);
#endif
	}

	float abs(float p_num) {
		return (p_num < 0) ? (-p_num) : (p_num);
	}

	float clamp(float p_t1, float p_t2, float p_crrNumber) {
		return (p_t1 > p_crrNumber) ? (p_t1) :
			((p_t2 < p_crrNumber) ? (p_t2) : (p_crrNumber));
	}

	float lerp(float p_t, float p_a, float p_b) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_lerp(_mm_set1_ps(p_a), _mm_set1_ps(p_b), _mm_set1_ps(p_t)));
#else
		return (p_b - p_a) * p_t + p_a;
#endif
	}

	int sign(float p_num) {
		return (p_num < 0) ? -1 : ((p_num > 0) ? 1 : 0);
	}

	float sin(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_sin(_mm_set1_ps(p_num)));
#else
		return norm::_sin(p_num);
#endif
	}

	float cos(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_cos(_mm_set1_ps(p_num)));
#else
		return norm::_cos(p_num);
#endif
	}

	float tan(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_tan(_mm_set1_ps(p_num)));
#else
		return norm::_cos(p_num);
#endif
	}

	float cot(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_cot(_mm_set1_ps(p_num)))
#else
		return 1 / tan(p_num);
#endif
	}

	float fade(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_fade(_mm_set1_ps(p_num)));
#else
		return pow(p_num, 3) * (p_num * (p_num * 6 - 15) + 10);
#endif
	}


	void sin_cos(float p_x, float* p_s, float* p_c) {
#ifdef FRSML_SSE
		__m128 t_both = _mm_set_ps(0, 0, p_x + PID2, p_x);
		__m128 t_sincos = nmmintrin::_sin(t_both);

		__m128 t_cos = _mm_shuffle_ps(t_sincos, t_sincos, _MM_SHUFFLE(0, 0, 0, 1));
		*p_s = _mm_cvtss_f32(t_sincos);
		*p_c = _mm_cvtss_f32(t_cos);
#else
		*p_s = sin(p_x);
		*p_c = cos(p_x);
#endif
	}

	float asin(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_asin(_mm_set1_ps(p_num)));
#else
		return norm::asin(p_num);
#endif
	}

	float acos(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_acos(_mm_set1_ps(p_num)));
#else
		return norm::acos(p_num);
#endif
	}

	float atan(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_atan(_mm_set1_ps(p_num)));
#else
		return norm::atan(p_num);
#endif
	}

	float atan2(float p_y, float p_x) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_atan2(_mm_set1_ps(p_y), _mm_set1_ps(p_x)));
#else
		return norm::atan2(p_y, p_x);
#endif
	}

	float maxf(float p_num, float p_num1) {
		return (p_num < p_num1) ? p_num1 : p_num;
	}

	float minf(float p_num, float p_num1) {
		return (p_num < p_num1) ? p_num : p_num1;
	}

	float sqrt(float p_num) {
#ifdef FRSML_SSE
		return _mm_cvtss_f32(nmmintrin::_sqrtf(_mm_set1_ps(p_num)));
#else
		return norm::sqrt(p_num);
#endif
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
#ifdef FRSML_SSE
		return to_vec2(
			_mm_dp_ps(to_pack4(p_vec), to_pack4(p_vec1), 0x33));
#else
		vec2 temp = p_vec * p_vec1;
		return vec2(temp.x + temp.y, temp.x + temp.y);
#endif
	}

	vec3 dot(vec3 p_vec, vec3 p_vec1) {
#ifdef FRSML_SSE
		return to_vec3(
			_mm_dp_ps(to_pack4(p_vec), to_pack4(p_vec1), 0x77));
#else
		vec3 temp = p_vec * p_vec1;
		float dp = temp.x + temp.y + temp.z;
		
		return vec3(dp, dp, dp);
#endif
	}

	vec4 dot(vec4 p_vec, vec4 p_vec1) {
#ifdef FRSML_SSE
		return to_vec4(
			_mm_dp_ps(to_pack4(p_vec), to_pack4(p_vec1), 0xFF));
#else
		vec4 temp = p_vec * p_vec1;
		float dp = temp.x + temp.y + temp.z + temp.w;
		
		return vec4(dp, dp, dp, dp);
#endif
	}

	vec3 cross(vec3 p_vec, vec3 p_vec1) {
#ifdef FRSML_SSE
		__m128 t1 = to_pack4(p_vec);
		__m128 t2 = to_pack4(p_vec1);

		__m128 t3 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(3, 1, 0, 2));
		__m128 t4 = _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 t5 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 t6 = _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(3, 1, 0, 2));

		__m128 c1 = _mm_mul_ps(t3, t4);
		__m128 c2 = _mm_mul_ps(t5, t6);

		return to_vec3(_mm_sub_ps(c1, c2));
#else
		return vec3(p_vec.y * p_vec1.z - p_vec.z * p_vec1.y,
					p_vec.z * p_vec1.x - p_vec.x * p_vec1.z,
					p_vec.x * p_vec1.y - p_vec.y * p_vec1.x);
#endif
	}

	vec2 angle(vec2 p_vec, vec2 p_vec1) {
		vec2 _t1 = p_vec.normalize();
		vec2 _t2 = p_vec1.normalize();

		_t1 = dot(_t1, _t2);
		return vec2(acos(_t1.x), acos(_t1.x));
	}

	vec3 angle(vec3 p_vec, vec3 p_vec1) {
		vec3 _t1 = p_vec.normalize();
		vec3 _t2 = p_vec1.normalize();

		_t1 = dot(_t1, _t2);
		return vec3(acos(_t1.x), acos(_t1.x), acos(_t1.x));
	}

	vec4 angle(vec4 p_vec, vec4 p_vec1) {
		vec4 _t1 = p_vec.normalize();
		vec4 _t2 = p_vec1.normalize();

		_t1 = dot(_t1, _t2);
		return vec4(acos(_t1.x), acos(_t1.x), acos(_t1.x), acos(_t1.x));
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