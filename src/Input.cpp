#include "Input.h"

bool Input::IsKeyPressed(int key)
{
	return GetAsyncKeyState(key) & 0x8000;
}

float Input::MouseMoved()
{
	return 0.0f;
}
