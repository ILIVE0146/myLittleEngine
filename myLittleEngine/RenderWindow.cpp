#include "RenderWindow.h"
#include "GlobalResources.h"
#include <memory>

RenderWindow::RenderWindow()
{
	static bool raw_input_initialized = false;
	if (raw_input_initialized == false)
	{
		RAWINPUTDEVICE rid{ 0x01 /*Mouse*/, 0x02, 0, NULL };

		if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == false)
		{
			ErrorLogger::Log(GetLastError(), "Failed to register raw input devices.");
			exit(-1);
		}

		raw_input_initialized = true;
	}
}

bool RenderWindow::Create(HINSTANCE Hinstance, std::string windowTitle, std::string windowClass, Vector2i windowSize)
{
	this->Hinstance = Hinstance;
	this->windowSize = windowSize;
	this->title = windowTitle;
	this->w_title = StringConverter::StringToWide(this->title);
	this->windowClass = windowClass;
	this->w_windowClass = StringConverter::StringToWide(this->windowClass);

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0, this->w_windowClass.c_str(), this->w_title.c_str(), WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, this->windowSize.x, this->windowSize.y, NULL, NULL, this->Hinstance, this);

	if (handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEX failed for the window: " + this->title);
		return false;
	}

	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages()
{
	MSG msg{};
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	if (msg.message == WM_NULL)
	{
		if (!IsWindow(this->handle))
		{
			this->handle = NULL;
			UnregisterClass(this->w_windowClass.c_str(), this->Hinstance);
			return false;
		}
	}

	return true;
}

void RenderWindow::Update()
{
	/*while (!mouse.isEventBufferEmpty())
	{
		MouseEvent me = mouse.readEvent();
		std::string outmsg = "x: " + std::to_string(me.getPosX()) + '\n';
		outmsg += "y: " + std::to_string(me.getPosY()) + '\n';
		OutputDebugStringA(outmsg.c_str());
	}*/

	while (!mouse.isEventBufferEmpty())
	{
		MouseEvent me = mouse.readEvent();
		if (me.getType() == MouseEvent::EventType::RAW_MOVE)
		{
			std::string outmsg = "x: " + std::to_string(me.getPosX()) + '\n' + "y: " + std::to_string(me.getPosY()) + '\n';
			OutputDebugStringA(outmsg.c_str());
		}
	}
}

LRESULT RenderWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		if (keyboard.getAutoRepeatKeys())
		{
			keyboard.onChar(keycode);
		}
		else
		{
			const bool wasPressed = lParam & (static_cast<long long>(1) << 30);
			if (!wasPressed)
			{
				keyboard.onChar(keycode);
			}
		}
		return 0;
	}
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		if (keyboard.getAutoRepeatKeys())
		{
			keyboard.onKeyPressed(keycode);
		}
		else
		{
			const bool wasPressed = lParam & (static_cast<long long>(1) << 30);
			if (!wasPressed)
			{
				keyboard.onKeyPressed(keycode);
			}
		}
		return 0;
	}
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		keyboard.onKeyReleased(keycode);

		return 0;
	}
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		mouse.onMouseMove(Vector2i(x, y));
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		mouse.onLeftPressed({ x, y });
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		mouse.onRightPressed({ x, y });
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		mouse.onMiddlePressed({ x, y });
		return 0;
	}
	case WM_LBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		mouse.onLeftReleased({ x, y });
		return 0;
	}
	case WM_RBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		mouse.onRightReleased({ x, y });
		return 0;
	}
	case WM_MBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		mouse.onMiddleReleased({ x, y });
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			mouse.onWheelUp({ x, y });
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			mouse.onWheelDown({ x, y });
		}
		return 0;
	}
	case WM_INPUT:
	{
		UINT dataSize = 0u;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
		
		if (dataSize > 0)
		{
			std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					mouse.onMouseMoveRaw(Vector2i(raw->data.mouse.lLastX, raw->data.mouse.lLastY));
				}
			}
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL)
	{
		UnregisterClass(this->w_windowClass.c_str(), this->Hinstance);
		DestroyWindow(this->handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:

		RenderWindow* const pWindow = reinterpret_cast<RenderWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);
		RenderWindow* pWindow = reinterpret_cast<RenderWindow*>(pCreate->lpCreateParams);
		if (pWindow == nullptr)
		{
			ErrorLogger::Log("Critical Error: Pointer to Render Window is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wparam, lparam);
	}
	default:
	{
		return DefWindowProc(hwnd, uMsg, wparam, lparam);
	}
	}
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc{};
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->Hinstance;

	/*
	HICON hIcon = static_cast<HICON>(::LoadImage(hInstance, MAKEINTRESOURCE(MYICON1), IMAGE_ICON,
	48, 48,    // or whatever size icon you want to load
	LR_DEFAULTCOLOR);
	*/

	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszClassName = this->w_windowClass.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);
}