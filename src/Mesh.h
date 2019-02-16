#pragma once
#include <d3d11.h>
#include "Vertex.h"
#include <vector>

class Mesh {

protected:
	Vertex * vertices;
	int vertexCount;
	int *indices;
	int indexCount;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	D3D11_BUFFER_DESC vbd;
	D3D11_BUFFER_DESC ibd;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	D3D11_SUBRESOURCE_DATA initialIndexData;
public:
	Mesh() {};
	Mesh(const char * filePath, ID3D11Device* &device);
	~Mesh();
	void SetVertices(Vertex * vertecies,int const &vertexCount);
	void SetIndices(int * indices,int const &indexCount);
	ID3D11Buffer* GetVertexBuffer() { return vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return indexBuffer; }
	int GetIndexCount() { return indexCount; }
	int GetVertexCount() { return vertexCount; }
	void SetBufferDesc(UINT usage, UINT BindFlags);
	void CreateBuffer(ID3D11Device* &device);
};