#include "GameApp.h"

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
	Graphics::SimpleDraw::Initialize(Graphics::GraphicsSystem::GraphicsSystem(), 99999);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	mCamera.SetPosition(Math::Vector3(5.0f, 5.0f, -5.0f));
	mCamera.SetLookAt(Math::Vector3::Zero());
}

void GameApp::OnTerminate()
{
	Input::InputSystem::StaticTerminate();

	Graphics::SimpleDraw::Terminate();
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

	// Update timer
	mTimer.Update();

	// Update input
	Input::InputSystem::Get()->Update();

	// Game logic
	if (GetAsyncKeyState(VK_F1))
	{
		Graphics::GraphicsSystem::Get()->ToggleFullscreen();
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	Input::InputSystem* inputSystem = Input::InputSystem::Get();
	const float kDeltaTime = mTimer.GetElapsedTime();
	const float kMoveSpeed = inputSystem->IsKeyDown(Keys::LSHIFT) ? 10.0f : 1.0f;
	const float kTurnSpeed = 90.0f;
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

	if (inputSystem->IsKeyPressed(Keys::ONE))
	{
		SpawnParticles();
	}
	else if (inputSystem->IsKeyPressed(Keys::TWO))
	{
		SpawnSticks();
	}
	else if (inputSystem->IsKeyPressed(Keys::THREE))
	{
		SpawnCloth();
	}

	Graphics::GraphicsSystem::Get()->BeginRender(Math::Vector4::Black());

	mPhysicsWorld.Update(kDeltaTime);
	mPhysicsWorld.DebugDraw();

	Graphics::SimpleDraw::AddTransform(Math::Matrix::Identity());
	Graphics::SimpleDraw::Render(mCamera);
	Graphics::GraphicsSystem::Get()->EndRender();
}

void GameApp::SpawnParticles()
{
	mPhysicsWorld.ClearAll();

	for (int i = 0; i < 100; ++i)
	{
		Physics::Particle* p = new Physics::Particle();
		p->SetPosition(Math::Vector3(0.0f, 0.0f, 0.0f));
		p->SetVelocity(Math::Vector3(
			Math::Random::GetF(-0.1f, 0.1f),
			Math::Random::GetF(0.0f, 0.25f),
			Math::Random::GetF(-0.1f, 0.1f)));
		p->SetRadius(0.05f);
		mPhysicsWorld.AddParticle(p);
	}
}

void GameApp::SpawnSticks()
{
	mPhysicsWorld.ClearAll();

	for (int i = 0; i < 50; ++i)
	{
		Physics::Particle* a = new Physics::Particle();
		a->SetPosition(Math::Vector3(0.0f, 0.0f, 0.0f));
		a->SetVelocity(Math::Vector3(
			Math::Random::GetF(-0.1f, 0.1f),
			Math::Random::GetF(0.0f, 0.25f),
			Math::Random::GetF(-0.1f, 0.1f)));
		a->SetRadius(0.05f);

		Physics::Particle* b = new Physics::Particle();
		b->SetPosition(Math::Vector3(0.0f, 0.0f, 0.0f));
		b->SetVelocity(Math::Vector3(
			Math::Random::GetF(-0.1f, 0.1f),
			Math::Random::GetF(0.0f, 0.25f),
			Math::Random::GetF(-0.1f, 0.1f)));
		b->SetRadius(0.05f);

		Physics::Spring* s = new Physics::Spring(a, b, 0.5f);

		mPhysicsWorld.AddParticle(a);
		mPhysicsWorld.AddParticle(b);
		mPhysicsWorld.AddConstraint(s);
	}
}

void GameApp::SpawnCloth()
{
	mPhysicsWorld.ClearAll();

	const int columns = 11;
	const int rows = 11;
	const float spacing = 0.5f;
	const float xOffset = columns * spacing * 0.5f;
	const float yOffset = 3.0f;

	std::vector<Physics::Particle*> particles;
	particles.reserve(columns * rows);

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			Math::Vector3 position(spacing * x - xOffset, yOffset, spacing * y);

			Physics::Particle* p = new Physics::Particle();
			p->SetPosition(position);
			p->SetRadius(0.05f);
			particles.push_back(p);
			mPhysicsWorld.AddParticle(p);

			if (y == 0)
			{
				Physics::Fixed* f = new Physics::Fixed(p, position);
				mPhysicsWorld.AddConstraint(f);
			}
		}
	}

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			if (x + 1 < columns)
			{
				mPhysicsWorld.AddConstraint(new Physics::Spring(
					particles[x + (y * columns)],
					particles[(x + 1) + (y * columns)],
					spacing));
			}
			if (y + 1 < rows)
			{
				mPhysicsWorld.AddConstraint(new Physics::Spring(
					particles[x + (y * columns)],
					particles[x + ((y + 1) * columns)],
					spacing));
			}
		}
	}
}