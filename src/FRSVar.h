#ifndef FRSVAR_H
#define FRSVAR_H


#include <nmmintrin.h>
#include <smmintrin.h>
#include <iostream>

//Wrapper of SSE var
#define FRSML_PI 3.14159265358979323846  
#define FRSML_PI_D2 1.57079632679489661923      
#define FRSML_PI_D4 0.785398163397448309616  

#ifdef _WIN32
#ifdef FRSML_EXPORTS
#define TFAPI __declspec(dllexport)
#else
#define TFAPI __declspec(dllimport)
#endif
#endif

//Division of high and up byte using these magical number
//Suffle thing will be fun with this
static const __m128i magicIntNum = _mm_set1_epi16(0x4B00);
static const __m128 magicFloatNum = _mm_set_ps1(8388608.0f);


//Forgive me, halation!
struct TFAPI FRS_float{
public:

	FRS_float(float n = 0) {
		//Forgive me, again, they didnt give me a choice!
		mainNum = _mm_load_ss(&n);
	}

	FRS_float(__m128 n) {
		mainNum = n;
	}

	void operator =(float need) {
		mainNum = _mm_load_ss(&need);
	}

	__m128& MainNum() {
		return mainNum;
	}

	 FRS_float operator + (FRS_float f1);
	 FRS_float operator - (FRS_float f1);
	 FRS_float operator * (FRS_float f1);
	 FRS_float operator / (FRS_float f1);
	
	 FRS_float operator + (float f1);
	 FRS_float operator - (float f1);
	 FRS_float operator * (float f1);
	 FRS_float operator / (float f1);

	 void operator += (float n);
	 void operator -= (float n);
	 void operator *= (float n);
	 void operator /= (float n);
	 void operator++();
	 void operator--();
	 bool operator == (FRS_float ant);
	 bool operator !=(FRS_float ant);
	 FRS_float operator |(FRS_float ant);
	 FRS_float operator &(FRS_float ant);
	 FRS_float operator ^(FRS_float ant);
	 void operator |=(FRS_float ant);
	 void operator &=(FRS_float ant);
	 void operator ^=(FRS_float ant);
	 bool operator >(FRS_float ant);
	 bool operator >=(FRS_float ant);
	 bool operator <(FRS_float ant);
	 bool operator <=(FRS_float ant);
	

	explicit operator float() const;

	static FRS_float get_128b_ff(float& n);

private:
	__m128 mainNum;
};


//A int array is nothing like this. Forgive me, again!
struct TFAPI FRS_int {
public:

	FRS_int(__m128i n) {
		mainInt = n;
	}

	FRS_int(int n=0) {
		mainInt = _mm_set1_epi32(n);
	}

	void operator = (int& a) {
		int* n = (int*)(&mainInt);
		a = n[1];
	}

	explicit operator int() const {
		return _mm_cvtsi128_si32(this->mainInt);
	}



	__m128i& MainNum() {
		return mainInt;
	}

	 FRS_int operator + (FRS_int f1);
	 FRS_int operator - (FRS_int f1);
	 FRS_int operator * (FRS_int f1);
	 FRS_int operator /(FRS_int f1);
	 void operator += (int n);
	 void operator -= (int n);
	 void operator *= (int n);
	 void operator /=(int n);

	
	 void operator++();
	 void operator--();
	 void operator =(int n);
	

	 bool operator ==(FRS_int& ant);
	 bool operator !=(FRS_int& ant);
	 bool operator >(FRS_int& ant);
	 bool operator >=(FRS_int& ant);
	 bool operator <(FRS_int& ant);
	 bool operator <=(FRS_int& ant);

	 FRS_int operator |(FRS_int ant);
	 FRS_int operator &(FRS_int ant);
	 FRS_int operator ^(FRS_int ant);

	 void operator |=(FRS_int ant);
	 void operator &=(FRS_int ant);
	 void operator ^=(FRS_int ant);

	 FRS_int operator <<(int a);
	 FRS_int operator >>(int a);

	 void operator <<=(int a);
	 void operator >>=(int a);

	static FRS_int set_128bi_fi(int& n);
	static int get_i_f128bi(FRS_int& i);
	

private:
	__m128i mainInt;
};


struct FRS_uint {

};

struct FRS_long {
public:

	FRS_long(__m128i n) {
		mainLong = n;
	}

	void operator = (long& a) {
		long* n= (long*)(&mainLong);
		a = n[1];
	}

	FRS_long& operator + (FRS_long f1);
	FRS_long& operator - (FRS_long f1);
	FRS_long& operator * (FRS_long f1);
	FRS_long& operator / (FRS_long f1);
	FRS_long& operator += (long n);
	FRS_long& operator -= (long n);
	FRS_long& operator++();
	FRS_long& operator--();
private:
	//Rarely use long
	__m128i mainLong;
};


struct FRS_string {
public:
	void ConvertToChar(char* to) {
		to = (char*)(_aligned_malloc(GetLength() * sizeof(char), 16));
	}

	float GetLength() {
		return (float)count;
	}


	

private:
	FRS_float count;
	__m128i* mainString;
};




#endif
TFAPI std::ostream& operator <<(std::ostream& para, const FRS_float& a);
TFAPI std::istream& operator >>(std::istream& para, FRS_float& a);
TFAPI std::ostream& operator <<(std::ostream& para, const FRS_int& a);
TFAPI std::istream& operator >>(std::istream& para, FRS_int& a);


TFAPI FRS_float ConvertToFloat(FRS_int ant);

TFAPI FRS_int ConvertToInt(FRS_float ant);