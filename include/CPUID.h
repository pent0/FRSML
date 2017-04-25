#ifndef CPUID_H
#define CPUID_H


//Apple 

#ifdef _WIN32
#include <intrin.h>
typedef __int32 FRS_uint32;

#elif defined __unix__ 
#include <stdint.h>
#endif

#ifdef _WIN32
#ifdef FRSML_EXPORTS
#define TFAPI __declspec(dllexport)
#else
#define TFAPI __declspec(dllimport)
#endif
#endif

//Check if set of extensions are supported on the platform
//Support now: Windows
struct TFAPI CPUID {
public:
#pragma region INSTRICTS_MATH_SUPPORT



	static bool FRS_MMX;
	static bool FRS_x64;
	static bool FRS_ABM;
	static bool FRS_RDRAND;
	static bool FRS_BMI1;
	static bool FRS_BMI2;
	static bool FRS_ADX;
	static bool FRS_PREFETCHWT1;

	static bool FRS_SSE;
	static bool FRS_SSE2;
	static bool FRS_SSE3;
	static bool FRS_SSSE3;
	static bool FRS_SSE41;
	static bool FRS_SSE42;
	static bool FRS_SSE4A;
	static bool FRS_AES;
	static bool FRS_SHA;

	static bool FRS_AVX;
	static bool FRS_XOP;
	static bool FRS_FMA3;
	static bool FRS_FMA4;
	static bool FRS_AVX2;

	static bool FRS_AVX512F;
	static bool FRS_AVX512CD;
	static bool FRS_AVX512PF;
	static bool FRS_AVX512ER;
	static bool FRS_AVX512VL;
	static bool FRS_AVX512BW;
	static bool FRS_AVX512DQ;
	static bool FRS_AVX512IFMA;
	static bool FRS_AVX512VBMI;
	static bool WINDOWS_64BIT;

#pragma endregion

	//- Start check CPU extensions
	static void StartDetectCPUFeaturesAndExtensions();
	//- Check if CPU detection whether has been started, 
	//to check information about CPU extensions
	static bool HasCPUDetectionStarted();

private:
	static FRS_uint32 registers[4];
	static bool StartedDetectQuestionMark;
};




#endif
