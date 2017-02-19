#include "FRSVar.h"
#include "AssertSSE.h"
#include "Vector.h"

FRS_float ConvertToFloat(FRS_int ant) {
	__m128 temp = _mm_cvtepi32_ps(ant.MainNum());
	return FRS_float(temp);
}

FRS_int ConvertToInt(FRS_float ant) {
	__m128i temp = _mm_cvtps_epi32(ant.MainNum());
	return FRS_int(temp);
}

#pragma region FRS_FLOAT_V3


 FRS_float FRS_float::operator &(FRS_float ant) {
	FRS_float temp(_mm_and_ps(this->mainNum, ant.mainNum));
	return temp;
}

 FRS_float FRS_float::operator ^(FRS_float ant) {
	FRS_float temp(_mm_xor_ps(this->mainNum, ant.mainNum));
	return temp;
}

 bool FRS_float::operator ==(FRS_float ant) {
	__m128 _compare = _mm_cmpneq_ps(this->mainNum, ant.mainNum);

	FRSML_ASSERT(_mm_movemask_ps(_compare) != (0 || 1), "FRS_Float Movemask Error");
	
	return (_mm_movemask_ps(_compare));

}


 void FRS_float::operator |=(FRS_float ant) {
	*this = *this | ant;
}

 void FRS_float::operator &=(FRS_float ant) {
	*this = *this & ant;
}

 void FRS_float::operator ^=(FRS_float ant) {
	*this = *this ^ ant;
}

 FRS_float FRS_float::operator |(FRS_float ant) {
	return FRS_float(_mm_or_ps(this->mainNum, ant.mainNum));
}

 bool FRS_float::operator !=(FRS_float ant) {
	return !(*this == ant);
}


 FRS_float FRS_float::operator + (FRS_float f1) {
	return FRS_float(_mm_add_ss(mainNum, f1.mainNum));
}

 FRS_float FRS_float::operator - (FRS_float f1) {
	return FRS_float(_mm_sub_ss(mainNum, f1.mainNum));
	
}

 FRS_float FRS_float::operator * (FRS_float f1) {
	return FRS_float(_mm_mul_ss(mainNum, f1.mainNum));
}

 FRS_float FRS_float::operator / (FRS_float f1) {
	return FRS_float(_mm_div_ss(mainNum, f1.mainNum));
}

 FRS_float FRS_float::operator + (float f1) {
	return FRS_float(_mm_add_ss(mainNum, _mm_load_ss(&f1)));
}

 FRS_float FRS_float::operator - (float f1) {
	return FRS_float(_mm_sub_ss(mainNum, _mm_load_ss(&f1)));
}

 FRS_float FRS_float::operator * (float f1) {
	return FRS_float(_mm_mul_ss(mainNum, _mm_load_ss(&f1)));
}

 FRS_float FRS_float::operator / (float f1) {
	return FRS_float(_mm_div_ss(mainNum, _mm_load_ss(&f1)));
}

 void FRS_float::operator += (float n) {
	 *this = *this + FRS_float::get_128b_ff(n);
}

 void FRS_float::operator -= (float n) {
	*this = *this - FRS_float::get_128b_ff(n);
}

 void FRS_float::operator *= (float n) {
	*this = *this * FRS_float::get_128b_ff(n);
}

 void FRS_float::operator /= (float n) {
	*this = *this / FRS_float::get_128b_ff(n);
}

 void FRS_float::operator++() {
	*this += 1;
}

 void FRS_float::operator--() {
	*this -= 1;
}

FRS_float FRS_float::get_128b_ff(float& n) {
	return FRS_float(_mm_load_ss(&n));
}

FRS_float::operator float() const{
	float t;
	_mm_store_ss(&t, this->mainNum);
	return t;
}


 bool FRS_float::operator >(FRS_float ant) {
	__m128 _cm = _mm_cmpgt_ss(this->mainNum, ant.mainNum);

	//Although 0x00 is 0, fancy!
	return (_mm_movemask_ps(_cm));
}

 bool FRS_float::operator >=(FRS_float ant) {
	__m128 _cm = _mm_cmpge_ss(this->mainNum, ant.mainNum);

	return (_mm_movemask_ps(_cm));
}

 bool FRS_float::operator <(FRS_float ant) {
	__m128 _cm = _mm_cmplt_ss(this->mainNum, ant.mainNum);

	//Although 0x00 is 0, fancy!
	return (_mm_movemask_ps(_cm));
}

 bool FRS_float::operator <=(FRS_float ant) {
	__m128 _cm = _mm_cmple_ss(this->mainNum, ant.mainNum);

	//Although 0x00 is 0, fancy!
	return (_mm_movemask_ps(_cm));
}

std::ostream& operator <<(std::ostream& _para, const FRS_float& a) {
	_para << (float)(a);
	return _para;
}

std::istream& operator >>(std::istream& _para, FRS_float& a) {
	float t;
	_para >> t;
	a.MainNum() = _mm_set1_ps(t);
	return _para;
}

#pragma endregion


#pragma region FRS_INT_V2
std::ostream& operator <<(std::ostream& _para, const FRS_int& a) {
	_para << (int)(a);
	return _para;
}

std::istream& operator >>(std::istream& _para, FRS_int& a) {
	int t;
	_para >> t;
	a.MainNum() = _mm_set1_epi32(t);
	return _para;
}

FRS_int FRS_int::set_128bi_fi(int& n) {
	return FRS_int(_mm_set1_epi32(n));
}

int FRS_int::get_i_f128bi(FRS_int& i) {
	return _mm_cvtsi128_si32(i.mainInt);
}

 FRS_int FRS_int::operator + (FRS_int f1) {
	return FRS_int(_mm_add_epi32(this->mainInt, f1.mainInt));
}

 FRS_int FRS_int::operator - (FRS_int f1) {
	return FRS_int(_mm_sub_epi32(this->mainInt, f1.mainInt));
	
}

 FRS_int FRS_int::operator * (FRS_int f1) {
	return FRS_int(_mm_mullo_epi32(this->mainInt, f1.mainInt));
}


 FRS_int FRS_int::operator / (FRS_int f1) {
	//Wrapper of division of vector4
	 FRSML::vec4i vec4(this->mainInt);
	vec4 /= FRS_int::get_i_f128bi(f1);
	return FRS_int(vec4.MainVector());
}

 void FRS_int::operator /=(int n) {
	FRSML::vec4i vec4(this->mainInt);
	vec4 /= n;
	*this = vec4.MainVector();
}

 void FRS_int::operator |=(FRS_int ant) {
	*this = *this | ant;
}

 void FRS_int::operator &=(FRS_int ant) {
	*this = *this & ant;
}

 void FRS_int::operator ^=(FRS_int ant) {
	*this = *this ^ ant;
}


 void FRS_int::operator =(int n) {
	this->mainInt = _mm_set_epi32(n, n, n, n);
}

 void FRS_int::operator += (int n) {
	*this = *this + set_128bi_fi(n);
}

 void FRS_int::operator -= (int n) {
	*this = *this + set_128bi_fi(n);
}

 void FRS_int::operator *= (int n) {
	*this = *this * set_128bi_fi(n);
}



 void FRS_int::operator++() {
	int i = 1;
	*this = *this + set_128bi_fi(i);
}

 void FRS_int::operator--() {
	int i = 1;
	*this = *this - set_128bi_fi(i);
}

 bool FRS_int::operator ==(FRS_int& ant) {
	__m128i _cmp = _mm_cmpeq_epi32(this->mainInt, ant.mainInt);
	return (_mm_movemask_epi8(_cmp));
}

 bool FRS_int::operator !=(FRS_int& ant) {
	//Flute++ 10/10
	return (!(*this == ant));
}

 bool FRS_int::operator>(FRS_int& ant) {
	__m128i _gt =  _mm_cmpgt_epi32(this->mainInt, ant.mainInt);
	return _mm_movemask_epi8(_gt);
}

 bool FRS_int::operator >=(FRS_int& ant) {
	__m128i _gt = _mm_cmpgt_epi32(this->mainInt, ant.mainInt);
	return (_mm_movemask_epi8(_gt) && (ant == *this));
}

 bool FRS_int::operator <(FRS_int& ant) {
	__m128i _gt = _mm_cmplt_epi32(this->mainInt, ant.mainInt);
	return _mm_movemask_epi8(_gt);
}

 bool FRS_int::operator <=(FRS_int& ant) {
	__m128i _gt = _mm_cmplt_epi32(this->mainInt, ant.mainInt);
	return (_mm_movemask_epi8(_gt) && (ant == *this));
}

 FRS_int FRS_int::operator |(FRS_int ant) {
	return FRS_int(_mm_or_si128(this->mainInt, ant.mainInt));
}

 FRS_int FRS_int::operator &(FRS_int ant) {
	return FRS_int(_mm_and_si128(this->mainInt, ant.mainInt));

}

 FRS_int FRS_int::operator ^(FRS_int ant) {
	return FRS_int(_mm_xor_si128(this->mainInt, ant.mainInt));
}

 FRS_int FRS_int::operator <<(int a) {
	return FRS_int(_mm_slli_epi32(this->mainInt, a));
}

 FRS_int FRS_int::operator >>(int a) {
	return FRS_int(_mm_srli_epi32(this->mainInt, a));
}

 void FRS_int::operator <<=(int a) {
	*this = *this << a;
}

 void FRS_int::operator >>=(int a) {
	*this = *this >> a;
}

#pragma endregion


/*
FRS_long& operator + (FRS_long f1);
FRS_long& operator - (FRS_long f1);
FRS_long& operator * (FRS_long f1);
FRS_long& operator / (FRS_long f1);
FRS_long& operator += (long n);
FRS_long& operator -= (long n);
FRS_long& operator++();
FRS_long& operator--();*/