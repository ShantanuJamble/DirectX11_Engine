#pragma once


#include <d3d11.h>
#include <iostream>

#define ASSERT(X) if(X) __debugbreak();

#define DXCall(X) \
	if (FAILED(X)){\
		ErrorLogCall(#X,__FILE__,__LINE__);\
		__debugbreak();\
	};


bool ErrorLogCall(const char * function, const char *file, int line);