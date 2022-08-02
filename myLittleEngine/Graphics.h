#pragma once

#include "Vector2.h"

#include "AdapterReader.h"

class Graphics
{
public:
	bool initialize(HWND hwnd, Vector2i size);
	void RenderFrame();
private:
	bool initializeDirectX(HWND hwnd, Vector2i size);

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
};

