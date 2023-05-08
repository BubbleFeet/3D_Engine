#ifndef INCLUDED_CORE_APPLICATION_H
#define INCLUDED_CORE_APPLICATION_H

// Description: Application base class.

#include "NonCopyable.h"

namespace Core {

class Application
{	
	NONCOPYABLE(Application);

public:
	Application();
	virtual ~Application();

	void Initialize(HINSTANCE instance, LPCSTR appName, uint32_t width, uint32_t height);
	void Terminate();

	void HookWindow(HWND hWnd);
	void UnhookWindow();

	void Update();

	void Kill()						{ mRunning = false; }

	HINSTANCE GetInstance() const	{ return mInstance; }
	HWND GetWindow() const			{ return mWindow; }
	const char* GetAppName() const	{ return mAppName.c_str(); }
	bool IsRunning() const			{ return mRunning; }

private:
	virtual void OnInitialize(uint32_t width, uint32_t height) = 0;
	virtual void OnTerminate() = 0;
	virtual void OnUpdate() = 0;

private:
	HINSTANCE mInstance;
	HWND mWindow;

	std::string mAppName;

	bool mRunning;
};

}  // namespace Core

#endif // #ifndef INCLUDED_CORE_APPLICATION_H


//// Const Correctness
//// - Bitwise constness
//// - Conceptual constness
//
//
//class Container
//{
//public:
//	void Start() { nextItem = 0;}
//	int GetNext() const {stuff[nextItem++]; ... }
//
//private:
//	std::vector<int> stuff;
//	mutable int nextItem;
//};
//
////void DoStuff(Foo foo)				// Pass by value
////void DoStuff(Foo& foo)			// Pass by reference
//void DoStuff(const Foo& foo)		// Pass by const reference
//{
//	// do stuff with foo
//}
//
//// Stack frame
//// has 3 things:
//// 1) Local variables
//// 2) Parameters
//// 3) Return address