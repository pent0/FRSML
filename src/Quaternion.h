#pragma once

#include "../include/Config.h"
#include <smmintrin.h>

#include "Standard.h"
#include "Vector.h"
#include "Matrix.h"

namespace FRSML {

	using namespace nmmintrin;

	struct TFAPI Quaternion : public vec4 {
	public:

		Quaternion(float x = 0, float y = 0, float z = 0, float w = 1) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Quaternion(__m128 _para) :vec4(_para) {};

		operator mat4();

		__m128& GenerateXYZW() {
			return _mm_set_ps(w, x, y, z);
		}

		inline static Quaternion Euler(vec3 euler);
		inline static Quaternion Rotate(vec3 axis, float angle);

		//Multi-quat!! Get it?
		inline Quaternion operator *(Quaternion tar1);
		Quaternion Normalize();

	};

	//Get the dot product of two quat
	TFAPI Quaternion Dot(Quaternion _para1, Quaternion _para2);

	//Get the angle create between two vec4
	TFAPI Quaternion Angle(Quaternion _para1, Quaternion _para2);
}
