#include "Texture.h"
// DirectX Tool Kit headers
#include "WICTextureLoader.h" // WIC = Windows Imaging Component


Texture::Texture(std::wstring filepath, ID3D11Device *& device, ID3D11DeviceContext *& context)
{
	// Load some textures
	DirectX::CreateWICTextureFromFile(
		device,					// The Direct3D device for resource creation
		context,				// Rendering context (this will auto-generate mip maps!!!)
		filepath.c_str(),				// Path to the file ("L" means wide characters)
		0,						// Texture ref?  No thanks!  (0 means we don't want an extra ref)
		&textureSRV);				// Actual SRV for use with shaders
}

Texture::~Texture()
{
	textureSRV->Release();
}
