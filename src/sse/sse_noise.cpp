#include "sse_noise.h"
#include "sse_standard.h"

namespace frsml {
	namespace nmmintrin {
		namespace noise {
			__m128 _grad(__m128i hash, __m128 x, __m128 y, __m128 z) {
				__m128i h = _mm_and_si128(hash, _mm_set1_epi32(15));
				__m128 u = _mm_extract_epi32(h, 3) < 8 ? x : y;

				int h2 = _mm_extract_epi32(h, 3);

				__m128 v = {};

				if (h2 < 4) {
					v = y;
				}
				else if (h2 == 12 || h2 == 14) {
					v = x;
				}
				else {
					v = z;
				}

				return _mm_add_ps(((h2 & 1) == 0 ? v : _mm_sub_ps(_mm_set1_ps(0), v))
					, ((h2 & 2 == 0) ? v : _mm_sub_ps(_mm_set1_ps(0), v)));
			}

			__m128 _perlin(__m128 x, __m128 y, __m128 z, const int* p) {
				__m128i t1r = _mm_set1_epi32(255);
				__m128 t2 = x;
				__m128 t3 = y;
				__m128 t4 = z;

				__m128i t11 = _mm_cvtps_epi32(t2);
				__m128i t12 = _mm_cvtps_epi32(t3);
				__m128i t13 = _mm_cvtps_epi32(t4);

				__m128i xi = _mm_and_si128(xi, t1r);
				__m128i yi = _mm_and_si128(yi, t1r);
				__m128i zi = _mm_and_si128(zi, t1r);

				__m128 xf = _mm_sub_ps(t2, _mm_round_ps(t2, 0x3));
				__m128 yf = _mm_sub_ps(t3, _mm_round_ps(t3, 0x3));
				__m128 zf = _mm_sub_ps(t4, _mm_round_ps(t4, 0x3));

				__m128 u = nmmintrin::_fade(xf);
				__m128 v = nmmintrin::_fade(yf);
				__m128 w = nmmintrin::_fade(zf);

				int x1 = _mm_extract_epi32(t11, 3);
				int y1 = _mm_extract_epi32(t12, 3);
				int z1 = _mm_extract_epi32(t13, 3);

				__m128i aaa = _mm_set1_epi32(p[p[p[x1] + y1] + z1]);
				__m128i aba = _mm_set1_epi32(p[p[p[x1] + y1 + 1] + z1]);
				__m128i aab = _mm_set1_epi32(p[p[p[x1] + y1] + z1 + 1]);
				__m128i abb = _mm_set1_epi32(p[p[p[x1] + y1 + 1] + z1 + 1]);
				__m128i baa = _mm_set1_epi32(p[p[p[x1 + 1] + y1] + z1]);
				__m128i bba = _mm_set1_epi32(p[p[p[x1 + 1] + y1 + 1] + z1]);
				__m128i bab = _mm_set1_epi32(p[p[p[x1 + 1] + y1] + z1 + 1]);
				__m128i bbb = _mm_set1_epi32(p[p[p[x1 + 1] + y1 + 1] + z1 + 1]);


				__m128 i1 = _mm_set1_ps(1);

				__m128 px1 = nmmintrin::_lerp(_grad(aaa, xf, yf, zf),
					_grad(baa, _mm_sub_ps(xf, i1), yf, zf),
					u);

				__m128 px2 = nmmintrin::_lerp(_grad(aba, xf, _mm_sub_ps(yf, i1), zf),
					_grad(baa, _mm_sub_ps(xf, i1), _mm_sub_ps(yf, i1), zf),
					u);

				__m128 py1 = nmmintrin::_lerp(px1, px2, v);

				px1 = nmmintrin::_lerp(_grad(aab, xf, yf, _mm_sub_ps(zf, i1)),
					_grad(bab, _mm_sub_ps(xf, i1), yf, _mm_sub_ps(zf, i1)),
					u);

				px2 = nmmintrin::_lerp(_grad(abb, xf, _mm_sub_ps(yf, i1), _mm_sub_ps(zf, i1)),
					_grad(bbb, _mm_sub_ps(xf, i1), _mm_sub_ps(yf, i1), _mm_sub_ps(zf, i1)),
					u);

				__m128 py2 = nmmintrin::_lerp(px1, px2, v);

				__m128 t5 = nmmintrin::_lerp(py1, py2, w);
				__m128 t6 = _mm_set1_ps(2);

				t5 = _mm_add_ps(t5, i1);
				return _mm_div_ps(t5, t6);
			}
		}
	}
}