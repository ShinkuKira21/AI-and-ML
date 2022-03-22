#pragma once

#ifdef __WIN32
	#define EXPORT _declspec(dllexport)
#else
	#define EXPORT
#endif

#ifdef __cplusplus
	extern "C" {
#endif
		struct A {
			int x; 
			int y;
		};
		EXPORT float XPlusY(float x, float y);
		EXPORT int RandomNumber();
		EXPORT int XY(A xy);
#ifdef __cplusplus
	}
#endif