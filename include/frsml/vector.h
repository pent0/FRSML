#ifndef FRSML_VECTOR_H
#define FRSML_VECTOR_H

#include <frsml/internal.h>

namespace frsml {

	/* MATH STRUCT SECTION */

	struct FRS_MATH_API vec2 {
		float x, y = 0;

		vec2();
		vec2(const vec2& p_vec);
		vec2(const float p_x, const float p_y);

		float& operator [](u8 p_index);

		inline bool operator == (vec2 p_vec);
		inline bool operator != (vec2 p_vec);

		inline vec2 operator +(vec2 p_vec);
		inline void operator +=(vec2 p_vec);
		inline vec2 operator +(float p_num);
		inline void operator +=(float p_num);

		inline void operator++();

		inline vec2 operator -(vec2 p_vec);
		inline void operator -=(vec2 p_vec);
		inline vec2 operator -(float p_num);
		inline void operator -=(float p_num);

		inline void operator --();

		inline vec2 operator * (vec2 p_vec);
		inline void operator *= (vec2 p_vec);

		inline vec2 operator *(float p_num);
		inline void operator *= (float p_num);

		inline vec2 operator / (vec2 p_vec);
		inline void operator /= (vec2 p_vec);

		inline vec2 operator /(float p_num);
		inline void operator /= (float p_num);

		inline float length();
		inline vec2 normalize();

		static vec2 up;
		static vec2 down;
		static vec2 left;
		static vec2 right;

	};

	struct FRS_MATH_API vec3 : public vec2 {
		float z = 0;

		vec3();
		vec3(const float p_x, const  float p_y, const  float p_z);
		vec3(const vec2& p_vec, float p_z);

		float& operator[](u8 p_index);

		inline bool operator == (vec3 p_vec);
		inline bool operator != (vec3 p_vec);

		inline vec3 operator +(vec3 p_vec);
		inline void operator +=(vec3 p_vec);
		inline vec3 operator +(float p_num);
		inline void operator +=(float p_num);

		inline void operator++();

		inline vec3 operator -(vec3 p_vec);
		inline void operator -=(vec3 p_vec);
		inline vec3 operator -(float p_num);
		inline void operator -=(float p_num);

		inline void operator --();

		inline vec3 operator * (vec3 p_vec);
		inline void operator *= (vec3 p_vec);

		inline vec3 operator *(float p_num);
		inline void operator *= (float p_num);

		inline vec3 operator / (vec3 p_vec);
		inline void operator /= (vec3 p_vec);

		inline vec3 operator /(float p_num);
		inline void operator /= (float p_num);

		inline float length();
		inline vec3 normalize();
	};

	struct FRS_MATH_API vec4 : public vec3 {
		float w = 0;

		vec4();
		vec4(const float p_x, const  float p_y, 
			const float p_z, const float p_w);
		vec4(const vec3& p_vec, float p_w);

		float& operator[](u8 p_index);

		inline bool operator == (vec4 p_vec);
		inline bool operator != (vec4 p_vec);

		inline vec4 operator +(vec4 p_vec);
		inline void operator +=(vec4 p_vec);
		inline vec4 operator +(float p_num);
		inline void operator +=(float p_num);

		inline void operator++();

		inline vec4 operator -(vec4 p_vec);
		inline void operator -=(vec4 p_vec);
		inline vec4 operator -(float p_num);
		inline void operator -=(float p_num);

		inline void operator --();

		inline vec4 operator * (vec4 p_vec);
		inline void operator *= (vec4 p_vec);

		inline vec4 operator *(float p_num);
		inline void operator *= (float p_num);

		inline vec4 operator / (vec4 p_vec);
		inline void operator /= (vec4 p_vec);

		inline vec4 operator /(float p_num);
		inline void operator /= (float p_num);

		inline float length();
		inline vec4 normalize();
	};

}

#endif