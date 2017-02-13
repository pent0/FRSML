#pragma once

#include <smmintrin.h>
#include "FRSVar.h"
#include "Matrix4x4.h"
#include "StandardMathSSE4.h"

namespace FRSML {

	using namespace nmmintrin;

	class TFAPI Quaternion {
	public:
		Quaternion(float x = 0, float y = 0, float z = 0, float w = 1){
			mainQuat = _mm_set_ps(w, x, y, z);
		}

		Quaternion(__m128 quatVal) {
			mainQuat = quatVal;
		}
		
		operator Matrix4() {
			Quaternion tmp = Normalize();
			__m128 quatX = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 quatY = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 quatZ = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 quatW = _mm_shuffle_ps(mainQuat, mainQuat, _MM_SHUFFLE(3, 3, 3, 3));

			__m128 tem1; {
				__m128 g1 = _Pow(quatY, _mm_set1_ps(2));
				__m128 g2 = _Pow(quatZ, _mm_set1_ps(2));
				g1 = _mm_add_ss(g1, g2);
				tem1 = _mm_sub_ss(_mm_set1_ps(1), g1);
				tem1 = _mm_shuffle_ps(tem1, tem1, _MM_SHUFFLE(0, 3, 3, 3));
			};


			__m128 tem2; {
				__m128 g1 = _Pow(quatX, _mm_set1_ps(2));
				__m128 g2 = _Pow(quatY, _mm_set1_ps(2));
				g1 = _mm_add_ss(g1, g2);
				tem2 = _mm_sub_ss(_mm_set1_ps(1), g1);
				tem2 = _mm_shuffle_ps(tem2, tem2, _MM_SHUFFLE(3, 3, 0, 3));
			};

			__m128 tem3; {
				__m128 g1 = _Pow(quatX, _mm_set1_ps(2));
				__m128 g2 = _Pow(quatZ, _mm_set1_ps(2));
				g1 = _mm_add_ss(g1, g2);
				tem3 = _mm_sub_ss(_mm_set1_ps(1), g1);
				tem3 = _mm_shuffle_ps(tem3, tem3, _MM_SHUFFLE(3, 0, 3, 3));
			};

			__m128 tem4; {
				__m128 g1 = _mm_mul_ss(quatX,quatY);
				__m128 g2 = _mm_mul_ss(quatW, quatZ);
				g1 = _mm_add_ss(g1, g2);
				tem4 = _mm_add_ss(_mm_set1_ps(2), g1);
				tem4 = _mm_shuffle_ps(tem4, tem4, _MM_SHUFFLE(0, 3, 3, 3));
			}

			__m128 tem5; {
				__m128 g1 = _mm_mul_ss(quatX, quatZ);
				__m128 g2 = _mm_mul_ss(quatW, quatY);
				g1 = _mm_add_ss(g1, g2);
				tem5 = _mm_mul_ss(_mm_set1_ps(2), g1);
				tem5 = _mm_shuffle_ps(tem5, tem5, _MM_SHUFFLE(3, 3, 0, 3));
			}

			__m128 tem6; {
				__m128 g1 = _mm_mul_ss(quatY, quatZ);
				__m128 g2 = _mm_mul_ps(quatW, quatX);
				g1 = _mm_add_ss(g1, g2);
				tem6 = _mm_mul_ss(_mm_set1_ps(2), g1);
				tem6 = _mm_shuffle_ps(tem6, tem6, _MM_SHUFFLE(3, 3, 0, 3));
			}

			__m128 tem7; {
				__m128 g1 = _mm_mul_ss(quatX, quatY);
				__m128 g2 = _mm_mul_ss(quatW, quatZ);
				g1 = _mm_sub_ss(g1, g2);
				tem7 = _mm_mul_ss(_mm_set1_ps(2), g1);
				tem7 = _mm_shuffle_ps(tem7, tem7, _MM_SHUFFLE(3, 0, 3, 3));
			}

			__m128 tem8; {
				__m128 g1 = _mm_mul_ss(quatX, quatZ);
				__m128 g2 = _mm_mul_ss(quatW, quatY);
				g1 = _mm_sub_ss(g1, g2);
				tem8 = _mm_mul_ss(_mm_set1_ps(2), g1);
				tem8 = _mm_shuffle_ps(tem8, tem8, _MM_SHUFFLE(0, 3, 3, 3));
			}

			__m128 tem9; {
				__m128 g1 = _mm_mul_ss(quatY, quatZ);
				__m128 g2 = _mm_mul_ss(quatW, quatX);
				g1 = _mm_sub_ss(g1, g2);
				tem9 = _mm_mul_ss(_mm_set1_ps(2), g1);
				tem9 = _mm_shuffle_ps(tem9, tem9, _MM_SHUFFLE(0, 3, 3, 3));
			}

			__m128 tem0 = _mm_set_ps(0, 0, 0, 1);

			__m128 tem10 = _mm_xor_ps(tem1, _mm_xor_ps(tem5, tem7));
			__m128 tem11 = _mm_xor_ps(tem4, _mm_xor_ps(tem3, tem6));
			__m128 tem12 = _mm_xor_ps(tem8, _mm_xor_ps(tem9, tem2));
			__m128 tem13 = _mm_xor_ps(_mm_setzero_ps(), tem0);

			return Matrix4(tem10, tem11, tem12, tem13);
	

			
		}

		float& X(); float& Y(); float& Z(); float& W();

		inline static Quaternion CreateQuat(vec3 euler);
		inline static Quaternion CreateQuat(vec3 axis, float angle);

		//Add two quaternion
		inline Quaternion operator +(Quaternion tar1);

		//Multi-quat!! Get it?
		inline Quaternion operator *(Quaternion tar1);
		Quaternion Normalize();

	private:
		__m128 mainQuat;
	};
}
