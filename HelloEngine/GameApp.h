#ifndef INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

// Description: Class for the game application.

#include <Core/Inc/Core.h>

class GameApp : public Core::Application
{
public:
	GameApp();
	virtual ~GameApp();

private:
	virtual void OnInitialize(uint32_t width, uint32_t height) override;
	virtual void OnTerminate() override;
	virtual void OnUpdate() override;

	Core::Window mWindow;
};

#endif // ifndef INCLUDED_GAMEAPP_H