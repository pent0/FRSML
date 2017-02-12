#include "VectorAnt.h"

namespace FRSML {

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
		return !(_mm_movemask_ps(_mm_cmpeq_ps(this->mainVec, ant.mainVec))!=1);
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


	vec2 vec2::Down = vec2(0, -1);
	vec2 vec2::Up = vec2(0, 1);
	vec2 vec2::Left = vec2(-1,0);
	vec2 vec2::Right = vec2(1, 0);

	float vec2::Length() {
		//0x31 = 0011 0001
		//0011 represents 0,0,x,y
		//0001 represents the place to store the result - the lowest bit
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mainVec, mainVec, 0x31)));
	}


	vec2::vec2(__m128 _para) {
		this->mainVec = _para;
	}

	vec2::vec2(float x, float y) {
		this->mainVec = _mm_set_ps(0, 0, x, y);;
	}


	vec2::vec2(float n) {
		this->mainVec = _mm_set_ps(0, 0, n, n);
	}

	bool vec2::operator ==(vec2 ant) {
		//Test all one ps but long written
		return (_mm_movemask_ps(_mm_cmpeq_ps(this->mainVec, ant.mainVec)) == 1);
	}


	bool vec2::operator !=(vec2 ant) {
		//Test all one ps but long written
		return (_mm_movemask_ps(_mm_cmpeq_ps(this->mainVec, ant.mainVec)) != 1);
	}

	vec2 vec2::Normalize() {
		__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainVec, mainVec, 0x33));
		return vec2(_mm_mul_ps(mainVec, inverse_normalize));
	}

	vec3 vec3::Normalize() {
		__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainVec, mainVec, 0x77));
		return vec3(_mm_mul_ps(mainVec, inverse_normalize));
	}


#pragma region ORIGINAL_MATH_OPERATOR

	vec2 vec2::operator +(vec2 ant) {
		return _mm_add_ps(this->mainVec, ant.mainVec);
	}

	vec2 vec2::operator -(vec2 ant) {
		return _mm_sub_ps(this->mainVec, ant.mainVec);
	}


	vec2 vec2::operator *(vec2 ant) {
		return _mm_mul_ps(this->mainVec, ant.mainVec);
	}


	vec2 vec2::operator /(vec2 ant) {
		return _mm_div_ps(this->mainVec, ant.mainVec);
	}

#pragma endregion

	vec2 vec2::operator +(float ant) {
		return _mm_add_ps(this->mainVec, _mm_set1_ps(ant));
	}


	vec2 vec2::operator -(float ant) {
		return _mm_sub_ps(this->mainVec, _mm_set1_ps(ant));
	}


	vec2 vec2::operator *(float ant) {
		return _mm_mul_ps(this->mainVec, _mm_set1_ps(ant));
	}


	vec2 vec2::operator /(float ant) {
		return _mm_div_ps(this->mainVec, _mm_set1_ps(ant));
	}


	void vec2::operator +=(vec2 ant) {
		*this = *this + ant;
	}


	void vec2::operator -=(vec2 ant) {
		*this = *this - ant;
	}


	void vec2::operator *=(vec2 ant) {
		*this = *this * ant;
	}


	void vec2::operator /=(vec2 ant) {
		*this = *this / ant;
	}



	void vec2::operator +=(float ant) {
		*this = *this + ant;
	}


	void  vec2::operator -=(float ant) {
		*this = *this - ant;
	}


	void vec2::operator *=(float ant) {
		*this = *this * ant;
	}


	void vec2::operator /=(float ant) {
		*this = *this / ant;
	}

	void vec2::operator ++() {
		*this = *this + 1;
	}

	void vec2::operator --() {
		*this = *this - 1;
	}

	vec2 vec2::operator& (vec2 _para) {
		return vec2(_mm_and_ps(this->mainVec, _para.mainVec));
	}


	vec2 vec2::operator^ (vec2 _para) {
		return vec2(_mm_xor_ps(this->mainVec, _para.mainVec));
	}

	vec2 vec2::operator| (vec2 _para) {
		return vec2(_mm_or_ps(this->mainVec, _para.mainVec));
	}


	float& vec2::X() {
		return mainVec.m128_f32[1];
	}


	float& vec2::Y() {
		return mainVec.m128_f32[0];
	}

	void vec2::operator |=(vec2 ant) {
		*this = *this | ant;
	}


	void vec2::operator &=(vec2 ant) {
		*this = *this & ant;
	}


	void vec2::operator ^=(vec2 ant) {
		*this = *this ^ ant;
	}

}

