#include "Vector.h"

namespace FRSML {

		float* value_ptr(vec4 vec) {
			float* value;
			value[3] = vec.x;
			value[2] = vec.y;
			value[1] = vec.z;
			value[0] = vec.w;

			return value;
		}

		vec4::vec4(float ant) {
			x = ant;
			y = ant;
			z = ant;
			w = ant;

		}

		vec4::vec4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}


		vec4::vec4(__m128 _set) {

			__m128 t1 = _mm_shuffle_ps(_set, _set, _MM_SHUFFLE(3, 3, 3, 3));
			__m128 t2 = _mm_shuffle_ps(_set, _set, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 t3 = _mm_shuffle_ps(_set, _set, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 t4 = _mm_shuffle_ps(_set, _set, _MM_SHUFFLE(0, 0, 0, 0));

			x = _mm_cvtss_f32(t1);
			y = _mm_cvtss_f32(t2);
			z = _mm_cvtss_f32(t3);
			w = _mm_cvtss_f32(t4);

		}
		
		
		vec4::vec4(vec3 _para, float _para2) {

			x = _para.x;
			y = _para.y;
			z = _para.z;
			w = _para2;
		}

		void vec4::operator =(vec4 ant) {
			x = ant.x;
			y = ant.y;
			z = ant.z;
			w = ant.w;
		}

		bool vec4::operator ==(vec4 ant) {
			return (x == ant.x
				&& y == ant.y
				&& z == ant.z
				&& w == ant.w);
		}

		vec4 vec4::operator +(vec4 ant) {
			vec4 temp{};

			temp.x = x + ant.x;
			temp.y = y + ant.y;
			temp.w = w + ant.w;
			temp.z = z + ant.z;

			return temp;
		}


		vec4 vec4::operator -(vec4 ant) {
			vec4 temp{};

			temp.x = x - ant.x;
			temp.y = y - ant.y;
			temp.w = w - ant.w;
			temp.z = z - ant.z;

			return temp;
		}

		vec4 vec4::operator *(vec4 ant) {
			vec4 temp{};

			temp.x = x * ant.x;
			temp.y = y * ant.y;
			temp.w = w * ant.w;
			temp.z = z * ant.z;

			return temp;
		}

		vec4 vec4::operator /(vec4 ant) {
			vec4 temp{};

			temp.x = x / ant.x;
			temp.y = y / ant.y;
			temp.w = w / ant.w;
			temp.z = z / ant.z;

			return temp;
		}

		vec4 vec4::operator +(float ant) {
			vec4 temp{};

			temp.x = x + ant;
			temp.y = y + ant;
			temp.w = w + ant;
			temp.z = z + ant;

			return temp;
		}

		vec4 vec4::operator -(float ant) {
			vec4 temp{};

			temp.x = x - ant;
			temp.y = y - ant;
			temp.w = w -ant;
			temp.z = z - ant;

			return temp;
		}

		vec4 vec4::operator *(float ant) {
			vec4 temp{};

			temp.x = x * ant;
			temp.y = y * ant;
			temp.w = w * ant;
			temp.z = z * ant;

			return temp;
		}

		vec4 vec4::operator /(float ant) {
			vec4 temp{};

			temp.x = x / ant;
			temp.y = y / ant;
			temp.w = w / ant;
			temp.z = z / ant;

			return temp;
		}

		float vec4::Length() {
			__m128 mainVec = GenerateXYZW();

			return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mainVec, mainVec, 0xF1)));
		}

		vec4 vec4::Normalize() {
			__m128 mainVec = GenerateXYZW();

			__m128 inverse_normalize = _mm_rsqrt_ps(_mm_dp_ps(mainVec, mainVec, 0xFF));
			return vec4(_mm_mul_ps(mainVec, inverse_normalize));
		}

		vec4::vec4(float* as) {
			x = as[0];
			y = as[1];
			z = as[2];
			w = as[3];
		}
}
