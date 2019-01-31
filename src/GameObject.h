#include <d3d11.h>
#include "Mesh.h"


class GameObject
{
private:
	Mesh * baseMesh;

	//Translation variables
	//Initialized to 0 as it only adds to the original values
	float trans_X = 0;
	float trans_Y = 0;
	float trans_Z = 0;
	//Queternions for rotation
	float pitch = 0;
	float yaw   = 0;
	float roll  = 0;
	//Scaling vars
	//Initilized to 1 as it's a multiplication
	float scale_X = 1;
	float scale_Y = 1;
	float scale_Z = 1;

public:
	GameObject();
	void SetMesh(Mesh * baseMesh);
	void Translate(float const &x, float const &y, float const &z);
	void Scale(float const &x, float const &y, float const &z);
	void Rotate(float const &pitch, float const &yaw, float const &roll);
	const DirectX::XMMATRIX GetWorldMatrix();
	~GameObject();
};