#ifndef VECTORANT_H
#define VECTORANT_H

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

		vec2(__m128 _para);
		vec2(float x, float y);
		vec2(float n = 0);

		__m128& MainVector() {
			return mainVec;
		}

		float X, Y;

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

		operator float*() const {

			float* value;
			value[0] = mainVec.m128_f32[3];
			value[1] = mainVec.m128_f32[2];

			return value;
		}

		friend float* value_ptr(vec2 vec);

		inline vec2 Normalize();

	private:

		void SetRealXY(float newX, float newY) {
			X = newX;
			Y = newY;
		}

		void SetRealXY(__m128 _para) {
			X = _para.m128_f32[1];
			Y = _para.m128_f32[0];
		}

		__m128 mainVec;
	};

	//A Vector3 class SIMD
	class TFAPI vec3 {
	public:
		vec3(__m128 _para);
		vec3(float x, float y, float Z);
		vec3(float n = 0);

		__m128& MainVector() {
			return mainVec;
		}

		float X, Y, Z = 0;

		inline bool operator == (vec3 ant);
		inline bool operator != (vec3 ant);
		inline vec3 operator +(vec3 ant);

		inline void operator +=(vec3 ant) {
			mainVec = _mm_add_ps(mainVec, ant.mainVec);
			SetRealXY(mainVec);
		}

		inline vec3 operator + (float ant);
		inline void operator += (float ant) {
			mainVec = _mm_sub_ps(mainVec, _mm_set1_ps(ant));
			SetRealXY(mainVec);
		}
		inline void operator ++() {
			mainVec = _mm_add_ps(mainVec, _mm_set1_ps(1));
			SetRealXY(mainVec);
		}
		inline vec3 operator -(vec3 ant);
		inline vec3 operator -(float ant);
		inline void operator -=(vec3 ant) {
			mainVec = _mm_sub_ps(mainVec, ant.mainVec);
			SetRealXY(mainVec);
		}
		inline void operator -=(float ant) {
			mainVec = _mm_sub_ps(mainVec, _mm_set1_ps(ant));
			SetRealXY(mainVec);
		}
		inline void operator --() {
			mainVec = _mm_sub_ps(mainVec, _mm_set1_ps(1));
			SetRealXY(mainVec);
		}
		inline vec3 operator *(vec3 ant);
		inline vec3 operator *(float ant);
		inline void operator *=(vec3 ant) {
			mainVec = _mm_mul_ps(mainVec, ant.mainVec);
			SetRealXY(mainVec);
		}
		inline void operator *=(float ant) {
			mainVec = _mm_mul_ps(mainVec, _mm_set1_ps(ant));
			SetRealXY(mainVec);
		}
		inline vec3 operator /(vec3 ant);
		inline vec3 operator /(float ant);
		inline void operator /=(vec3 ant) {
			mainVec = _mm_div_ps(mainVec, ant.mainVec);
			SetRealXY(mainVec);
		}
		inline void operator /=(float ant) {
			mainVec = _mm_div_ps(mainVec, _mm_set1_ps(ant));
			SetRealXY(mainVec);
		}

		inline vec3 operator &(vec3 ant);
		inline void operator &=(vec3 ant) {
			mainVec = _mm_and_ps(mainVec, ant.mainVec);
			SetRealXY(mainVec);
		}
		inline vec3 operator ^(vec3 ant);
		inline void operator ^=(vec3 ant) {
			mainVec = _mm_xor_ps(mainVec, ant.mainVec);
			SetRealXY(mainVec);
		}
		inline vec3 operator |(vec3 ant);
		inline void operator |=(vec3 ant) {
			mainVec = _mm_or_ps(mainVec, ant.mainVec);
			SetRealXY(mainVec);
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

		operator float*() const {

			float* value;
			value[0] = mainVec.m128_f32[3];
			value[1] = mainVec.m128_f32[2];
			value[2] = mainVec.m128_f32[1];

			return value;
		}

	private:
		__m128 mainVec;

		void SetRealXY(float newX, float newY, float newZ) {
			X = newX;
			Y = newY;
			Z = newZ;
		}

		void SetRealXY(__m128 _para) {
			X = _para.m128_f32[2];
			Y = _para.m128_f32[1];
			Z = _para.m128_f32[0];
		}

	};


	class TFAPI vec4 {
	public:

		vec4(float ant = 0);
		vec4(float x, float y, float z, float w);
		vec4(float* as);
		vec4(vec3 _para, float _para2);

		__m128& MainVector();
		vec4(__m128 _set);
		void operator =(vec4 ant);
		bool operator ==(vec4 ant);
		vec4 operator +(vec4 ant);
		vec4 operator -(vec4 ant);
		void operator -=(vec4 ant) {
			*this = *this - ant;
			SetRealXY(mainVec);
		}

		void operator +=(vec4 ant) {
			*this = *this - ant;
			SetRealXY(mainVec);
		}

		void operator *=(vec4 ant) {
			*this = *this * ant;
			SetRealXY(mainVec);
		}

		void operator /=(vec4 ant) {
			*this = *this / ant;
			SetRealXY(mainVec);
		}

		vec4 operator *(vec4 ant);
		vec4 operator /(vec4 ant);
		vec4 operator +(float ant);
		vec4 operator -(float ant);
		vec4 operator *(float ant);
		vec4 operator /(float ant);
		void operator /=(float ant) {
			*this = *this / ant;
			SetRealXY(mainVec);
		}

		friend float* value_ptr(vec4 vec);

		float X, Y, Z, W = 0;

		float Length();
		vec4 Normalize();

		operator float*() const {

			float* value;
			value[0] = mainVec.m128_f32[3];
			value[1] = mainVec.m128_f32[2];
			value[2] = mainVec.m128_f32[1];
			value[3] = mainVec.m128_f32[0];

			return value;
		}

	private:
		__m128 mainVec;

		void SetRealXY(float newX, float newY, float newZ, float newW) {
			X = newX;
			Y = newY;
			Z = newZ;
			W = newW;
		}

		void SetRealXY(__m128 _para) {
			X = _para.m128_f32[3];
			Y = _para.m128_f32[2];
			Z = _para.m128_f32[1];
			W = _para.m128_f32[0];
		}

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
