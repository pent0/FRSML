#pragma once

#include <smmintrin.h>
#include <iostream>

#include "Standard.h"
#include "Vector.h"

namespace FRSML {

	class TFAPI Matrix4 {
	public:

		Matrix4(float** rowContent);
		Matrix4(float* row1, float* row2, float* row3, float* row4);
		Matrix4(float n = 0);
		Matrix4(vec4 row1, vec4 row2, vec4 row3, vec4 row4);

		vec4 rows[4] = {};

		bool IsMatrixIndentiy();

		Matrix4 Transpose();
		float Determinant();

		//Wrapper to return the member number of Matrix
		struct Matrix4Proxy
		{
			Matrix4* matrix;
			int matrixIndex1;

			Matrix4Proxy(Matrix4 *mat, int i) : matrix(mat), matrixIndex1(i) {}

			//I do not feel sastified with this :-(
			float& operator [](std::size_t matrixIndex2)
			{
				return matrix->rows[matrixIndex1].MainVector().m128_f32[3 - matrixIndex2];
			}

		};

		//Return the number given by its position
		Matrix4Proxy operator[](std::size_t i) {
			return Matrix4Proxy(this, i);
		}

		friend Matrix4 Translate(Matrix4 base, vec3 trans);

		//Rotate a matrix with axis
		//You can use Quaternion instead. I'm also provide an converter of Euler vector
		friend TFAPI Matrix4 Rotate(Matrix4 base, float rot, vec3 dir);

		friend Matrix4 Scale(Matrix4 base, float scale);

		friend float** value_ptr(Matrix4 mat);

		//Very sad that this method is o(n^3), but i can just understand this max.
		Matrix4 Inverse();

		friend vec4 operator * (vec4 _para1, Matrix4 _para2);

		inline Matrix4 operator *(Matrix4 _para);

		inline void operator *= (Matrix4 _para) {
			*this = *this*_para;
		}

		inline Matrix4 operator +(Matrix4 _para);
		inline Matrix4 operator -(Matrix4 _para);

	private:

		vec4 cols[4] = {};
	};

	static Matrix4 Identity{
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 }
	};

	static Matrix4 Zero{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	};

	TFAPI Matrix4 CreatePerspectiveMatrix(float zoom,
		vec2 extent,
		float zNear,
		float zFar);

	TFAPI Matrix4 CreateOrthoMatrix(float left,
		float right, float bottom,
		float top, float zNear, float zFar);

	//I have the up vector already.
	TFAPI Matrix4 LookAt(vec3 camPos, vec3 camTarget, vec3 up);

	TFAPI std::ostream& operator <<(std::ostream&, Matrix4);

	
};


