#ifndef VECTORANT_H
#define VECTORANT_H

#include <nmmintrin.h>
#include <functional>

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
		//This is very diffcult to handle
		float& X(); float& Y();

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

		inline vec2 Normalize();

	private:
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

		float& X();
		float& Y();
		float& Z();

		inline bool operator == (vec3 ant);
		inline bool operator != (vec3 ant);
		inline vec3 operator +(vec3 ant);
		inline void operator +=(vec3 ant) {
			*this = *this + ant;
		}
		inline vec3 operator + (float ant);
		inline void operator += (float ant) {
			*this = *this + vec3(ant);
		}
		inline void operator ++() {
			*this += 1;
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
			*this -= 1;
		}
		inline vec3 operator *(vec3 ant);
		inline vec3 operator *(float ant);
		inline void operator *=(vec3 ant) {
			*this = *this* ant;
		}
		inline void operator *=(float ant) {
			*this = *this * vec3(ant);
		}
		inline vec3 operator /(vec3 ant);
		inline vec3 operator /(float ant);
		inline void operator /=(vec3 ant) {
			*this = *this / ant;
		}
		inline void operator /=(float ant) {
			*this = *this / vec3(ant);
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

	
		//@ Return the length of a Vector3 vec
		//Using dot product with mask = 0x71 = 0111 0001, 
		//we can dot 3 floats with themselves and put it in the lowest bit.
		inline float Length();

		inline vec3 Normalize();

	private:
		__m128 mainVec;

	};


}

#endif
