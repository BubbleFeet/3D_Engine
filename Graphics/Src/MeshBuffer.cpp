#include "Precompiled.h"
#include "MeshBuffer.h"

#include "GraphicsSystem.h"

using namespace Graphics;

MeshBuffer::MeshBuffer()
	: mVertexBuffer(nullptr)
	, mIndexBuffer(nullptr)
	, mVertexCount(0)
	, mIndexCount(0)
{
}

MeshBuffer::~MeshBuffer()
{
	ASSERT(mVertexBuffer == nullptr, "[MeshBuffer] Vertex buffer not released!");
	ASSERT(mIndexBuffer == nullptr, "[MeshBuffer] Index buffer not released!");
}

void MeshBuffer::Initialize(const Mesh& mesh)
{
	Initialize(mesh.GetVertices(), mesh.GetNumVertices(), mesh.GetIndices(), mesh.GetNumIndices());
}

void MeshBuffer::Initialize(const void* vertexData, uint32_t numVertices, const uint32_t* indexData, uint32_t numIndices, bool dynamic)
{
	mVertexCount = numVertices;
	mIndexCount = numIndices;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * mVertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertexData;

	ID3D11Device* device = Graphics::GraphicsSystem::Get()->GetDevice();
	device->CreateBuffer(&bd, &initData, &mVertexBuffer);

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(uint32_t) * mIndexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indexData;

	device->CreateBuffer(&bd, &initData, &mIndexBuffer);
}

void MeshBuffer::Terminate()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mIndexBuffer);
}

void MeshBuffer::Render()
{
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();

	// Set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	// Set primitive topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Check if we are using index buffer
	if (mIndexBuffer != nullptr)
	{
		// Set index buffer
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Draw indexed mesh
		context->DrawIndexed(mIndexCount, 0, 0);
	}
	else
	{
		// Draw mesh
		context->Draw(mVertexCount, 0);
	}
}