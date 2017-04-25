#ifndef VECTORANT_H
#define VECTORANT_H

#pragma warning (disable: 4700)

#include <nmmintrin.h>
#include <functional>
#include <intrin.h>

#ifdef _WIN32
	#ifdef FRSML_EXPORTS
		#define TFAPI __declspec(dllexport)
	#define TFTEMPLATE
	#else
		#define TFAPI __declspec(dllimport)
		#define TFTEMPLATE extern
	#endif
#endif



namespace FRSML{

	//I dont love _mm_shuffle so much, it's mask is __
	//A Vector2 class SIMD
	class TFAPI vec2 {
	public:

		float x, y = 0;

		vec2(const vec2& ot) {
			x = ot.x;
			y = ot.y;
		}

		vec2(__m128 at) {
			__m128 t1 = _mm_shuffle_ps(at, at, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 t2 = _mm_shuffle_ps(at, at, _MM_SHUFFLE(0, 0, 0, 0));

			x = _mm_cvtss_f32(t1);
			y = _mm_cvtss_f32(t2);

		}

		vec2(float x, float y);
		vec2(float n = 0);

		float& operator [](std::size_t matrixIndex2)
		{
			switch (matrixIndex2) {
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			default:
				break;
			}

		}

		__m128 GenerateXYZW() {
			return _mm_set_ps(0,0,x,y);
		} 


		inline bool operator == (vec2 ant);
		inline bool operator != (vec2 ant);

		inline vec2 operator +(vec2 ant);
		inline void operator +=(vec2 ant);
		inline vec2 operator + (float ant);
		inline void operator += (float ant);
		inline void operator ++();
		inline vec2 operator -(vec2 ant);
		inline vec2 operator -(float ant);
		inline void operator -=(vec2 ant);
		inline void operator -=(float ant);
		inline void operator --();
		inline vec2 operator *(vec2 ant);
		inline vec2 operator *(float ant);
		inline void operator *=(vec2 ant);
		inline void operator *=(float ant);
		inline vec2 operator /(vec2 ant);
		inline vec2 operator /(float ant);
		inline void operator /=(vec2 ant);
		inline void operator /=(float ant);

		inline vec2 operator &(vec2 ant);
		inline void operator &=(vec2 ant);
		inline vec2 operator ^(vec2 ant);
		inline void operator ^=(vec2 ant);
		inline vec2 operator |(vec2 ant);
		inline void operator |=(vec2 ant);

		//@ Return the length of a Vector2 vec
		//Using dot product with mask = 0x31 = 0011 0001, 
		//we can dot 3 floats with themselves and put it in the lowest bit.
		inline float Length();

		static vec2 Down;
		static vec2 Up;
		static vec2 Left;
		static vec2 Right;

		explicit operator float*() const {

			float value[2];

			value[0] = x;
			value[1] = y;

			return value;
		}

		friend float* value_ptr(vec2 vec);

		inline vec2 Normalize();

	private:

	};

	//A Vector3 class SIMD
	class TFAPI vec3 {
	public:
		vec3(__m128 _para);
		vec3(float x, float y, float Z);
		vec3(float n = 0);

		float x, y, z = 0;

		inline bool operator == (vec3 ant);
		inline bool operator != (vec3 ant);
		inline vec3 operator +(vec3 ant);
		inline void operator +=(vec3 ant) {
			*this = *this + ant;
		}

		inline vec3 operator + (float ant);
		inline void operator += (float ant) {
			*this = *this + ant;
		}

		inline void operator ++() {
			*this = *this + 1;
		}
		inline vec3 operator -(vec3 ant);
		inline vec3 operator -(float ant);
		inline void operator -=(vec3 ant) {
			*this = *this - ant;
		}
		inline void operator -=(float ant) {
			*this = *this - ant;
		}
		inline void operator --() {
			*this = *this - 1;
		}
		inline vec3 operator *(vec3 ant);
		inline vec3 operator *(float ant);
		inline void operator *=(vec3 ant) {
			*this = *this * ant;
		}
		inline void operator *=(float ant) {
			*this = *this * ant;
		}
		inline vec3 operator /(vec3 ant);
		inline vec3 operator /(float ant);
		inline void operator /=(vec3 ant) {
			*this = *this / ant;
		}
		inline void operator /=(float ant) {
			*this = *this / ant;
		}

		inline vec3 operator &(vec3 ant);
		inline void operator &=(vec3 ant) {
			*this = *this & ant;
		}
		inline vec3 operator ^(vec3 ant);
		inline void operator ^=(vec3 ant) {
			*this = *this ^ ant;
		}
		inline vec3 operator |(vec3 ant);
		inline void operator |=(vec3 ant) {
			*this = *this | ant;
		}

		static vec3 Down;
		static vec3 Forward;
		static vec3 Backward;
		static vec3 Up;
		static vec3 Left;
		static vec3 Right;

		friend float* value_ptr(vec3 vec);
		//@ Return the length of a Vector3 vec
		//Using dot product with mask = 0x71 = 0111 0001, 
		//we can dot 3 floats with themselves and put it in the lowest bit.
		inline float Length();

		inline vec3 Normalize();

		explicit operator float*() const {

			float value[3];

			value[0] = x;
			value[1] = y;
			value[2] = z;

			return value;
		}

		__m128 GenerateXYZW() {
			return _mm_set_ps(0, x, y, z);
		}

	private:
	

	};


	struct TFAPI vec4 {
	public:

		vec4(float ant = 0);
		vec4(float x, float y, float z, float w);
		vec4(float* as);
		vec4(vec3 _para, float _para2);

		vec4(__m128 _set);
		void operator =(vec4 ant);
		bool operator ==(vec4 ant);
		vec4 operator +(vec4 ant);
		vec4 operator -(vec4 ant);
		void operator -=(vec4 ant) {
			*this = *this - ant;
		}

		void operator +=(vec4 ant) {
			*this = *this - ant;
		}

		void operator *=(vec4 ant) {
			*this = *this * ant;
		}

		void operator /=(vec4 ant) {
			*this = *this / ant;
		}

		vec4 operator *(vec4 ant);
		vec4 operator /(vec4 ant);
		vec4 operator +(float ant);
		vec4 operator -(float ant);
		vec4 operator *(float ant);
		vec4 operator /(float ant);
		void operator /=(float ant) {
			*this = *this / ant;
		}

		friend float* value_ptr(vec4 vec);

		float x, y, z, w = 0;

		float Length();
		vec4 Normalize();

		explicit operator float*() const {

			float* value = (float*)malloc(sizeof(float) * 4);
			value[0] = x;
			value[1] = y;
			value[2] = z;
			value[3] = w;

			return value;
		}

		float& operator [](std::size_t matrixIndex2)
		{
			switch (matrixIndex2) {
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

		}

		__m128 GenerateXYZW() {
			return _mm_set_ps(x, y, z, w);
		}

	private:

	};

	/*Decrepated, but still in use*/
	class TFAPI vec4i {
	public:

		vec4 ConvertToVector4f();

		vec4i(__m128i _gene);

		//vec4i(FRS_int ant);


		vec4i(int x, int y, int w, int z);

		vec4i(int t = 0);

		int& X();

		int& Y();

		int& Z();

		int& W();

		void operator =(vec4i ant);

		vec4i operator ==(vec4i ant);


#pragma region OPERATOR

		vec4i operator + (vec4i ant);
		vec4i operator -(vec4i ant);
		vec4i operator * (vec4i ant);
		vec4i operator /(vec4i ant);

		vec4i operator +(int ant);
		vec4i operator -(int ant);
		vec4i operator *(int ant);
		vec4i operator /(int ant);

		void operator +=(vec4i ant);

		void operator -=(vec4i ant);

		void operator *=(vec4i ant);

		void operator +=(int ant);

		void operator -=(int ant);

		void operator *=(int ant);

		void operator /=(int ant);

		vec4i operator &(vec4i ant);

		void operator &=(vec4i ant);

		vec4i operator ^(vec4i ant);

		void operator ^=(vec4i ant);

		vec4i operator |(vec4i ant);

		void operator |=(vec4i ant);

		float Length();

		__m128i& MainVector();

#pragma endregion

	private:
		__m128i mainVec;
		void _frs_getmagnum_i(int divisor, __m128i& mul, __m128i& shift1, __m128i& sign);

	};


}

#endif
