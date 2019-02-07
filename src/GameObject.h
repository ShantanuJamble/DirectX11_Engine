#pragma once
#include <d3d11.h>
#include "Mesh.h"



class GameObject
{
protected:
	Mesh * baseMesh;
	DirectX::XMMATRIX worldMatrix;
	//Queternions for rotation
	float pitch;
	float yaw;
	float roll;

	//Scaling vars
	//Initilized to 1 as it's a multiplication
	DirectX::XMFLOAT3 scale;

	//Positinal Components
	DirectX::XMVECTOR position;//Also maintains translation values
	DirectX::XMVECTOR front;
	DirectX::XMVECTOR up;
	DirectX::XMVECTOR right;

	float movementSpeed;

public:
	GameObject(Mesh * const & mesh, DirectX::XMFLOAT3& front, DirectX::XMFLOAT3& position, float const & speed);
	void SetMesh(Mesh *& mesh);
	void Translate(float const &x, float const &y, float const &z);
	void Scale(float const &x, float const &y, float const &z);
	void Rotate(float const &pitch, float const &yaw, float const &roll);
	const DirectX::XMMATRIX& GetWorldMatrix();
	void MoveForward(float const & deltaTime);
	void MoveBackward(float const & deltaTime);
	void MoveRight(float const & deltaTime);
	void MoveLeft(float const & deltaTime);
	void MoveUp(float const & deltaTime);
	void MoveDown(float const & deltaTime);
	~GameObject();
};