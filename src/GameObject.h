#include <d3d11.h>
#include "Mesh.h"


class GameObject
{
private:
	Mesh * baseMesh;

	//Translation variables
	DirectX::XMFLOAT3 translation;

	//Queternions for rotation
	float pitch = 0;
	float yaw   = 0;
	float roll  = 0;

	//Scaling vars
	//Initilized to 1 as it's a multiplication
	DirectX::XMFLOAT3 scale;

public:
	GameObject();
	void SetMesh(Mesh * baseMesh);
	void Translate(float const &x, float const &y, float const &z);
	void Scale(float const &x, float const &y, float const &z);
	void Rotate(float const &pitch, float const &yaw, float const &roll);
	const DirectX::XMMATRIX GetWorldMatrix();
	~GameObject();
};