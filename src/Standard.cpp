#include "Standard.h"
#include <intrin.h>

//Get NOT of 32-bit signed int
//Add to the library of mmintrin
__m128i _mm_not_epi32(__m128i _A) {
	__m128i t1 = {}; t1 = _mm_cmpeq_epi8(t1, t1);
	return _mm_xor_si128(t1, _A);
}

//temp solution
float _mm_extract_psn(__m128 a, int pos) {

	__m128 shuffle = {};

	switch (pos) {
	case 3:
		shuffle = _mm_shuffle_ps(a, a, MASK3);
		break;
	case 2:
		shuffle = _mm_shuffle_ps(a, a, MASK2);
		break;
	case 1:
		shuffle = _mm_shuffle_ps(a, a, MASK1);
		break;
	case 0:
		shuffle = _mm_shuffle_ps(a, a, MASK0);
		break;
	default: 
		return -1;
		break;
	}

	return _mm_cvtss_f32(shuffle);
}

//Get NOT of a float
//Add to the library of mmintrin
__m128 _mm_not_ps(__m128 _A) {
	__m128 t1 = {}; t1 = _mm_cmpeq_ps(t1, t1);
	return _mm_xor_ps(t1, _A);
}

__m128i _mm_div_epi32(__m128i _para1, __m128i _para) {
	int divisor = (int)(_mm_cvtss_f32(_mm_cvtepi32_ps(_para)));
	__m128i mt, m1, ms = {};
	const int32_t divisorabs = (divisor < 0) ? -divisor : divisor;
	int32_t sh, m;
	if (divisorabs > 1) {
		_BitScanReverse((unsigned long*)(&sh), divisorabs - 1);
		m = int32_t((int64_t(1) << (32 + sh)) / divisorabs - ((int64_t(1) << 32) - 1));
		//int32_t(((int64_t)1 << (32 + sh)) / divisorabs - ((int64_t)(1) << 32) - 1);
		//std::cout << sh << " " << m << std::endl;
	}
	else {
		sh = 0;
		m = 1;
		if (divisor == 0) m /= divisor;
		if (uint32_t(divisorabs) == 0x80000000u) {
			m = 0x80000001;
			sh = 30;
		}

	}

	mt = _mm_set1_epi32(m);
	//Found n - the shifter using bitscanreserve!
	m1 = _mm_setr_epi32(sh, 0, 0, 0);
	ms = _mm_set1_epi32(divisor < 0 ? -1 : 0);
	__m128i t1 = _mm_mul_epi32(_para1, mt);
	__m128i t2 = _mm_srli_epi64(t1, 32);
	__m128i t3 = _mm_srli_epi64(_para1, 32);
	__m128i t4 = _mm_mul_epi32(t3, mt);
	__m128i t5 = _mm_set_epi32(-1, 0, -1, 0);
	__m128i t6 = _mm_blendv_epi8(t2, t4, t5);
	__m128i t7 = _mm_add_epi32(t6, _para1);
	__m128i t8 = _mm_sra_epi32(t7, m1);
	__m128i t9 = _mm_srai_epi32(_para1, 31);
	__m128i t10 = _mm_sub_epi32(t9, ms);
	__m128i t11 = _mm_sub_epi32(t8, t10);
	return _mm_xor_si128(t11, ms);
}


namespace FRSML {

	float ToDegrees(float radians) {
		return (float)(FRS_float(radians)*HALFWISEANGLE / PI);
	}

	//Convert Radians to Degrees! Whoa!
	float ToRadians(float degrees) {
		return (float)(FRS_float(degrees) / HALFWISEANGLE * PI);
	}

	namespace nmmintrin {

		__m128 _Pow(__m128 x, __m128 y) {

			__m128 tmp = nmmintrin::_Log(x);
			__m128 tmp2 = _mm_mul_ss(x, y);

			tmp2 = nmmintrin::_Exp(tmp2);

			return tmp2;
		}

		//Use fast convert, may leak mem
		//Conversation take from grunttthepeon.
		__m128 _Log(__m128 _para) {
			__m128i emm0;

			__m128 one = *(__m128*)_F_1;
			__m128 x = _para;

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
			x = _mm_add_ps(x, _mm_add_ps(y,tmp));
			x = _mm_or_ps(x, invalid_mask);
			
			return x;
	
		}

		__m128 _Exp(__m128 _para) {
			__m128 tmp = _mm_setzero_ps();
			__m128 x = _para;
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
			x = _mm_sub_ps(x, _mm_add_ps(tmp,tmp2));

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

		__m128 _Absf(__m128 m)
		{
			__m128 sign = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
			FRSML_ASSERT_WV(_mm_andnot_ps(sign, m).m128_f32[0] == m.m128_f32[0], "CACULATE ABS WRONG", _mm_andnot_ps(sign, m).m128_f32[0], m.m128_f32[0]);
			return _mm_andnot_ps(sign, m);
		}

		__m128i _Abs(__m128i _para) {
			return _mm_abs_epi32(_para);
		}

		__m128 _Maxf(__m128 _A, __m128 _B) {
			return _mm_max_ps(_A, _B);
		}

		__m128 _Minf(__m128 _A, __m128 _B) {
			return _mm_min_ps(_A, _B);
		}

		__m128i _Max(__m128i _A, __m128i _B) {
			return _mm_max_epi32(_A, _B);
		}

		__m128i _Min(__m128i _A, __m128i _B) {
			return _mm_min_epi32(_A, _B);
		}

		__m128 _Sqrtf(__m128 ant) {
			return _mm_sqrt_ps(ant);
		}

		__m128i _Sqrt(__m128i ant) {
			__m128 t2 = _mm_cvtepi32_ps(ant);
			t2 = _mm_sqrt_ps(t2);
			return _mm_cvtps_epi32(t2);
		}


		__m128 _Signf(__m128 _para) {
			//return _mm_cvtepi32_ps(_mm_sign_epi32(_mm_set1_epi32(1), _mm_cvtps_epi32(_para)));
			const __m128i MASK = _mm_set1_epi32(0xffffffff);

			__m128 a = _mm_setr_ps(1, 1, 1, 1);

			__m128 f = _mm_xor_ps(_para, a);
			__m128i i = _mm_castps_si128(f);
			i = _mm_srai_epi32(i, 31); i = _mm_xor_si128(i, MASK);
			f = _mm_cvtepi32_ps(i);

			return _mm_mul_ps(f, _mm_set1_ps(-1));

		}

		__m128 BalanceToPiDistance(__m128 _para) {
			__m128 piarr2 = _mm_set1_ps(PI * 2);
			__m128 piarrsg = _mm_set1_ps(-PI);
			__m128 piarr = _mm_set1_ps(PI);
			__m128 piarrd2 = _mm_div_ps(_mm_set1_ps(PI), _mm_set1_ps(2));

			__m128 t3 = _para; __m128 t4, t5 = {};
			while (_mm_movemask_ps(_mm_cmpgt_ps(t3, piarr))) {
				t4 = _mm_cmpgt_ps(t3, piarr);
				t5 = _mm_and_ps(t4, piarr2);
				t3 = _mm_sub_ps(t3, t5);
			}

			while (_mm_movemask_ps(_mm_cmplt_ps(t3, piarrsg))) {
				t4 = _mm_cmplt_ps(t3, piarrsg);
				t5 = _mm_and_ps(t4, piarr2);
				t3 = _mm_add_ps(t3, t5);
			}

			FRSML_ASSERT_WV(-PI > t3.m128_f32[0] || t3.m128_f32[0]> PI, "THE BALANCED VALUE IS OUT OF RANGE", t3.m128_f32[0], 0);
			return t3;
		}

#pragma region CACULATE_SINCOSTAN_ASIN_ACOS_ATAN
		inline __m128 _Sin(__m128 _para) {
			__m128 sign = _Signf(_para);
			__m128 t0 = BalanceToPiDistance(_para);
			__m128 t1 = _mm_mul_ps(t0, t0);
			__m128 t2 = _mm_set1_ps(MGNBR1);
			__m128 t3 = _mm_set1_ps(MGNBR2);
			__m128 t4 = _mm_set1_ps(MGNBR3);
			__m128 t5 = _mm_set1_ps(MGNBR4);
			__m128 t6 = _mm_sub_ps(t1, t3);
			t6 = _mm_mul_ps(t6, t1);
			t6 = _mm_add_ps(t2, t6);
			__m128 t7 = _mm_sub_ps(t1, t4);
			t7 = _mm_mul_ps(t6, t7);
			t7 = _mm_mul_ps(t7, t0);
			__m128 t8 = _mm_div_ps(t7, t5);
			t8 = _mm_mul_ps(sign, t8);
			return t8;
		}


		inline __m128 _Cos(__m128 _para) {
			__m128 t1 = _mm_add_ps(_para, _mm_set1_ps(PID2));
			return _Sin(t1);

		}

		inline __m128 _Tan(__m128 _para) {
			__m128 t1 = _Sin(_para);
			__m128 t2 = _Cos(_para);
			return _mm_div_ps(t1, t2);
		}

		inline __m128 _Cot(__m128 _para) {
			__m128 t1 = _Sin(_para);
			__m128 t2 = _Cos(_para);
			return _mm_div_ps(t2, t1);
		}

		//http://http.developer.nvidia.com/Cg/asin.html
		inline __m128 _Asin(__m128 _para) {
			__m128 t1 = _mm_cmplt_ps(_para, _mm_set1_ps(0));
			__m128 t2 = _Absf(_para);
			__m128 t3 = _mm_set1_ps(-0.0187293);
			__m128 t4 = _mm_mul_ps(t3, t2);
			t4 = _mm_add_ps(t4, _mm_set1_ps(0.0742610));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_sub_ps(t4, _mm_set1_ps(0.2121144));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_add_ps(t4, _mm_set1_ps(1.5707288));
			t4 = _mm_mul_ps(t4, _Sqrtf(_mm_sub_ps(_mm_set1_ps(1), t2)));
			__m128 t5 = _mm_sqrt_ps(_mm_sub_ps(_mm_set1_ps(1), t2));
			__m128 t6 = _mm_mul_ps(t4, t5);
			t4 = _mm_sub_ps(_mm_set1_ps(PID2), t6);
			__m128 t7 = _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(2), t1), t4);
			t4 = _mm_sub_ps(t4, t7);
			return t4;
		}

		inline __m128 _Acos(__m128 _para) {
			__m128 t1 = _mm_cmplt_ps(_para, _mm_set1_ps(0));
			__m128 t2 = _Absf(_para);
			__m128 t3 = _mm_set1_ps(-0.0187293);
			__m128 t4 = _mm_mul_ps(t3, t2);
			t4 = _mm_add_ps(t4, _mm_set1_ps(0.0742610));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_sub_ps(t4, _mm_set1_ps(0.2121144));
			t4 = _mm_mul_ps(t4, t2);
			t4 = _mm_add_ps(t4, _mm_set1_ps(1.5707288));
			t4 = _mm_mul_ps(t4, _Sqrtf(_mm_sub_ps(_mm_set1_ps(1), t2)));
			__m128 t5 = _mm_mul_ps(_mm_set1_ps(2), t1);
			__m128 t6 = _mm_mul_ps(t5, t4);
			t4 = _mm_sub_ps(t4, t6);
			__m128 t7 = _mm_mul_ps(t1, _mm_set1_ps(PI));
			return _mm_add_ps(t7, t4);
		}


		inline __m128 _Atan2(__m128 _Y, __m128 _X) {
			__m128 t1 = _Absf(_X);
			__m128 t2 = _Absf(_Y);
			__m128 t3 = _Maxf(t1, t2); __m128 t4 = _Minf(t1, t2);

			t1 = _mm_div_ps(_mm_set1_ps(1), t3);
			t1 = _mm_mul_ps(t1, t4);
			__m128 t6 = _mm_mul_ps(t1, t1);
			t3 = _mm_set1_ps(-0.013480470);
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_add_ps(t3, _mm_set1_ps(0.057477314));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_sub_ps(t3, _mm_set1_ps(0.121239071));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_add_ps(t3, _mm_set1_ps(0.195635925));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_sub_ps(t3, _mm_set1_ps(0.332994597));
			t3 = _mm_mul_ps(t3, t6);
			t3 = _mm_add_ps(t3, _mm_set1_ps(0.999995630));
			t1 = _mm_mul_ps(t3, t1);

			FRSML_ASSERT(t1.m128_f32[0] != _X.m128_f32[0] || t1.m128_f32[0] != _Y.m128_f32[0], "THE ATAN PRECACATED VALUE ERROR");

			__m128 t7 = _mm_cmpgt_ps(_Absf(_Y), _Absf(_X));
			__m128 t8 = _mm_and_ps(t7, _mm_sub_ps(_mm_set1_ps(1.570796327), t1));
			__m128 t9 = _mm_and_ps(_mm_not_ps(t7), t1);

			t1 = _mm_or_ps(t8, t9);
			FRSML_ASSERT(t1.m128_f32[0] != _X.m128_f32[0] || t1.m128_f32[0] != _Y.m128_f32[0], "THE ATAN PRECACATED VALUE ERROR");
			t7 = _mm_cmplt_ps(_X, _mm_set1_ps(0));
			t8 = _mm_and_ps(t7, _mm_sub_ps(_mm_set1_ps(PI), t1));
			t9 = _mm_and_ps(_mm_not_ps(t7), t1);
			t1 = _mm_or_ps(t8, t9);
			FRSML_ASSERT(t1.m128_f32[0] != _X.m128_f32[0] || t1.m128_f32[0] != _Y.m128_f32[0], "THE ATAN PRECACATED VALUE ERROR");
			t7 = _mm_cmplt_ps(_Y, _mm_set1_ps(0));
			t8 = _mm_and_ps(t7, _mm_sub_ps(_mm_set1_ps(0), t1));
			t9 = _mm_and_ps(_mm_not_ps(t7), t1);
			t1 = _mm_or_ps(t8, t9);
			FRSML_ASSERT(t1.m128_f32[0] != _X.m128_f32[0] || t1.m128_f32[0] != _Y.m128_f32[0], "THE ATAN PRECACATED VALUE ERROR");
			return t1;
		}

		inline __m128 _Atan(__m128 _X) {
			return _Atan2(_X, _mm_set1_ps(1));
		}
	}

	vec2 Abs(vec2 _para) {
		return _funcWrp1p(nmmintrin::_Absf, _para);
	}

	vec3 Abs(vec3 _para) {
		return _funcWrp1p(nmmintrin::_Absf, _para);
	}

	vec4 Abs(vec4 _para) {
		return _funcWrp1p(nmmintrin::_Absf, _para);
	}

	vec2 Min(vec2 _para1, vec2 _para2) {
		return _funcWrp2p(nmmintrin::_Minf, _para1, _para2);
	}

	vec2 Max(vec2 _para1, vec2 _para2) {
		return _funcWrp2p(nmmintrin::_Maxf, _para1, _para2);
	}

	vec3 Min(vec3 _para1, vec3 _para2) {
		return _funcWrp2p(nmmintrin::_Minf, _para1, _para2);
	}

	vec3 Max(vec3 _para1, vec3 _para2) {
		return _funcWrp2p(nmmintrin::_Maxf, _para1, _para2);
	}

	vec4 Min(vec4 _para1, vec4 _para2) {
		return _funcWrp2p(nmmintrin::_Minf, _para1, _para2);
	}

	vec4 Max(vec4 _para1, vec4 _para2) {
		return _funcWrp2p(nmmintrin::_Maxf, _para1, _para2);
	}

	vec2 Dot(vec2 _para1, vec2 _para2) {
		return _mm_dp_ps(_para1.MainVector(), _para2.MainVector(), 0x33);
	}

	vec3 Dot(vec3 _para1, vec3 _para2) {
		return  _mm_dp_ps(_para1.MainVector(), _para2.MainVector(), 0x77);
	}



	vec4 Dot(vec4 _para1, vec4 _para2) {
		return _mm_dp_ps(_para1.MainVector(), _para2.MainVector(), 0xFF);
	}

	vec2 Angle(vec2 _para1, vec2 _para2) {
		vec2 _t1 = _para1.Normalize();
		vec2 _t2 = _para2.Normalize();
		_t1 = Dot(_t1, _t2);
		return nmmintrin::_Acos(_t1.MainVector());
	}


	vec3 Angle(vec3 _para1, vec3 _para2) {
		vec3 _t1 = _para1.Normalize();
		vec3 _t2 = _para2.Normalize();
		_t1 = Dot(_t1, _t2);
		return nmmintrin::_Acos(_t1.MainVector());
	}

	vec4 Angle(vec4 _para1, vec4 _para2) {
		vec4 _t1 = _para1.Normalize();
		vec4 _t2 = _para2.Normalize();
		_t1 = Dot(_t1,_t2);
		return nmmintrin::_Acos(_t1.MainVector());
	}

	//Reflect a vector with in and norm dir
	//And scale is already in vector, so dont worry
	vec2 Reflect(vec2 inDir, vec2 inNorm) {
		vec2 norm = inNorm.Normalize();
		return inDir - (Dot(inDir, norm))*norm*2;
	}

	//Reflect a vector with in and norm dir
	//And scale is already in vector, so dont worry
	vec3 Reflect(vec3 inDir, vec3 inNorm) {
		vec3 norm = inNorm.Normalize();
		return inDir - (Dot(inDir, norm))*norm * 2;
	}

	//Reflect a vector with in and norm dir
	//And scale is already in vector, so dont worry
	vec4 Reflect(vec4 inDir, vec4 inNorm) {
		vec4 norm = inNorm.Normalize();
		return inDir - (Dot(inDir, norm))*norm * 2;
	}


	vec3 Cross(vec3 _para1, vec3 _para2) {
		__m128 t1 = _para1.MainVector();
		__m128 t2 = _para2.MainVector();
		__m128 c1 = _mm_mul_ps(_mm_shuffle_ps(t1, t1, _MM_SHUFFLE(3, 1, 2, 0)),
			_mm_shuffle_ps(t2, t2, _MM_SHUFFLE(3, 2, 0, 1)));
		__m128 c2 = _mm_mul_ps(_mm_shuffle_ps(t1, t1, _MM_SHUFFLE(3, 2, 0, 1)),
			_mm_shuffle_ps(t2, t2, _MM_SHUFFLE(3, 1, 2, 0)));

		return _mm_sub_ps(c1, c2);
	}

	//Return the distance between two Vector!!!!!!
	float Distance(vec2 _start, vec2 _end) {
		return (_end - _start).Length();
	}

	//Return the distance between two Vector!!!!!!
	float Distance(vec3 _start, vec3 _end) {
		return (_end - _start).Length();
	}

	//Return the distance between two Vector!!!!!!
	float Distance(vec4 _start, vec4 _end) {
		return (_end - _start).Length();
	}


#pragma region FLOAT HANDLER

	//Clamp the value
	float Clamp(float _t1, float _t2, float crrNumber) {
		return (crrNumber < _t1) ? _t1 : ((crrNumber>_t2)?_t2:crrNumber);
	}

	//Return the value between a and b. Basically, t is the percent in short written
	float Lerp(float t, float a, float b) {
		return (1 - t)*a + t*b;
	}

	//Get the Max value between two float
	float Max(float _A, float _B) {
		return (_A >= _B) ? (_A) : (_B);
	}

	//Get the Min value between two float
	float Min(float _A, float _B) {
		return (_A <= _B) ? (_A) : (_B);
	}

	//Get the Square Root value of a float using SSE
	//Whoa, technology!
	float Sqrt(float ant) {
		__m128 t1 = _mm_load_ss(&ant);
		return _mm_cvtss_f32(t1);

	}

	//Get the Sin value of a float using SSE
	//Whoa, technology!
	float Sin(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Sin(t);
		return _mm_cvtss_f32(t);
	}

	//Get the Cos value of a float using SSE
	//Whoa, technology!
	float Cos(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Cos(t);
		return _mm_cvtss_f32(t);
	}

	//Get the Tan value of a float using SSE
	//Whoa, technology!
	float Tan(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Tan(t);
		return _mm_cvtss_f32(t);
	}

	//Get the Cotan value of a float using SSE
	//Whoa, technology!
	float Cot(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Cot(t);
		return _mm_cvtss_f32(t);
	}

	//The sin value of X will be put into "s" array
	//The cos value of Y will be put into "c" array
	//... Using SSE technology! Whoa!
	void SinCos(float x, float* s, float* c) {
		__m128 both = _mm_set_ps(0, 0, x + PID2, x);
		__m128 sincos = nmmintrin::_Sin(both);
		//When shuffle, the sin got taken out, leving alone the cos.
		//The original will only have the same type of sin
		__m128 cos = _mm_shuffle_ps(sincos, sincos, _MM_SHUFFLE(0, 0, 0, 1));
		*s = _mm_cvtss_f32(sincos);
		*c = _mm_cvtss_f32(cos);
	}

	//Get the Asin value of a float using SSE
	//Whoa, technology!
	float Asin(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Asin(t);
		return _mm_cvtss_f32(t);
	}

	//Get the Acos value of a float using SSE
	//Whoa, technology!
	float Acos(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Acos(t);
		return _mm_cvtss_f32(t);
	}

	//Get the Atan value of a float using SSE
	//Whoa, technology!
	float Atan(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Atan(t);
		return _mm_cvtss_f32(t);
	}

	//Cacluate the e^x value
	double Exp(double x) {
		__m128 tmp = _mm_set_ss(x);
		tmp = nmmintrin::_Exp(tmp);
		return _mm_cvtss_f32(tmp);
	}

	//Caculate the logarithym value base e
	float Log(float x) {
		__m128 tmp = _mm_set_ss(x);
		tmp = nmmintrin::_Log(tmp);
		return _mm_cvtss_f32(tmp);
	}

	//Caculate the logarithym value base 2
	float Log2(float x) {
		__m128 tmp = _mm_set_ss(x);

		tmp = nmmintrin::_Log(tmp);
		tmp = _mm_div_ps(tmp, _mm_set_ss(LOG2));

		return _mm_cvtss_f32(tmp);
	}

	//Caculate the logarithym value base "base"
	float Log(float x, float base) {
		__m128 tmp = _mm_set_ss(x);

		tmp = nmmintrin::_Log(tmp);
		tmp = _mm_div_ps(tmp, nmmintrin::_Log(_mm_set_ss(base)));

		return _mm_cvtss_f32(tmp);
	}


	float Pow(float x, float y) {
		__m128 tmp = _mm_set_ss(x);
		__m128 tmp2 = _mm_set_ss(y);

		tmp = nmmintrin::_Log(tmp);
		tmp2 = _mm_mul_ss(tmp, tmp2);

		tmp2 = nmmintrin::_Exp(tmp2);

		return _mm_cvtss_f32(tmp2);
	}

	//Atan2 cacluates the degrees of the angle created
	//between coordinate line (origin to point2d line) and axis
	//Or basicly, it is Arctan of (-y/-x); And its tech is SSE!
	//Whoa!
	float Atan2(float _Y, float _X) {
		__m128 t = _mm_set1_ps(_X);
		__m128 t1 = _mm_set1_ps(_Y);
		__m128 t3 = nmmintrin::_Atan2(t1, t);
		return _mm_cvtss_f32(t3);
	}

	//I dont think it makes things faster than normal, so throw it here ^-^
	//It caculate the Sign of a float. Whoa technology!
	float Sign(float _para) {
		__m128 t = _mm_set1_ps(_para);
		t = nmmintrin::_Signf(t);
		return _mm_cvtss_f32(t);
	}

	//Caculate the absolute value of a float! Using SSE tech! Whoa!
	float Abs(float _para) {
		return (_para < 0) ? -_para : _para;
	}
#pragma endregion

#pragma region FRS_INT HANDLER
	//Get the Max value between two float
	FRS_int Max(FRS_int _A, FRS_int _B) {
		__m128i t1 = _A.MainNum(); __m128i t2 = _B.MainNum();
		t1 = _mm_max_epi32(t1, t2);
		return FRS_int(t1);
	}

	//Get the Min value between two float
	FRS_int Min(FRS_int _A, FRS_int _B) {
		__m128i t1 = _A.MainNum(); __m128i t2 = _B.MainNum();
		t1 = _mm_min_epi32(t1, t2);
		return FRS_int(t1);
	}

	//Get the Square Root value of a float using SSE
	//Whoa, technology!
	FRS_float Sqrt(FRS_int ant) {
		__m128i t1 = ant.MainNum();
		__m128 t2 = _mm_cvtepi32_ps(t1);
		t2 = nmmintrin::_Sqrtf(t2);
		return FRS_float(t2);

	}

	//Caculate the absolute value of a float! Using SSE tech! Whoa!
	FRS_int Abs(FRS_int _para) {
		__m128i t1 = _para.MainNum();
		t1 = nmmintrin::_Abs(t1);
		return t1;
	}

	
#pragma endregion

#pragma region FRS_FLOAT HANDLER
	//Get the Max value between two float
	FRS_float Max(FRS_float _A, FRS_float _B) {
		__m128 t1 = _A.MainNum(); __m128 t2 = _B.MainNum();
		t1 = _mm_max_ps(t1, t2);
		return FRS_float(t1);
	}

	//Get the Min value between two float
	FRS_float Min(FRS_float _A, FRS_float _B) {
		__m128 t1 = _A.MainNum(); __m128 t2 = _B.MainNum();
		t1 = _mm_min_ps(t1, t2);
		return FRS_float(t1);
	}

	//Caculate the absolute value of a float! Using SSE tech! Whoa!
	FRS_float Abs(FRS_float _para) {
		__m128 t1 = _para.MainNum();
		t1 = nmmintrin::_Absf(t1);
		return t1;
	}

	//Get the Square Root value of a float using SSE
	//Whoa, technology!
	FRS_float Sqrt(FRS_float ant) {
		__m128 t1 = ant.MainNum();
		t1 = nmmintrin::_Sqrtf(t1);
		return FRS_float(t1);

	}

	//Get the Sin value of a float using SSE
	//Whoa, technology!
	FRS_float Sin(FRS_float _para) {
		__m128 t = _para.MainNum();
		t = nmmintrin::_Sin(t);
		return FRS_float(t);
	}

	//Get the Cos value of a float using SSE
	//Whoa, technology!
	FRS_float Cos(FRS_float _para) {
		__m128 t = _para.MainNum();
		t = nmmintrin::_Cos(t);
		return FRS_float(t);
	}

	//Get the Tan value of a float using SSE
	//Whoa, technology!
	FRS_float Tan(FRS_float _para) {
		__m128 t = _para.MainNum();
		t = nmmintrin::_Tan(t);
		return FRS_float(t);
	}

	//Get the Cot value of a float using SSE
	//Whoa, technology!
	FRS_float Cot(FRS_float _para) {
		__m128 t = _para.MainNum();
		t = nmmintrin::_Cot(t);
		return FRS_float(t);
	}

	//Get the Asin value of a float using SSE
	//Whoa, technology!
	FRS_float Asin(FRS_float _para) {
		__m128 t = _para.MainNum();
		t = nmmintrin::_Asin(t);
		return FRS_float(t);
	}

	//Get the Acos value of a float using SSE
	//Whoa, technology!
	FRS_float Acos(FRS_float _para) {
		__m128 t = _para.MainNum();
		t = nmmintrin::_Acos(t);
		return FRS_float(t);
	}

	//Atan2 cacluates the degrees of the angle created
	//between coordinate line (origin to point2d line) and axis
	//Or basicly, it is Arctan of (-y/-x); And its tech is SSE!
	//Whoa!
	FRS_float Atan2(FRS_float _Y, FRS_float _X) {
		__m128 t = _X.MainNum(); __m128 t2 = _Y.MainNum();
		t = nmmintrin::_Atan2(t2, t);
		return FRS_float(t);
	}

	//Get the Atan value of a float using SSE
	//Whoa, technology!
	FRS_float Atan(FRS_float _X) {
		__m128 t = _X.MainNum();
		t = nmmintrin::_Atan(t);
		return FRS_float(t);
	}

	//Get the Sin value of a float using SSE
	//Whoa, technology!
	FRS_float Sin(FRS_int _para) {
		__m128i t = _para.MainNum();
		__m128 t1 = _mm_cvtepi32_ps(t);
		t1= nmmintrin::_Sin(t1);
		return FRS_float(t1);
	}

	//Get the Cos value of a float using SSE
	//Whoa, technology!
	FRS_float Cos(FRS_int _para) {
		__m128i t = _para.MainNum();
		__m128 t1 = _mm_cvtepi32_ps(t);
		t1 = nmmintrin::_Cos(t1);
		return FRS_float(t1);
	}

	//Get the Tan value of a float using SSE
	//Whoa, technology!
	FRS_float Tan(FRS_int _para) {
		__m128i t = _para.MainNum();
		__m128 t1 = _mm_cvtepi32_ps(t);
		t1 = nmmintrin::_Tan(t1);
		return FRS_float(t1);
	}

	//Get the Cot value of a float using SSE
	//Whoa, technology!
	FRS_float Cot(FRS_int _para) {
		__m128i t = _para.MainNum();
		__m128 t1 = _mm_cvtepi32_ps(t);
		t1 = nmmintrin::_Cot(t1);
		return FRS_float(t1);
	}

	//Get the Asin value of a float using SSE
	//Whoa, technology!
	FRS_float Asin(FRS_int _para) {
		__m128i t = _para.MainNum();
		__m128 t1 = _mm_cvtepi32_ps(t);
		t1 = nmmintrin::_Asin(t1);
		return FRS_float(t1);
	}

	//Get the Acos value of a float using SSE
	//Whoa, technology!
	FRS_float Acos(FRS_int _para) {
		__m128i t = _para.MainNum();
		__m128 t1 = _mm_cvtepi32_ps(t);
		t1 = nmmintrin::_Acos(t1);
		return FRS_float(t1);
	}

	//Atan2 cacluates the degrees of the angle created
	//between coordinate line (origin to point2d line) and axis
	//Or basicly, it is Arctan of (-y/-x); And its tech is SSE!
	//Whoa!
	FRS_float Atan2(FRS_int _Y, FRS_int _X) {
		__m128i t = _X.MainNum(); __m128i t2 = _Y.MainNum();
		__m128 t3 = _mm_cvtepi32_ps(t); __m128 t4 = _mm_cvtepi32_ps(t2);
		t3 = nmmintrin::_Atan2(t4, t3);
		return FRS_float(t3);
	}

	//Get the Atan value of a float using SSE
	//Whoa, technology!
	FRS_float Atan(FRS_int _X) {
		__m128i t = _X.MainNum();
		__m128 t1 = _mm_cvtepi32_ps(t);
		t1 = nmmintrin::_Atan(t1);
		return FRS_float(t1);
	}

	//Lazy, Atan(1-x) = Acot = (x) :3
#pragma endregion


	


	
}