/*
	MATH INTERNAL HEADER
*/

#pragma once

#include <nmmintrin.h>

#include "..\include\fmath.h"

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef _MSC_VER
#define BIT_SCAN_REVERSE _BitScanReverse
#endif

#define EXP2_TABLE_SIZE_LOG2 9
#define MGNBR1 531.7555982144694 
#define MGNBR2 32.521961561056756
#define MGNBR3 9.47803843894324
#define MGNBR4 5040
#define LOG2 1.44269504088896340736 

#define DOUBLE_CONST(Key, v) \
    static const __declspec(align(16)) double _F_##Key[4] = { v,v,v, v }

#define INT_CONST(Key, v) \
    static const __declspec(align(16)) int _I_##Key[4] = {v, v, v, v}

#define MASK3 255
#define MASK2 170
#define MASK1 85
#define MASK0 0

#define GET_MASK(p_num) MASK##p_num

namespace frs {

	DOUBLE_CONST(1, 1.0f);
	DOUBLE_CONST(half, 0.5f);

	DOUBLE_CONST(cephes_log2, 1.44269504088896341);
	DOUBLE_CONST(cephes_c1, 0.693359375);
	DOUBLE_CONST(cephes_c2, -2.12194440e-4);

	DOUBLE_CONST(cephes_p0, 1.9875691500E-4);
	DOUBLE_CONST(cephes_p1, 1.3981999507E-3);
	DOUBLE_CONST(cephes_p2, 8.3334519073E-3);
	DOUBLE_CONST(cephes_p3, 4.1665795894E-2);
	DOUBLE_CONST(cephes_p4, 1.6666665459E-1);
	DOUBLE_CONST(cephes_p5, 5.0000001201E-1);

	INT_CONST(min_norm_pos, 0x00800000);
	INT_CONST(mant_mask, 0x7f800000);
	INT_CONST(inv_mant_mask, ~0x7f800000);

	INT_CONST(sign_mask, (int)0x80000000);
	INT_CONST(inv_sign_mask, ~0x80000000);

	//The min, max of the exp return
	DOUBLE_CONST(exp_upper, 88.3762626647949);
	DOUBLE_CONST(exp_lower, -88.3762626647949);

	DOUBLE_CONST(cephes_SQRTHF, 0.707106781186547524);
	DOUBLE_CONST(cephes_log_p0, 7.0376836292E-2);
	DOUBLE_CONST(cephes_log_p1, -1.1514610310E-1);
	DOUBLE_CONST(cephes_log_p2, 1.1676998740E-1);
	DOUBLE_CONST(cephes_log_p3, -1.2420140846E-1);
	DOUBLE_CONST(cephes_log_p4, +1.4249322787E-1);
	DOUBLE_CONST(cephes_log_p5, -1.6668057665E-1);
	DOUBLE_CONST(cephes_log_p6, +2.0000714765E-1);
	DOUBLE_CONST(cephes_log_p7, -2.4999993993E-1);
	DOUBLE_CONST(cephes_log_p8, +3.3333331174E-1);
	DOUBLE_CONST(cephes_log_q1, -2.12194440e-4);
	DOUBLE_CONST(cephes_log_q2, 0.693359375);

	INT_CONST(triplemask, 0x7f);

	/*
		MATH EXTENSIONS SECTION
	*/
	__m128 FRS_MATH_API to_pack4(vec2 p_vec);
	__m128 FRS_MATH_API to_pack4(vec3 p_vec);
	__m128 FRS_MATH_API to_pack4(vec4 p_vec);

	vec2 FRS_MATH_API to_vec2(__m128 p_vec);
	vec3 FRS_MATH_API to_vec3(__m128 p_vec);
	vec4 FRS_MATH_API to_vec4(__m128 p_vec);

}