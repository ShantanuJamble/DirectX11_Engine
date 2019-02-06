#include "GameObject.h"
#include <iostream>


DirectX::XMVECTOR worldUp = DirectX::XMVectorSet(0, 1, 0, 0);

GameObject::GameObject()
{
	this->baseMesh = NULL;
	front = DirectX::XMVectorSet(0, 0, -1, 0);
	position = DirectX::XMVectorSet(0, 0, 0, 0);
	up = DirectX::XMVectorSet(0, 1, 0, 0);
	right = DirectX::XMVector4Cross(front,worldUp,DirectX::XMQuaternionIdentity());
	roll = pitch = yaw = 0;
	scale.x = scale.y = scale.z = 1;
	movementSpeed = 5.0f;
}

void GameObject::SetMesh(Mesh * baseMesh)
{
	this->baseMesh = baseMesh;
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
const DirectX::XMMATRIX GameObject::GetWorldMatrix()
{
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
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
		right = DirectX::XMVector4Cross(front, worldUp, DirectX::XMQuaternionIdentity());
		up =  DirectX::XMVector4Cross(right, front, DirectX::XMQuaternionIdentity());
	}

	//Translate
	worldMatrix = DirectX::XMMatrixMultiply(worldMatrix, DirectX::XMMatrixTranslationFromVector(position));
	return worldMatrix;
}


//Following functions handle the movement of object in the specific direction.
void GameObject::MoveForward(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(front, velocity* 1));
}

void GameObject::MoveBackward(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(front, velocity * -1));
}

void GameObject::MoveRight(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(right, velocity * 1));
}

void GameObject::MoveLeft(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position = DirectX::XMVectorAdd(position, DirectX::XMVectorScale(right, velocity * -1));
} 

GameObject::~GameObject()
{
}
