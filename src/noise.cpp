#include <frsml/noise.h>
#include <random>

#include "math_internal.h"
#include "sse/sse_standard.h"

namespace frsml {
	const int permutations[] = { 151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};

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

	__m128 perlin(__m128 x, __m128 y, __m128 z, const int* p) {
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

		__m128i aaa = _mm_set1_epi32(p[p[p[x1] +y1] +z1]);
		__m128i aba = _mm_set1_epi32(p[p[p[x1] + y1 + 1] + z1]);
		__m128i aab = _mm_set1_epi32(p[p[p[x1] + y1] + z1+1]);
		__m128i abb = _mm_set1_epi32(p[p[p[x1] + y1+1] + z1 + 1]);
		__m128i baa = _mm_set1_epi32(p[p[p[x1+1] + y1] + z1]);
		__m128i bba = _mm_set1_epi32(p[p[p[x1+1] + y1+1] + z1]);
		__m128i bab = _mm_set1_epi32(p[p[p[x1+1] + y1] + z1 + 1]);
		__m128i bbb = _mm_set1_epi32(p[p[p[x1+1] + y1+1] + z1 + 1]);


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