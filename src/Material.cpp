#include "Material.h"



Material::Material(SimpleVertexShader *& vShader, SimplePixelShader *& pShader)
	:vertexShader(vShader),pixelShader(pShader),shininess(70.0f)
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

Material::~Material()
{
	delete vertexShader;
	delete pixelShader;
}
