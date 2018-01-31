#ifndef FRSML_IMPL_NORM_NORM_NOISE_H
#define FRSML_IMPL_NORM_NORM_NOISE_H

#include <frsml/noise.h>

namespace frsml {
	namespace norm {
		namespace noise {
			float _perlin(float x, float y, float z, const int* p);
			float _grad(int hash, float x, float y, float z);
		}
	}
}

#endif
