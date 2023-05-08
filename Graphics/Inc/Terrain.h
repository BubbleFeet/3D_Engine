#pragma once
#ifndef INCLUDED_GRAPHICS_TERRAIN_H
#define INCLUDED_GRAPHICS_TERRAIN_H


#include "ConstantBuffer.h"
#include "Camera.h"
#include "Heightmap.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "Texture.h"
#include "VertexShader.h"


namespace Graphics {

	class Camera;

	class Terrain
	{
	public:
		Terrain();
		~Terrain();

		void Initialize(const char* filename, uint32_t width, uint32_t length, float maxHeight);
		void Terminate();

		void SetLayer(const wchar_t* filename, uint32_t layer, float minHeight, float maxHeight, float fequency);

		void Render(const Camera& camera);

		Heightmap& GetHeightMap() { return mHeightmap; }

private:
	NONCOPYABLE(Terrain)

	static const uint32_t kMaxTerrainLayers = 4;

	struct CBuffer
	{
		Math::Matrix WVP;
		Math::Vector4 layer[kMaxTerrainLayers];
	};

	TypedConstantBuffer<CBuffer> mCBuffer;

	VertexShader mVertexShader;
	PixelShader mPixelShader;

	Heightmap mHeightmap;
	Mesh mMesh;
	MeshBuffer mMeshBuffer;

	Texture mLayerTextures[kMaxTerrainLayers];
	Math::Vector3 mLayerInfo[kMaxTerrainLayers];

	Sampler mSampler;
};
}	// namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_TERRAIN_H