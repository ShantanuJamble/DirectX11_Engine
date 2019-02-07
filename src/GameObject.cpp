#include "GameObject.h"
#include <iostream>

static DirectX::XMVECTOR worldUp = DirectX::XMVectorSet(0, 1, 0, 0);


///TODO: Use Member initilizer lists.
GameObject::GameObject(Mesh* const & mesh, Material * const material, DirectX::XMFLOAT3& front, DirectX::XMFLOAT3& position, float const & speed)
	: baseMesh(mesh), baseMaterial(material), pitch(0), yaw(0), roll(0), scale(1, 1, 1), movementSpeed(speed)
{
	this->front = DirectX::XMVectorSet(front.x, front.y, front.z, 0);
	this->position = DirectX::XMVectorSet(position.x, position.y, position.z, 0);
	up = DirectX::XMVectorSet(0, 1, 0, 0);
	right = DirectX::XMVector4Cross(worldUp, this->front, DirectX::XMQuaternionIdentity());
}


void GameObject::SetMesh(Mesh*& baseMesh)
{
	this->baseMesh = baseMesh;
}
void GameObject::SetMaterial(Material *& material)
{
	baseMaterial = material;
}

//Takes in values of translation along each axis and stores for fututre calculations.
void GameObject::Translate(float const & x, float const  & y, float const  & z)
{
	position = DirectX::XMVectorSet(x, y, z,0);
}

//Takes in values of scaling along each axis and stores for fututre calculations.
void GameObject::Scale(float const  & x, float const  & y, float const  & z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

//Maintain Pitch,roll and yaw for the gameobject.
void GameObject::Rotate(float const & pitch, float const & yaw, float const & roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}


//Performs the SRT operations and returns the world matrix to the shader for darwing. 
const DirectX::XMMATRIX& GameObject::GetWorldMatrix()
{
	worldMatrix = DirectX::XMMatrixIdentity();
	//Scale 
	worldMatrix = DirectX::XMMatrixMultiply(worldMatrix, DirectX::XMMatrixScaling(scale.x, scale.y, scale.z));

	//Rotate
	DirectX::XMVECTOR rotationVector = DirectX::XMQuaternionRotationRollPitchYaw(DirectX::XMConvertToRadians(pitch), 
																				 DirectX::XMConvertToRadians(yaw),
																				 DirectX::XMConvertToRadians(roll)
																			     );
	worldMatrix = DirectX::XMMatrixMultiply(worldMatrix, DirectX::XMMatrixRotationQuaternion(rotationVector));
	if (roll != 0 || pitch != 0 || yaw != 0)
	{
		front = DirectX::XMVector4Normalize(rotationVector);
		right = DirectX::XMVector4Cross(worldUp, front, DirectX::XMQuaternionIdentity());
		up =  DirectX::XMVector4Cross(right, front, DirectX::XMQuaternionIdentity());
	}

	//Translate
	worldMatrix = DirectX::XMMatrixMultiply(worldMatrix, DirectX::XMMatrixTranslationFromVector(position));
	return worldMatrix;
}


//Following functions handle the movement of object in the specific direction.
void GameObject::MoveForward(float const & deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(front, velocity* 1));
}

void GameObject::MoveBackward(float const & deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(front, velocity * -1));
}

void GameObject::MoveRight(float const & deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(right, velocity * 1));
}

void GameObject::MoveLeft(float const & deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(right, velocity * -1));
}
void GameObject::MoveUp(float const  & deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(worldUp, velocity * 1));
}

void GameObject::MoveDown(float const  & deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(worldUp, velocity * -1));
}


GameObject::~GameObject()
{
}
