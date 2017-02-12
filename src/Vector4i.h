#ifndef VECTOR4I_H
#define VECTOR4I_H

#include <smmintrin.h>
#include <intrin.h>
#include "Vector4f.h"
#include "FRSVar.h"

#ifdef _WIN32
#ifdef FRSML_EXPORTS
#define TFAPI __declspec(dllexport)
#else
#define TFAPI __declspec(dllimport)
#endif
#endif

namespace FRSML {
	class TFAPI vec4i {
	public:

		vec4 ConvertToVector4f();
	
		vec4i(__m128i _gene);

		vec4i(FRS_int ant);


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
