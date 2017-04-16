#include "Vector.h"

namespace FRSML {

		float* value_ptr(vec4 vec) {
			float* value;
			value[0] = vec.X;
			value[1] = vec.Y;
			value[2] = vec.Z;
			value[3] = vec.W;

			return value;
		}

		vec4::vec4(float ant) {
			mainVec = _mm_set_ps1(ant);
			SetRealXY(ant, ant, ant, ant);
		}

		vec4::vec4(float x, float y, float z, float w) {
			mainVec = _mm_set_ps(x, y, z, w);
			SetRealXY(x,y,z,w);
		}

		__m128 &vec4::MainVector() {
			return mainVec;
		}

		vec4::vec4(__m128 _set) {
			mainVec = _set;
			SetRealXY(mainVec);
		}
		
		
		vec4::vec4(vec3 _para, float _para2) {

			__m128 tmp = _para.MainVector();
			__m128 tmp2 = _mm_set_ps(_para2, 0, 0, 0);
			tmp = _mm_xor_ps(tmp, tmp2);
			tmp = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(2, 1, 0, 3));

			mainVec = tmp;

			SetRealXY(mainVec);
		}

		void vec4::operator =(vec4 ant) {
			mainVec = ant.mainVec;
			SetRealXY(mainVec);
		}

		bool vec4::operator ==(vec4 ant) {
			__m128 _eua = _mm_cmpeq_ps(this->mainVec, ant.mainVec);
			return _mm_movemask_ps(_eua);
		}

		vec4 vec4::operator +(vec4 ant) {
			return vec4(_mm_add_ps(this->mainVec, ant.mainVec));
		}


		vec4 vec4::operator -(vec4 ant) {
			return vec4(_mm_sub_ps(this->mainVec, ant.mainVec));
		}

		vec4 vec4::operator *(vec4 ant) {
			return vec4(_mm_mul_ps(this->mainVec, ant.mainVec));
		}

		vec4 vec4::operator /(vec4 ant) {
			return vec4(_mm_div_ps(this->mainVec, ant.mainVec));
		}

		vec4 vec4::operator +(float ant) {
			return vec4(_mm_add_ps(this->mainVec, _mm_set1_ps(ant)));
		}

		vec4 vec4::operator -(float ant) {
			return vec4(_mm_sub_ps(this->mainVec, _mm_set1_ps(ant)));
		}

		vec4 vec4::operator *(float ant) {
			return vec4(_mm_mul_ps(this->mainVec, _mm_set1_ps(ant)));
		}

		vec4 vec4::operator /(float ant) {
			return vec4(_mm_div_ps(this->mainVec, _mm_set1_ps(ant)));
		}

		float vec4::Length() {
			return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mainVec, mainVec, 0xF1)));
		}

		vec4 vec4::Normalize() {
			__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainVec, mainVec, 0xFF));
			return vec4(_mm_mul_ps(mainVec, inverse_normalize));
		}

		vec4::vec4(float* as) {
			this->mainVec = _mm_load_ps(as);
			SetRealXY(mainVec);
		}
}
