#pragma once

#include <d3d11.h>
#include "SimpleShader.h"
class Material
{
private:
	SimpleVertexShader * vertexShader;
	SimplePixelShader * pixelShader;
public:
	Material(SimpleVertexShader* & vertexShader, SimplePixelShader* & pixelShader);
	SimpleVertexShader* & GetVertexShader();
	SimplePixelShader* & GetPixelShader();
	~Material();
};

