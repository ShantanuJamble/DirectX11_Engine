#pragma once
#include <d3d11.h>

class Sampler
{
private:
	ID3D11SamplerState* samplerState;
public:
	Sampler(D3D11_SAMPLER_DESC& sampDesc, ID3D11Device* &device, ID3D11DeviceContext* &context);
	ID3D11SamplerState*& GetSamplerState();
	~Sampler();
};

