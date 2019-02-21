#include "Material.h"



Material::Material(SimpleVertexShader *& vShader, SimplePixelShader *& pShader, Texture*& intexture, Sampler*& insample)
	:vertexShader(vShader),pixelShader(pShader),texture(intexture),sampler(insample),shininess(70.0f)
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

Texture *& Material::GetTexture()
{
	return texture;
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
