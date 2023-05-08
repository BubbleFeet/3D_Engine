#include "GameApp.h"
#include "Graphics\Inc\Texture.h"

using namespace Graphics;

namespace
{
	const Math::Vector3 kCasterPosition(0.0f, 3.0f, 0.0f);

	const float kLightDistance = 5.0f;
	const Math::Vector3 kLightDirection(1.0f, -1.0f, 1.0f);
	const Math::Vector3 kLightPosition
	{
		kCasterPosition.x - (kLightDirection.x * kLightDistance),
		kCasterPosition.y - (kLightDirection.y * kLightDistance),
		kCasterPosition.z - (kLightDirection.z * kLightDistance)
	};

	const float kDepthMapSize = 1024;

	const Math::Matrix kMatNDCtoUV
	(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f
	);

	const float kTreeScaleX = 1.0f;
	const float kTreeScaleY = 1.0f;
	const int kTreeCount = 20;

	float RandomFloat()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	float RandomFloat(float min, float max)
	{
		return min + (RandomFloat() * (max - min));
	}
}

GameApp::GameApp()
	: mPointVertexBuffer(nullptr)
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
	mCamera.SetDirection(Math::Vector3(0.0f, -1.0f, 2.0f));
	mCamera.Setup(0.01f, 1000.0f, 60.0f * Math::kDegToRad, (float)width / (float)height);

	mLightCamera.SetPosition(kLightPosition);
	mLightCamera.SetDirection(kLightDirection);
	mLightCamera.Setup(1.0f, 500.0f, 60.0f * Math::kDegToRad, 1.0f);

	mDepthVertexShader.Initialize(L"../Data/Shaders/DepthMap.fx");
	const uint32_t kDepthMapSize = 1024;
	mDepthMap.Initialize(kDepthMapSize, kDepthMapSize);

	mConstantBuffer.Initialize();

	Mesh* circleM = new Mesh();
	MeshBuilder::CreateSphere((*circleM), 256, 256);
	std::string circleT = "earth.jpg";
	mModels.mMeshes.push_back(circleM);
	mModels.mTextures.push_back(circleT);

	MeshBuilder::CreateSkybox(mSkyMesh);
	mSkyMeshBuffer.Initialize(mSkyMesh.GetVertices(), mSkyMesh.GetNumVertices(), mSkyMesh.GetIndices(), mSkyMesh.GetNumIndices());
	mSkyTexture.Initialize(L"../Textures/space_cube.dds");
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

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC; // Instead of D3D11_USAGE_DEFAULT
	bd.ByteWidth = sizeof(Graphics::Vertex) * kTreeCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Instead of 0

	Graphics::Vertex vertex[kTreeCount];
	for (int i = 0; i < kTreeCount; ++i)
	{
		float x = RandomFloat(-5.0f, 5.0f);
		float z = RandomFloat(-5.0f, 5.0f);
		vertex[i].position.x = x;
		vertex[i].position.y = kTreeScaleY;
		vertex[i].position.z = z;
	}

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = &vertex;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mPointVertexBuffer);
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
	mDepthMap.Terminate();

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

	cb.lightAmbient = Math::Vector4::White();
	cb.lightDiffuse = Math::Vector4::White();
	cb.lightSpecular = Math::Vector4::White();

	cb.materialAmbient = Math::Vector4::White();
	cb.materialDiffuse = Math::Vector4::White();
	cb.materialSpecular = Math::Vector4::White();

	Graphics::GraphicsSystem::Get()->BeginRender();

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
	mConstantBuffer.BindVS(0);
	mConstantBuffer.BindPS(0);

	mVertexShader.Bind();
	mPixelShader.Bind();
	mTextures[0].BindPS(0);
	mModels.mMeshBuffers[0]->Render();

	dataSkybox.wvp = Math::Transpose(view * projection);
	mConstantBufferSkybox.Set(dataSkybox);
	mConstantBufferSkybox.BindVS(0);

	// set vertex buffer
	UINT stride = sizeof(Graphics::Vertex);
	UINT offset = 0;
	Graphics::GraphicsSystem::Get()->GetContext()->IASetVertexBuffers(0, 1, &mPointVertexBuffer, &stride, &offset);
	Graphics::GraphicsSystem::Get()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	Graphics::GraphicsSystem::Get()->GetContext()->Draw(kTreeCount, 0);


	Graphics::GraphicsSystem::Get()->EndRender();
}

void GameApp::GenerateDepthMap()
{
	mDepthMap.BeginRender();
	
	Math::Matrix matView = mLightCamera.GetViewMatrix();
	Math::Matrix matProj = mLightCamera.GetProjectionMatrix();

	Math::Matrix world = Math::Matrix::RotationY(0);

	mDepthVertexShader.Bind();
	mDepthPixelShader.Bind();

	// Draw Earth

	DepthCB data;
	data.wvp = (world * matView * matProj);
	data.displacementScale = 0.1f;
	mDepthBuffer.Set(data);
	mDepthBuffer.BindVS();

	mSampler.BindPS(0);
	mTextures[0].BindPS(0);
	mModels.mMeshBuffers[0]->Render();

	mDepthMap.EndRender();
}