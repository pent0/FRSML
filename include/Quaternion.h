#pragma once

#include "../include/Config.h"
#include <smmintrin.h>

#include "Standard.h"
#include "Matrix.h"

namespace FRSML {

	using namespace nmmintrin;

	class TFAPI Quaternion {
	public:
		Quaternion(float x = 0, float y = 0, float z = 0, float w = 1){
			mainQuat = _mm_set_ps(w, x, y, z);
		}

		Quaternion(__m128 quatVal) {
			mainQuat = quatVal;
		}
		
		operator mat4();

		__m128& MainQuat() {
			return mainQuat;
		}

		float& X(); float& Y(); float& Z(); float& W();

		inline static Quaternion Euler(vec3 euler);
		inline static Quaternion Rotate(vec3 axis, float angle);

		//Add two quaternion
		inline Quaternion operator +(Quaternion tar1);

		//Multi-quat!! Get it?
		inline Quaternion operator *(Quaternion tar1);
		Quaternion Normalize();

	private:
		__m128 mainQuat;
	};

	//Get the dot product of two quat
	TFAPI Quaternion Dot(Quaternion _para1, Quaternion _para2);

	//Get the angle create between two vec4
	TFAPI Quaternion Angle(Quaternion _para1, Quaternion _para2);
}
