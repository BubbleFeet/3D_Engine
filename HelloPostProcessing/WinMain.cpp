#include "GameApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdline, int nCmdShow)
{
	GameApp myApp;
	myApp.Initialize(hInstance, "Hello Post Processing!", 1024, 720);

	while (myApp.IsRunning())
	{
		myApp.Update();
	}

	myApp.Terminate();
	return 0;
}
