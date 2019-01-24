#include "Mesh.h"

Mesh::~Mesh()
{
	vertexBuffer->Release();
	indexBuffer->Release();
}

void Mesh::SetVertices(Vertex * vertecies,int const &vertexCount)
{
	this->vertices = vertecies;
	this->vertexCount = vertexCount;
}

void Mesh::SetIndices(int * indices,int const &indexCount)
{
	this->indices = indices;
	this->indexCount = indexCount;
}

void Mesh::SetBufferDesc(UINT usage, UINT BindFlags)
{
	
	switch(BindFlags)
	{
		case D3D11_BIND_VERTEX_BUFFER:
			// Create the VERTEX BUFFER description -----------------------------------
			// - The description is created on the stack because we only need
			//    it to create the buffer.  The description is then useless.
			vbd.Usage = D3D11_USAGE_IMMUTABLE;
			vbd.ByteWidth = sizeof(Vertex) * vertexCount;       // 3 = number of vertices in the buffer
			vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
			vbd.CPUAccessFlags = 0;
			vbd.MiscFlags = 0;
			vbd.StructureByteStride = 0;

			// Create the proper struct to hold the initial vertex data
			// - This is how we put the initial data into the buffer
			initialVertexData.pSysMem = vertices;

		case D3D11_BIND_INDEX_BUFFER:
			// Create the INDEX BUFFER description ------------------------------------
			// - The description is created on the stack because we only need
			//    it to create the buffer.  The description is then useless.
			ibd.Usage = D3D11_USAGE_IMMUTABLE;
			ibd.ByteWidth = sizeof(int) * indexCount;         // 3 = number of indices in the buffer
			ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
			ibd.CPUAccessFlags = 0;
			ibd.MiscFlags = 0;
			ibd.StructureByteStride = 0;

			// Create the proper struct to hold the initial index data
			// - This is how we put the initial data into the buffer
			initialIndexData.pSysMem = indices;
	}
}

void Mesh::CreateBuffer(ID3D11Device*  &device)
{
	device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);//Creating VertexBuffer
	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);//Creating IndexBuffer
}


