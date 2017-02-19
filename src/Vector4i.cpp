#include "Vector.h"

namespace FRSML {

	vec4 vec4i::ConvertToVector4f() {
		__m128 _ccar = _mm_cvtepi32_ps(mainVec);
		return vec4(_ccar);

	}


	vec4i::vec4i(__m128i _gene) {
		mainVec = _gene;
	}

	/*
	vec4i::vec4i(FRS_int ant) {
		mainVec = ant.MainNum();
	}*/


	vec4i::vec4i(int x, int y, int w, int z) {
		mainVec = _mm_set_epi32(x, y, z, w);
	}

	vec4i::vec4i(int t) {
		mainVec = _mm_set1_epi32(t);
	}

	int& vec4i::X() {
		return mainVec.m128i_i32[3];
	}

	int& vec4i::Y() {
		return mainVec.m128i_i32[2];
	}

	int& vec4i::Z() {
		return mainVec.m128i_i32[1];
	}
		
	int& vec4i::W() {
		return mainVec.m128i_i32[0];
	}

	void vec4i::operator =(vec4i ant) {
		mainVec = ant.mainVec;
	}

	vec4i vec4i::operator ==(vec4i ant) {
		return _mm_test_all_ones(_mm_cmpeq_epi32(mainVec, ant.mainVec));
	}


#pragma region OPERATOR

	vec4i vec4i::operator + (vec4i ant) {
		return vec4i(_mm_add_epi32(this->mainVec, ant.mainVec));
	}

	vec4i vec4i::operator -(vec4i ant) {
		return vec4i(_mm_sub_epi32(this->mainVec, ant.mainVec));
	}

	vec4i vec4i::operator * (vec4i ant) {
		return vec4i(_mm_add_epi32(this->mainVec, ant.mainVec));
	}

	vec4i vec4i::operator /(vec4i ant) {
			vec4 _c1(_mm_castsi128_ps(this->mainVec));
			vec4 _c2(_mm_castsi128_ps(ant.mainVec));
			vec4 _c3 = _c1 / _c2;
			__m128i n = _mm_cvtps_epi32(_c3.MainVector());
			return vec4i(n);
	}

	vec4i vec4i::operator +(int ant) {
		return vec4i(mainVec) + vec4i(ant);
	}

	vec4i vec4i::operator -(int ant) {
		return vec4i(mainVec) - vec4i(ant);
	}

	vec4i vec4i::operator *(int ant) {
		return vec4i(mainVec) * vec4i(ant);
	}

	vec4i vec4i::operator /(int ant) {
		__m128i mt, m1, ms;
		_frs_getmagnum_i(ant, mt, m1, ms);
		__m128i t1 = _mm_mul_epi32(this->mainVec, mt);
		__m128i t2 = _mm_srli_epi64(t1, 32);
		__m128i t3 = _mm_srli_epi64(this->mainVec, 32);
		__m128i t4 = _mm_mul_epi32(t3, mt);
		__m128i t5 = _mm_set_epi32(-1, 0, -1, 0);
		__m128i t6 = _mm_blendv_epi8(t2, t4, t5);
		__m128i t7 = _mm_add_epi32(t6, this->mainVec);
		__m128i t8 = _mm_sra_epi32(t7, m1);
		__m128i t9 = _mm_srai_epi32(this->mainVec, 31);
		__m128i t10 = _mm_sub_epi32(t9, ms);
		__m128i t11 = _mm_sub_epi32(t8, t10);
		return vec4i(_mm_xor_si128(t11, ms));

	}

	void vec4i::operator +=(vec4i ant) {
		*this = *this + ant;
	}

	void vec4i::operator -=(vec4i ant) {
		*this = *this - ant;
	}

	void vec4i::operator *=(vec4i ant) {
		*this = *this * ant;
	}

	void vec4i::operator +=(int ant) {
		*this = *this + ant;
	}

	void vec4i::operator -=(int ant) {
		*this = *this - ant;
	}

	void vec4i::operator *=(int ant) {
		*this = *this * ant;
	}

	void vec4i::operator /=(int ant) {
		*this = *this / ant;
	}

	vec4i vec4i::operator &(vec4i ant) {
		return vec4i(_mm_and_si128(mainVec, ant.mainVec));
	}

	void vec4i::operator &=(vec4i ant) {
		*this = *this&ant;
	}

	vec4i vec4i::operator ^(vec4i ant) {
		return vec4i(_mm_xor_si128(mainVec, ant.mainVec));
	}

	void vec4i::operator ^=(vec4i ant) {
		*this = *this^ant;
	}

	vec4i vec4i::operator |(vec4i ant) {
		return vec4i(_mm_or_si128(mainVec, ant.mainVec));
	}

	void vec4i::operator |=(vec4i ant) {
		*this = *this | ant;
	}

	float vec4i::Length() {
		return ConvertToVector4f().Length();
	}

	__m128i& vec4i::MainVector() {
		return mainVec;
	}

#pragma endregion

	//Agner method!
	void vec4i::_frs_getmagnum_i(int divisor, __m128i& mul, __m128i& shift1, __m128i& sign) {
			const int32_t divisorabs = (divisor < 0) ? -divisor : divisor;
			int32_t sh, m;
			if (divisorabs > 1) {
				_BitScanReverse((unsigned long*)(&sh), divisorabs - 1);
				m = int32_t((int64_t(1) << (32 + sh)) / divisorabs - ((int64_t(1) << 32) - 1));
				//int32_t(((int64_t)1 << (32 + sh)) / divisorabs - ((int64_t)(1) << 32) - 1);
				//std::cout << sh << " " << m << std::endl;
			}
			else {
				sh = 0;
				m = 1;
				if (divisor == 0) m /= divisor;
				if (uint32_t(divisorabs) == 0x80000000u) {
					m = 0x80000001;
					sh = 30;
				}

			}

			mul = _mm_set1_epi32(m);
			//Found n - the shifter using bitscanreserve!
			shift1 = _mm_setr_epi32(sh, 0, 0, 0);
			sign = _mm_set1_epi32(divisor < 0 ? -1 : 0);
		}
	};

