#ifndef INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

#include <Math\Inc\MathUtil.h>
#include <Core\Inc\Core.h>
#include <Graphics\Inc\Graphics.h>
#include <Input\Inc\Input.h>

class GameApp : public Core::Application
{
public:
	GameApp();
		
	virtual ~GameApp();

	struct Models
	{
		std::vector<Graphics::Mesh*> mMeshes;
		std::vector<std::string> mTextures;
		std::vector<Graphics::MeshBuffer*> mMeshBuffers;
	};

private:
	virtual void OnInitialize(uint32_t width, uint32_t height) override;
	virtual void OnTerminate() override;
	virtual void OnUpdate() override;
	 
	Core::Window mWindow;
	Core::Timer mTimer;

	struct CB
	{
		Math::Matrix world;
		Math::Matrix wvp;

		Math::Vector3 cameraPosition;
		float padding0;

		Math::Vector3 lightDirection;
		float padding1;

		Math::Vector4 lightAmbient;
		Math::Vector4 lightDiffuse;
		Math::Vector4 lightSpecular;

		Math::Vector4 materialAmbient;
		Math::Vector4 materialDiffuse;
		Math::Vector4 materialSpecular;
	};


	struct ConstantDataSkybox
	{
		Math::Matrix wvp;
	};

	Graphics::Camera mCamera;
	Graphics::TypedConstantBuffer<CB> mConstantBuffer;

	Graphics::PixelShader mPixelShader;
	Graphics::VertexShader mVertexShader;
	Graphics::Sampler mSampler;
	Graphics::MeshBuffer mMeshBuffer;

	Graphics::Texture* mTextures;

	Models mModels;

	// skybox
	Graphics::Mesh mSkyMesh;
	Graphics::MeshBuffer mSkyMeshBuffer;
	Graphics::PixelShader mSkyPixelShader;
	Graphics::VertexShader mSkyVertexShader;
	Graphics::Texture mSkyTexture;
	Graphics::TypedConstantBuffer<ConstantDataSkybox> mConstantBufferSkybox;
};

#endif //ifndef INCLUDED_GAMEAPP_H