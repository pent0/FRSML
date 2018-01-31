#ifndef FRSML_STANDARD_H
#define FRSML_STANDARD_H

#include "internal.h"

namespace frsml {

	struct vec2;
	struct vec3;
	struct vec4;
	struct mat4;

	vec2 FRS_MATH_API abs(vec2 p_vec);
	vec3 FRS_MATH_API abs(vec3 p_vec);
	vec4 FRS_MATH_API abs(vec4 p_vec);

	vec2 FRS_MATH_API dot(vec2 p_vec, vec2 p_vec1);
	vec3 FRS_MATH_API dot(vec3 p_vec, vec3 p_vec1);
	vec4 FRS_MATH_API dot(vec4 p_vec, vec4 p_vec1);

	vec3 FRS_MATH_API cross(vec3 p_vec, vec3 p_vec1);

	vec2 FRS_MATH_API angle(vec2 p_vec, vec2 p_vec1);
	vec3 FRS_MATH_API angle(vec3 p_vec, vec3 p_vec1);
	vec4 FRS_MATH_API angle(vec4 p_vec, vec4 p_vec1);

	vec2 FRS_MATH_API reflect(vec2 p_inDir, vec2 p_inNorm);
	vec3 FRS_MATH_API reflect(vec3 p_inDir, vec3 p_inNorm);
	vec4 FRS_MATH_API reflect(vec4 p_inDir, vec4 p_inNorm);

	float FRS_MATH_API distance(vec2 p_start, vec2 p_end);
	float FRS_MATH_API distance(vec3 p_start, vec3 p_end);
	float FRS_MATH_API distance(vec4 p_start, vec4 p_end);

	float FRS_MATH_API exp(float x);
	float FRS_MATH_API log(float x);
	float FRS_MATH_API log2(float x);
	float FRS_MATH_API log(float x, float base);
	float FRS_MATH_API pow(float x, float y);

	float FRS_MATH_API abs(float p_num);
	float FRS_MATH_API clamp(float p_t1, float p_t2, float p_crrNumber);
	float FRS_MATH_API lerp(float p_t, float p_a, float p_b);

	int FRS_MATH_API sign(float p_num);

	float FRS_MATH_API sin(float p_num);
	float FRS_MATH_API cos(float p_num);
	float FRS_MATH_API tan(float p_num);
	float FRS_MATH_API cot(float p_num);

	void  FRS_MATH_API sin_cos(float p_x, float* p_s, float* p_c);

	float FRS_MATH_API asin(float p_num);
	float FRS_MATH_API acos(float p_num);
	float FRS_MATH_API atan(float p_num);
	float FRS_MATH_API atan2(float p_x, float p_y);
	float FRS_MATH_API maxf(float p_num, float p_num1);
	float FRS_MATH_API minf(float p_num, float p_num1);
	float FRS_MATH_API sqrt(float p_num);

	float FRS_MATH_API fade(float p_num);

	mat4 FRS_MATH_API  perspective_matrix(float p_zoom,
		vec2 p_extent, float p_zNear, float p_zFar);

	mat4 FRS_MATH_API  ortho_matrix(float p_left, float p_right, float p_bottom, float p_top,
		float p_zNear, float p_zFar);
}

#endif