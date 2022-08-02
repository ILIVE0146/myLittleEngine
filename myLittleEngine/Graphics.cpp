#include "Graphics.h"

bool Graphics::initialize(HWND hwnd, Vector2i size)
{
    if (!this->initializeDirectX(hwnd, size))
    {
        return false;
    }

    return true;
}

void Graphics::RenderFrame()
{
	float bgcolor[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
	this->swapChain->Present(1 /*Vsync*/, NULL);
}

bool Graphics::initializeDirectX(HWND hwnd, Vector2i size)
{
    std::vector<AdapterData> adapters = AdapterReader::getAdapterData();
	
    if (adapters.size() < 1)
    {
		ErrorLogger::Log("No Graphics adapters found");
		return false;
	}

    SIZE_T maxDedicatedVideoMemory = 0;
    size_t index = 0;
	
    for ( auto itr = adapters.begin(); itr != adapters.end(); ++itr )
	{
		if (itr->description.DedicatedVideoMemory > maxDedicatedVideoMemory)
		{
			maxDedicatedVideoMemory = itr->description.DedicatedVideoMemory;
			index = itr - adapters.begin();
		}
	}

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferDesc.Width = size.x;
	scd.BufferDesc.Height = size.y;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	
	scd.OutputWindow = hwnd;
	
	scd.Windowed = TRUE;
	
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		adapters[index].pAdapter.Get(),
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		NULL,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		this->swapChain.GetAddressOf(),
		this->device.GetAddressOf(),
		NULL,
		this->deviceContext.GetAddressOf()
	);
	
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create device and swapchain");
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create render target view.");
		return false;
	}

	hr = this->device->CreateRenderTargetView(backBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());

	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), NULL);

    return true;
}
