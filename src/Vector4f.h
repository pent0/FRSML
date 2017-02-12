#ifndef VECTOR4F_H
#define VECTOR4F_H

#include <smmintrin.h>


#ifdef _WIN32
#ifdef FRSML_EXPORTS
#define TFAPI __declspec(dllexport)
#else
#define TFAPI __declspec(dllimport)
#endif
#endif

namespace FRSML {
	class TFAPI vec4 {
	public:

		vec4(float ant = 0);
		vec4(float x, float y, float z, float w);
		vec4(float* as);

		__m128& MainVector();
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

		float X();
		float Y();
		float Z();
		float W();

		float Length();
		vec4 Normalize();

	private:
		__m128 mainVec;

	};
}

#endif
