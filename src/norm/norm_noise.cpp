#include "norm_standard.h"
#include "norm_noise.h"

namespace frsml {
	namespace norm {
		namespace noise {
			float _perlin(float x, float y, float z, const int* p) {
				int xi = (int)x & 255;
				int yi = (int)y & 255;
				int zi = (int)z & 255;

				float xf = x - (int)x;
				float yf = y - (int)y;
				float zf = z - (int)z;

				float u = norm::_fade(xf);
				float v = norm::_fade(yf);
				float w = norm::_fade(zf);

				int aaa = p[p[p[xi] + yi] + zi];
				int aab = p[p[p[xi] + yi] + zi + 1];
				int aba = p[p[p[xi] + yi + 1] + zi];
				int abb = p[p[p[xi] + yi + 1] + zi + 1];
				int baa = p[p[p[xi + 1] + yi] + zi];
				int bab = p[p[p[xi + 1] + yi] + zi + 1];
				int bba = p[p[p[xi + 1] + yi + 1] + zi];
				int bbb = p[p[p[xi + 1] + yi + 1] + zi + 1];
				
				float x1 = norm::_lerp(_grad(aaa, xf, yf, zf),
					_grad(baa, xf - 1, yf, zf),
					u);

				float x2 = norm::_lerp(_grad(aba, xf, yf - 1, zf),
					_grad(bba, xf - 1, yf - 1, zf),
					u);

				float y1 = norm::_lerp(x1, x2, v);

				x1 = norm::_lerp(_grad(aab, xf, yf, zf),
					_grad(bab, xf - 1, yf, zf-1),
					u);

				x2 = norm::_lerp(_grad(abb, xf, yf - 1, zf-1),
					_grad(bbb, xf - 1, yf - 1, zf - 1),
					u);

				float y2 = norm::_lerp(x1, x2, v);

				return (norm::_lerp(y1, y2, w) + 1) / 2;
			}

			float _grad(int hash, float x, float y, float z) {
				switch (hash & 0xF) {
					case 0x0: return x + y;
					case 0x1: return -x + y;
					case 0x2: return x - y;
					case 0x3: return -x - y;
					case 0x4: return x + z;
					case 0x5: return -x + z;
					case 0x6: return x - z;
					case 0x7: return -x - z;
					case 0x8: return y + z;
					case 0x9: return -y + z;
					case 0xA: return y - z;
					case 0xB: return -y - z;
					case 0xC: return y + x;
					case 0xD: return -y + z;
					case 0xE: return y - x;
					case 0xF: return -y - z;
					default: return 0;
				}
			}
		}
	}
}