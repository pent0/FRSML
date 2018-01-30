#ifndef FRSML_QUATERNION_H
#define FRSML_QUATERNION_H

#include <frsml/internal.h>
#include <frsml/vector.h>

namespace frsml {
	
	class mat4;

	struct FRS_MATH_API quat: public vec4 {
		quat();
		quat(float w, float x, float y, float z);

		quat operator * (quat p_quat);

		quat normalize();

		static quat euler(vec3 p_euler);
		static quat rotate(vec3 p_axis, float p_angle);

		operator mat4();
	};
}

#endif