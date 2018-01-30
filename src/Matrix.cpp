#include <frsml/matrix.h>
#include <frsml/vector.h>
#include <frsml/standard.h>

#include "math_internal.h"

namespace frsml {
	mat4::mat4() {
		cols[0] = vec4::vec4(1, 0, 0, 0);
		cols[1] = vec4::vec4(0, 1, 0, 0);
		cols[2] = vec4::vec4(0, 0, 1, 0);
		cols[3] = vec4::vec4(0, 0, 0, 1);
	}

	mat4::mat4(vec4 p_cols[4]) {
		cols[0] = p_cols[0];
		cols[1] = p_cols[1];
		cols[2] = p_cols[2];
		cols[3] = p_cols[3];
	}

	mat4::mat4(float p_floats[16]) {
		for (u32 i = 0; i < 4; i++) {
			cols[i] = vec4::vec4(p_floats[i],
				p_floats[i + 4], p_floats[i + 8], p_floats[i + 12]);
		}
	}

	inline mat4 mat4::operator +(mat4 p_mat) {
		mat4 t_mat4 = mat4::mat4();

		t_mat4.cols[0] = cols[0] + p_mat.cols[0];
		t_mat4.cols[1] = cols[1] + p_mat.cols[1];
		t_mat4.cols[2] = cols[2] + p_mat.cols[2];
		t_mat4.cols[3] = cols[3] + p_mat.cols[3];

		return t_mat4;
	}

	inline mat4 mat4::operator -(mat4 p_mat) {
		mat4 t_mat4 = mat4::mat4();

		t_mat4.cols[0] = cols[0] - p_mat.cols[0];
		t_mat4.cols[1] = cols[1] - p_mat.cols[1];
		t_mat4.cols[2] = cols[2] - p_mat.cols[2];
		t_mat4.cols[3] = cols[3] - p_mat.cols[3];

		return t_mat4;
	}

	inline mat4 mat4::operator *(mat4 p_mat) {
		vec4 t_new_cols[4];

#if 1

		__m128 t_col1 = to_pack4(p_mat.cols[0]);
		__m128 t_col2 = to_pack4(p_mat.cols[1]);
		__m128 t_col3 = to_pack4(p_mat.cols[2]);
		__m128 t_col4 = to_pack4(p_mat.cols[3]);

		for (u32 i = 0; i < 4; i++) {
			__m128 t_col_x = _mm_set1_ps(cols[i].x);
			__m128 t_col_y = _mm_set1_ps(cols[i].y);
			__m128 t_col_z = _mm_set1_ps(cols[i].z);
			__m128 t_col_w = _mm_set1_ps(cols[i].w);

			__m128 t1 = _mm_mul_ps(t_col1, t_col_x);
			__m128 t2 = _mm_mul_ps(t_col2, t_col_y);
			__m128 t3 = _mm_mul_ps(t_col3, t_col_z);
			__m128 t4 = _mm_mul_ps(t_col4, t_col_w);

			t1 = _mm_add_ps(t1, t2);
			t3 = _mm_add_ps(t3, t4);
			t1 = _mm_add_ps(t1, t3);

			t_new_cols[i] = to_vec4(t1);
		}
#else
		for (u32 i = 0; i < 4; i++) {
			vec4 t1 = p_mat.cols[0] * cols[i].x;
			vec4 t2 = p_mat.cols[1] * cols[i].y;
			vec4 t3 = p_mat.cols[2] * cols[i].z;
			vec4 t4 = p_mat.cols[3] * cols[i].w;

			t_new_cols[i] = t1 + t2 + t3 + t4;
		}
#endif
		return mat4(t_new_cols);
	}

	long mat4::determinant() {
#if 1
		vec4 t_rows[4];

		t_rows[0] = vec4::vec4(cols[0].x, cols[1].x,
			cols[2].x, cols[3].x);
		t_rows[1] = vec4::vec4(cols[0].y, cols[1].y,
			cols[2].y, cols[3].y);
		t_rows[2] = vec4::vec4(cols[0].z, cols[1].z,
			cols[2].z, cols[3].z);
		t_rows[3] = vec4::vec4(cols[0].w, cols[1].w,
			cols[2].w, cols[3].w);

		__m128 t_mainVec[4];

		for (u32 i = 0; i < 4; i++) {
			t_mainVec[i] = to_pack4(t_rows[i]);
		}

		__m128 t_template0; {
			__m128 t1 = _mm_shuffle_ps(t_mainVec[1], t_mainVec[1], _MM_SHUFFLE(2, 1, 0, 3));
			__m128 t2 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(1, 0, 2, 3));
			__m128 t3 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(0, 2, 1, 3));
			__m128 t4 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(0, 2, 1, 3));
			__m128 t5 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(1, 0, 2, 3));

			t_template0 = _mm_mul_ps(_mm_set1_ps(t_rows[0].x), t1);
			t_template0 = _mm_mul_ps(t_template0, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 t_template1; {
			__m128 t1 = _mm_shuffle_ps(t_mainVec[1], t_mainVec[1], _MM_SHUFFLE(3, 1, 0, 2));
			__m128 t2 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(0, 3, 1, 2));
			__m128 t3 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(1, 0, 3, 2));
			__m128 t4 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(1, 0, 3, 2));
			__m128 t5 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(0, 3, 1, 2));

			t_template1 = _mm_mul_ps(_mm_set1_ps(t_rows[0].y), t1);
			t_template1 = _mm_mul_ps(t_template1, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 t_template2; {
			__m128 t1 = _mm_shuffle_ps(t_mainVec[1], t_mainVec[1], _MM_SHUFFLE(3, 2, 0, 1));
			__m128 t2 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(2, 0, 3, 1));
			__m128 t3 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(0, 3, 2, 1));
			__m128 t4 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(0, 3, 2, 1));
			__m128 t5 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(2, 0, 3, 1));

			t_template2 = _mm_mul_ps(_mm_set1_ps(t_rows[0].z), t1);
			t_template2 = _mm_mul_ps(t_template2, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 t_template3; {
			__m128 t1 = _mm_shuffle_ps(t_mainVec[1], t_mainVec[1], _MM_SHUFFLE(3, 2, 1, 0));
			__m128 t2 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(1, 3, 2, 0));
			__m128 t3 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(2, 1, 3, 0));
			__m128 t4 = _mm_shuffle_ps(t_mainVec[2], t_mainVec[2], _MM_SHUFFLE(2, 1, 3, 0));
			__m128 t5 = _mm_shuffle_ps(t_mainVec[3], t_mainVec[3], _MM_SHUFFLE(1, 3, 2, 0));

			t_template3 = _mm_mul_ps(_mm_set1_ps(t_rows[0].w), t1);
			t_template3 = _mm_mul_ps(t_template3, _mm_sub_ps(_mm_mul_ps(t2, t3), _mm_mul_ps(t4, t5)));
		}

		__m128 t_res = _mm_add_ps(t_template0, _mm_add_ps(t_template1, _mm_add_ps(t_template2, t_template3)));

		__m128 t_r1 = _mm_shuffle_ps(t_res, t_res, MASK3);
		__m128 t_r2 = _mm_shuffle_ps(t_res, t_res, MASK2);
		__m128 t_r3 = _mm_shuffle_ps(t_res, t_res, MASK1);

		t_r1 = _mm_add_ss(t_r1, _mm_add_ss(t_r2, t_r3));

		return static_cast<long>(_mm_cvtss_f32(t_r1));
#else
		for (int i = 0; i < 4; ++i) {
			bool found = false;

			for (int j = i; j < 4; ++j) {
				if (((i == 0) && (cols[j].x)) ||
					((i == 1) && (cols[j].y)) ||
					((i == 2) && (cols[j].z)) ||
					((i == 3) && (cols[j].w))) {
					if (i != j) {
						vec4 t_row = cols[i];
						cols[i] = cols[j];
						cols[j] = t_row;
					}

					found = true;
					break;
				}
			}


			if (!found) return 0;

			for (int j = i + 1; j < 4; ++j) {
				while (true) {
					float del = 
						cols[j][i] / cols[i][i];

					for (int k = i; k < 4; ++k) {
						switch (k) {
						case 0:
							cols[j].x -= del * cols[i].x;
							break;
						case 1:
							cols[j].y -= del * cols[i].y;
							break;
						case 2:
							cols[j].z -= del * cols[i].z;
							break;
						case 3:
							cols[j].w -= del * cols[i].w;
							break;
						}
					}

					if (cols[j][i] == 0) {
						break;
					}
					else {
						vec4 t_row = cols[i];
						cols[i] = cols[j];
						cols[j] = t_row;
					}
				}
			}

		}

		long res = 1;

		for (int i = 0; i < 4; ++i) {
			res *= (long)cols[i][i];
		}

		return res;
#endif
	}

	mat4 mat4::inverse() {

		__m128 t_rows_i[4];
		__m128 t_rows[4];

		t_rows_i[0] = _mm_set_ps(1, 0, 0, 0);
		t_rows_i[1] = _mm_set_ps(0, 1, 0, 0);
		t_rows_i[2] = _mm_set_ps(0, 0, 1, 0);
		t_rows_i[3] = _mm_set_ps(0, 0, 0, 1);

		t_rows[0] = _mm_set_ps(cols[0].x, cols[1].x,
			cols[2].x, cols[3].x);
		t_rows[1] = _mm_set_ps(cols[0].y, cols[1].y,
			cols[2].y, cols[3].y);
		t_rows[2] = _mm_set_ps(cols[0].z, cols[1].z,
			cols[2].z, cols[3].z);
		t_rows[3] = _mm_set_ps(cols[0].w, cols[1].w,
			cols[2].w, cols[3].w);

		__m128 t1, t2;

		t1 = _mm_shuffle_ps(t_rows[0], t_rows[0], GET_MASK(3));
		t_rows[0] = _mm_div_ps(t_rows[0], t1);
		t_rows_i[0] = _mm_div_ps(t_rows_i[0], t1);

		t2 = _mm_shuffle_ps(t_rows[1], t_rows[1], GET_MASK(3));
		t_rows[1] = _mm_sub_ps(t_rows[1], _mm_mul_ps(t_rows[0], t2));
		t_rows_i[1] = _mm_sub_ps(t_rows_i[1], _mm_mul_ps(t_rows_i[0], t2));

		t2 = _mm_shuffle_ps(t_rows[2], t_rows[2], GET_MASK(3));
		t_rows[2] = _mm_sub_ps(t_rows[2], _mm_mul_ps(t_rows[0], t2));
		t_rows_i[2] = _mm_sub_ps(t_rows_i[2], _mm_mul_ps(t_rows_i[0], t2));

		t2 = _mm_shuffle_ps(t_rows[3], t_rows[3], GET_MASK(3));
		t_rows[3] = _mm_sub_ps(t_rows[3], _mm_mul_ps(t_rows[0], t2));
		t_rows_i[3] = _mm_sub_ps(t_rows_i[3], _mm_mul_ps(t_rows_i[0], t2));


		t1 = _mm_shuffle_ps(t_rows[1], t_rows[1], GET_MASK(2));
		t_rows[1] = _mm_div_ps(t_rows[1], t1);
		t_rows_i[1] = _mm_div_ps(t_rows_i[1], t1);

		t2 = _mm_shuffle_ps(t_rows[0], t_rows[0], GET_MASK(2));
		t_rows[0] = _mm_sub_ps(t_rows[0], _mm_mul_ps(t_rows[1], t2));
		t_rows_i[0] = _mm_sub_ps(t_rows_i[0], _mm_mul_ps(t_rows_i[1], t2));

		t2 = _mm_shuffle_ps(t_rows[2], t_rows[2], GET_MASK(2));
		t_rows[2] = _mm_sub_ps(t_rows[2], _mm_mul_ps(t_rows[1], t2));
		t_rows_i[2] = _mm_sub_ps(t_rows_i[2], _mm_mul_ps(t_rows_i[1], t2));

		t2 = _mm_shuffle_ps(t_rows[3], t_rows[3], GET_MASK(2));
		t_rows[3] = _mm_sub_ps(t_rows[3], _mm_mul_ps(t_rows[1], t2));
		t_rows_i[3] = _mm_sub_ps(t_rows_i[3], _mm_mul_ps(t_rows_i[1], t2));


		t1 = _mm_shuffle_ps(t_rows[2], t_rows[2], GET_MASK(1));
		t_rows[2] = _mm_div_ps(t_rows[2], t1);
		t_rows_i[2] = _mm_div_ps(t_rows_i[2], t1);

		t2 = _mm_shuffle_ps(t_rows[0], t_rows[0], GET_MASK(1));
		t_rows[0] = _mm_sub_ps(t_rows[0], _mm_mul_ps(t_rows[2], t2));
		t_rows_i[0] = _mm_sub_ps(t_rows_i[0], _mm_mul_ps(t_rows_i[2], t2));

		t2 = _mm_shuffle_ps(t_rows[1], t_rows[1], GET_MASK(1));
		t_rows[1] = _mm_sub_ps(t_rows[2], _mm_mul_ps(t_rows[2], t2));
		t_rows_i[1] = _mm_sub_ps(t_rows_i[2], _mm_mul_ps(t_rows_i[2], t2));

		t2 = _mm_shuffle_ps(t_rows[3], t_rows[3], GET_MASK(1));
		t_rows[3] = _mm_sub_ps(t_rows[3], _mm_mul_ps(t_rows[2], t2));
		t_rows_i[3] = _mm_sub_ps(t_rows_i[3], _mm_mul_ps(t_rows_i[2], t2));


		t1 = _mm_shuffle_ps(t_rows[3], t_rows[3], GET_MASK(0));
		t_rows[3] = _mm_div_ps(t_rows[3], t1);
		t_rows_i[3] = _mm_div_ps(t_rows_i[3], t1);

		t2 = _mm_shuffle_ps(t_rows[0], t_rows[0], GET_MASK(0));
		t_rows[0] = _mm_sub_ps(t_rows[0], _mm_mul_ps(t_rows[3], t2));
		t_rows_i[0] = _mm_sub_ps(t_rows_i[0], _mm_mul_ps(t_rows_i[3], t2));

		t2 = _mm_shuffle_ps(t_rows[2], t_rows[2], GET_MASK(0));
		t_rows[2] = _mm_sub_ps(t_rows[2], _mm_mul_ps(t_rows[3], t2));
		t_rows_i[2] = _mm_sub_ps(t_rows_i[2], _mm_mul_ps(t_rows_i[3], t2));

		t2 = _mm_shuffle_ps(t_rows[1], t_rows[1], GET_MASK(0));
		t_rows[1] = _mm_sub_ps(t_rows[1], _mm_mul_ps(t_rows[3], t2));
		t_rows_i[1] = _mm_sub_ps(t_rows_i[1], _mm_mul_ps(t_rows_i[3], t2));

		vec4 t_vecs[4];

		for (u32 i = 0; i < 4; i++) {
			t_vecs[i] = to_vec4(t_rows_i[i]);
		}

		return mat4(t_vecs).transpose();

	}

	mat4 mat4::transpose() {
		vec4 t_rows[4];

		t_rows[0] = vec4::vec4(cols[0].x, cols[1].x,
			cols[2].x, cols[3].x);
		t_rows[1] = vec4::vec4(cols[0].y, cols[1].y,
			cols[2].y, cols[3].y);
		t_rows[2] = vec4::vec4(cols[0].z, cols[1].z,
			cols[2].z, cols[3].z);
		t_rows[3] = vec4::vec4(cols[0].w, cols[1].w,
			cols[2].w, cols[3].w);

		return mat4(t_rows);
	}

	mat4 mat4::translate(vec3 p_trans) {
		mat4 t_mat = mat4::mat4();

		t_mat.cols[3].x = p_trans.x;
		t_mat.cols[3].y = p_trans.y;
		t_mat.cols[3].z = p_trans.z;

		return t_mat * (*this);
	}

	mat4 mat4::rotate(float p_angle, vec3 p_dir) {
		mat4 t_mat;

		float t = cos(p_angle);
		float t2 = sin(p_angle);

		if (p_dir == vec3(-1, 0, 0)) {
			t_mat.cols[1].y = t;
			t_mat.cols[2].x = -t2;
			t_mat.cols[1].z = t2;
			t_mat.cols[2].y = t;
		}
		else if (p_dir == vec3(0, 1, 0)) {
			t_mat.cols[0].x = t;
			t_mat.cols[2].x = t2;
			t_mat.cols[0].z = -t2;
			t_mat.cols[2].z = t;
		}
		else if (p_dir == vec3(0, 0, 1)) {
			t_mat.cols[0].x = t;
			t_mat.cols[1].x = -t2;
			t_mat.cols[0].y = t2;
			t_mat.cols[1].y = -t;
		}

		return t_mat * (*this);
	}

	mat4 mat4::scale(float p_scale) {
		mat4 t_mat = mat4::mat4();
		t_mat.cols[0].x = t_mat.cols[1].y = t_mat.cols[2].z = p_scale;

		return (t_mat) * (*this);
	}

	mat4 perspective_matrix(float p_zoom,
		vec2 p_extent, float p_zNear, float p_zFar) {
		float t_aspect = p_extent.x / p_extent.y;

		float t1 = p_zoom / 2;
		t1 = 1 / tan(t1);

		float t2 = p_zFar - p_zNear;
		float t3 = p_zFar * p_zNear;

		t3 = t3 / t2 * -1;

		float t4 = p_zFar * t2;
		t4 *= -1;

		float t_res = t1;
		float t_res2 = t3;
		float t_res3 = t4;

		vec4 t_cols[4];

		t_cols[0] = vec4::vec4(t_res * t_aspect, 0, 0, 0);
		t_cols[1] = vec4::vec4(0, t_res, 0, 0);
		t_cols[2] = vec4::vec4(0, 0, t_res3, -1);
		t_cols[3] = vec4::vec4(0, 0, t_res2, 0);

		return mat4(t_cols);
	}

	mat4 ortho_matrix(float p_left, float p_right, float p_bottom, float p_top,
		float p_zNear, float p_zFar) {
		float t1 = 2 / (p_right - p_left);
		float t2 = 2 / (p_top - p_bottom);
		float t3 = -(p_right + p_left) / (p_right - p_left);
		float t4 = -(p_top + p_bottom) / (p_top - p_bottom);
		float t5 = -2 / (p_zNear - p_zFar);
		float t6 = -(p_zFar + p_zNear) / (p_zFar - p_zNear);

		vec4 t_cols[4];

		t_cols[0] = vec4::vec4(t1, 0, 0, 0);
		t_cols[1] = vec4::vec4(0, t2, 0, 0);
		t_cols[2] = vec4::vec4(0, 0, t5, 0);
		t_cols[3] = vec4::vec4(t3, t4, t6, 1);

		return mat4(t_cols);
	}
}
