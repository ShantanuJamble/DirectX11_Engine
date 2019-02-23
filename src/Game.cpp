#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Input.h"
#include "Material.h"
#include "FileHandler.h"
#include "Texture.h"


// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		// The application's handle
		"DirectX Game",	   	// Text for the window's title bar
		1280,			// Width of the window's client area
		720,			// Height of the window's client area
		true),			// Show extra stats (fps) in title bar?
		camera(XMFLOAT3(0, 0, 1), XMFLOAT3(0, 0, -5), 5.0f),
		material(nullptr)
{

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.\n");
#endif

}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	// Clean up our other resources
	delete material;
	
	delete sampler;
	for (auto& mesh : meshes) delete mesh;
	for (auto& objects : gameObjects) delete objects;
	for (auto& texture : textures) delete texture;
	
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	

	//Updating lighting
	directionalLight = {
				XMFLOAT4(0.1f , 0.1f, 0.1f ,1.0f),
				XMFLOAT4(1,1,1,1),
				XMFLOAT3(-1,0,0)

			};

	pointLight = {
				XMFLOAT4(1,1,1,1),
				XMFLOAT3(0,3,0)
	};

	//Creating multiple textures
	Texture * sampleTextureStone= new Texture(L"Textures/stone.png", device, context);
	Texture * sampleTextureWall= new Texture(L"Textures/wall.png", device, context);
	textures.push_back(sampleTextureStone);
	textures.push_back(sampleTextureWall);
	D3D11_SAMPLER_DESC sampDesc = {}; // " = {}" fills the whole struct with zeros!
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;			// This will ensure mip maps are used!
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR ;		//D3D11_FILTER_ANISOTROPIC;	// Tri-linear filtering
	//sampDesc.MaxAnisotropy = 16; // Must  be set for anisotropic filtering
	
	//TODO::Here we will ask material class to create Sampler with the above desc.
	sampler = new Sampler(sampDesc, device, context);
	LoadShaders();
	CreateBasicGeometry();
	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	SimpleVertexShader * tvertexShader = new SimpleVertexShader(device, context);
	tvertexShader->LoadShaderFile(L"VertexShader.cso");

	SimplePixelShader * tpixelShader = new SimplePixelShader(device, context);
	tpixelShader->LoadShaderFile(L"PixelShader.cso");

	material = new Material(tvertexShader, tpixelShader,textures[0],sampler);
	
}





// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	float incr = 0.0f;
	int index = 0;
	
	std::string pathToAssets = FileHandler::getCWD();
	pathToAssets.append("\\..\\..\\..\\assets\\models\\");
	std::string pathToHelix = pathToAssets.append("helix.obj");
	Mesh * cubeMesh = new Mesh(pathToHelix.c_str(),device);
	meshes.push_back(cubeMesh);
	
	GameObject * cubeObject= new GameObject(cubeMesh,material, XMFLOAT3(0,0,1), XMFLOAT3(0,0,0),5.0f);
	gameObjects.push_back(cubeObject);


	
}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	camera.ChangeAspectRatio(width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (Input::IsKeyPressed(VK_ESCAPE))
		Quit();
	
	camera.CheckKeyPress(deltaTime);
	curAngle += 0.05f;
	if (curAngle >= 360)
	{
		curAngle -= 360;
	}
	for (int index = 0;index<gameObjects.size();index++)
	{
		gameObjects[index]->Rotate(0, curAngle, 0);
		gameObjects[index]->Translate(sin(totalTime) * 2, 0, 0);

	}
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	DirectX::XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(camera.GetViewMatrix()));
	DirectX::XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(camera.GetProjectionMatrix()));
	Material *objectMaterial;
	SimpleVertexShader* objectVertexShader;
	SimplePixelShader* objectPixelShader;
	Texture* objectTexture;
	Sampler* objectSampler;
	for(auto gameObject:gameObjects)
	{
		objectMaterial = gameObject->GetMaterial();
		objectTexture = objectMaterial->GetTexture();
		objectSampler = objectMaterial->GetSampler();
		objectVertexShader = objectMaterial->GetVertexShader();
		objectPixelShader = objectMaterial->GetPixelShader();
		DirectX::XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(gameObject->GetWorldMatrix()));
		
		objectVertexShader->SetMatrix4x4("world", worldMatrix);
		objectVertexShader->SetMatrix4x4("view", viewMatrix);
		objectVertexShader->SetMatrix4x4("projection", projectionMatrix);
		
		objectPixelShader->SetData("directionalLight", &directionalLight, sizeof(DirectionalLight));
		objectPixelShader->SetFloat("shininess", objectMaterial->GetShinniness());
		objectPixelShader->SetFloat3("CameraPosition", XMFLOAT3(0, 0, -5));
		objectPixelShader->SetFloat("shinniness", objectMaterial->GetShinniness());
		objectPixelShader->SetData("pointLight", &pointLight, sizeof(PointLight));
		// Once you've set all of the data you care to change for
		// the next draw call, you need to actually send it to the GPU
		//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
		objectVertexShader->CopyAllBufferData();
		objectPixelShader->CopyAllBufferData();

		// Set texture-related resources
		objectPixelShader->SetSamplerState("BasicSampler", objectSampler->GetSamplerState());
		objectPixelShader->SetShaderResourceView("DiffuseTexture",objectTexture->GetTextureSRV());
		//pixelShader->SetShaderResourceView("SpecularMap", specSRV);

		// Set the vertex and pixel shaders to use for the next Draw() command
		//  - These don't technically need to be set every frame...YET
		//  - Once you start applying different shaders to different objects,
		//    you'll need to swap the current shaders before each draw
		objectVertexShader->SetShader();
		objectPixelShader->SetShader();

		// Set buffers in the input assembler
		//  - Do this ONCE PER OBJECT you're drawing, since each object might
		//    have different geometry.
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		ID3D11Buffer * vertexBufferTmp;
		Mesh *tmpMesh = gameObject->GetMesh();
		
		vertexBufferTmp = tmpMesh->GetVertexBuffer();
		context->IASetVertexBuffers(0, 1, &vertexBufferTmp, &stride, &offset);
		context->IASetIndexBuffer(tmpMesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);



		// Finally do the actual drawing
		//  - Do this ONCE PER OBJECT you intend to draw
		//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
		//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
		//     vertices in the currently set VERTEX BUFFER
		//UINT indexCount = 3;

		context->DrawIndexed(
			tmpMesh->GetIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices
	
	}

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here..
	if (buttonState & 0x0001)
	{
		long x_diff = x - prevMousePos.x;
		long y_diff = y - prevMousePos.y;
		camera.MouseControl(x_diff, y_diff);
	}
	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion