#pragma once


#include <d3d11.h>
#include <iostream>

#define ASSERT(X) if(X) __debugbreak();

#define DXCall(X) \
	HRESULT hr = S_OK;\
	hr = X;\
	if (FAILED(hr)){\
		ErrorLogCall(#X,__FILE__,__LINE__,hr);\
		__debugbreak();\
	};


void ErrorLogCall(const char * function, const char *file, int line,HRESULT hr)
{
	std::cout << "ERROR CODE: "<<hr<< ",in "<<function << "  in " << file << " at " << line << std::endl;
}
