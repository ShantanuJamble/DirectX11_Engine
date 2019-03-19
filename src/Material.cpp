#include "Material.h"



Material::Material(SimpleVertexShader *& vShader, SimplePixelShader *& pShader, Texture*& inalbedotexture,Texture*& inroughnesstexture, Sampler*& insample)
	:vertexShader(vShader),pixelShader(pShader),albedotexture(inalbedotexture),roughnesstexture(inroughnesstexture), sampler(insample),shininess(70.0f)
{

}

SimpleVertexShader *& Material::GetVertexShader()
{
	return vertexShader;
}

SimplePixelShader *& Material::GetPixelShader()
{
	return pixelShader;
}

Texture *& Material::GetalbedoTexture()
{
	return albedotexture;
}

Sampler *& Material::GetSampler()
{
	return sampler;
}

Material::~Material()
{
	if(vertexShader)
		delete vertexShader;
	if(pixelShader)
		delete pixelShader;
}
