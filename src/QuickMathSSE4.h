#ifndef QUICKMATHSSE4_H
#define QUICKMATHSSE4_H

#include <smmintrin.h>	
#include "FRSVar.h"

#define PI 3.14159265358979323846264338327950288f
#define PI2 6.28318530717958647692528676655900577f
#define PID2 1.57079632679489661923132169163975144f
#define PISQ 9.86960440108935861883449099987615114f
#define HALFWISEANGLE FRS_float(180)

#ifdef _WIN32
#ifdef FRSML_EXPORTS
#define TFAPI __declspec(dllexport)
#else
#define TFAPI __declspec(dllimport)
#endif
#endif

namespace FRSML {
	float TFAPI ToDegrees(float radians);
	float TFAPI ToRadians(float degrees);
	
}

#endif