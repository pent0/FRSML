#include "Quaternion.h"

namespace FRSML {
	Quaternion Quaternion::Normalize() {
		__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainQuat, mainQuat, 0xFF));
		return Quaternion(_mm_mul_ps(mainQuat, inverse_normalize));
	}

	Quaternion Quaternion::operator+(Quaternion tar1) {
		return Quaternion(_mm_add_ps(this->mainQuat, tar1.mainQuat));
	}

	Quaternion Quaternion::CreateQuat(vec3 euler) {

		//return (float)(FRS_float(radians)*HALFWISEANGLE / PI)

		vec3 tmp = _mm_div_ps(_mm_mul_ps(euler.MainVector(),_mm_set1_ps(PI)),_mm_set1_ps(180));

		__m128 t1 = _mm_shuffle_ps(tmp.MainVector(), tmp.MainVector(), _MM_SHUFFLE(2, 2, 2, 2));
		__m128 t2 = _mm_shuffle_ps(tmp.MainVector(), tmp.MainVector(), _MM_SHUFFLE(1, 1, 1, 1));
		__m128 t3 = _mm_shuffle_ps(tmp.MainVector(), tmp.MainVector(), _MM_SHUFFLE(0, 0, 0, 0));

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

	Quaternion Quaternion::CreateQuat(vec3 axis, float angle) {
		vec3 tmp = axis.Normalize();

		__m128 tmp2 = (_mm_div_ps(_mm_set1_ps(angle), _mm_set1_ps(2)));
		__m128 tmp3 = _mm_shuffle_ps(tmp.MainVector(), tmp.MainVector(), _MM_SHUFFLE(2, 2, 2, 2));
		__m128 tmp4 = _mm_shuffle_ps(tmp.MainVector(), tmp.MainVector(), _MM_SHUFFLE(1, 1, 1, 1));
		__m128 tmp5 = _mm_shuffle_ps(tmp.MainVector(), tmp.MainVector(), _MM_SHUFFLE(0, 0, 0, 0));

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


	float& Quaternion::X() {
		return mainQuat.m128_f32[2];
	}

	float& Quaternion::Y() {
		return mainQuat.m128_f32[1];
	}
	
	float& Quaternion::Z() {
		return mainQuat.m128_f32[0];
	}
	
	float& Quaternion::W() {
		return mainQuat.m128_f32[3];
	}

	Quaternion Quaternion::operator *(Quaternion tar1) {
		__m128 t1 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(3, 3, 3, 3));
		__m128 t2 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 t3 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 t4 = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(0, 0, 0, 0));
	
		__m128 grand0; {
			__m128 c1 = _mm_shuffle_ps(tar1.mainQuat, tar1.mainQuat, _MM_SHUFFLE(3, 2, 1, 0));
			grand0 = _mm_mul_ps(t1, c1);
		};

		__m128 grand1; {
			__m128 c1 = _mm_shuffle_ps(tar1.mainQuat, tar1.mainQuat, _MM_SHUFFLE(2, 3, 0, 1));
			grand1 = _mm_mul_ps(t2, c1);
		};

		__m128 grand2; {
			__m128 c1 = _mm_shuffle_ps(tar1.mainQuat, tar1.mainQuat, _MM_SHUFFLE(1, 0, 3, 2));
			grand2 = _mm_mul_ps(t3, c1);
		};

		__m128 grand3; {
			__m128 c1 = _mm_shuffle_ps(tar1.mainQuat, tar1.mainQuat, _MM_SHUFFLE(0, 1, 2, 3));
			grand3 = _mm_mul_ps(t4, c1);
		};

		grand1 = _mm_mul_ps(grand1, _mm_set_ps(-1, 1, -1, 1));
		grand2 = _mm_mul_ps(grand2, _mm_set_ps(-1, 1, 1, -1));
		grand3 = _mm_mul_ps(grand3, _mm_set_ps(-1, -1, 1, 1));

		grand0 = _mm_add_ps(grand0, _mm_add_ps(grand1, _mm_add_ps(grand2, grand3)));


		return Quaternion(grand0);
	}
}