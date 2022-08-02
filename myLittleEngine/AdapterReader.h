#pragma once

#include "ErrorLogger.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")

class AdapterData
{
public:
	AdapterData(Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter);
	Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
	DXGI_ADAPTER_DESC description;
};

class AdapterReader
{
public:
	static std::vector<AdapterData> getAdapterData();
private:
	static std::vector<AdapterData> adapters;
};

