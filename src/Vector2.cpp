#include "Vector.h"

namespace FRSML {




	vec2 vec2::Down = vec2(0, -1);
	vec2 vec2::Up = vec2(0, 1);
	vec2 vec2::Left = vec2(-1,0);
	vec2 vec2::Right = vec2(1, 0);

	float* value_ptr(vec2 vec) {
		float* value;
		value[0] = vec.x;
		value[1] = vec.y;
		
		return value;
	}

	float vec2::Length() {
		//0x31 = 0011 0001
		//0011 represents 0,0,x,y
		//0001 represents the place to store the result - the lowest bit
		__m128 mainVec = GenerateXYZW();
		
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mainVec, mainVec, 0x31)));
	}


	vec2::vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}


	vec2::vec2(float n) {
		this->x = n;
		this->y = n;
	}

	bool vec2::operator ==(vec2 ant) {
		//Test all one ps but long written
		return (x == ant.x
			&& y == ant.y);
	}


	bool vec2::operator !=(vec2 ant) {
		//Test all one ps but long written
		return (_mm_movemask_ps(_mm_cmpeq_ps(GenerateXYZW()
			, ant.GenerateXYZW())) != 0xF);
	}

	vec2 vec2::Normalize() {
		__m128 mainVec = GenerateXYZW();

		__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainVec, mainVec, 0x33));
		inverse_normalize.m128_f32[3] = inverse_normalize.m128_f32[2] = 0;
		return vec2(
			_mm_mul_ps(mainVec, inverse_normalize));
	}

	vec3 vec3::Normalize() {
		__m128 mainVec = GenerateXYZW();

		__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainVec, mainVec, 0x77));
		//Quick dirty way to prevent inf
		inverse_normalize.m128_f32[3] = 0;
		return vec3(_mm_mul_ps(mainVec, inverse_normalize));
	}


#pragma region ORIGINAL_MATH_OPERATOR

	vec2 vec2::operator +(vec2 ant) {
		vec2 temp{};

		temp.x = x + ant.x;
		temp.y = y + ant.y;

		return temp;
	}

	vec2 vec2::operator -(vec2 ant) {
		vec2 temp{};

		temp.x = x - ant.x;
		temp.y = y - ant.y;

		return temp;
	}


	vec2 vec2::operator *(vec2 ant) {
		vec2 temp{};

		temp.x = x * ant.x;
		temp.y = y * ant.y;

		return temp;
	}


	vec2 vec2::operator /(vec2 ant) {
		vec2 temp{};

		temp.x = x / ant.x;
		temp.y = y / ant.y;

		return temp;
	}

#pragma endregion

	vec2 vec2::operator +(float ant) {
		vec2 temp{};

		temp.x = x + ant;
		temp.y = y + ant;

		return temp;
	}


	vec2 vec2::operator -(float ant) {
		vec2 temp{};

		temp.x = x - ant;
		temp.y = y - ant;

		return temp;
	}


	vec2 vec2::operator *(float ant) {
		vec2 temp{};

		temp.x = x * ant;
		temp.y = y * ant;

		return temp;
	}


	vec2 vec2::operator /(float ant) {
		vec2 temp{};

		temp.x = x / ant;
		temp.y = y / ant;

		return temp;
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
		return vec2(_mm_and_ps(GenerateXYZW(), 
			_para.GenerateXYZW()));
	}


	vec2 vec2::operator^ (vec2 _para) {
		return vec2(_mm_xor_ps(GenerateXYZW(),
			_para.GenerateXYZW()));
	}

	vec2 vec2::operator| (vec2 _para) {
		return vec2(_mm_or_ps(GenerateXYZW(),
			_para.GenerateXYZW()));
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

