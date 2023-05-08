#include "Precompiled.h"
#include "ScreenMeshBuffer.h"
#include "Vertex.h"
#include "GraphicsSystem.h"

using namespace Graphics;

ScreenMeshBuffer::ScreenMeshBuffer()
	: mVertexBuffer(nullptr)
{
}

ScreenMeshBuffer::~ScreenMeshBuffer()
{
	ASSERT(mVertexBuffer == nullptr, "[ScreenMeshBuffer] Vertex buffer not released.");
}

void ScreenMeshBuffer::Initialize()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	Vertex vertices[4];
	vertices[0].position = Math::Vector3(-1.0f, -1.0f, 0.0f); // bottom left
	vertices[1].position = Math::Vector3(-1.0f,  1.0f, 0.0f); // top left
	vertices[2].position = Math::Vector3( 1.0f,  1.0f, 0.0f); // top right
	vertices[3].position = Math::Vector3( 1.0f, -1.0f, 0.0f); // bottom right


	// FOR THE TEXCOORD BELOW : YOU MUST FIGURE OUT WHAT TO DO WITH TEXCOORD IN VERTEX.H
	vertices[0].texcoord = Math::Vector2(0.0f, 1.0f);
	vertices[1].texcoord = Math::Vector2(0.0f, 0.0f);
	vertices[2].texcoord = Math::Vector2(1.0f, 1.0f);
	vertices[3].texcoord = Math::Vector2(1.0f, 0.0f);

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertices;

	ID3D11Device* device = Graphics::GraphicsSystem::Get()->GetDevice();
	device->CreateBuffer(&bd, &initData, &mVertexBuffer);
}

void ScreenMeshBuffer::Terminate()
{
	SafeRelease(mVertexBuffer);
}

void ScreenMeshBuffer::Render()
{
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();

	//set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//set primitieve topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//draw mesh
	context->Draw(4, 0);
}
