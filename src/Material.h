#pragma once

#include <d3d11.h>
#include "SimpleShader.h"
#include "Texture.h"
#include "Sampler.h"
class Material
{
private:
	SimpleVertexShader * vertexShader;
	SimplePixelShader * pixelShader;
	Texture * texture;
	Sampler * sampler;
	float shininess;
public:
	Material(SimpleVertexShader* & vertexShader, SimplePixelShader* & pixelShader, Texture*& texutre, Sampler *& sampDesc);
	SimpleVertexShader* & GetVertexShader();
	SimplePixelShader* & GetPixelShader();
	Texture*& GetTexture();
	Sampler*& GetSampler();
	void SetShinniness(const float & shine)
	{
		shininess = shine;
	}
	const float & GetShinniness()
	{
		return shininess;
	}

	void SetSamplerDesciption(D3D11_SAMPLER_DESC& sampDesc);
	~Material();
};

