#include <frsml/quat.h>
#include <frsml/vector.h>

#include "sse/sse_standard.h"
#include "math_internal.h"

namespace frsml {
	quat::quat() : vec4() {};
	quat::quat(float w, float x, float y, float z) :
		vec4(x, y, z, w) {};

	inline quat quat::operator * (quat p_quat) {
		__m128 t_main1 = to_pack4(static_cast<vec4>(*this));
		__m128 t_main2 = to_pack4(static_cast<vec4>(p_quat));

		__m128 t1 = _mm_shuffle_ps(t_main1, t_main1, MASK3);
		__m128 t2 = _mm_shuffle_ps(t_main1, t_main1, MASK2);
		__m128 t3 = _mm_shuffle_ps(t_main1, t_main1, MASK1);
		__m128 t4 = _mm_shuffle_ps(t_main1, t_main1, MASK0);

		__m128 t_res0; {
			__m128 c0 = _mm_shuffle_ps(t_main2, t_main2, _MM_SHUFFLE(3, 2, 1, 0));
			t_res0 = _mm_mul_ps(t1, c0);
		}

		__m128 t_res1; {
			__m128 c1 = _mm_shuffle_ps(t_main2, t_main2, _MM_SHUFFLE(2, 3, 0, 1));
			t_res1 = _mm_mul_ps(t2, c1);
		}

		__m128 t_res2; {
			__m128 c2 = _mm_shuffle_ps(t_main2, t_main2, _MM_SHUFFLE(1, 0, 3, 2));
			t_res2 = _mm_mul_ps(t3, c2);
		}

		__m128 t_res3; {
			__m128 c3 = _mm_shuffle_ps(t_main2, t_main2, _MM_SHUFFLE(0, 1, 2, 3));
			t_res3 = _mm_mul_ps(t4, c3);
		}

		t_res1 = _mm_mul_ps(t_res0, _mm_set_ps(-1, 1, -1, 1));
		t_res2 = _mm_mul_ps(t_res1, _mm_set_ps(-1, 1, 1, -1));
		t_res3 = _mm_mul_ps(t_res2, _mm_set_ps(-1, -1, 1, 1));

		t_res0 = _mm_add_ps(t_res0, _mm_add_ps(t_res1, _mm_add_ps(t_res2, t_res3)));

		vec4 t_res = to_vec4(t_res0);

		return quat(t_res.w, t_res.x, t_res.y, t_res.z);
	}

	quat quat::euler(vec3 p_euler) {
		__m128 t_temp = _mm_div_ps(_mm_mul_ps(to_pack4(p_euler), _mm_set1_ps(PI)), _mm_set1_ps(180));

		__m128 t1 = _mm_shuffle_ps(t_temp, t_temp, MASK2);
		__m128 t2 = _mm_shuffle_ps(t_temp, t_temp, MASK1);
		__m128 t3 = _mm_shuffle_ps(t_temp, t_temp, MASK0);

		t1 = _mm_div_ps(t1, _mm_set1_ps(2));
		t2 = _mm_div_ps(t2, _mm_set1_ps(2));
		t3 = _mm_div_ps(t3, _mm_set1_ps(2));

		__m128 t4 = nmmintrin::_cos(t3);
		__m128 t5 = nmmintrin::_sin(t3);
		__m128 t6 = nmmintrin::_cos(t1);
		__m128 t7 = nmmintrin::_sin(t1);
		__m128 t8 = nmmintrin::_cos(t2);
		__m128 t9 = nmmintrin::_sin(t2);

		__m128 t_quatW = _mm_mul_ps(t4, _mm_mul_ps(t6, t8));
		t_quatW = _mm_add_ps(t_quatW, _mm_mul_ps(t5, _mm_mul_ps(t7, t9)));

		__m128 t_quatX = _mm_mul_ps(t4, _mm_mul_ps(t7, t8));
		t_quatX = _mm_sub_ps(t_quatX, _mm_mul_ps(t5, _mm_mul_ps(t6, t9)));

		__m128 t_quatY = _mm_mul_ps(t4, _mm_mul_ps(t6, t9));
		t_quatY = _mm_add_ps(t_quatY, _mm_mul_ps(t5, _mm_mul_ps(t7, t8)));

		__m128 t_quatZ = _mm_mul_ps(t5, _mm_mul_ps(t6, t8));
		t_quatZ = _mm_sub_ps(t_quatZ, _mm_mul_ps(t4, _mm_mul_ps(t7, t9)));

		float w = _mm_cvtss_f32(t_quatW);
		float x = _mm_cvtss_f32(t_quatX);
		float y = _mm_cvtss_f32(t_quatY);
		float z = _mm_cvtss_f32(t_quatZ);

		return quat(w, x, y, z);
	}

	quat quat::rotate(vec3 p_axis, float p_angle) {
		__m128 tmp = to_pack4(p_axis.normalize());

		__m128 tmp2 = (_mm_div_ps(_mm_set1_ps(p_angle), _mm_set1_ps(2)));
		__m128 tmp3 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 tmp4 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 tmp5 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(0, 0, 0, 0));

		__m128 quatW = nmmintrin::_cos(tmp2);
		__m128 quatX = _mm_mul_ps(nmmintrin::_sin(tmp2), tmp3);
		__m128 quatY = _mm_mul_ps(nmmintrin::_sin(tmp2), tmp4);
		__m128 quatZ = _mm_mul_ps(nmmintrin::_sin(tmp2), tmp5);

		float w = _mm_cvtss_f32(quatW);
		float x = _mm_cvtss_f32(quatX);
		float y = _mm_cvtss_f32(quatY);
		float z = _mm_cvtss_f32(quatZ);

		return quat(w, x, y, z);
	}

	quat quat::normalize(){
#ifdef FRS_OPTIMIZED
		__m128 t_vec = to_pack4(*this);
		__m128 t_rlength = _mm_sqrt_ps(_mm_dp_ps(t_vec, t_vec, 0x33));

		return to_vec2(_mm_div_ps(t_vec, t_rlength));
#else
		float t_length = length();

		return quat(x / t_length, y / t_length, z / t_length,
			w / t_length);
#endif
	}

	quat::operator mat4() {
		__m128 t_mainQuat = 
			to_pack4(*this);

		quat t_temp = normalize();

		__m128 t_quatX = _mm_shuffle_ps(t_mainQuat, t_mainQuat, MASK2);
		t_quatX = _mm_set_ps(0, 0, 0, sse_extensions::_mm_extract_psn(t_quatX, 0));
		__m128 t_quatY = _mm_shuffle_ps(t_mainQuat, t_mainQuat, MASK1);
		t_quatX = _mm_set_ps(0, 0, 0, sse_extensions::_mm_extract_psn(t_quatX, 0));
		__m128 t_quatZ = _mm_shuffle_ps(t_mainQuat, t_mainQuat, MASK0);
		t_quatX = _mm_set_ps(0, 0, 0, sse_extensions::_mm_extract_psn(t_quatX, 0));
		__m128 t_quatW = _mm_shuffle_ps(t_mainQuat, t_mainQuat, MASK3);
		t_quatX = _mm_set_ps(0, 0, 0, sse_extensions::_mm_extract_psn(t_quatX, 0));

		__m128 tem1; {
			__m128 g1 = nmmintrin::_pow(t_quatY, _mm_set1_ps(2));
			__m128 g2 = nmmintrin::_pow(t_quatZ, _mm_set1_ps(2));
			g1 = _mm_add_ss(g1, g2);
			tem1 = _mm_sub_ss(_mm_set1_ps(1), g1);
			tem1 = _mm_shuffle_ps(tem1, tem1, _MM_SHUFFLE(0, 3, 3, 3));
		};


		__m128 tem2; {
			__m128 g1 = nmmintrin::_pow(t_quatX, _mm_set1_ps(2));
			__m128 g2 = nmmintrin::_pow(t_quatY, _mm_set1_ps(2));
			g1 = _mm_add_ss(g1, g2);
			tem2 = _mm_sub_ss(_mm_set1_ps(1), g1);
			tem2 = _mm_shuffle_ps(tem2, tem2, _MM_SHUFFLE(3, 3, 0, 3));
		};

		__m128 tem3; {
			__m128 g1 = nmmintrin::_pow(t_quatX, _mm_set1_ps(2));
			__m128 g2 = nmmintrin::_pow(t_quatZ, _mm_set1_ps(2));
			g1 = _mm_add_ss(g1, g2);
			tem3 = _mm_sub_ss(_mm_set1_ps(1), g1);
			tem3 = _mm_shuffle_ps(tem3, tem3, _MM_SHUFFLE(3, 0, 3, 3));
		};

		__m128 tem4; {
			__m128 g1 = _mm_mul_ss(t_quatX, t_quatY);
			__m128 g2 = _mm_mul_ss(t_quatW, t_quatZ);
			g1 = _mm_add_ss(g1, g2);
			tem4 = _mm_add_ss(_mm_set1_ps(2), g1);
			tem4 = _mm_shuffle_ps(tem4, tem4, _MM_SHUFFLE(0, 3, 3, 3));
		}

		__m128 tem5; {
			__m128 g1 = _mm_mul_ss(t_quatX, t_quatZ);
			__m128 g2 = _mm_mul_ss(t_quatW, t_quatY);
			g1 = _mm_add_ss(g1, g2);
			tem5 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem5 = _mm_shuffle_ps(tem5, tem5, _MM_SHUFFLE(3, 3, 0, 3));
		}

		__m128 tem6; {
			__m128 g1 = _mm_mul_ss(t_quatY, t_quatZ);
			__m128 g2 = _mm_mul_ps(t_quatW, t_quatX);
			g1 = _mm_add_ss(g1, g2);
			tem6 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem6 = _mm_shuffle_ps(tem6, tem6, _MM_SHUFFLE(3, 3, 0, 3));
		}

		__m128 tem7; {
			__m128 g1 = _mm_mul_ss(t_quatX, t_quatY);
			__m128 g2 = _mm_mul_ss(t_quatW, t_quatZ);
			g1 = _mm_sub_ss(g1, g2);
			tem7 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem7 = _mm_shuffle_ps(tem7, tem7, _MM_SHUFFLE(3, 0, 3, 3));
		}

		__m128 tem8; {
			__m128 g1 = _mm_mul_ss(t_quatX, t_quatZ);
			__m128 g2 = _mm_mul_ss(t_quatW, t_quatY);
			g1 = _mm_sub_ss(g1, g2);
			tem8 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem8 = _mm_shuffle_ps(tem8, tem8, _MM_SHUFFLE(0, 3, 3, 3));
		}

		__m128 tem9; {
			__m128 g1 = _mm_mul_ss(t_quatY, t_quatZ);
			__m128 g2 = _mm_mul_ss(t_quatW, t_quatX);
			g1 = _mm_sub_ss(g1, g2);
			tem9 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem9 = _mm_shuffle_ps(tem9, tem9, _MM_SHUFFLE(0, 3, 3, 3));
		}

		__m128 tem0 = _mm_set_ps(0, 0, 0, 1);

		__m128 tem10 = _mm_xor_ps(tem1, _mm_xor_ps(tem5, tem7));
		__m128 tem11 = _mm_xor_ps(tem4, _mm_xor_ps(tem3, tem6));
		__m128 tem12 = _mm_xor_ps(tem8, _mm_xor_ps(tem9, tem2));
		__m128 tem13 = _mm_xor_ps(_mm_setzero_ps(), tem0);

		vec4 t_cols[4];

		t_cols[0] = to_vec4(tem10);
		t_cols[1] = to_vec4(tem11);
		t_cols[2] = to_vec4(tem12);
		t_cols[3] = to_vec4(tem13);

		return mat4(t_cols).transpose();
	}
}