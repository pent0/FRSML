#ifndef FRSML_QUATERNION_H
#define FRSML_QUATERNION_H

#include "internal.h"
#include "vector.h"
#include "matrix.h"

namespace frsml {
	
	struct mat4;

	struct FRS_MATH_API quat: public vec4 {
		quat();
		quat(float w, float x, float y, float z);

		quat operator * (quat p_quat);

		quat normalize() const;

		static quat euler(vec3 p_euler);
		static quat rotate(vec3 p_axis, float p_angle);

		explicit operator frsml::mat4() const;
	};
}

#endif