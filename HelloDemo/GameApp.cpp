#include "GameApp.h"
#include "Graphics\Inc\Texture.h"

using namespace Graphics;

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize(uint32_t width, uint32_t height)
{
	mWindow.Initialize(GetInstance(), GetAppName(), width, height);
	HookWindow(mWindow.GetWindowHandle());

	mTimer.Initialize();
	
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	mCamera.SetPosition(Math::Vector3(0.0f, 0.0f, -2.0f));

	mConstantBuffer.Initialize();

	//start work
	/*Mesh* cubeM = new Mesh();
	MeshBuilder::buildCube((*cubeM), .1);
	std::string cubeT = "blood.png";
	mModels.mMeshes.push_back(cubeM);
	mModels.mTextures.push_back(cubeT);*/

	Mesh* circleM = new Mesh();
	MeshBuilder::CreateSphere((*circleM), 256, 256);
	std::string circleT = "Box.dds";
	mModels.mMeshes.push_back(circleM);
	mModels.mTextures.push_back(circleT);

	//Mesh* skyM = new Mesh();
	//MeshBuilder::buildSkyBox((*skyM), 100);
	//std::string skyT = "space.jpg";
	//mModels.mMeshes.push_back(skyM);
	//mModels.mTextures.push_back(skyT);

	MeshBuilder::CreateSkybox(mSkyMesh);
	mSkyMeshBuffer.Initialize(mSkyMesh.GetVertices(), mSkyMesh.GetNumVertices(), mSkyMesh.GetIndices(), mSkyMesh.GetNumIndices());
	mSkyTexture.Initialize(L"../Textures/Box.dds");
	mSkyPixelShader.Initialize(L"../Data/Shaders/Skybox.fx");
	mSkyVertexShader.Initialize(L"../Data/Shaders/Skybox.fx");
	mConstantBufferSkybox.Initialize();

	//crunch numbers
	for (size_t i = 0; i < mModels.mMeshes.size(); i++)
	{
		mModels.mMeshBuffers.push_back(new MeshBuffer());
		mModels.mMeshBuffers[i]->Initialize(mModels.mMeshes[i]->GetVertices(),
										   mModels.mMeshes[i]->GetNumVertices(),
										   mModels.mMeshes[i]->GetIndices(),
										   mModels.mMeshes[i]->GetNumIndices());
	}

	mTextures = new Texture[mModels.mTextures.size()];
	for (size_t i = 0; i < mModels.mTextures.size(); ++i)
	{
		wchar_t fileName[1024];
		mbstowcs_s(nullptr, fileName, mModels.mTextures[i].c_str(), 1024);
		std::wstring finalFileName;

		finalFileName = L"../Textures/";
		finalFileName += fileName;
		mTextures[i].Initialize(finalFileName.c_str());
	}
	//end work

	mVertexShader.Initialize(L"../Data/Shaders/Lighting.fx");
	mPixelShader.Initialize(L"../Data/Shaders/Lighting.fx");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameApp::OnTerminate()
{
	for (size_t i = 0; i < mModels.mMeshes.size(); i++)
	{
		//SafeDelete(mModels.mMeshes[i]);
		mModels.mMeshes[i]->Terminate();
		mTextures[i].Terminate();
		mModels.mMeshBuffers[i]->Terminate();
	}

	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mSkyMesh.Terminate();
	mSkyMeshBuffer.Terminate();
	mSkyPixelShader.Terminate();
	mSkyTexture.Terminate();
	mSkyVertexShader.Terminate();
	mConstantBufferSkybox.Terminate();

	Graphics::GraphicsSystem::StaticTerminate();
	Input::InputSystem::StaticTerminate();

	UnhookWindow();
	mWindow.Terminate();
}

void GameApp::OnUpdate()
{
	if (mWindow.ProcessMessage())
	{
		Kill();
		return;
	}

	Graphics::GraphicsSystem* GraphicsSystem = Graphics::GraphicsSystem::Get();
	Input::InputSystem* InputSystem = Input::InputSystem::Get();
	InputSystem->Update();
	
	if (InputSystem->IsKeyPressed(Keys::ESCAPE))
	{
		PostQuitMessage(0);
	}
	if (InputSystem->IsKeyPressed(Keys::F1))
	{
		GraphicsSystem->ToggleFullscreen();
	}

	mTimer.Update();
	const float kDeltaTime = mTimer.GetElapsedTime();
	const float kTotalTime = mTimer.GetTotalTime();
	const float kMoveSpeed = 10.0f;
	const float kTurnSpeed = 250.0f;

	if (InputSystem->IsKeyDown(Keys::W))
	{
		mCamera.Walk(kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::A))
	{
		mCamera.Strafe(-kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::S))
	{
		mCamera.Walk(-kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::D))
	{
		mCamera.Strafe(kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::E))
	{
		mCamera.Rise(kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::Q))
	{
		mCamera.Rise(-kMoveSpeed * kDeltaTime);
	}

	mCamera.Yaw(InputSystem->GetMouseMoveX() * kTurnSpeed * kDeltaTime);
	mCamera.Pitch(InputSystem->GetMouseMoveY() * kTurnSpeed *kDeltaTime);

	Math::Matrix world = Math::Matrix::RotationY(0);
	Math::Matrix view = mCamera.GetViewMatrix();
	Math::Matrix projection = mCamera.GetProjectionMatrix();
	Math::Matrix WVP = world * view * projection;

	CB cb;
	cb.world = Math::Matrix::Transpose(world);
	cb.wvp = Math::Matrix::Transpose(WVP);
	cb.cameraPosition = mCamera.GetPosition();
	cb.lightDirection = Math::Vector3(1.0f, -1.0f, 1.0f);

	cb.lightAmbient = Math::Vector4::Blue();
	cb.lightDiffuse = Math::Vector4::Red();
	cb.lightSpecular = Math::Vector4::Black();

	cb.materialAmbient = Math::Vector4::White();
	cb.materialDiffuse = Math::Vector4::White();
	cb.materialSpecular = Math::Vector4::White();

	mRenderTarget.BeginRender();

	Math::Matrix matWorldSkybox = Math::Matrix::Translation(mCamera.GetPosition());

	ConstantDataSkybox dataSkybox;
	dataSkybox.wvp = Math::Transpose(matWorldSkybox * view * projection);
	mConstantBufferSkybox.Set(dataSkybox);
	mConstantBufferSkybox.BindVS(0);
	mSkyTexture.BindPS(0);
	mSampler.BindPS(0);
	mSkyVertexShader.Bind();
	mSkyPixelShader.Bind();

	Graphics::GraphicsSystem::Get()->EnableDepthTesting(false);
	mSkyMeshBuffer.Render();
	Graphics::GraphicsSystem::Get()->EnableDepthTesting(true);

	mConstantBuffer.Set(cb);
	mConstantBuffer.BindVS();
	mConstantBuffer.BindPS();
	//mVertexShader.Bind();
	//mPixelShader.Bind();

	dataSkybox.wvp = Math::Transpose(view * projection);
	mConstantBufferSkybox.Set(dataSkybox);
	mConstantBufferSkybox.BindVS(0);


	for (uint32_t i = 0; i < mModels.mTextures.size(); i++)
	{
		mTextures[i].BindPS(0);
		mModels.mMeshBuffers[i]->Render();
	}

	mRenderTarget.EndRender();

	Graphics::GraphicsSystem::Get()->BeginRender();

	dataSkybox.wvp = Math::Transpose(matWorldSkybox * view * projection);
	mConstantBufferSkybox.Set(dataSkybox);
	mConstantBufferSkybox.BindVS(0);
	mSkyTexture.BindPS(0);
	mSampler.BindPS(0);
	mSkyVertexShader.Bind();
	mSkyPixelShader.Bind();

	Graphics::GraphicsSystem::Get()->EnableDepthTesting(false);
	mSkyMeshBuffer.Render();
	Graphics::GraphicsSystem::Get()->EnableDepthTesting(true);

	mConstantBuffer.Set(cb);
	mConstantBuffer.BindVS();
	mConstantBuffer.BindPS();
	//mVertexShader.Bind();
	//mPixelShader.Bind();

	dataSkybox.wvp = Math::Transpose(view * projection);
	mConstantBufferSkybox.Set(dataSkybox);
	mConstantBufferSkybox.BindVS(0);


	for (uint32_t i = 0; i < mModels.mTextures.size(); i++)
	{
		mTextures[i].BindPS(0);
		mModels.mMeshBuffers[i]->Render();
	}

	Graphics::GraphicsSystem::Get()->EndRender();
}