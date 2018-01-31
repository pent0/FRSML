#ifndef FRSML_IMPL_SSE_SSE_EXTENSIONS
#define FRSML_IMPL_SSE_SSE_EXTENSIONS

#include "../math_internal.h"

namespace frs {
	namespace sse_extensions {
		float   FRS_MATH_API _mm_extract_psn(__m128 p_para, int p_pos);
		__m128  FRS_MATH_API _mm_not_ps(__m128 p_para);
		__m128i FRS_MATH_API _mm_not_epi32(__m128i p_para);
		__m128i FRS_MATH_API _mm_div_epi32(__m128i p_para1, __m128i p_para2);
	}
}

#endif
