#include "Sampler.h"

Sampler::Sampler(D3D11_SAMPLER_DESC & sampDesc, ID3D11Device *& device, ID3D11DeviceContext *& context)
{
	device->CreateSamplerState(&sampDesc, &samplerState);
}

ID3D11SamplerState *& Sampler::GetSamplerState()
{
	return samplerState;
}

Sampler::~Sampler()
{
	samplerState->Release();
}
