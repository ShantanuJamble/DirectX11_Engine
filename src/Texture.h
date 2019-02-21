#pragma once

#include <string>
#include <d3d11.h>

class Texture
{
private:
	ID3D11ShaderResourceView* textureSRV;
public:
	Texture(std::wstring filepath,ID3D11Device* &device, ID3D11DeviceContext* &context);
	ID3D11ShaderResourceView*& GetTextureSRV() { return textureSRV; }

	~Texture();
};

