#include "GameObject.h"
#include <iostream>

//Should be moved to some contants header
const  float toRadians = 3.14159265f / 180.0f;
GameObject::GameObject()
{
	this->baseMesh = NULL;
}

void GameObject::SetMesh(Mesh * baseMesh)
{
	this->baseMesh = baseMesh;
}


//Takes in values of translation along each axis and stores for fututre calculations.
void GameObject::Translate(float const & x, float const  & y, float const  & z)
{
	
	trans_X = x;
	trans_Y = y;
	trans_Z = z;
}

//Takes in values of scaling along each axis and stores for fututre calculations.
void GameObject::Scale(float const  & x, float const  & y, float const  & z)
{
	scale_X = x;
	scale_Y = y;
	scale_Z = z;
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
	worldMatrix = DirectX::XMMatrixMultiply(worldMatrix, DirectX::XMMatrixScaling(scale_X, scale_Y, scale_Z));

	//Rotate
	DirectX::XMVECTOR rotationVector = DirectX::XMQuaternionRotationRollPitchYaw(pitch*toRadians, yaw*toRadians , roll*toRadians);
	worldMatrix = DirectX::XMMatrixMultiply(worldMatrix, DirectX::XMMatrixRotationQuaternion(rotationVector));	
	

	//Translate
	worldMatrix = DirectX::XMMatrixMultiply(worldMatrix, DirectX::XMMatrixTranslation(trans_X, trans_Y, trans_Z));
	return worldMatrix;
}

GameObject::~GameObject()
{
}
