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
	Texture * albedotexture;
	Texture * roughnesstexture;
	Sampler * sampler;
	float shininess;
public:
	Material(SimpleVertexShader* & vertexShader, SimplePixelShader* & pixelShader, Texture*& albedotexutre, Texture*& roughnesstexutre, Sampler *& sampDesc);
	SimpleVertexShader* & GetVertexShader();
	SimplePixelShader* & GetPixelShader();
	Texture*& GetalbedoTexture();
	Texture*& GetroughenssTexture() { return roughnesstexture; }
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

