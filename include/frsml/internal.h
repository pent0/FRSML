#ifndef FRSML_INTERNAL_H
#define FRSML_INTERNAL_H

#ifndef FRSML_CONFIG_H
#define FRSML_CONFIG_H

#include "config.h"

#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef char int8;
typedef int int32;
typedef short int16;
typedef unsigned long int64;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned long uint64;
typedef unsigned char uint8;

typedef unsigned long long size64;
typedef unsigned int size32;

#define PI 3.14159265358979323846264338327950288f
#define PI2 6.28318530717958647692528676655900577f
#define PID2 1.57079632679489661923132169163975144f
#define PISQ 9.86960440108935861883449099987615114f

#ifdef _WIN32
	#ifdef FRSML_DYNAMIC
		#ifdef FRSML_DYNAMIC_EXPORTS
			#define FRS_MATH_API __declspec(dllexport)
		#else
			#define FRS_MATH_API __declspec(dllimport)
		#endif
	#else
		#define FRS_MATH_API
	#endif
#else
	#define FRS_MATH_API
#endif

#endif