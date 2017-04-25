#pragma once

#pragma warning(disable: 57)

#include <nmmintrin.h>

#include "Vector.h"
#include "Standard.h"

#ifdef _WIN32
#ifdef FRSML_EXPORTS
#define TFAPI __declspec(dllexport)
#else
#define TFAPI __declspec(dllimport)
#endif
#endif

namespace FRSML {

	struct TFAPI mat4 {
	public:

		mat4();
		mat4(vec4 tCols[4]);
		mat4(float* col1, float* col2, float* col3, float* col4);
		mat4(float** colss);
		mat4(vec4 col1, vec4 col2, vec4 col3, vec4 col4);


		float Determinant();

		//Return the number given by its position
		vec4& operator[](std::size_t i) {
			return cols[i];
		}

		friend TFAPI mat4 Translate(mat4 base, vec3 trans);
		friend TFAPI mat4 Rotate(mat4 base, float rot, vec3 dir);
		friend TFAPI mat4 Scale(mat4 base, float scale);

		mat4 Inverse();
		mat4 Transpose();

		inline mat4 operator *(mat4 _para);

		inline void operator *= (mat4 _para) {
			*this = *this*_para;
		}

		inline mat4 operator +(mat4 _para);
		inline mat4 operator -(mat4 _para);

	private:

		vec4 cols[4] = {};
	};
	

	TFAPI mat4 LookAt(vec3 camPos, vec3 camTarget, vec3 up);

	TFAPI mat4 CreatePerspectiveMatrix(float zoom,
		vec2 extent,
		float zNear,
		float zFar);

	TFAPI mat4 CreateOrthoMatrix(float left,
		float right, float bottom,
		float top, float zNear, float zFar);

	static mat4 Identity{
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 }
	};

	TFAPI float** value_ptr(mat4 mat);

	TFAPI std::ostream& operator <<(std::ostream& stream, mat4 matrix);

	static mat4 Zero{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	};

}
