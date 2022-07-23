// myLittleEngine.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "myLittleEngine.h"
#include "RenderWindow.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	RenderWindow rw;
	rw.Create(hInstance, "New Window", "MyWindowClass", Vector2i(800, 600));

	while (rw.ProcessMessages() == true)
	{
		rw.Update();
	}
}