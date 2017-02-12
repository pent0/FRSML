#include "QuickMathSSE4.h"

namespace FRSML {
	//Convert Degrees to Radians! Whoa!
	float ToDegrees(float radians) {
		return (float)(FRS_float(radians)*HALFWISEANGLE / PI);
	}

	//Convert Radians to Degrees! Whoa!
	float ToRadians(float degrees) {
		return (float)(FRS_float(degrees) / HALFWISEANGLE * PI);
	}
}
