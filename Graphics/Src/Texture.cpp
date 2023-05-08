#include "Precompiled.h"

#include "Texture.h"

#include "GraphicsSystem.h"
#include <DirectXTK/Inc/DDSTextureLoader.h>
#include <DirectXTK/Inc/WICTextureLoader.h>

using namespace Graphics;

Texture::Texture()
	: mShaderResourceView(nullptr)
{
}

Texture::~Texture()
{
	ASSERT(mShaderResourceView == nullptr, "[Texture] Texture not released!");
}

void Texture::Initialize(const wchar_t* filename)
{
	ID3D11Device* device = GraphicsSystem::Get()->GetDevice();
	ID3D11DeviceContext* context = GraphicsSystem::Get()->GetContext();

	if (wcsstr(filename, L".dds") != nullptr)
	{
		DirectX::CreateDDSTextureFromFile(device, filename, nullptr, &mShaderResourceView);
	}

	else
	{
		DirectX::CreateWICTextureFromFile(device, filename, nullptr, &mShaderResourceView);
	}
}

void Texture::Initialize(const void * data, uint32_t width, uint32_t height)
{
	auto device = Graphics::GraphicsSystem::Get()->GetDevice();
	
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 0;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;

	HRESULT hr;

	hr = device->CreateTexture2D(&desc, &initData, &texture);
	ASSERT(SUCCEEDED(hr), "[Graphics::Texture] Failed to create Texture.");
	hr = device->CreateShaderResourceView(texture, nullptr, &mShaderResourceView);
	ASSERT(SUCCEEDED(hr), "[Graphics::Texture] Failed to create Shader Resource View.");
	SafeRelease(texture);
}

void Texture::Terminate()
{
	SafeRelease(mShaderResourceView);
}

void Texture::BindPS(uint32_t slot)
{
	GraphicsSystem::Get()->GetContext()->PSSetShaderResources(slot, 1, &mShaderResourceView);
}

void Texture::BindVS(uint32_t slot)
{
	GraphicsSystem::Get()->GetContext()->VSSetShaderResources(slot, 1, &mShaderResourceView);
}
