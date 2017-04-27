#include "Quaternion.h"

namespace FRSML {
	Quaternion Quaternion::Normalize() {
		__m128 mainQuat = GenerateXYZW();

		__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainQuat, mainQuat, 0xFF));
		return Quaternion(_mm_mul_ps(mainQuat, inverse_normalize));
	}


	Quaternion Quaternion::Euler(vec3 euler) {

		//return (float)(FRS_float(radians)*HALFWISEANGLE / PI)

		__m128 tmp = _mm_div_ps(_mm_mul_ps(euler.GenerateXYZW() ,_mm_set1_ps(PI)),_mm_set1_ps(180));

		__m128 t1 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 t2 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 t3 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(0, 0, 0, 0));

		t1 = _mm_div_ps(t1, _mm_set1_ps(2));
		t2 = _mm_div_ps(t2, _mm_set1_ps(2));
		t3 = _mm_div_ps(t3, _mm_set1_ps(2));


		__m128 t4 = _Cos(t3);
		__m128 t5 = _Sin(t3);
		__m128 t6 = _Cos(t1);
		__m128 t7 = _Sin(t1);
		__m128 t8 = _Cos(t2);
		__m128 t9 = _Sin(t2);

		__m128 quatW = _mm_mul_ps(t4, _mm_mul_ps(t6, t8));
		quatW = _mm_add_ps(quatW,_mm_mul_ps(t5, _mm_mul_ps(t7, t9)));

		__m128 quatX = _mm_mul_ps(t4, _mm_mul_ps(t7, t8));
		quatX = _mm_sub_ps(quatX, _mm_mul_ps(t5, _mm_mul_ps(t6, t9)));

		__m128 quatY = _mm_mul_ps(t4, _mm_mul_ps(t6, t9));
		quatY = _mm_add_ps(quatY, _mm_mul_ps(t5, _mm_mul_ps(t7, t8)));
	
		__m128 quatZ = _mm_mul_ps(t5, _mm_mul_ps(t6, t8));
		quatZ = _mm_sub_ps(quatZ, _mm_mul_ps(t4, _mm_mul_ps(t7, t9)));


		float w = _mm_cvtss_f32(quatW);
		float x = _mm_cvtss_f32(quatX);
		float y = _mm_cvtss_f32(quatY);
		float z = _mm_cvtss_f32(quatZ);

		return Quaternion(x, y, z, w);
	}

	Quaternion Quaternion::Rotate(vec3 axis, float angle) {
		__m128 tmp = axis.Normalize().GenerateXYZW();

		__m128 tmp2 = (_mm_div_ps(_mm_set1_ps(angle), _mm_set1_ps(2)));
		__m128 tmp3 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 tmp4 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 tmp5 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(0, 0, 0, 0));

		__m128 quatW = _Cos(tmp2);
		__m128 quatX = _mm_mul_ps(_Sin(tmp2),tmp3);
		__m128 quatY = _mm_mul_ps(_Sin(tmp2), tmp4);
		__m128 quatZ = _mm_mul_ps(_Sin(tmp2), tmp5);

		float w = _mm_cvtss_f32(quatW);
		float x = _mm_cvtss_f32(quatX);
		float y = _mm_cvtss_f32(quatY);
		float z = _mm_cvtss_f32(quatZ);

		return Quaternion(x, y, z, w);
		
	}


	Quaternion Quaternion::operator *(Quaternion tar1) {

		__m128 mainQuat = GenerateXYZW();
		__m128 mainQuat2 = tar1.GenerateXYZW();

		__m128 t1 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(3, 3, 3, 3));
		__m128 t2 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 t3 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 t4 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(0, 0, 0, 0));
	
		__m128 grand0; {
			__m128 c1 = _mm_shuffle_ps(mainQuat2, mainQuat2, _MM_SHUFFLE(3, 2, 1, 0));
			grand0 = _mm_mul_ps(t1, c1);
		};

		__m128 grand1; {
			__m128 c1 = _mm_shuffle_ps(mainQuat2, mainQuat2, _MM_SHUFFLE(2, 3, 0, 1));
			grand1 = _mm_mul_ps(t2, c1);
		};

		__m128 grand2; {
			__m128 c1 = _mm_shuffle_ps(mainQuat2, mainQuat2, _MM_SHUFFLE(1, 0, 3, 2));
			grand2 = _mm_mul_ps(t3, c1);
		};

		__m128 grand3; {
			__m128 c1 = _mm_shuffle_ps(mainQuat2, mainQuat2, _MM_SHUFFLE(0, 1, 2, 3));
			grand3 = _mm_mul_ps(t4, c1);
		};

		grand1 = _mm_mul_ps(grand1, _mm_set_ps(-1, 1, -1, 1));
		grand2 = _mm_mul_ps(grand2, _mm_set_ps(-1, 1, 1, -1));
		grand3 = _mm_mul_ps(grand3, _mm_set_ps(-1, -1, 1, 1));

		grand0 = _mm_add_ps(grand0, _mm_add_ps(grand1, _mm_add_ps(grand2, grand3)));


		return Quaternion(grand0);
	}

	Quaternion Dot(Quaternion _para1, Quaternion _para2) {
		return  _mm_dp_ps(_para1.GenerateXYZW(), _para2.GenerateXYZW(), 0xFF);
	}	
	
	Quaternion Angle(Quaternion _para1, Quaternion _para2) {
		Quaternion _t1 = _para1.Normalize();
		Quaternion _t2 = _para2.Normalize();
		_t1 = Dot(_t1, _t2);
		return nmmintrin::_Acos(_t1.GenerateXYZW());
	}

	Quaternion::operator mat4() {

		__m128 mainQuat = GenerateXYZW();

		Quaternion tmp = Normalize();
		__m128 quatX = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(2, 2, 2, 2));
		quatX = _mm_set_ps(0, 0, 0, _mm_extract_psn(quatX, _MM_SHUFFLE(0, 0, 0, 0)));
		__m128 quatY = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(1, 1, 1, 1));
		quatY = _mm_set_ps(0, 0, 0, _mm_extract_psn(quatY, _MM_SHUFFLE(0, 0, 0, 0)));
		__m128 quatZ = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(0, 0, 0, 0));
		quatZ = _mm_set_ps(0, 0, 0, _mm_extract_psn(quatZ, _MM_SHUFFLE(0, 0, 0, 0)));
		__m128 quatW = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(3, 3, 3, 3));
		quatW = _mm_set_ps(0, 0, 0, _mm_extract_psn(quatW, _MM_SHUFFLE(0, 0, 0, 0)));

		__m128 tem1; {
			__m128 g1 = _Pow(quatY, _mm_set1_ps(2));
			__m128 g2 = _Pow(quatZ, _mm_set1_ps(2));
			g1 = _mm_add_ss(g1, g2);
			tem1 = _mm_sub_ss(_mm_set1_ps(1), g1);
			tem1 = _mm_shuffle_ps(tem1, tem1, _MM_SHUFFLE(0, 3, 3, 3));
		};


		__m128 tem2; {
			__m128 g1 = _Pow(quatX, _mm_set1_ps(2));
			__m128 g2 = _Pow(quatY, _mm_set1_ps(2));
			g1 = _mm_add_ss(g1, g2);
			tem2 = _mm_sub_ss(_mm_set1_ps(1), g1);
			tem2 = _mm_shuffle_ps(tem2, tem2, _MM_SHUFFLE(3, 3, 0, 3));
		};

		__m128 tem3; {
			__m128 g1 = _Pow(quatX, _mm_set1_ps(2));
			__m128 g2 = _Pow(quatZ, _mm_set1_ps(2));
			g1 = _mm_add_ss(g1, g2);
			tem3 = _mm_sub_ss(_mm_set1_ps(1), g1);
			tem3 = _mm_shuffle_ps(tem3, tem3, _MM_SHUFFLE(3, 0, 3, 3));
		};

		__m128 tem4; {
			__m128 g1 = _mm_mul_ss(quatX, quatY);
			__m128 g2 = _mm_mul_ss(quatW, quatZ);
			g1 = _mm_add_ss(g1, g2);
			tem4 = _mm_add_ss(_mm_set1_ps(2), g1);
			tem4 = _mm_shuffle_ps(tem4, tem4, _MM_SHUFFLE(0, 3, 3, 3));
		}

		__m128 tem5; {
			__m128 g1 = _mm_mul_ss(quatX, quatZ);
			__m128 g2 = _mm_mul_ss(quatW, quatY);
			g1 = _mm_add_ss(g1, g2);
			tem5 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem5 = _mm_shuffle_ps(tem5, tem5, _MM_SHUFFLE(3, 3, 0, 3));
		}

		__m128 tem6; {
			__m128 g1 = _mm_mul_ss(quatY, quatZ);
			__m128 g2 = _mm_mul_ps(quatW, quatX);
			g1 = _mm_add_ss(g1, g2);
			tem6 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem6 = _mm_shuffle_ps(tem6, tem6, _MM_SHUFFLE(3, 3, 0, 3));
		}

		__m128 tem7; {
			__m128 g1 = _mm_mul_ss(quatX, quatY);
			__m128 g2 = _mm_mul_ss(quatW, quatZ);
			g1 = _mm_sub_ss(g1, g2);
			tem7 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem7 = _mm_shuffle_ps(tem7, tem7, _MM_SHUFFLE(3, 0, 3, 3));
		}

		__m128 tem8; {
			__m128 g1 = _mm_mul_ss(quatX, quatZ);
			__m128 g2 = _mm_mul_ss(quatW, quatY);
			g1 = _mm_sub_ss(g1, g2);
			tem8 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem8 = _mm_shuffle_ps(tem8, tem8, _MM_SHUFFLE(0, 3, 3, 3));
		}

		__m128 tem9; {
			__m128 g1 = _mm_mul_ss(quatY, quatZ);
			__m128 g2 = _mm_mul_ss(quatW, quatX);
			g1 = _mm_sub_ss(g1, g2);
			tem9 = _mm_mul_ss(_mm_set1_ps(2), g1);
			tem9 = _mm_shuffle_ps(tem9, tem9, _MM_SHUFFLE(0, 3, 3, 3));
		}

		__m128 tem0 = _mm_set_ps(0, 0, 0, 1);

		__m128 tem10 = _mm_xor_ps(tem1, _mm_xor_ps(tem5, tem7));
		__m128 tem11 = _mm_xor_ps(tem4, _mm_xor_ps(tem3, tem6));
		__m128 tem12 = _mm_xor_ps(tem8, _mm_xor_ps(tem9, tem2));
		__m128 tem13 = _mm_xor_ps(_mm_setzero_ps(), tem0);

		return mat4(tem10, tem11, tem12, tem13).Transpose();



	}

}