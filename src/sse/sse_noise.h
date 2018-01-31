#ifndef FRSML_IMPL_SSE_SSE_NOISE
#define FRSML_IMPL_SSE_SSE_NOISE

#include "../math_internal.h"

namespace frsml {
	namespace nmmintrin {
		namespace noise {
			__m128 _grad(__m128i hash, __m128 x, __m128 y, __m128 z);
			__m128 _perlin(__m128 x, __m128 y, __m128 z, const int* p);
		}
	}
}

#endif
