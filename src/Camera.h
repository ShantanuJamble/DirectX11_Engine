#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
private:
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
	int screenWidth, screenHeight;
	float rotationspeed;
	
public:
	Camera(DirectX::XMFLOAT3& front, DirectX::XMFLOAT3& position, float const & speed);
	~Camera();
	void Update();
	const DirectX::XMMATRIX& GetViewMatrix();
	const DirectX::XMMATRIX& GetProjectionMatrix();
	void ChangeAspectRatio(int width, int height);
	void CheckKeyPress(float const &deltaTime);
	void MouseControl(long& xChanged,long& yChanged);
};