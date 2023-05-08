#include "GameApp.h"

namespace
{
	struct SimpleVertex
	{
		Math::Vector3 position;
		Math::Vector4 color;
	};

	const SimpleVertex kVertices[] = 
	{
		{ Math::Vector3(-0.5f, 0.5f, 0.0f), Math::Vector4::Red() },
		{ Math::Vector3(0.5f, 0.5f, 0.0f), Math::Vector4::Blue() },
		{ Math::Vector3(-0.5f, -0.5f, 0.0f), Math::Vector4::Green() },
		{ Math::Vector3(0.5f, -0.5f, 0.0f), Math::Vector4::Magenta() },
	};

	const int32_t kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);

	const uint32_t kIndices[] =
	{
		0, 1, 2,
		1, 3, 2
	};
	
	const int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);
}

GameApp::GameApp()
	: mVertexBuffer(nullptr)
	, mIndexBuffer(nullptr)
	, mInputLayout(nullptr)
	, mVertexShader(nullptr)
	, mPixelShader(nullptr)
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

	mCamera.SetPosition(Math::Vector3(0.0f, 0.0f, -5.0f));

	mConstantBuffer.Initialize();

	//////////////////////////////////
	// Create and fill vertex buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * kVertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = kVertices;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mVertexBuffer);

	/////////////////////////////////
	// Create and fill index buffer
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(uint32_t) * kIndexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = kIndices;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mIndexBuffer);

	/////////////////////////////////////////
	// Compile and create the vertex shader
	// D3DCOMPILE_DEBUG flag improves the shader debugging experience
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	ID3DBlob* pShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
	(
		L"../Data/Shaders/DoSomething.fx",
		nullptr,
		nullptr,
		"VS", // Function name you are sending it
		"vs_5_0",
		shaderFlags,
		0,
		&pShaderBlob,
		&pErrorBlob
	);

	ASSERT(SUCCEEDED(hr), "Failed to compile shader. Error: %s", (char*)pErrorBlob->GetBufferPointer());
	SafeRelease(pErrorBlob);

	// Create vertex buffer
	Graphics::GraphicsSystem::Get()->GetDevice()->CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &mVertexShader);

	////////////////////////////////////
	//Define vertex description and create the input layout using the shader blob
	const D3D11_INPUT_ELEMENT_DESC kVertexLayout[] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	Graphics::GraphicsSystem::Get()->GetDevice()->CreateInputLayout
	(
		kVertexLayout,
		sizeof(kVertexLayout) / sizeof(kVertexLayout[0]),
		pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(),
		&mInputLayout
	);

	SafeRelease(pShaderBlob);
	///
	/////////////////////////////////////////
	// Compile and create the pixel shader
	hr = D3DCompileFromFile
	(
		L"../Data/Shaders/DoNothing.fx",
		nullptr,
		nullptr,
		"PS", // Function name you are sending it
		"ps_5_0",
		shaderFlags,
		0,
		&pShaderBlob,
		&pErrorBlob
	);

	ASSERT(SUCCEEDED(hr), "Failed to compile shader. Error: %s", (char*)pErrorBlob->GetBufferPointer());
	SafeRelease(pErrorBlob);

	// Create pixel buffer
	Graphics::GraphicsSystem::Get()->GetDevice()->CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &mPixelShader);
	SafeRelease(pShaderBlob);
}

void GameApp::OnTerminate()
{
	SafeRelease(mPixelShader);
	SafeRelease(mVertexShader);
	SafeRelease(mInputLayout);
	SafeRelease(mIndexBuffer);
	SafeRelease(mVertexBuffer);

	Graphics::GraphicsSystem::StaticTerminate();

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

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto inputSystem = Input::InputSystem::Get();

	inputSystem->Update();

	if (inputSystem->IsKeyPressed(Keys::ESCAPE))
	{
		PostQuitMessage(0);
	}

	if (inputSystem->IsKeyPressed(Keys::F1))
	{
		graphicsSystem->ToggleFullscreen();
	}

	mTimer.Update();

	const float kDeltaTime = mTimer.GetElapsedTime();
	const float kTotalTime = mTimer.GetTotalTime();

	const float kMoveSpeed = 1.0f;
	const float kTurnSpeed = 180.0f;
	if (inputSystem->IsKeyDown(Keys::W))
	{
		mCamera.Walk(kMoveSpeed * kDeltaTime);
	}
	else if (inputSystem->IsKeyDown(Keys::S))
	{
		mCamera.Walk(-kMoveSpeed * kDeltaTime);
	}
	if (inputSystem->IsKeyDown(Keys::D))
	{
		mCamera.Strafe(kMoveSpeed * kDeltaTime);
	}
	else if (inputSystem->IsKeyDown(Keys::A))
	{
		mCamera.Strafe(-kMoveSpeed * kDeltaTime);
	}
	mCamera.Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * kDeltaTime);
	mCamera.Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * kDeltaTime);

	static float dt = 0.0f;
	dt += 0.001f;
	
	CB cb;
	cb.w = Math::Transpose(Math::Matrix::RotationY(dt));
	cb.v = Math::Transpose(mCamera.GetViewMatrix());
	cb.p = Math::Transpose(mCamera.GetProjectionMatrix());
	mConstantBuffer.Set(cb);
	mConstantBuffer.BindVS();

	
	Graphics::GraphicsSystem::Get()->BeginRender();

	// Bind the input layout, vertex shader, and pixel shader
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();
	context->IASetInputLayout(mInputLayout);
	context->VSSetShader(mVertexShader, nullptr, 0);
	context->PSSetShader(mPixelShader, nullptr, 0);

	// Set vertex buffer
	uint32_t stride = sizeof(SimpleVertex);
	uint32_t offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	// Set Index Buffer
	context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set Primitive Topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Draw mesh
	context->DrawIndexed(kIndexCount, 0, 0);

	Graphics::GraphicsSystem::Get()->EndRender();
}



// For homework:
// Create MeshBuffer class
// maintains two interface pointers
//		i.e.
//				ID3D11Buffer* mVertexBuffer;
//				ID3D11Buffer* mIndexBuffer;
// - has initialize and terminate functions
// - has draw function
// ** the initalize function should take the following as params
//		- const Vertex* vertices
//		- uint32_t vertexCount
//		- const uint32_t* indices
//		- uint32_t indexCount
//
// Part B) Create Mesh Class
// - maintains two arrays
//		i.e.
//		- const Vertex* vertices
//		- uint32_t vertexCount
//		- const uint32_t* indices
//		- uint32_t indexCount
//
// Part C) Create MeshBuilder class
// - At a mininum, should support creating the following primitives
//	static void CreatePlane(Mesh& mesh, u32 rows, u32 columns, f32 scale);
//	static void CreateCube(Mesh& mesh, ...);
//	static void CreateSphere(Mesh& mesh, u32 slices, u32 rings);
