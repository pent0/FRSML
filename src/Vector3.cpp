#include "Vector.h"

namespace FRSML {

	vec3 vec3::Down = vec3(0, -1, 0);
	vec3 vec3::Forward = vec3(0, 0, 1);
	vec3 vec3::Backward = vec3(0, 0, -1);
	vec3 vec3::Up = vec3(0, 1, 0);
	vec3 Left = vec3(-1, 0, 0);
	vec3 Right = vec3(1, 0, 0);


	float vec3::Length() {
		//0x71 = 0111 0001
		//0111 represents 0,x,y,z
		//0001 represents the place to store the result - the lowest bit
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mainVec, mainVec, 0x71)));
	}

	vec3::vec3(__m128 _para) {
		this->mainVec = _para;
	}

	vec3::vec3(float x, float y, float z) {
		this->mainVec = _mm_set_ps(0, x, y, z);;
	}


	vec3::vec3(float n) {
		this->mainVec = _mm_set_ps(0, n, n, n);
	}


	bool vec3::operator ==(vec3 ant) {
		//Test all one ps but long written
		return !(_mm_movemask_ps(_mm_cmpeq_ps(this->mainVec, ant.mainVec)) != 1);
	}


	bool vec3::operator !=(vec3 ant) {
		//Test all one ps but long written
		return (_mm_movemask_ps(_mm_cmpeq_ps(this->mainVec, ant.mainVec)) != 1);
	}




#pragma region ORIGINAL_MATH_OPERATOR

	vec3 vec3::operator +(vec3 ant) {
		return _mm_add_ps(this->mainVec, ant.mainVec);
	}

	vec3 vec3::operator -(vec3 ant) {
		return _mm_sub_ps(this->mainVec, ant.mainVec);
	}


	vec3 vec3::operator *(vec3 ant) {
		return _mm_mul_ps(this->mainVec, ant.mainVec);
	}


	vec3 vec3::operator /(vec3 ant) {
		return _mm_div_ps(this->mainVec, ant.mainVec);
	}

#pragma endregion

	vec3 vec3::operator +(float ant) {
		return _mm_add_ps(this->mainVec, _mm_set1_ps(ant));
	}


	vec3 vec3::operator -(float ant) {
		return _mm_sub_ps(this->mainVec, _mm_set1_ps(ant));
	}


	vec3 vec3::operator *(float ant) {
		return _mm_mul_ps(this->mainVec, _mm_set1_ps(ant));
	}


	vec3 vec3::operator /(float ant) {
		return _mm_div_ps(this->mainVec, _mm_set1_ps(ant));
	}

	vec3 vec3::operator& (vec3 _para) {
		return vec3(_mm_and_ps(this->mainVec, _para.mainVec));
	}


	vec3 vec3::operator^ (vec3 _para) {
		return vec3(_mm_xor_ps(this->mainVec, _para.mainVec));
	}

	vec3 vec3::operator| (vec3 _para) {
		return vec3(_mm_or_ps(this->mainVec, _para.mainVec));
	}


	float& vec3::X() {
		return mainVec.m128_f32[2];
	}

	float& vec3::Y() {
		return mainVec.m128_f32[1];
	}

	float& vec3::Z() {
		return mainVec.m128_f32[0];
	}

	float* value_ptr(vec3 vec) {
		float* value;
		value[0] = vec.X();
		value[1] = vec.Y();
		value[2] = vec.Z();

		return value;
	}
}
