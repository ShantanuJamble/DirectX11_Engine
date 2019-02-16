#pragma once

#include <d3d11.h>
#include "SimpleShader.h"
class Material
{
private:
	SimpleVertexShader * vertexShader;
	SimplePixelShader * pixelShader;
	float shininess;
public:
	Material(SimpleVertexShader* & vertexShader, SimplePixelShader* & pixelShader);
	SimpleVertexShader* & GetVertexShader();
	SimplePixelShader* & GetPixelShader();

	void SetShinniness(const float & shine)
	{
		shininess = shine;
	}
	const float & GetShinniness()
	{
		return shininess;
	}
	~Material();
};

