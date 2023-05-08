#include "Precompiled.h"
#include "GeometryShader.h"
#include "GraphicsSystem.h"

using namespace Graphics;

void GeometryShader::Bind()
{
	auto context = Graphics::GraphicsSystem::Get()->GetContext();

	context->GSSetShader(mGeometryShader, nullptr, 0);
}

void GeometryShader::Initialize(const wchar_t* fileName)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
	(
		fileName,
		nullptr,
		nullptr,
		"GS",
		"gs_5_0",
		shaderFlags,
		0,
		&shaderBlob,
		&errorBlob
	);
	ASSERT(SUCCEEDED(hr), "Failed to compile shader, Error %s", (char*)errorBlob->GetBufferPointer());
	SafeRelease(errorBlob);

	hr = Graphics::GraphicsSystem::Get()->GetDevice()->CreateGeometryShader
	(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mGeometryShader
	);

	SafeRelease(shaderBlob);
}

void GeometryShader::Terminate()
{
	SafeRelease(mGeometryShader);
}