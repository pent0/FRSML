#ifndef FRSML_MATRIX_H
#define FRSML_MATRIX_H

#include <frsml/internal.h>
#include <frsml/vector.h>

namespace frsml {

	struct FRS_MATH_API mat4 {
		mat4();
		mat4(vec4 p_cols[4]);
		mat4(float p_floats[16]);

		inline mat4 operator +(mat4 p_mat);
		inline mat4 operator -(mat4 p_mat);
		inline mat4 operator *(mat4 p_mat);

		long determinant();

		mat4 inverse();
		mat4 transpose();

		mat4 translate(vec3 p_trans);
		mat4 rotate(float p_angle, vec3 p_dir);
		mat4 scale(float p_scale);

		vec4 cols[4];
	};
}
	
#endif