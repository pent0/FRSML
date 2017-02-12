#include "Quaternion.h"

namespace FRSML {
	Quaternion Quaternion::Normalize() {
		__m128 mag = _mm_sqrt_ss(_mm_dp_ps(mainQuat, mainQuat, 0xF1));
		mag = _mm_div_ps(mainQuat, mag);
		return Quaternion(mag);
	}

	Quaternion Quaternion::operator+(Quaternion tar1) {
		return Quaternion(_mm_add_ps(this->mainQuat, tar1.mainQuat));
	}

	Quaternion Quaternion::CreateQuaternion(vec3 axis, float angle) {
		float angleQuat = Cos(angle/2);
		float axisX = axis.X() * sin(angle / 2);
		float axisY = axis.Y() * sin(angle / 2);
		float axisZ = axis.Z() * sin(angle / 2);
		return Quaternion(angleQuat, axisX, axisY, axisZ);
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