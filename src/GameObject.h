#pragma once
#include <d3d11.h>
#include "Mesh.h"
#include "Material.h"


class GameObject
{
protected:
	Mesh * baseMesh;
	Material * baseMaterial;
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
	GameObject(Mesh * const & mesh, Material *const material, DirectX::XMFLOAT3& front, DirectX::XMFLOAT3& position, float const & speed);

	//Mesh related methods
	void SetMesh(Mesh *& mesh);
	Mesh *& GetMesh() { return baseMesh; }

	// Movement related methods
	void Translate(float const &x, float const &y, float const &z);
	void Scale(float const &x, float const &y, float const &z);
	void Rotate(float const &pitch, float const &yaw, float const &roll);
	void MoveForward(float const & deltaTime);
	void MoveBackward(float const & deltaTime);
	void MoveRight(float const & deltaTime);
	void MoveLeft(float const & deltaTime);
	void MoveUp(float const & deltaTime);
	void MoveDown(float const & deltaTime);
	const DirectX::XMFLOAT3  GetPosition() { 
		DirectX::XMFLOAT3 tmpposition;
		DirectX::XMStoreFloat3(&tmpposition, position);
		return tmpposition;
	}

	//Material managing methods
	void SetMaterial(Material *& material);
	Material *& GetMaterial() { return baseMaterial; }
	//WorldMatrix
	const DirectX::XMMATRIX& GetWorldMatrix();
	~GameObject();
};