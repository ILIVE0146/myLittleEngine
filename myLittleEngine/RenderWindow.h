#pragma once

#include "ErrorLogger.h"
#include "Vector2.h"
#include "Keyboard.h"
#include "Mouse.h"

class RenderWindow
{
public:
    bool Create(HINSTANCE Hinstance, std::string windowTitle, std::string windowClass, Vector2i windowSize);

    bool ProcessMessages();
    void Update();

    LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    ~RenderWindow();

private:
    void RegisterWindowClass();
    HWND handle = NULL;
    HINSTANCE Hinstance = NULL;
    std::string title = "";
    std::wstring w_title = L"";
    std::string windowClass = "";
    std::wstring w_windowClass = L"";
    Vector2i windowSize = Vector2i(0, 0);

    Keyboard keyboard;
    Mouse mouse;
};
