#include <d3d11.h>
#include "Input.h"
#include "Camera.h"
static DirectX::XMVECTOR worldUp = DirectX::XMVectorSet(0, 1, 0, 0);

Camera::Camera(Mesh * const & mesh, DirectX::XMFLOAT3 & front, DirectX::XMFLOAT3 & position, float const & speed)
	:GameObject(mesh,front,position,speed)
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
