#include "Matrix.h"
#include <cmath>

namespace FRSML {

	mat4::mat4() {
		cols[0] = vec4(1, 0, 0, 0);
		cols[1] = vec4(0, 1, 0, 0);
		cols[2] = vec4(0, 0, 1, 0);
		cols[3] = vec4(0, 0, 0, 1);

	}

	mat4::mat4(vec4 tCols[4]) {
		cols[0] = tCols[0];
		cols[1] = tCols[1];
		cols[2] = tCols[2];
		cols[3] = tCols[3];

	}

	mat4::mat4(float* col1, float* col2, float* col3, float* col4) {
		cols[0] = vec4(col1);
		cols[1] = vec4(col2);
		cols[2] = vec4(col3);
		cols[3] = vec4(col4);

	}

	mat4::mat4(float** colss) {

		for (uint32_t i = 0; i < 4; i++) {
			cols[i] = vec4(colss[0][i], colss[1][i],
				colss[2][i], colss[3][i]);
		}


	}

	mat4::mat4(vec4 col1, vec4 col2, vec4 col3, vec4 col4) {
		cols[0] = col1;
		cols[1] = col2;
		cols[2] = col3;
		cols[3] = col4;

	}

	mat4 Translate(mat4 base, vec3 trans) {

		mat4 temp = Identity;

		temp.cols[3].x = trans.x;
		temp.cols[3].y = trans.y;
		temp.cols[3].z = trans.z;

		temp *= base;

		return temp;

	}

	mat4 Rotate(mat4 base, float rot, vec3 dir) {

		mat4 temp{};

		float t = FRSML::Cos(rot);
		float t2 = FRSML::Sin(rot);

		if (dir == vec3::Left) {
			temp[1][1] = t;
			temp[2][1] = -t2;
			temp[1][2] = t2;
			temp[2][2] = t;
		}
		else if (dir == vec3::Up) {
			temp[0][0] = t;
			temp[2][0] = t2;
			temp[0][2] = -t2;
			temp[2][2] = t;
		}
		else if (dir == vec3::Forward) {
			temp[0][0] = t;
			temp[1][0] = -t2;
			temp[0][1] = t2;
			temp[1][1] = t;
		}

		temp *= base;

		return temp;

	}

	mat4 Scale(mat4 base, float scale) {
		mat4 val{};

		val[0][0] = val[1][1] = val[2][2] = scale;

		return base*val;
	}

	float** value_ptr(mat4 mat) {

		float** value = (float**)malloc(4 * sizeof(float*));
		
		for (uint32_t i = 0; i < 4; i++) {
			value[i] = (float*)malloc(4 * sizeof(float));
		}

		for (uint32_t i = 0; i < 4; i++) {
			for (uint32_t j = 0; j < 4; j++) {
				value[i][j] = mat[i][j];
			}
		}

		return value;

	}

	mat4 mat4::Inverse() {

		vec4 protectorRows[4];
		vec4 identityRows[4];

		__m128 mainVec[4] = {};

		identityRows[0] = vec4(1, 0, 0, 0);
		identityRows[1] = vec4(0, 1, 0, 0);
		identityRows[2] = vec4(0, 0, 1, 0);
		identityRows[3] = vec4(0, 0, 0, 1);

		for (uint32_t i = 0; i < 4; i++) {

			protectorRows[i] = vec4(this->cols[0][i],
				this->cols[1][i],
				this->cols[2][i],
				this->cols[3][i]);

		}


		mainVec[0] = mainVec[0];
		mainVec[1] = mainVec[1];
		mainVec[2] = mainVec[2];
		mainVec[3] = mainVec[3];

#pragma region STEP1

		__m128 t1 = _mm_shuffle_ps(mainVec[0], mainVec[0], _MM_SHUFFLE(3, 3, 3, 3));
		protectorRows[0] /= t1; identityRows[0] /= t1;

		__m128 t2 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(3, 3, 3, 3));
		protectorRows[1] -= protectorRows[0] * t2;
		identityRows[1] -= identityRows[0] * t2;

		t2 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(3, 3, 3, 3));
		protectorRows[2] -= protectorRows[0] * t2;
		identityRows[2] -= identityRows[0] * t2;

		t2 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(3, 3, 3, 3));
		protectorRows[3] -= protectorRows[0] * t2;
		identityRows[3] -= identityRows[0] * t2;

#pragma endregion
		//Divide the first row with the first element itself in protector, also take the first element got there to be divided with first row of identity
		//Subtract things. Hard to imagine, but we just got the first element got self to multi... Can't tell enough
#pragma region STEP2
		t1 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(2, 2, 2, 2));
		protectorRows[1] /= t1; identityRows[1] /= t1;

		t2 = _mm_shuffle_ps(mainVec[0], mainVec[0], _MM_SHUFFLE(2, 2, 2, 2));
		protectorRows[0] -= protectorRows[1] * t2;
		identityRows[0] -= identityRows[1] * t2;

		t2 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(2, 2, 2, 2));
		protectorRows[2] -= protectorRows[1] * t2;
		identityRows[2] -= identityRows[1] * t2;

		t2 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(2, 2, 2, 2));
		protectorRows[3] -= protectorRows[1] * t2;
		identityRows[3] -= identityRows[1] * t2;
#pragma endregion
		//Divide the second with the first element itself in protector, also take the second element got there to be divided with second row of identity
		//Like up there
#pragma region STEP3
		t1 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(1, 1, 1, 1));
		protectorRows[2] /= t1; identityRows[2] /= t1;

		t2 = _mm_shuffle_ps(mainVec[0], mainVec[0], _MM_SHUFFLE(1, 1, 1, 1));
		protectorRows[0] -= protectorRows[2] * t2;
		identityRows[0] -= identityRows[2] * t2;

		t2 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(1, 1, 1, 1));
		protectorRows[1] -= protectorRows[2] * t2;
		identityRows[1] -= identityRows[2] * t2;

		t2 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(1, 1, 1, 1));
		protectorRows[3] -= protectorRows[2] * t2;
		identityRows[3] -= identityRows[2] * t2;
#pragma endregion
		//Divide the third with the first element itself in protector, also take the third element got there to be divided with second row of identity
		//Like up there
#pragma region STEP4
		t1 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(0, 0, 0, 0));
		protectorRows[3] /= t1; identityRows[3] /= t1;

		t2 = _mm_shuffle_ps(mainVec[0], mainVec[0], _MM_SHUFFLE(0, 0, 0, 0));
		protectorRows[0] -= protectorRows[3] * t2;
		identityRows[0] -= identityRows[3] * t2;

		t2 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(0, 0, 0, 0));
		protectorRows[1] -= protectorRows[3] * t2;
		identityRows[1] -= identityRows[3] * t2;

		t2 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(0, 0, 0, 0));
		protectorRows[2] -= protectorRows[3] * t2;
		identityRows[2] -= identityRows[3] * t2;
#pragma endregion
		//Do the same step again, we got the input matrix become identity matrix! And the identity become inverse matrix of input!
		return mat4(protectorRows).Transpose();


	}

	mat4 mat4::operator *(mat4 _para) {

		__m128 newCols[4] = {};

		__m128 col1 = _mm_set_ps(_para.cols[0].x,
			_para.cols[0].y,
			_para.cols[0].z,
			_para.cols[0].w);

		__m128 col2 = _mm_set_ps(_para.cols[1].x,
			_para.cols[1].y,
			_para.cols[1].z,
			_para.cols[1].w);

		__m128 col3 = _mm_set_ps(_para.cols[2].x,
			_para.cols[2].y,
			_para.cols[2].z,
			_para.cols[2].w);

		__m128 col4 = _mm_set_ps(_para.cols[3].x,
			_para.cols[3].y,
			_para.cols[3].z,
			_para.cols[3].w);;

		for (uint32_t i = 0; i < 4; i++) {
			
			__m128 colPara1 = _mm_set1_ps(cols[i].x);
			__m128 colPara2 = _mm_set1_ps(cols[i].y);
			__m128 colPara3 = _mm_set1_ps(cols[i].z);
			__m128 colPara4 = _mm_set1_ps(cols[i].w);;

			__m128 t1 = _mm_mul_ps(col1, colPara1);
			__m128 t2 = _mm_mul_ps(col2, colPara2);
			__m128 t3 = _mm_mul_ps(col3, colPara3);
			__m128 t4 = _mm_mul_ps(col4, colPara4);

			t1 = _mm_add_ps(t1, t2);
			t3 = _mm_add_ps(t3, t4);
			t4 = _mm_add_ps(t1, t3);

			newCols[i] = t4;

		}

		return mat4{
			newCols[0], newCols[1], newCols[2], newCols[3]
		};

	}

	mat4 mat4::operator +(mat4 _para) {

		vec4 newCols[4] = {};

		for (uint32_t i = 0; i < 4; i++) {
			newCols[i] = cols[i] + _para.cols[i];
		}

		return mat4{ newCols[0], newCols[1], newCols[2], newCols[3] };
	}

	mat4 mat4::operator -(mat4 _para){
		vec4 newCols[4] = {};

		for (uint32_t i = 0; i < 4; i++) {
			newCols[i] = cols[i] - _para.cols[i];
		}

		return mat4{ newCols[0], newCols[1], newCols[2], newCols[3] };
	}

	mat4 mat4::Transpose() {

		vec4 rows[4];

		for (uint32_t i = 0; i < 4; i++) {

			rows[i] = vec4(this->cols[0].GenerateXYZW().m128_f32[3 - i],
				this->cols[1].GenerateXYZW().m128_f32[3 - i],
				this->cols[2].GenerateXYZW().m128_f32[3 - i],
				this->cols[3].GenerateXYZW().m128_f32[3 - i]);

		}

		return mat4(rows);

	}

	float mat4::Determinant() {

		vec4 rows[4] = {};

		for (uint32_t i = 0; i < 4; i++) {

			rows[i] = vec4(this->cols[0].GenerateXYZW().m128_f32[3 - i],
				this->cols[1].GenerateXYZW().m128_f32[3 - i],
				this->cols[2].GenerateXYZW().m128_f32[3 - i],
				this->cols[3].GenerateXYZW().m128_f32[3 - i]);

		}

		__m128 mainVec[4] = {};

		mainVec[1] = mainVec[1];
		mainVec[2] = mainVec[2];
		mainVec[3] = mainVec[3];

		__m128 template0; {
			__m128 t1 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(2, 1, 0, 3));
			__m128 t2 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(1, 0, 2, 3));
			__m128 t3 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(0, 2, 1, 3));
			__m128 t4 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(0, 2, 1, 3));
			__m128 t5 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(1, 0, 2, 3));
			template0 = _mm_mul_ps(_mm_set_ps1(rows[0].x), t1);
			template0 = _mm_mul_ps(template0, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));

		};

		__m128 template1; {
			__m128 t1 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(3, 1, 0, 2));
			__m128 t2 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(0, 3, 1, 2));
			__m128 t3 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(1, 0, 3, 2));
			__m128 t4 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(1, 0, 3, 2));
			__m128 t5 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(0, 3, 1, 2));
			template1 = _mm_mul_ps(_mm_set_ps1(rows[0].y), t1);
			template1 = _mm_mul_ps(template1, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 template2; {
			__m128 t1 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(3, 2, 0, 1));
			__m128 t2 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(2, 0, 3, 1));
			__m128 t3 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(0, 3, 2, 1));
			__m128 t4 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(0, 3, 2, 1));
			__m128 t5 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(2, 0, 3, 1));
			template2 = _mm_mul_ps(_mm_set_ps1(rows[0].z), t1);
			template2 = _mm_mul_ps(template2, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 template3; {
			__m128 t1 = _mm_shuffle_ps(mainVec[1], mainVec[1], _MM_SHUFFLE(3, 2, 1, 0));
			__m128 t2 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(1, 3, 2, 0));
			__m128 t3 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(2, 1, 3, 0));
			__m128 t4 = _mm_shuffle_ps(mainVec[2], mainVec[2], _MM_SHUFFLE(2, 1, 3, 0));
			__m128 t5 = _mm_shuffle_ps(mainVec[3], mainVec[3], _MM_SHUFFLE(1, 3, 2, 0));
			template3 = _mm_mul_ps(_mm_set_ps1(rows[0].w), t1);
			template3 = _mm_mul_ps(template3, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 grandDad = _mm_add_ps(template0,
			_mm_add_ps(template1, _mm_add_ps(template2, template3)));

		__m128 m1 = _mm_shuffle_ps(grandDad, grandDad, _MM_SHUFFLE(3, 3, 3, 3));
		__m128 m2 = _mm_shuffle_ps(grandDad, grandDad, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 m3 = _mm_shuffle_ps(grandDad, grandDad, _MM_SHUFFLE(1, 1, 1, 1));

		m1 = _mm_add_ss(m1, _mm_add_ss(m2, m3));

		return _mm_cvtss_f32(m1);
	}

	mat4 LookAt(vec3 camPos, vec3 camTarget, vec3 up) {
		//CamDirection equals to the z yaw.
		vec3 camDir = (camPos - camTarget).Normalize();
		vec3 camRight = Cross(camDir, up).Normalize();
		vec3 camUp = Cross(camRight, camDir);

		mat4 mat1{ 
			vec4(-camRight.x, camUp.x, camDir.x, 0),
			vec4(-camRight.y, camUp.y, camDir.y, 0),
			vec4(-camRight.z, camUp.z, camDir.z, 0),
			vec4(-Dot(camRight, camPos).x, -Dot(camUp, camPos).y, -Dot(camDir, camPos).z, 1)
		};

		return mat1;
	}

	mat4 CreateOrthoMatrix(float left,
		float right, float bottom,
		float top, float zNear, float zFar) {

		float t1 = 2 / (right - left);
		float t2 = 2 / (top - bottom);
		float t3 = -(right + left) / (right - left);
		float t4 = -(top + bottom) / (top - bottom);
		float t5 = -2 / (zFar - zNear);
		float t6 = -(zFar + zNear) / (zFar - zNear);

		return mat4{
			{ t1,0,0,0 },
			{ 0,t2,0,0 },
			{ 0,0,t5,0 },
			{ t3,t4,t6,1 }
		};

	}

	mat4 CreatePerspectiveMatrix(float zoom,
		vec2 extent,
		float zNear,
		float zFar) {

		float aspect = extent.y / extent.x;

		__m128 t1 = _mm_set1_ps(1);
		__m128 t2 = _mm_set1_ps(zoom / 2);
		//__m128 t3 = _mm_set1_ps(PI / 180);
		__m128 t4 = _mm_mul_ps(t2, /*t3*/ t1);
		t4 = nmmintrin::_Tan(t4);
		t4 = _mm_div_ps(t1, t4);
		__m128 t5 = _mm_set1_ps(zFar - zNear);
		__m128 t6 = _mm_mul_ps(_mm_set1_ps(zNear), _mm_set1_ps(zFar));
		t6 = _mm_div_ps(t6, t5);
		t6 = _mm_mul_ps(_mm_set1_ps(-1), t6);

		__m128 t7 = _mm_set1_ps(zFar);
		t7 = _mm_div_ps(t7, t5);
		t7 = _mm_mul_ps(_mm_set1_ps(-1), t7);

		float grand1 = _mm_extract_psn(t4, 3);
		float grand2 = _mm_extract_psn(t6, 3);
		float grand3 = _mm_extract_psn(t7, 3);

		mat4 returnVal(
		{ grand1 * aspect,0,0,0 },
		{ 0, grand1, 0,0 },
		{ 0,0,grand3, -1 },
		{ 0,0,grand2, 0 }
		);

		return returnVal;

	}

	std::ostream& operator <<(std::ostream& stream, mat4 matrix) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				stream << matrix[i][j] << " ";
			stream << "\n";
		}

		stream << "\n";

		return stream;
	}

}
