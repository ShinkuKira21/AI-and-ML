#pragma once

#ifdef __WIN32
	#define EXPORT _declspec(dllexport)
#else
	#define EXPORT
#endif

#ifdef __cplusplus
	extern "C" {
#endif
	struct CMemory {
		int value;
	};

	namespace CreateData {
		EXPORT CMemory CreateCMemory(int size);
	}

#ifdef __cplusplus
	}
#endif