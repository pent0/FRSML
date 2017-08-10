#include "math_internal.h"

namespace frs {

	vec2 vec2::up = vec2(0, 1);
	vec2 vec2::down = vec2(0, -1);
	vec2 vec2::left = vec2(-1, 0);
	vec2 vec2::right = vec2(1, 0);

	vec2::vec2() = default;
	vec2::vec2(const vec2& p_vec) : x(p_vec.x), y(p_vec.y) {};
	vec2::vec2(const float x, const float y) : x(x), y(y) {};
	
	float& vec2::operator [](u8 p_index) {
		switch (p_index) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		default:
			break;
		}

		return x;
	}

	inline bool vec2::operator == (vec2 p_vec) {
		return (p_vec.x == x) && (p_vec.y == y);
	}

	inline bool vec2::operator != (vec2 p_vec) {
		return !(p_vec == *this);
	}

	inline vec2 vec2::operator +(vec2 p_vec) {
		return vec2(x + p_vec.x, y + p_vec.y);
	}

	inline void vec2::operator +=(vec2 p_vec) {
		x += p_vec.x;
		y += p_vec.y;
	}

	inline vec2 vec2::operator +(float p_num) {
		return vec2(x + p_num, y + p_num);
	}

	inline void vec2::operator +=(float p_num) {
		x += p_num;
		y += p_num;
	}

	inline void vec2::operator++() {
		x++;
		y++;
	}

	inline vec2 vec2::operator -(vec2 p_vec) {
		return vec2(x - p_vec.x, y - p_vec.y);
	}

	inline void vec2::operator -=(vec2 p_vec) {
		x -= p_vec.x;
		y -= p_vec.y;
	}

	inline vec2 vec2::operator -(float p_num) {
		return vec2(x - p_num, y - p_num);
	}

	inline void vec2::operator -=(float p_num) {
		x -= p_num;
		y -= p_num;
	}

	inline void vec2::operator --() {
		x--; 
		y--;
	}

	inline vec2 vec2::operator * (vec2 p_vec) {
		return vec2(x * p_vec.x, y * p_vec.y);
	}

	inline void vec2::operator *= (vec2 p_vec) {
		x *= p_vec.x;
		y *= p_vec.y;
	}

	inline vec2 vec2::operator *(float p_num) {
		return vec2(x * p_num, y * p_num);
	}

	inline void vec2::operator *= (float p_num) {
		x *= p_num;
		y *= p_num;
	}

	inline vec2 vec2::operator / (vec2 p_vec) {
		return vec2(x / p_vec.x, y / p_vec.y);
	}

	inline void vec2::operator /= (vec2 p_vec) {
		x /= p_vec.x;
		y /= p_vec.y;
	}

	inline vec2 vec2::operator /(float p_num) {
		return vec2(x / p_num, y / p_num);
	}

	inline void vec2::operator /= (float p_num) {
		x /= p_num;
		y /= p_num;
	}

	inline float vec2::length() {
#ifdef FRS_OPTIMIZED
		__m128 t_vec = to_pack4(*this);

		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(t_vec, t_vec, 0x31)));
#else
		return sqrt(x * x + y * y);
#endif
	}

	inline vec2 vec2::normalize() {
#ifdef FRS_OPTIMIZED
		__m128 t_vec = to_pack4(*this);
		__m128 t_rlength = _mm_sqrt_ps(_mm_dp_ps(t_vec, t_vec, 0x33));

		return to_vec2(_mm_div_ps(t_vec, t_rlength));
#else
		float t_length = length();

		return vec2(x / t_length, y / t_length);
#endif
	}

	vec3::vec3(const vec2& p_vec, float p_z) : vec2(p_vec) {
		z = p_z;
	}

	vec3::vec3() : vec2() {};

	vec3::vec3(const float p_x,const float p_y,const float p_z) : vec2(p_x, p_y) {
		z = p_z;
	}

	float& vec3::operator[](u8 p_index) {
		switch (p_index) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		default:
			break;
		}

		return x;
	}

	inline bool vec3::operator == (vec3 p_vec) {
		return (p_vec.x == x) && (p_vec.y == y)
			&& (p_vec.z == z);
	}

	inline bool vec3::operator != (vec3 p_vec) {
		return !(p_vec == *this);
	}

	inline vec3 vec3::operator +(vec3 p_vec) {
		return vec3(x + p_vec.x, y + p_vec.y, z + p_vec.z);
	}

	inline void vec3::operator +=(vec3 p_vec) {
		x += p_vec.x;
		y += p_vec.y;
		z += p_vec.z;
	}

	inline vec3 vec3::operator +(float p_num) {
		return vec3(x + p_num, y + p_num, z + p_num);
	}

	inline void vec3::operator +=(float p_num) {
		x += p_num;
		y += p_num;
		z += p_num;
	}

	inline void vec3::operator++() {
		x++;
		y++;
		z++;
	}

	inline vec3 vec3::operator -(vec3 p_vec) {
		return vec3(x - p_vec.x, y - p_vec.y, z - p_vec.z);
	}

	inline void vec3::operator -=(vec3 p_vec) {
		x -= p_vec.x;
		y -= p_vec.y;
		z -= p_vec.z;
	}

	inline vec3 vec3::operator -(float p_num) {
		return vec3(x - p_num, y - p_num, z - p_num);
	}

	inline void vec3::operator -=(float p_num) {
		x -= p_num;
		y -= p_num;
		z -= p_num;
	}

	inline void vec3::operator --() {
		x--;
		y--;
		z--;
	}

	inline vec3 vec3::operator * (vec3 p_vec) {
		return vec3(x * p_vec.x, y * p_vec.y, z * p_vec.z);
	}

	inline void vec3::operator *= (vec3 p_vec) {
		x *= p_vec.x;
		y *= p_vec.y;
		z *= p_vec.z;
	}

	inline vec3 vec3::operator *(float p_num) {
		return vec3(x * p_num, y * p_num, z * p_num);
	}

	inline void vec3::operator *= (float p_num) {
		x *= p_num;
		y *= p_num;
		z *= p_num;
	}

	inline vec3 vec3::operator / (vec3 p_vec) {
		return vec3(x / p_vec.x, y / p_vec.y, z / p_vec.z);
	}

	inline void vec3::operator /= (vec3 p_vec) {
		x /= p_vec.x;
		y /= p_vec.y;
		z /= p_vec.z;
	}

	inline vec3 vec3::operator /(float p_num) {
		return vec3(x / p_num, y / p_num, z / p_num);
	}

	inline void vec3::operator /= (float p_num) {
		x /= p_num;
		y /= p_num;
		z /= p_num;
	}

	inline float vec3::length() {
#ifdef FRS_OPTIMIZED
		__m128 t_vec = to_pack4(*this);

		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(t_vec, t_vec, 0x31)));
#else
		return sqrt(x * x + y * y + z * z);
#endif
	}

	inline vec3 vec3::normalize() {
#ifdef FRS_OPTIMIZED
		__m128 t_vec = to_pack4(*this);
		__m128 t_rlength = _mm_sqrt_ps(_mm_dp_ps(t_vec, t_vec, 0x33));

		return to_vec3(_mm_div_ps(t_vec, t_rlength));
#else
		float t_length = length();

		return vec3(x / t_length, y / t_length, z / t_length);
#endif
	}

	vec4::vec4() : vec3() {};

	vec4::vec4(const float p_x, const float p_y,
		const float p_z, const float p_w) : vec3(p_x, p_y, p_z) {
		w = p_w;
	}

	vec4::vec4(const vec3& p_vec, float p_w): vec3(p_vec) {
		w = p_w;
	}

	float& vec4::operator[](u8 p_index) {
		switch (p_index) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		case 3:
			return w;
			break;
		default:
			break;
		}

		return x;
	}

	inline bool vec4::operator == (vec4 p_vec) {
		return (p_vec.x == x) && (p_vec.y == y)
			&& (p_vec.z == z) && (p_vec.w == w);
	}

	inline bool vec4::operator != (vec4 p_vec) {
		return !(p_vec == *this);
	}

	inline vec4 vec4::operator +(vec4 p_vec) {
		return vec4(x + p_vec.x, y + p_vec.y, z + p_vec.z,
			w + p_vec.w);
	}

	inline void vec4::operator +=(vec4 p_vec) {
		x += p_vec.x;
		y += p_vec.y;
		z += p_vec.z;
		w += p_vec.w;
	}

	inline vec4 vec4::operator +(float p_num) {
		return vec4(x + p_num, y + p_num, z + p_num,
			w + p_num);
	}

	inline void vec4::operator +=(float p_num) {
		x += p_num;
		y += p_num;
		z += p_num;
		w += p_num;
	}

	inline void vec4::operator++() {
		x++;
		y++;
		z++;
		w++;
	}

	inline vec4 vec4::operator -(vec4 p_vec) {
		return vec4(x - p_vec.x, y - p_vec.y, z - p_vec.z,
			w - p_vec.w);
	}

	inline void vec4::operator -=(vec4 p_vec) {
		x -= p_vec.x;
		y -= p_vec.y;
		z -= p_vec.z;
		w -= p_vec.w;
	}

	inline vec4 vec4::operator -(float p_num) {
		return vec4(x - p_num, y - p_num, z - p_num,
			w - p_num);
	}

	inline void vec4::operator -=(float p_num) {
		x -= p_num;
		y -= p_num;
		z -= p_num;
		w -= p_num;
	}

	inline void vec4::operator --() {
		x--;
		y--;
		z--;
		w--;
	}

	inline vec4 vec4::operator * (vec4 p_vec) {
		return vec4(x * p_vec.x, y * p_vec.y, z * p_vec.z,
			w * p_vec.w);
	}

	inline void vec4::operator *= (vec4 p_vec) {
		x *= p_vec.x;
		y *= p_vec.y;
		z *= p_vec.z;
		w *= p_vec.w;
	}

	inline vec4 vec4::operator *(float p_num) {
		return vec4(x * p_num, y * p_num, z * p_num,
			w * p_num);
	}

	inline void vec4::operator *= (float p_num) {
		x *= p_num;
		y *= p_num;
		z *= p_num;
		w *= p_num;
	}

	inline vec4 vec4::operator / (vec4 p_vec) {
		return vec4(x / p_vec.x, y / p_vec.y, z / p_vec.z,
			w / p_vec.w);
	}

	inline void vec4::operator /= (vec4 p_vec) {
		x /= p_vec.x;
		y /= p_vec.y;
		z /= p_vec.z;
		w /= p_vec.w;
	}

	inline vec4 vec4::operator /(float p_num) {
		return vec4(x / p_num, y / p_num, z / p_num,
			w / p_num);
	}

	inline void vec4::operator /= (float p_num) {
		x /= p_num;
		y /= p_num;
		z /= p_num;
		w /= p_num;
	}

	inline float vec4::length() {
#ifdef FRS_OPTIMIZED
		__m128 t_vec = to_pack4(*this);

		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(t_vec, t_vec, 0x31)));
#else
		return sqrt((x * x + y * y + 
			z * z + w * w));
#endif
	}

	inline vec4 vec4::normalize() {
#ifdef FRS_OPTIMIZED
		__m128 t_vec = to_pack4(*this);
		__m128 t_rlength = _mm_sqrt_ps(_mm_dp_ps(t_vec, t_vec, 0x33));

		return to_vec4(_mm_div_ps(t_vec, t_rlength));
#else
		float t_length = length();

		return vec4(x / t_length, y / t_length, z / t_length,
			w / t_length);
#endif
	}
}

