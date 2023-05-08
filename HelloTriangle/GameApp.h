#ifndef INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

// Description: Class for the game application

#include <Core\Inc\Core.h>
#include <Graphics\Inc\Graphics.h>
#include <Input\Inc\Input.h>
#include <Math\Inc\MathUtil.h>

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
		Math::Matrix w;
		Math::Matrix v;
		Math::Matrix p;
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
