#pragma once
#include <stdio.h>
#include <direct.h>
#include <string>
#define GetCurrentDir _getcwd
class FileHandler
{
public:
	static std::string getCWD()
	{
		char cCurrentPath[FILENAME_MAX];

		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		{
			return "";
		}

		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; 

		return cCurrentPath;
		
	}
};



