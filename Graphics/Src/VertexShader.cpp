#include "Precompiled.h"
#include "VertexShader.h"
#include "GraphicsSystem.h"

using namespace Graphics;


void VertexShader::Bind()
{
	auto context = Graphics::GraphicsSystem::Get()->GetContext();

	context->IASetInputLayout(mInputLayout);
	context->VSSetShader(mVertexShader, nullptr, 0);
}

void VertexShader::Initialize(const wchar_t* fileName, const char* entry)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	ID3DBlob* pShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
		(
			fileName,
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",
			shaderFlags,
			0,
			&pShaderBlob,
			&pErrorBlob
			);

	ASSERT(SUCCEEDED(hr), "Failed to compile mVertexShader. Error %s", (char*)pErrorBlob->GetBufferPointer());
	SafeRelease(pErrorBlob);

	hr = Graphics::GraphicsSystem::Get()->GetDevice()->CreateVertexShader
		(
			pShaderBlob->GetBufferPointer(),
			pShaderBlob->GetBufferSize(),
			nullptr,
			&mVertexShader
			);
	
	//create the input layout
	const D3D11_INPUT_ELEMENT_DESC kVertexLayout[] =
	{
		{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",			0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDWEIGHTS",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = Graphics::GraphicsSystem::Get()->GetDevice()->CreateInputLayout
		(
			kVertexLayout,
			sizeof(kVertexLayout) / sizeof(kVertexLayout[0]),
			pShaderBlob->GetBufferPointer(),
			pShaderBlob->GetBufferSize(),
			&mInputLayout
			);

	SafeRelease(pShaderBlob);

}

void VertexShader::Terminate()
{
	SafeRelease(mVertexShader);
	SafeRelease(mInputLayout);
}

