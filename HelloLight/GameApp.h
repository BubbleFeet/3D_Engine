#ifndef INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

// Description: Class for the game application

#include <Core/Inc/Core.h>
#include <Graphics\Inc\Graphics.h>
#include <Input\Inc\Input.h>
#include <Math\Inc\MathHeaders.h>

class GameApp : public Core::Application
{
public:
	GameApp();
	virtual ~GameApp();

private:
	virtual void OnInitialize(uint32_t width, uint32_t height) override;
	virtual void OnTerminate() override;
	virtual void OnUpdate() override;

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

	Core::Window mWindow;

	Graphics::Camera mCamera;
	Graphics::TypedConstantBuffer<CB> mConstantBuffer;

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;

	//Encapsulate these three in pixel shader or vertex shader class
	ID3D11InputLayout* mInputLayout;
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
};

#endif // #ifndef INCLUDED_GAMEAPP_H
