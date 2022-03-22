#pragma once
#include <vector>

#ifdef __cplusplus
	extern "C" {
#endif
		struct A {
			int x; 
			int y;
		};
		_declspec(dllexport) float XPlusY(float x, float y);
		_declspec(dllexport) int RandomNumber();
		_declspec(dllexport) int XY(A xy);
#ifdef __cplusplus
	}
#endif