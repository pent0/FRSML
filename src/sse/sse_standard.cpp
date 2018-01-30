#include "sse_extensions.h"
#include "sse_standard.h"

namespace frsml {
	namespace nmmintrin {

		__m128 _floor(__m128 p_para) {
			__m128 one = _mm_set1_ps(1.0f);
			__m128 t = _mm_cvtepi32_ps(_mm_cvttps_epi32(p_para));

			__m128 r = _mm_sub_ps(t, _mm_and_ps(_mm_cmplt_ps(p_para, t), one));

			return r;
		}


		__m128 _mod(__m128 x, __m128 y) {
			if (_mm_movemask_ps(_mm_cmpeq_ps(x, y))) {
				return x;
			}

			__m128 m = _mm_sub_ps(x, _mm_mul_ps(y, _floor(_mm_div_ps(x, y))));

			if (_mm_movemask_ps(_mm_cmpgt_ps(y, _mm_set1_ps(0)))) {
				if (_mm_movemask_ps(_mm_cmpge_ps(m, y)))
					return _mm_set1_ps(0);

				if (_mm_movemask_ps(_mm_cmplt_ps(m, _mm_set1_ps(0))))
					return _mm_add_ps(y, m);
			}
			else {
				if (_mm_movemask_ps(_mm_cmple_ps(m, y)))
					return _mm_set1_ps(0);

				if (_mm_movemask_ps(_mm_cmpgt_ps(m, _mm_set1_ps(0))))
					return _mm_add_ps(y, m);
			}

			return m;
		}


		__m128i _abs(__m128i p_para) {
			return _mm_abs_epi32(p_para);
		}

		__m128 _absf(__m128 p_para) {
			__m128 t_sign = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
			return _mm_andnot_ps(t_sign, p_para);
		}

		__m128 _maxf(__m128 p_a, __m128 p_b) {
			return _mm_max_ps(p_a, p_b);
		}

		__m128 _minf(__m128 p_a, __m128 p_b) {
			return _mm_min_ps(p_a, p_b);
		}

		__m128i _max(__m128i p_a, __m128i p_b) {
			return _mm_max_epi32(p_a, p_b);
		}

		__m128i _min(__m128i p_a, __m128i p_b) {
			return _mm_min_epi32(p_a, p_b);
		}

		__m128 _sqrtf(__m128 p_num) {
			return _mm_sqrt_ps(p_num);
		}

		__m128i _sqrt(__m128i p_num) {
			__m128 t_t2 = _mm_cvtepi32_ps(p_num);
			t_t2 = _mm_sqrt_ps(t_t2);

			return _mm_cvtps_epi32(t_t2);
		}

		__m128 _signf(__m128 p_num) {
			const __m128i MASK = _mm_set1_epi32(0xffffffff);

			__m128 a = _mm_setr_ps(1, 1, 1, 1);

			__m128 f = _mm_xor_ps(p_num, a);
			__m128i i = _mm_castps_si128(f);

			i = _mm_srai_epi32(i, 31); i = _mm_xor_si128(i, MASK);
			f = _mm_cvtepi32_ps(i);

			if (_mm_extract_ps(f, 3) == 0) {
				return _mm_set1_ps(-1);
			}

			return _mm_mul_ps(f, _mm_set1_ps(-1));
		}

		inline __m128 balance_to_pi_distance(__m128 p_para) {
			return _mm_sub_ps(_mod(_mm_add_ps(p_para, _mm_set1_ps(PI)), _mm_set1_ps(PI2)), _mm_set1_ps(PI));
		}

		inline __m128 _sin(__m128 p_para)
		{
			__m128 t0 = balance_to_pi_distance(p_para);


			__m128 t1 = _mm_div_ps(_mm_set1_ps(4), _mm_set1_ps(PI));
			__m128 t2 = _mm_div_ps(_mm_set1_ps(-4), _mm_mul_ps(_mm_set1_ps(PI), _mm_set1_ps(PI)));

			__m128 t3 = _mm_set1_ps(0.225f);
			__m128 t4 = _mm_mul_ps(t1, t0);
			__m128 t5 = _mm_mul_ps(t2, _mm_mul_ps(t0, _absf(t0)));

			__m128 t6 = _mm_add_ps(t4, t5);
			__m128 t7 = _mm_mul_ps(t6, _absf(t6));
			t7 = _mm_sub_ps(t7, t6);
			t7 = _mm_mul_ps(t3, t7);
			t7 = _mm_add_ps(t7, t6);

			return t7;
		}


		inline __m128 _cos(__m128 p_para) {
			__m128 t1 = _mm_add_ps(p_para, _mm_set1_ps(PID2));
			return _sin(t1);
		}

		inline __m128 _tan(__m128 p_para) {
			__m128 t1 = _sin(p_para);
			__m128 t2 = _cos(p_para);
			return _mm_div_ps(t1, t2);
		}

		inline __m128 _cot(__m128 p_para) {
			__m128 t1 = _cos(p_para);
			__m128 t2 = _sin(p_para);

			return _mm_div_ps(t1, t2);
		}

		inline __m128 _asin(__m128 p_para) {
			__m128 t1 = _mm_cmplt_ps(p_para, _mm_set1_ps(0));
			__m128 t2 = _absf(p_para);
			__m128 t3 = _mm_set1_ps(-0.0187293f);
			__m128 t4 = _mm_mul_ps(t3, t2);

			t4 = _mm_add_ps(t4, _mm_set1_ps(0.0742610f));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_sub_ps(t4, _mm_set1_ps(0.2121144f));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_add_ps(t4, _mm_set1_ps(1.5707288f));
			t4 = _mm_mul_ps(t4, _sqrtf(_mm_sub_ps(_mm_set1_ps(1), t2)));

			__m128 t5 = _mm_sqrt_ps(_mm_sub_ps(_mm_set1_ps(1), t2));
			__m128 t6 = _mm_mul_ps(t4, t5);
			t4 = _mm_sub_ps(_mm_set1_ps(PID2), t6);
			__m128 t7 = _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(2), t1), t4);
			t4 = _mm_sub_ps(t4, t7);

			return t4;
		}

		inline __m128 _acos(__m128 p_para) {
			__m128 t1 = _mm_cmplt_ps(p_para, _mm_set1_ps(0));
			__m128 t2 = _absf(p_para);
			__m128 t3 = _mm_set1_ps(-0.0187293f);
			__m128 t4 = _mm_mul_ps(t3, t2);
			t4 = _mm_add_ps(t4, _mm_set1_ps(0.0742610f));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_sub_ps(t4, _mm_set1_ps(0.2121144f));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_add_ps(t4, _mm_set1_ps(1.5707288f));
			t4 = _mm_mul_ps(t4, _sqrtf(_mm_sub_ps(_mm_set1_ps(1), t2)));
			__m128 t5 = _mm_mul_ps(_mm_set1_ps(2), t1);
			__m128 t6 = _mm_mul_ps(t5, t4);
			t4 = _mm_sub_ps(t4, t6);
			__m128 t7 = _mm_mul_ps(t1, _mm_set1_ps(PI));
			return _mm_add_ps(t7, t4);
		}

		inline __m128 _atan2(__m128 p_y, __m128 p_x) {
			__m128 t1 = _absf(p_y);
			__m128 t2 = _absf(p_x);
			__m128 t3 = _maxf(t1, t2);
			__m128 t4 = _minf(t1, t2);

			t1 = _mm_div_ps(_mm_set1_ps(1), t3);
			t1 = _mm_mul_ps(t1, t4);
			__m128 t6 = _mm_mul_ps(t1, t1);
			t3 = _mm_set1_ps(-0.013480470f);
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_add_ps(t3, _mm_set1_ps(0.057477314f));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_sub_ps(t3, _mm_set1_ps(0.121239071f));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_add_ps(t3, _mm_set1_ps(0.195635925f));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_sub_ps(t3, _mm_set1_ps(0.332994597f));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_add_ps(t3, _mm_set1_ps(0.999995630f));
			t1 = _mm_mul_ps(t3, t1);

			__m128 t7 = _mm_cmpgt_ps(_absf(p_x), _absf(p_y));
			__m128 t8 = _mm_and_ps(t7, _mm_sub_ps(_mm_set1_ps(1.570796327f), t1));
			__m128 t9 = _mm_and_ps(sse_extensions::_mm_not_ps(t7), t1);
			
			t1 = _mm_or_ps(t8, t9);

			t7 = _mm_cmplt_ps(p_y, _mm_set1_ps(0));
			t8 = _mm_and_ps(t7, _mm_sub_ps(_mm_set1_ps(PI), t1));
			t9 = _mm_and_ps(sse_extensions::_mm_not_ps(t7), t1);
			t1 = _mm_or_ps(t8, t9);

			t7 = _mm_cmplt_ps(p_x, _mm_set1_ps(0));
			t8 = _mm_and_ps(t7, _mm_sub_ps(_mm_set1_ps(0), t1));
			t9 = _mm_and_ps(sse_extensions::_mm_not_ps(t7), t1);
			t1 = _mm_or_ps(t8, t9);

			return t1;
		}

		inline __m128 _atan(__m128 p_x) {
			return _atan2(p_x, _mm_set1_ps(1));
		}

		inline __m128 _pow(__m128 p_x, __m128 p_y) {
			__m128 tmp = _log(p_x);
			__m128 tmp2 = _mm_mul_ss(p_x, p_y);

			tmp2 = _exp(tmp2);

			return tmp2;
		}

		inline __m128 _exp(__m128 p_para) {
			__m128 tmp = _mm_setzero_ps();
			__m128 x = p_para;
			__m128 fx; __m128i emm0;

			__m128 oneD = *(__m128*)_F_1;


			//Set back to its origin, basically clamp
			x = _mm_min_ps(x, *(__m128*)_F_exp_upper);
			x = _mm_max_ps(x, *(__m128*)_F_exp_lower);

			fx = _mm_mul_ps(x, *(__m128*)_F_cephes_log2);
			fx = _mm_add_ps(fx, *(__m128*)_F_half);

			emm0 = _mm_cvttps_epi32(fx);
			tmp = _mm_cvtepi32_ps(emm0);

			__m128 flag = _mm_cmpgt_ps(tmp, fx);
			flag = _mm_and_ps(flag, oneD);
			fx = _mm_sub_ps(tmp, flag);

			tmp = _mm_mul_ps(fx, *(__m128*)_F_cephes_c1);
			__m128 tmp2 = _mm_mul_ps(fx, *(__m128*)_F_cephes_c2);
			x = _mm_sub_ps(x, _mm_add_ps(tmp, tmp2));

			__m128 z = _mm_mul_ps(x, x);
			__m128 y = *(__m128*)_F_cephes_p0;
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_p1);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_p2);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_p3);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_p4);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_p5);
			y = _mm_mul_ps(y, z);
			y = _mm_add_ps(y, x);
			y = _mm_add_ps(y, oneD);

			emm0 = _mm_cvtps_epi32(fx);
			emm0 = _mm_add_epi32(emm0, *(__m128i*)_I_triplemask);
			emm0 = _mm_slli_epi32(emm0, 23);
			__m128 pow2n = _mm_castsi128_ps(emm0);

			y = _mm_mul_ps(y, pow2n);
			return y;
		}

		inline __m128 _log(__m128 p_para) {
			__m128i emm0;

			__m128 one = *(__m128*)_F_1;
			__m128 x = p_para;

			__m128 invalid_mask = _mm_cmple_ps(x, _mm_setzero_ps());

			x = _mm_max_ps(x, *(__m128*)_I_min_norm_pos);

			emm0 = _mm_srli_epi32(_mm_castps_si128(x), 23);

			x = _mm_and_ps(x, *(__m128*)_I_inv_mant_mask);
			x = _mm_or_ps(x, *(__m128*)_F_half);

			emm0 = _mm_sub_epi32(emm0, *(__m128i*)_I_triplemask);
			__m128 e = _mm_cvtepi32_ps(emm0);

			e = _mm_add_ps(e, one);

			__m128 mask = _mm_cmplt_ps(x, *(__m128*)_F_cephes_SQRTHF);
			__m128 tmp = _mm_and_ps(x, mask);

			x = _mm_sub_ps(x, one);
			e = _mm_sub_ps(e, _mm_and_ps(one, mask));
			x = _mm_add_ps(x, tmp);



			__m128 z = _mm_mul_ps(x, x);

			__m128 y = *(__m128*)_F_cephes_log_p0;
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p1);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p2);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p3);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p4);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p5);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p6);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p7);
			y = _mm_mul_ps(y, x);
			y = _mm_add_ps(y, *(__m128*)_F_cephes_log_p8);
			y = _mm_mul_ps(y, _mm_mul_ps(x, z));

			tmp = _mm_mul_ps(e, *(__m128*)_F_cephes_log_q1);
			y = _mm_add_ps(y, tmp);

			//Precision
			tmp = _mm_mul_ps(z, *(__m128*)_F_half);
			y = _mm_sub_ps(y, tmp);

			tmp = _mm_mul_ps(e, *(__m128*)_F_cephes_log_q2);
			x = _mm_add_ps(x, _mm_add_ps(y, tmp));
			x = _mm_or_ps(x, invalid_mask);

			return x;
		}
	}
	}


}