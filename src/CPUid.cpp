#include "CPUID.h"

#pragma region _VAR_REDEFINITION

FRS_uint32 CPUID::registers[4];

bool CPUID::StartedDetectQuestionMark;
bool CPUID::FRS_MMX;
bool CPUID::FRS_x64;
bool CPUID::FRS_ABM;
bool CPUID::FRS_RDRAND;
bool CPUID::FRS_BMI1;
bool CPUID::FRS_BMI2;
bool CPUID::FRS_ADX;
bool CPUID::FRS_PREFETCHWT1;

bool CPUID::FRS_SSE;
bool CPUID::FRS_SSE2;
bool CPUID::FRS_SSE3;
bool CPUID::FRS_SSSE3;
bool CPUID::FRS_SSE41;
bool CPUID::FRS_SSE42;
bool CPUID::FRS_SSE4A;
bool CPUID::FRS_AES;
bool CPUID::FRS_SHA;

bool CPUID::FRS_AVX;
bool CPUID::FRS_XOP;
bool CPUID::FRS_FMA3;
bool CPUID::FRS_FMA4;
bool CPUID::FRS_AVX2;

bool CPUID::FRS_AVX512F;
bool CPUID::FRS_AVX512CD;
bool CPUID::FRS_AVX512PF;
bool CPUID::FRS_AVX512ER;
bool CPUID::FRS_AVX512VL;
bool CPUID::FRS_AVX512BW;
bool CPUID::FRS_AVX512DQ;
bool CPUID::FRS_AVX512IFMA;
bool CPUID::FRS_AVX512VBMI;
bool CPUID::WINDOWS_64BIT;
#pragma endregion

bool CPUID::HasCPUDetectionStarted() {
	if (!StartedDetectQuestionMark) return false;
	return true;
}

void CPUID::StartDetectCPUFeaturesAndExtensions() {
	StartedDetectQuestionMark = true;
#ifdef  _WIN32
	 __cpuid((int*)registers, 0);
	 int _nie = registers[0];

	 __cpuid((int*)registers, 0x80000000);
	 int _neie = registers[0];

	 if (_nie >= 0x00000001) {
		 __cpuid(registers, 0x00000001);

		 FRS_MMX = (registers[3] & ((int)(1 << 23))) != 0;
		 FRS_SSE = (registers[3] & ((int)(1 << 25))) != 0;
		 FRS_SSE2 = (registers[3] & ((int)(1 << 26))) != 0;
		 FRS_SSE3 = (registers[2] & ((int)(1 << 0))) != 0;
		 FRS_SSSE3 = (registers[2] & ((int)(1 << 9))) != 0;
		 FRS_SSE41 = (registers[2] & ((int)(1 << 19))) != 0;
		 FRS_SSE42 = (registers[2] & ((int)(1 << 20))) != 0;

		 FRS_AES = (registers[2] & ((int)(1 << 25))) != 0;
		 FRS_AVX = (registers[2] & ((int)(1 << 28))) != 0;

		 FRS_FMA3 = (registers[2] & ((int)(1 << 12))) != 0;
		 FRS_RDRAND = (registers[2] & ((int)(1 << 30))) != 0;
	 }
	 if (_nie >= 0x00000007) {
		 __cpuid(registers, 0x00000007);

		 FRS_AVX2 = (registers[1] & ((int)(1 << 5))) != 0;
		 FRS_BMI1 = (registers[1] & ((int)(1 << 3))) != 0;
		 FRS_BMI2 = (registers[1] & ((int)(1 << 8))) != 0;

		 FRS_ADX = (registers[1] & ((int)(1 << 19))) != 0;
		 FRS_SHA = (registers[1] & ((int)(1 << 29))) != 0;
		 FRS_PREFETCHWT1 = (registers[1] & ((int)(1 << 0))) != 0;

		 FRS_AVX512F = (registers[1] & ((int)(1 << 16))) != 0;
		 FRS_AVX512CD = (registers[1] & ((int)(1 << 28))) != 0;
		 FRS_AVX512PF = (registers[1] & ((int)(1 << 29))) != 0;
		 FRS_AVX512ER = (registers[1] & ((int)(1 << 27))) != 0;
		 FRS_AVX512VL = (registers[1] & ((int)(1 << 31))) != 0;
		 FRS_AVX512BW = (registers[1] & ((int)(1 << 30))) != 0;
		 FRS_AVX512DQ = (registers[1] & ((int)(1 << 17))) != 0;
		 FRS_AVX512IFMA = (registers[1] & ((int)(1 << 21))) != 0;
		 FRS_AVX512VBMI = (registers[1] & ((int)(1 << 1))) != 0;
	 }
	 if (_neie >= 0x80000001) {
		 __cpuid(registers, 0x80000001);

		 FRS_x64 = (registers[3] & (int)(1 << 29)) != 0;
		 WINDOWS_64BIT = FRS_x64;
		 FRS_ABM = (registers[2] & (int)(1 << 5)) != 0;
		 FRS_SSE4A = (registers[2] & (int)(1 << 6)) != 0;

		 FRS_FMA4 = (registers[2] & (int)(1 << 16)) != 0;
		 FRS_XOP = (registers[2] & (int)(1 << 11)) != 0;

	 }


#endif //  _WIN32
 }

