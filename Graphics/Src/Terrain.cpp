#include "Precompiled.h"
#include "GraphicsSystem.h"
#include "Terrain.h"
#include "Camera.h"
#include "MeshBuilder.h"

using namespace Graphics;

Terrain::Terrain() {}
Terrain::~Terrain() {}

void Terrain::Initialize(const char* filename, uint32_t width, uint32_t length, float maxHeight)
{
	mCBuffer.Initialize();

	mVertexShader.Initialize(L"../Data/Shaders/Terrain.fx");
	mPixelShader.Initialize(L"../Data/Shaders/Terrain.fx");

	mHeightmap.GenerateFromRAW(filename, width, length);

	MeshBuilder::CreateTerrain(mMesh, mHeightmap, width, length, maxHeight);
	mMeshBuffer.Initialize(mMesh.GetVertices(), mMesh.GetNumVertices(), mMesh.GetIndices(), mMesh.GetNumIndices());

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
}

void Terrain::Terminate()
{
	mCBuffer.Terminate();

	mVertexShader.Terminate();
	mPixelShader.Terminate();

	mHeightmap.Clear();
	mMesh.Terminate();
	mMeshBuffer.Terminate();

	for (uint32_t i = 0; i < kMaxTerrainLayers; ++i)
	{
		mLayerTextures[i].Terminate();
	}

	mSampler.Terminate();
}

void Terrain::SetLayer(const wchar_t* filename, uint32_t layer, float minHeight, float maxHeight, float frequency)
{
	ASSERT(layer < kMaxTerrainLayers, "[Terrain] Only support %d layers.", kMaxTerrainLayers);
	ASSERT(minHeight <= maxHeight && frequency > 0.0f, "[Terrain] Invalid layer params.");

	// C-string to wide character string
	// TODO: Move this to a helper function somewhere
	// e.g.		Utils::CStringToWString(...)
	//wchar_t buffer[1024];
	//mbstowcs(buffer, filename, 1024);

	mLayerTextures[layer].Initialize(filename);
	mLayerInfo[layer].x = minHeight;
	mLayerInfo[layer].y = maxHeight;
	mLayerInfo[layer].z = frequency;

}

void Terrain::Render(const Camera& camera)
{
	Math::Matrix matView = camera.GetViewMatrix();
	Math::Matrix matProj = camera.GetProjectionMatrix();

	CBuffer cb;
	cb.WVP = Math::Transpose(matView * matProj);
	for (uint32_t i = 0; i < kMaxTerrainLayers; ++i)
	{
		cb.layer[i] = Math::Vector4(mLayerInfo[i].x, mLayerInfo[i].y, mLayerInfo[i].z, 0.0f);
		mLayerTextures[i].BindPS(i);
	}

	mCBuffer.Set(cb);
	mCBuffer.BindVS(0);
	mCBuffer.BindPS(0);

	mSampler.BindPS(0);

	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}