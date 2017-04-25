#include "Vector.h"

namespace FRSML {

	vec3 vec3::Down = vec3(0, -1, 0);
	vec3 vec3::Forward = vec3(0, 0, 1);
	vec3 vec3::Backward = vec3(0, 0, -1);
	vec3 vec3::Up = vec3(0, 1, 0);
	vec3 vec3::Left = vec3(-1, 0, 0);
	vec3 vec3::Right = vec3(1, 0, 0);


	float vec3::Length() {
		//0x71 = 0111 0001
		//0111 represents 0,x,y,z
		//0001 represents the place to store the result - the lowest bit
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(GenerateXYZW(), GenerateXYZW(), 0x71)));
	}

	vec3::vec3(__m128 _para) {

		__m128 t1 = _mm_shuffle_ps(_para, _para, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 t2 = _mm_shuffle_ps(_para, _para, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 t3 = _mm_shuffle_ps(_para, _para, _MM_SHUFFLE(0, 0, 0, 0));

		x = _mm_cvtss_f32(t1);
		y = _mm_cvtss_f32(t2);
		z = _mm_cvtss_f32(t3);

	}

	vec3::vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}


	vec3::vec3(float n) {
		this->x = n;
		this->y = n;
		this->z = n;
	}


	bool vec3::operator ==(vec3 ant) {
		//Test all one ps but long written
		return (x == ant.x
			&& y == ant.y
			&& z == ant.z);
	}


	bool vec3::operator !=(vec3 ant) {
		//Test all one ps but long written
		return (x != ant.x
			|| y != ant.y
			|| z != ant.z);
	}




#pragma region ORIGINAL_MATH_OPERATOR

	vec3 vec3::operator +(vec3 ant) {
		vec3 temp{};

		temp.x = x + ant.x;
		temp.y = y + ant.y;
		temp.z = z + ant.z;

		return temp;
	}

	vec3 vec3::operator -(vec3 ant) {
		vec3 temp{};

		temp.x = x - ant.x;
		temp.y = y - ant.y;
		temp.z = z - ant.z;

		return temp;
	}


	vec3 vec3::operator *(vec3 ant) {
		vec3 temp{};

		temp.x = x * ant.x;
		temp.y = y * ant.y;
		temp.z = z * ant.z;

		return temp;
	}


	vec3 vec3::operator /(vec3 ant) {
		vec3 temp{};

		temp.x = x / ant.x;
		temp.y = y / ant.y;
		temp.z = z / ant.z;

		return temp;
	}

#pragma endregion

	vec3 vec3::operator +(float ant) {
		vec3 temp{};

		temp.x = x + ant;
		temp.y = y + ant;
		temp.z = z + ant;

		return temp;
	}


	vec3 vec3::operator -(float ant) {
		vec3 temp{};

		temp.x = x - ant;
		temp.y = y - ant;
		temp.z = z - ant;

		return temp;
	}


	vec3 vec3::operator *(float ant) {

		vec3 temp{};

		temp.x = x * ant;
		temp.y = y * ant;
		temp.z = z * ant;

		return temp;
	}


	vec3 vec3::operator /(float ant) {
		vec3 temp{};

		temp.x = x / ant;
		temp.y = y / ant;
		temp.z = z / ant;

		return temp;
	}

	vec3 vec3::operator& (vec3 _para) {
		return vec3(_mm_and_ps(GenerateXYZW(), _para.GenerateXYZW()));
	}


	vec3 vec3::operator^ (vec3 _para) {
		return vec3(_mm_xor_ps(GenerateXYZW(), _para.GenerateXYZW()));
	}

	vec3 vec3::operator| (vec3 _para) {
		return vec3(_mm_or_ps(GenerateXYZW(), _para.GenerateXYZW()));
	}


	float* value_ptr(vec3 vec) {
		float* value;

		value[0] = vec.x;
		value[1] = vec.y;
		value[2] = vec.z;

		return value;
	}
}
