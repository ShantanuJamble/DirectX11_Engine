#pragma once
#include <DirectXMath.h>
#include <vector>

#include "DXCore.h"
#include "GameObject.h"
#include "Mesh.h"
#include "SimpleShader.h"
#include "Camera.h"
#include "Material.h"
#include "Lights.h"
#include "Texture.h"
#include "Sampler.h"
class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	//void CreateMatrices();
	void CreateBasicGeometry();

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	//Keeping track of Meshes and GameObjects
	std::vector<Mesh *> meshes;
	std::vector<GameObject *> gameObjects;
	
	//Rotation factors
	float curAngle = 0.0f;
	
	//Camera
	Camera camera;
	
	//Material
	Material * material;
	std::vector<Texture *> textures;
	Sampler * sampler;
	//Lighting
	DirectionalLight directionalLight;
	PointLight pointLight;

	//Toggling between objects
	int currentObj;
};

