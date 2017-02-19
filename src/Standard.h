#ifndef STANARDMATHSSE4_H
#define STANARDMATHSSE4_H

#include <smmintrin.h>
#include <functional>

#include "Vector.h"
#include "FRSVar.h"
#include "AssertSSE.h"

#define EXP2_TABLE_SIZE_LOG2 9
#define MGNBR1 531.7555982144694 
#define MGNBR2 32.521961561056756
#define MGNBR3 9.47803843894324
#define MGNBR4 5040
#define LOG2 1.44269504088896340736 

#define PI 3.14159265358979323846264338327950288f
#define PI2 6.28318530717958647692528676655900577f
#define PID2 1.57079632679489661923132169163975144f
#define PISQ 9.86960440108935861883449099987615114f
#define HALFWISEANGLE FRS_float(180)

#ifdef _WIN32
#ifdef FRSML_EXPORTS
#define TFAPI __declspec(dllexport)
#define TFTEMPLATE
#else
#define TFAPI __declspec(dllimport)
#define TFTEMPLATE extern
#endif
#endif

#define FLOAT_CONST(Key, v) \
    static const __declspec(align(16)) float _F_##Key[4] = { v,v,v, v }

#define INT_CONST(Key, v) \
    static const __declspec(align(16)) int _I_##Key[4] = {v, v, v, v}

FLOAT_CONST(1, 1.0f);
FLOAT_CONST(half, 0.5f);

FLOAT_CONST(cephes_log2, 1.44269504088896341);
FLOAT_CONST(cephes_c1, 0.693359375);
FLOAT_CONST(cephes_c2, -2.12194440e-4);

FLOAT_CONST(cephes_p0, 1.9875691500E-4);
FLOAT_CONST(cephes_p1, 1.3981999507E-3);
FLOAT_CONST(cephes_p2, 8.3334519073E-3);
FLOAT_CONST(cephes_p3, 4.1665795894E-2);
FLOAT_CONST(cephes_p4, 1.6666665459E-1);
FLOAT_CONST(cephes_p5, 5.0000001201E-1);

INT_CONST(min_norm_pos, 0x00800000);
INT_CONST(mant_mask, 0x7f800000);
INT_CONST(inv_mant_mask, ~0x7f800000);

INT_CONST(sign_mask, (int)0x80000000);
INT_CONST(inv_sign_mask, ~0x80000000);

//The min, max of the exp return
FLOAT_CONST(exp_upper, 88.3762626647949);
FLOAT_CONST(exp_lower, -88.3762626647949);

FLOAT_CONST(cephes_SQRTHF, 0.707106781186547524);
FLOAT_CONST(cephes_log_p0, 7.0376836292E-2);
FLOAT_CONST(cephes_log_p1, -1.1514610310E-1);
FLOAT_CONST(cephes_log_p2, 1.1676998740E-1);
FLOAT_CONST(cephes_log_p3, -1.2420140846E-1);
FLOAT_CONST(cephes_log_p4, +1.4249322787E-1);
FLOAT_CONST(cephes_log_p5, -1.6668057665E-1);
FLOAT_CONST(cephes_log_p6, +2.0000714765E-1);
FLOAT_CONST(cephes_log_p7, -2.4999993993E-1);
FLOAT_CONST(cephes_log_p8, +3.3333331174E-1);
FLOAT_CONST(cephes_log_q1, -2.12194440e-4);
FLOAT_CONST(cephes_log_q2, 0.693359375);

#define MASK3 255
#define MASK2 170
#define MASK1 85
#define MASK0 0

INT_CONST(triplemask, 0x7f);

//Get NOT of 32-bit signed int
//Add to the library of mmintrin
__m128i TFAPI _mm_not_epi32(__m128i _A);

//Get NOT of a float
//Add to the library of mmintrin
float TFAPI _mm_extract_psn(__m128 a, int pos);
__m128 TFAPI  _mm_not_ps(__m128 _A);
__m128i TFAPI _mm_div_epi32(__m128i _para1, __m128i ant);

template class TFAPI std::function<__m128(__m128)>;
template class TFAPI std::function<__m128(__m128, __m128)>;
typedef std::function<__m128(__m128)> TF_MATH_FUNC;
typedef std::function<__m128(__m128, __m128)> TF_MATH_FUNC2;

namespace FRSML {

	float TFAPI ToDegrees(float radians);
	float TFAPI ToRadians(float degrees);

	namespace nmmintrin {
		TFAPI __m128i _Abs(__m128i _para);
		TFAPI __m128 _Absf(__m128 m);
		TFAPI __m128 _Maxf(__m128 _A, __m128 _B);
		TFAPI __m128 _Minf(__m128 _A, __m128 _B);
		TFAPI __m128i _Max(__m128i _A, __m128i _B);
		TFAPI __m128i _Min(__m128i _A, __m128i _B);
		TFAPI __m128 _Sqrtf(__m128 ant);
		TFAPI __m128i _Sqrt(__m128i ant);
		TFAPI __m128 _Signf(__m128 _para);
		inline TFAPI __m128 BalanceToPiDistance(__m128 _para);
		inline TFAPI __m128 _Sin(__m128 _para);
		inline TFAPI __m128 _Cos(__m128 _para);
		inline TFAPI __m128 _Tan(__m128 _para);
		inline TFAPI __m128 _Cot(__m128 _para);
		inline TFAPI __m128 _Asin(__m128 _para);
		inline TFAPI __m128 _Acos(__m128 _para);
		inline TFAPI __m128 _Atan2(__m128 _Y, __m128 _X);
		inline TFAPI __m128 _Atan(__m128 _X);
		inline TFAPI __m128 _Pow(__m128 x, __m128 y);
		//My mom tells me something different. Dont tell her i do thiz
		//This was probally a dick move of mine. But the documentation is old
		//And i just port this code from cmath source. Sorry :P
		inline TFAPI __m128 _Exp(__m128 _para);
		inline TFAPI __m128 _Log(__m128 _para);
	}

	template <class T> T _funcWrp1p(TF_MATH_FUNC func, T _para) {
		return T(func(_para.MainVector()));
	}

	template <class T> T _funcWrp2p(TF_MATH_FUNC2 func, T _para1, T _para2) {
		return T(func(_para1.MainVector(), _para2.MainVector()));
	}

	//Get the absolute value of a vec2
	TFAPI vec2 Abs(vec2 _para);

	//Get the absolute value of a vec3
	TFAPI vec3 Abs(vec3 _para);

	//Get the absolute value of a vec4
	TFAPI vec4 Abs(vec4 _para);

	//Get the Min value between two vec2 Vector
	TFAPI vec2 Min(vec2 _para1, vec2 _para2);

	//Get the Max value between two vec2 Vector
	TFAPI vec2 Max(vec2 _para1, vec2 _para2);

	//Get the Min value between two vec3 Vector
	TFAPI vec3 Min(vec3 _para1, vec3 _para2);

	//Get the Max value between two vec3 Vector
	TFAPI vec3 Max(vec3 _para1, vec3 _para2);

	//Get the Min value between two vec4 Vector
	TFAPI vec4 Min(vec4 _para1, vec4 _para2);

	//Get the Max value between two vec4 Vector
	TFAPI vec4 Max(vec4 _para1, vec4 _para2);

	//Get the cross product of two vec3
	TFAPI vec3 Cross(vec3 _para1, vec3 _para2);

	//Get the dot product of two vec2
	TFAPI vec2 Dot(vec2 _para1, vec2 _para2);

	//Get the dot product of two vec3
	TFAPI vec3 Dot(vec3 _para1, vec3 _para2);

	//Get the dot product of two vec4
	TFAPI vec4 Dot(vec4 _para1, vec4 _para2);

	//Get the cross product of two vec2
	TFAPI vec2 Dot(vec2 _para1, vec2 _para2);

	//Get the angle create between two vec2
	TFAPI vec2 Angle(vec2 _para1, vec2 _para2);

	//Get the angle create between two vec3
	TFAPI vec3 Angle(vec3 _para1, vec3 _para2);

	//Get the angle create between two vec4
	TFAPI vec4 Angle(vec4 _para1, vec4 _para2);

	//Reflect the Vector with direction and normal
	TFAPI vec2 Reflect(vec2 inDir, vec2 inNorm);

	//Reflect the Vector with direction and normal
	TFAPI vec3 Reflect(vec3 inDir, vec3 inNorm);

	//Reflect the Vector with direction and normal
	TFAPI vec4 Reflect(vec4 inDir, vec4 inNorm);

	//Return the distance between two Vector!!!!!!
	TFAPI float Distance(vec2 _start, vec2 _end);

	//Return the distance between two Vector!!!!!!
	TFAPI float Distance(vec3 _start, vec3 _end);

	//Return the distance between two Vector!!!!!!
	TFAPI float Distance(vec4 _start, vec4 _end);

	//Caculate the absolute value of an int! Using SSE tech! Whoa!
	TFAPI FRS_int Abs(FRS_int _para);

	//Caculate the absolute value of a float! Using SSE tech! Whoa!
	TFAPI  FRS_float Abs(FRS_float _para);

	//Cacluate the e^x value
	TFAPI double Exp(double x);

	//Caculate the logarithym value base e
	TFAPI float Log(float x);

	//Caculate the logarithym value base 2
	TFAPI float Log2(float x);

	//Caculate the logarithym value base "base"
	TFAPI float Log(float x, float base);

	//Caculate x^y;
	TFAPI float Pow(float x, float y);

	//Get the Square Root value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Sqrt(FRS_int ant);

	//Get the Square Root value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Sqrt(FRS_float ant);

	//Get the Max value between two int
	TFAPI FRS_int Max(FRS_int _A, FRS_int _B);

	//Get the Min value between two int
	TFAPI FRS_int Min(FRS_int _A, FRS_int _B);

	//Get the Max value between two float
	TFAPI FRS_float Max(FRS_float _A, FRS_float _B);

	//Get the Min value between two float
	TFAPI FRS_float Min(FRS_float _A, FRS_float _B);

	//Get the Sin value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Sin(FRS_float _A);

	//Get the Cos value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Cos(FRS_float _A);

	//Get the Tan value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Tan(FRS_float _A);

	//Get the Cotan value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Cot(FRS_float _A);

	//Get the Asin value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Asin(FRS_float _A);

	//Get the Acos value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Acos(FRS_float _A);

	TFAPI FRS_float Atan2(FRS_float _A, FRS_float _B);

	//Get the Atan value of a float using SSE
	//Whoa, technology!
	TFAPI FRS_float Atan(FRS_float _A);

	//Get the Sin value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Sin(FRS_int _A);

	//Get the Cos value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Cos(FRS_int _A);

	//Get the Tan value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Tan(FRS_int _A);

	//Get the Cotan value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Cot(FRS_int _A);

	//Get the Asin value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Asin(FRS_int _A);

	//Get the Acos value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Acos(FRS_int _A);

	//Atan2 cacluates the degrees of the angle created
	//between coordinate line (origin to point2d line) and axis
	//Or basicly, it is Arctan of (-y/-x); And its tech is SSE!
	//Whoa!
	TFAPI FRS_float Atan2(FRS_int _X, FRS_int _Y);

	//Get the Atan value of an int using SSE
	//Whoa, technology!
	TFAPI FRS_float Atan(FRS_int _A);

	//Caculate the absolute value of a float! Using SSE tech! Whoa!
	TFAPI float Abs(float _para);

	//Clamp the value
	TFAPI float Clamp(float _t1, float _t2, float crrNumber);

	//Return the value between a and b. Basically, t is the percent in short written
	TFAPI float Lerp(float t, float a, float b);

	//I dont think it makes things faster than normal, so throw it here ^-^
	//It caculate the Sign of a float. Whoa technology!
	TFAPI float Sign(float _para);

	//Get the Sin value of a float using SSE
	//Whoa, technology!
	TFAPI float Sin(float _para);

	//Get the Cos value of a float using SSE
	//Whoa, technology!
	TFAPI float Cos(float _para);

	//Get the Tan value of a float using SSE
	//Whoa, technology!
	TFAPI float Tan(float _para);

	//Get the Cotan value of a float using SSE
	//Whoa, technology!
	TFAPI float Cot(float _para);

	//The sin value of X will be put into "s" array
	//The cos value of Y will be put into "c" array
	//... Using SSE technology! Whoa!
	TFAPI void SinCos(float x, float* s, float* c);

	//Get the Asin value of a float using SSE
	//Whoa, technology!
	TFAPI float Asin(float _para);

	//Get the Acos value of a float using SSE
	//Whoa, technology!
	TFAPI float Acos(float _para);


	//Get the Atan value of a float using SSE
	//Whoa, technology!
	TFAPI float Atan(float _para);

	//Atan2 cacluates the degrees of the angle created
	//between coordinate line (origin to point2d line) and axis
	//Or basicly, it is Arctan of (-y/-x); And its tech is SSE!
	//Whoa!
	TFAPI float Atan2(float _X, float _Y);

	//Get the Max value between two float
	TFAPI float Max(float _A, float _B);

	//Get the Max value between two float
	TFAPI float Min(float _A, float _B);

	//Get the Square Root value of a float using SSE
	//Whoa, technology!
	TFAPI float Sqrt(float ant);

}

#endif

