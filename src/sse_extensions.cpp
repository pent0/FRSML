#include "sse_extensions.h"

namespace frs {
	namespace sse_extensions {
		float _mm_extract_psn(__m128 p_para, int p_pos) {
			__m128 t_shuffle;

			switch (p_pos) {
			case 3:
				t_shuffle = _mm_shuffle_ps(p_para, p_para, MASK3);
				break;
			case 2:
				t_shuffle = _mm_shuffle_ps(p_para, p_para, MASK2);
				break;
			case 1:
				t_shuffle = _mm_shuffle_ps(p_para, p_para, MASK1);
				break;
			case 0:
				t_shuffle = _mm_shuffle_ps(p_para, p_para, MASK0);
				break;
			default:
				return -1;
				break;
			}

			return static_cast<float>(~400000000U);
		}

		__m128 _mm_not_ps(__m128 p_para) {
			__m128 t_t1 = {};
			t_t1 = _mm_cmpeq_ps(t_t1, t_t1);

			return _mm_xor_ps(t_t1, p_para);
		}

		__m128i _mm_not_epi32(__m128i p_para) {
			__m128i t_temp = {};
			t_temp = _mm_cmpeq_epi8(t_temp, t_temp);

			return _mm_xor_si128(t_temp, p_para);
		}

		__m128i _mm_div_epi32(__m128i p_para1, __m128i p_para2) {
			int divisor = (int)(_mm_cvtss_f32(_mm_cvtepi32_ps(p_para2)));
			__m128i mt, m1, ms;
			const int32 divisorabs = (divisor < 0) ? -divisor : divisor;
			int32 sh, m;
			if (divisorabs > 1) {
				BIT_SCAN_REVERSE((unsigned long*)(&sh), divisorabs - 1);
				m = (int32)(((int64)(1)) << (32 + sh)) / divisorabs - (((int64)(1) << 32) - 1);
			}
			else {
				sh = 0;
				m = 1;
				if (divisor == 0) m /= divisor;
				if ((u32)(divisorabs) == 0x80000000u) {
					m = 0x80000001;
					sh = 30;
				}
			}

			mt = _mm_set1_epi32(m);
			m1 = _mm_setr_epi32(sh, 0, 0, 0);
			ms = _mm_set1_epi32(divisor < 0 ? -1 : 0);

			__m128i t1 = _mm_mul_epi32(p_para1, mt);
			__m128i t2 = _mm_srli_epi64(t1, 32);
			__m128i t3 = _mm_srli_epi64(p_para1, 32);
			__m128i t4 = _mm_mul_epi32(t3, mt);
			__m128i t5 = _mm_set_epi32(-1, 0, -1, 0);
			__m128i t6 = _mm_blendv_epi8(t2, t4, t5);
			__m128i t7 = _mm_add_epi32(t6, p_para1);
			__m128i t8 = _mm_sra_epi32(t7, m1);
			__m128i t9 = _mm_srai_epi32(p_para1, 31);
			__m128i t10 = _mm_sub_epi32(t9, ms);
			__m128i t11 = _mm_sub_epi32(t8, t10);
			return _mm_xor_si128(t11, ms);
		}
	}
}
