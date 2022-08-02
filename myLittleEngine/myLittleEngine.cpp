// myLittleEngine.cpp : Defines the entry point for the application.
//

#include "Graphics.h"

#include "framework.h"
#include "myLittleEngine.h"
#include "RenderWindow.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	RenderWindow rw;
	if (!rw.Create(hInstance, "New Window", "MyWindowClass", Vector2i(800, 600)))
	{
		ErrorLogger::Log("Unable to Initialize Render Window");
		exit(-1);
	}

	while (rw.ProcessMessages() == true)
	{
		rw.Update();
		rw.Render();
	}
}