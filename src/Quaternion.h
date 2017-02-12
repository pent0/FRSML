#pragma once

#include <smmintrin.h>
#include "FRSVar.h"
#include "Matrix4x4.h"
#include "StandardMathSSE4.h"

namespace FRSML {
	class TFAPI Quaternion {
	public:
		Quaternion(float x = 0, float y = 0, float z = 0, float w = 1){
			mainQuat = _mm_set_ps(w, x, y, z);
		}

		Quaternion(__m128 quatVal) {
			mainQuat = quatVal;
		}

		/*
		operator Matrix4() {
			Quaternion temp = Normalize();
		}*/

		float& X(); float& Y(); float& Z(); float& W();

		static Quaternion CreateQuaternion(vec3 axis, float angle);

		//Add two quaternion
		inline Quaternion operator +(Quaternion tar1);

		//Multi-quat!! Get it?
		inline Quaternion operator *(Quaternion tar1);
		Quaternion Normalize();

	private:
		__m128 mainQuat;
	};
}
