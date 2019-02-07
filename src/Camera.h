#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
private:
	DirectX::XMMATRIX viewMatrix;
public:
	Camera(Mesh * const& mesh, DirectX::XMFLOAT3& front, DirectX::XMFLOAT3& position, float const & speed);
	~Camera();
	const DirectX::XMMATRIX& GetViewMatrix();
	void CheckKeyPress(float const &deltaTime);
};