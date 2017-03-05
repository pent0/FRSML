#include "Matrix4x4.h"

namespace FRSML {

	Matrix4::Matrix4(float* row1, float* row2, float* row3, float* row4) {
		this->rows[0] = row1;
		this->rows[1] = row2;
		this->rows[2] = row3;
		this->rows[3] = row4;

		cols[0] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 3),
			_mm_extract_psn(this->rows[1].MainVector(), 3),
			_mm_extract_psn(this->rows[2].MainVector(), 3),
			_mm_extract_psn(this->rows[3].MainVector(), 3));

		cols[1] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 2),
			_mm_extract_psn(this->rows[1].MainVector(), 2),
			_mm_extract_psn(this->rows[2].MainVector(), 2),
			_mm_extract_psn(this->rows[3].MainVector(), 2));

		cols[2] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 1),
			_mm_extract_psn(this->rows[1].MainVector(), 1),
			_mm_extract_psn(this->rows[2].MainVector(), 1),
			_mm_extract_psn(this->rows[3].MainVector(), 1));

		cols[3] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 0),
			_mm_extract_psn(this->rows[1].MainVector(), 0),
			_mm_extract_psn(this->rows[2].MainVector(), 0),
			_mm_extract_psn(this->rows[3].MainVector(), 0));

	}

	Matrix4::Matrix4(float** content) {
		
		this->rows[0] = content[0];
		this->rows[1] = content[1];
		this->rows[2] = content[2];
		this->rows[3] = content[3];

		cols[0] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 3),
			_mm_extract_psn(this->rows[1].MainVector(), 3),
			_mm_extract_psn(this->rows[2].MainVector(), 3),
			_mm_extract_psn(this->rows[3].MainVector(), 3));

		cols[1] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 2),
			_mm_extract_psn(this->rows[1].MainVector(), 2),
			_mm_extract_psn(this->rows[2].MainVector(), 2),
			_mm_extract_psn(this->rows[3].MainVector(), 2));

		cols[2] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 1),
			_mm_extract_psn(this->rows[1].MainVector(), 1),
			_mm_extract_psn(this->rows[2].MainVector(), 1),
			_mm_extract_psn(this->rows[3].MainVector(), 1));

		cols[3] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 0),
			_mm_extract_psn(this->rows[1].MainVector(), 0),
			_mm_extract_psn(this->rows[2].MainVector(), 0),
			_mm_extract_psn(this->rows[3].MainVector(), 0));
	}

	Matrix4::Matrix4(float n ) {
		this->rows[0] = n;
		this->rows[1] = n;
		this->rows[2] = n;
		this->rows[3] = n;

		cols[0] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 3),
			_mm_extract_psn(this->rows[1].MainVector(), 3),
			_mm_extract_psn(this->rows[2].MainVector(), 3),
			_mm_extract_psn(this->rows[3].MainVector(), 3));

		cols[1] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 2),
			_mm_extract_psn(this->rows[1].MainVector(), 2),
			_mm_extract_psn(this->rows[2].MainVector(), 2),
			_mm_extract_psn(this->rows[3].MainVector(), 2));

		cols[2] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 1),
			_mm_extract_psn(this->rows[1].MainVector(), 1),
			_mm_extract_psn(this->rows[2].MainVector(), 1),
			_mm_extract_psn(this->rows[3].MainVector(), 1));

		cols[3] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 0),
			_mm_extract_psn(this->rows[1].MainVector(), 0),
			_mm_extract_psn(this->rows[2].MainVector(), 0),
			_mm_extract_psn(this->rows[3].MainVector(), 0));
	}

	Matrix4::Matrix4(vec4 row1, vec4 row2, vec4 row3, vec4 row4) {
		this->rows[0] = row1;
		this->rows[1] = row2;
		this->rows[2] = row3;
		this->rows[3] = row4;

		cols[0] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 3),
			_mm_extract_psn(this->rows[1].MainVector(), 3),
			_mm_extract_psn(this->rows[2].MainVector(), 3),
			_mm_extract_psn(this->rows[3].MainVector(), 3));

		cols[1] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 2),
			_mm_extract_psn(this->rows[1].MainVector(), 2),
			_mm_extract_psn(this->rows[2].MainVector(), 2),
			_mm_extract_psn(this->rows[3].MainVector(), 2));

		cols[2] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 1),
			_mm_extract_psn(this->rows[1].MainVector(), 1),
			_mm_extract_psn(this->rows[2].MainVector(), 1),
			_mm_extract_psn(this->rows[3].MainVector(), 1));

		cols[3] = _mm_set_ps(_mm_extract_psn(this->rows[0].MainVector(), 0),
			_mm_extract_psn(this->rows[1].MainVector(), 0),
			_mm_extract_psn(this->rows[2].MainVector(), 0),
			_mm_extract_psn(this->rows[3].MainVector(), 0));

	}

	bool Matrix4::IsMatrixIndentiy() {
		if (this->rows[0].X() == 1 &&
			this->rows[1].Y() == 1 &&
			this->rows[2].Z() == 1 &&
			this->rows[3].W() == 1)
			return true;

		return false;
	}

	Matrix4 CreatePerspectiveMatrix(float zoom,
		vec2 extent,
		float zNear,
		float zFar) {

		float aspect = extent.X() / extent.Y();

		__m128 t0 = _mm_set1_ps(1);
		__m128 t1 = _mm_set1_ps(zoom / 2);
		__m128 t2 = _mm_set1_ps(aspect);
		__m128 t3 = _mm_set1_ps(zNear);
		__m128 t4 = _mm_set1_ps(zFar);
		__m128 t5 = _mm_sub_ps(t3, t4);

		__m128 grand1 = _mm_div_ps(t0, nmmintrin::_Tan(t1));
		__m128 grand2 = _mm_mul_ps(_mm_div_ps(t0, t2), grand1);

		__m128 grand3 = _mm_sub_ps(t4,t3);
		grand3 = _mm_div_ps(t4,grand3);
		
		__m128 grand4 = _mm_sub_ps(t4,t3);
		grand4 = _mm_div_ps(_mm_mul_ps(t4, _mm_mul_ps(_mm_set1_ps(-1), t3)), grand4);

		float fn1 = _mm_extract_psn(grand1, 3);
		float fn2 = _mm_extract_psn(grand2, 3);
		float fn3 = _mm_extract_psn(grand3, 3);
		float fn4 = _mm_extract_psn(grand4, 3);

		return Matrix4{
			{fn1,0,0,0},
			{0,fn2,0,0},
			{0,0,fn3,1},
			{0,0,fn4,0}
		};
	}


	Matrix4 LookAt(vec3 camPos, vec3 camTarget) {
		//CamDirection equals to the z yaw.
		vec3 camDir = (camTarget - camPos).Normalize();
		//Cam roll - x
		vec3 camRight = Cross(vec3::Up, camDir);
		vec3 camUp = Cross(camDir, camRight);

		vec4 row1{ camDir,0 };
		vec4 row2{ camRight,0 };
		vec4 row3{ camUp,0 };
		vec4 row4{ 0,0,0,1 };

		vec4 col1{ 1,0,0,0 };
		vec4 col2{ 0,1,0,0 };
		vec4 col3{ 0,0,1,0 };
		vec4 col4{ camPos, -1 };

		col4.MainVector() = _mm_sub_ps(_mm_set_ps1(0), col4.MainVector());

		Matrix4 mat1{ row1,row2,row3,row4 };
		Matrix4 mat2{ col1,col2,col3,col4 };
		mat2 = mat2.Transpose();

		return mat1*mat2;
	}

	Matrix4 CreateOrthoMatrix(float left,
		float right, float bottom,
		float top, float zNear, float zFar) {

		float t1 = 2 / (right - left);
		float t2 = 2 / (top - bottom);
		float t3 = -(right + left) / (right - left);
		float t4 = -(top + bottom) / (top - bottom);
		float t5 = -2 / (zFar - zNear);
		float t6 = -(zFar + zNear) / (zFar - zNear);

		return Matrix4{
			{t1,0,0,t3},
			{0,t2,0,t4},
			{0,0,t5,t6},
			{0,0,0,1}
		};

	}

	float** value_ptr(Matrix4 mat) {
		float** valueptr;

		for (short i = 0; i <= 3; i++) {
			for (short j = 0; j <= 3; j++)
			{
				valueptr[i][j] = _mm_extract_psn(mat.rows[i].MainVector(), 3);
			}
		}

		return valueptr;
	}

	Matrix4 Matrix4::Inverse() {

		Matrix4 protector = *this;
		//I personally want to avoid loop in optimazation library
		/*
		
		Matrix4 identity{ { 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 } };
		__m128 temp;

		for (int i = 0; i < 4; i++) {
			/*
			int c[4]; 

			//Lazy code fix soon
			c[0] = (protector.rows[0].MainVector().m128_f32[3-i]) == 0;
			c[1] = (protector.rows[1].MainVector().m128_f32[3-i]) == 0;
			c[2] = (protector.rows[2].MainVector().m128_f32[3-i]) == 0;
			c[3] = (protector.rows[3].MainVector().m128_f32[3-i]) == 0;

			for (int j = 0; j < 4; j++) {
				if (c[j] && i != j) {
					std::cout << i << " " << j << std::endl;
					vec4 temp = protector.rows[j];
					protector.rows[j] = protector.rows[i];
					protector.rows[i] = temp;

					temp = identity.rows[j];
					identity.rows[j] = identity.rows[i];
					identity.rows[i] = temp;
				}
			}

			
			const int shfVal = 3 - i;
			//temp = _mm_shuffle_ps(protector.rows[i].MainVector(), protector.rows[i].MainVector(), _MM_SHUFFLE(shfVal, shfVal, shfVal, shfVal));
			float temp = protector.rows[i].MainVector().m128_f32[3 - i];
			protector.rows[i] /= temp;
			identity.rows[i] /= temp;


			for (int j = 0; j < 4; j++) {
				if (j!=i) {
					float tempk = protector.rows[j].MainVector().m128_f32[3 - i];
					protector.rows[j] -= protector.rows[i] * tempk;
					identity.rows[j] -= identity.rows[i] * tempk;
				}
			
			}

			std::cout << "PROTECTOR: " << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					std::cout << protector[i][j] << " ";
				std::cout << std::endl;
			}

			std::cout << "IDENTITY: " << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					std::cout << identity[i][j] << " ";
				std::cout << std::endl;
			}


		}
		
		return identity; */
		
		Matrix4 identity{
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,0,1}
		};

#pragma region STEP1
		__m128 t1 = _mm_shuffle_ps(protector.rows[0].MainVector(), protector.rows[0].MainVector(), _MM_SHUFFLE(3, 3, 3, 3));
		protector.rows[0] /= t1; identity.rows[0] /= t1;

		__m128 t2 = _mm_shuffle_ps(protector.rows[1].MainVector(),protector.rows[1].MainVector(),_MM_SHUFFLE(3,3,3,3));
		protector.rows[1] -= protector.rows[0] * t2;
		identity.rows[1] -= identity.rows[0] * t2;

		t2 = _mm_shuffle_ps(protector.rows[2].MainVector(), protector.rows[2].MainVector(), _MM_SHUFFLE(3, 3, 3, 3));
		protector.rows[2] -= protector.rows[0] * t2;
		identity.rows[2] -= identity.rows[0] * t2;

		t2 = _mm_shuffle_ps(protector.rows[3].MainVector(), protector.rows[3].MainVector(), _MM_SHUFFLE(3, 3, 3, 3));
		protector.rows[3] -= protector.rows[0] * t2;
		identity.rows[3] -= identity.rows[0] * t2;

#pragma endregion
        //Divide the first row with the first element itself in protector, also take the first element got there to be divided with first row of identity
		//Subtract things. Hard to imagine, but we just got the first element got self to multi... Can't tell enough
#pragma region STEP2
		t1 = _mm_shuffle_ps(protector.rows[1].MainVector(), protector.rows[1].MainVector(), _MM_SHUFFLE(2, 2, 2, 2));
		protector.rows[1] /= t1; identity.rows[1] /= t1;

		t2 = _mm_shuffle_ps(protector.rows[0].MainVector(), protector.rows[0].MainVector(), _MM_SHUFFLE(2, 2, 2, 2));
		protector.rows[0] -= protector.rows[1] * t2;
		identity.rows[0] -= identity.rows[1] * t2;

		t2 = _mm_shuffle_ps(protector.rows[2].MainVector(), protector.rows[2].MainVector(), _MM_SHUFFLE(2, 2, 2, 2));
		protector.rows[2] -= protector.rows[1] * t2;
		identity.rows[2] -= identity.rows[1] * t2;

		t2 = _mm_shuffle_ps(protector.rows[3].MainVector(), protector.rows[3].MainVector(), _MM_SHUFFLE(2, 2, 2, 2));
		protector.rows[3] -= protector.rows[1] * t2;
		identity.rows[3] -= identity.rows[1] * t2;
#pragma endregion
		//Divide the second with the first element itself in protector, also take the second element got there to be divided with second row of identity
		//Like up there
#pragma region STEP3
		t1 = _mm_shuffle_ps(protector.rows[2].MainVector(), protector.rows[2].MainVector(), _MM_SHUFFLE(1, 1, 1, 1));
		protector.rows[2] /= t1; identity.rows[2] /= t1;

		t2 = _mm_shuffle_ps(protector.rows[0].MainVector(), protector.rows[0].MainVector(), _MM_SHUFFLE(1, 1, 1, 1));
		protector.rows[0] -= protector.rows[2] * t2;
		identity.rows[0] -= identity.rows[2] * t2;

		t2 = _mm_shuffle_ps(protector.rows[1].MainVector(), protector.rows[1].MainVector(), _MM_SHUFFLE(1, 1, 1, 1));
		protector.rows[1] -= protector.rows[2] * t2;
		identity.rows[1] -= identity.rows[2] * t2;

		t2 = _mm_shuffle_ps(protector.rows[3].MainVector(), protector.rows[3].MainVector(), _MM_SHUFFLE(1, 1, 1, 1));
		protector.rows[3] -= protector.rows[2] * t2;
		identity.rows[3] -= identity.rows[2] * t2;
#pragma endregion
		//Divide the third with the first element itself in protector, also take the third element got there to be divided with second row of identity
		//Like up there
#pragma region STEP4
		t1 = _mm_shuffle_ps(protector.rows[3].MainVector(), protector.rows[3].MainVector(), _MM_SHUFFLE(0, 0, 0, 0));
		protector.rows[3] /= t1; identity.rows[3] /= t1;

		t2 = _mm_shuffle_ps(protector.rows[0].MainVector(), protector.rows[0].MainVector(), _MM_SHUFFLE(0, 0, 0, 0));
		protector.rows[0] -= protector.rows[3] * t2;
		identity.rows[0] -= identity.rows[3] * t2;

		t2 = _mm_shuffle_ps(protector.rows[1].MainVector(), protector.rows[1].MainVector(), _MM_SHUFFLE(0, 0, 0, 0));
		protector.rows[1] -= protector.rows[3] * t2;
		identity.rows[1] -= identity.rows[3] * t2;

		t2 = _mm_shuffle_ps(protector.rows[2].MainVector(), protector.rows[2].MainVector(), _MM_SHUFFLE(0, 0, 0, 0));
		protector.rows[2] -= protector.rows[3] * t2;
		identity.rows[2] -= identity.rows[3] * t2;
#pragma endregion
		//Do the same step again, we got the input matrix become identity matrix! And the identity become inverse matrix of input!

		return identity;

	}

	Matrix4 Matrix4::operator*(Matrix4 _para){
		__m128 newRow[4];

		__m128 row1 = _para.rows[0].MainVector();
		__m128 row2 = _para.rows[1].MainVector();
		__m128 row3 = _para.rows[2].MainVector();
		__m128 row4 = _para.rows[3].MainVector();

		//Except this one, i have no idea
		for (int i = 0; i < 4; i++) {

			__m128 t1 = _mm_shuffle_ps(rows[i].MainVector(), rows[i].MainVector(), _MM_SHUFFLE(3,3,3,3));
			__m128 t2 = _mm_shuffle_ps(rows[i].MainVector(), rows[i].MainVector(), _MM_SHUFFLE(2, 2, 2, 2));
			__m128 t3 = _mm_shuffle_ps(rows[i].MainVector(), rows[i].MainVector(), _MM_SHUFFLE(1, 1, 1, 1));
			__m128 t4 = _mm_shuffle_ps(rows[i].MainVector(), rows[i].MainVector(), _MM_SHUFFLE(0, 0, 0, 0));

			__m128 c1 = _mm_mul_ps(t1, row1);
			__m128 c2 = _mm_mul_ps(t2, row2);
			c1 = _mm_add_ps(c1, c2);

			c2 = _mm_mul_ps(t3, row3);
			__m128 c3 = _mm_mul_ps(t4, row4);
			c2 = _mm_add_ps(c2, c3);
			c2 = _mm_add_ps(c1, c2);

			newRow[i] = c2;
		}

		return Matrix4(newRow[0],newRow[1],newRow[2],newRow[3]);
	}

	Matrix4 Matrix4::Transpose() {
		return Matrix4(cols[0], cols[1], cols[2], cols[3]);
	}

	std::ostream& operator <<(std::ostream& stream, Matrix4 matrix) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				stream << matrix[i][j] << " ";
			stream << "\n";
		}

		stream << "\n";

		return stream;
	}

	Matrix4 Matrix4::operator +(Matrix4 _para) {
		Matrix4 temp;
		temp.rows[0] = rows[0] + _para.rows[0];
		temp.rows[1] = rows[1] + _para.rows[1];
		temp.rows[2] = rows[2] + _para.rows[2];
		temp.rows[3] = rows[3] + _para.rows[3];
	
		return temp;
	}

	Matrix4 Matrix4::operator -(Matrix4 _para) {
		Matrix4 temp;

		temp.rows[0] = rows[0] - _para.rows[0];
		temp.rows[1] = rows[1] - _para.rows[1];
		temp.rows[2] = rows[2] - _para.rows[2];
		temp.rows[3] = rows[3] - _para.rows[3];

		return temp;
	}

	float Matrix4::Determinant() {

		__m128 template0; {
			__m128 t1 = _mm_shuffle_ps(rows[1].MainVector(),rows[1].MainVector(),_MM_SHUFFLE(2,1,0,3));
			__m128 t2 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(1, 0, 2, 3));
			__m128 t3 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(0,2,1,3));
			__m128 t4 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(0, 2, 1, 3));
			__m128 t5 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(1, 0, 2, 3));
			template0 = _mm_mul_ps(_mm_set_ps1(rows[0].X()), t1);
			template0 = _mm_mul_ps(template0, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		
		};

		__m128 template1;  {
			__m128 t1 = _mm_shuffle_ps(rows[1].MainVector(), rows[1].MainVector(), _MM_SHUFFLE(3, 1, 0, 2));
			__m128 t2 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(0, 3, 1, 2));
			__m128 t3 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(1, 0, 3, 2));
			__m128 t4 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(1, 0, 3, 2));
			__m128 t5 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(0, 3, 1, 2));
			template1 = _mm_mul_ps(_mm_set_ps1(rows[0].Y()), t1);
			template1 = _mm_mul_ps(template1, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 template2; {
			__m128 t1 = _mm_shuffle_ps(rows[1].MainVector(), rows[1].MainVector(), _MM_SHUFFLE(3, 2, 0, 1));
			__m128 t2 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(2, 0, 3, 1));
			__m128 t3 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(0, 3, 2, 1));
			__m128 t4 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(0, 3, 2, 1));
			__m128 t5 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(2, 0, 3, 1));
			template2 = _mm_mul_ps(_mm_set_ps1(rows[0].Z()), t1);
			template2 = _mm_mul_ps(template2, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 template3; {
			__m128 t1 = _mm_shuffle_ps(rows[1].MainVector(), rows[1].MainVector(), _MM_SHUFFLE(3, 2, 1, 0));
			__m128 t2 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(1, 3, 2, 0));
			__m128 t3 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(2, 1, 3, 0));
			__m128 t4 = _mm_shuffle_ps(rows[2].MainVector(), rows[2].MainVector(), _MM_SHUFFLE(2, 1, 3, 0));
			__m128 t5 = _mm_shuffle_ps(rows[3].MainVector(), rows[3].MainVector(), _MM_SHUFFLE(1, 3, 2, 0));
			template3 = _mm_mul_ps(_mm_set_ps1(rows[0].W()), t1);
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

	Matrix4 Translate(Matrix4 base, vec3 trans) {
		
		Matrix4 temp = Identity;

		temp.rows[0].W() = trans.X();
		temp.rows[1].W() = trans.Y();
		temp.rows[3].W() = trans.Z();

		temp *= base;

		return temp;
	}

	Matrix4 Rotate(Matrix4 base, float rot, vec3 dir) {

		Matrix4 temp = Identity;

		float t = Cos(rot);
		float t2 = Sin(rot);

		if (dir == vec3::Left) {
			temp[2][2] = t;
			temp[2][3] = -t2;
			temp[3][2] = t2;
			temp[3][3] = t;
		}
		else if (dir == vec3::Up) {
			temp[1][1] = t;
			temp[1][3] = t2;
			temp[3][1] = -t2;
			temp[3][3] = t;
		}
		else if (dir == vec3::Forward) {
			temp[1][1] = t;
			temp[1][2] = -t2;
			temp[2][1] = t2;
			temp[2][2] = t;
		}

		temp *= base;

		return temp;

	}

	Matrix4 Scale(Matrix4 base, float scale) {

		Matrix4 temp = Identity;

		temp.rows[0].X() = scale;
		temp.rows[1].Y() = scale;
		temp.rows[3].Z() = scale;

		temp *= base;

		return temp;
	}

}