#ifndef INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>
#include <Physics/Inc/Physics.h>

class GameApp : public Core::Application
{
public:
	GameApp();
	~GameApp();

private:
	void OnInitialize(uint32_t width, uint32_t height) override;
	void OnTerminate() override;
	void OnUpdate() override;

	void SpawnParticles();
	void SpawnSticks();
	void SpawnCloth();

	Core::Window mWindow;
	Core::Timer mTimer;

	Graphics::Camera mCamera;

	Physics::PhysicsWorld mPhysicsWorld;
};

#endif // #ifndef INCLUDED_GAMEAPP_H