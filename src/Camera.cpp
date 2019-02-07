#include <d3d11.h>
#include "Input.h"
#include "Camera.h"
#include "Material.h"
#define PI 3.1415926535f
static DirectX::XMVECTOR worldUp = DirectX::XMVectorSet(0, 1, 0, 0);

Camera::Camera(DirectX::XMFLOAT3 & front, DirectX::XMFLOAT3 & position, float const & speed)
	:GameObject((Mesh*)nullptr, (Material *)nullptr, front, position, speed), screenWidth(1280), screenHeight(720)
{
}

Camera::~Camera()
{
}

const DirectX::XMMATRIX & Camera::GetViewMatrix()
{
	viewMatrix = DirectX::XMMatrixLookToLH(
		position,     // The position of the "camera"
		front,     // Direction the camera is looking
		worldUp);     // "Up" direction in 3D space (prevents roll)
	return viewMatrix;
}

const DirectX::XMMATRIX & Camera::GetProjectionMatrix()
{
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		0.25f * PI,		// Field of View Angle
		(float)screenWidth / screenHeight,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	return projectionMatrix;
}

void Camera::ChangeAspectRatio(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}
void Camera::CheckKeyPress(float const & deltaTime)
{
	if (Input::IsKeyPressed('W'))
		MoveForward(deltaTime);
	if (Input::IsKeyPressed('S'))
		MoveBackward(deltaTime);
	if (Input::IsKeyPressed('A'))
		MoveLeft(deltaTime);
	if (Input::IsKeyPressed('D'))
		MoveRight(deltaTime);
	if (Input::IsKeyPressed(VK_SPACE))
		MoveUp(deltaTime);
	if (Input::IsKeyPressed('X'))
		MoveDown(deltaTime);
}
