#include <d3d11.h>
#include "Mesh.h"


class GameObject
{
protected:
	Mesh * baseMesh;

	//Queternions for rotation
	float pitch = 0;
	float yaw   = 0;
	float roll  = 0;

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
	GameObject();
	void SetMesh(Mesh * baseMesh);
	void Translate(float const &x, float const &y, float const &z);
	void Scale(float const &x, float const &y, float const &z);
	void Rotate(float const &pitch, float const &yaw, float const &roll);
	const DirectX::XMMATRIX GetWorldMatrix();
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	~GameObject();
};