#include "DirectXRenderer.h"
#include "SpikeConfig.h"
#include "Timer.h"

SpikeRenderer::DirectXRenderer::DirectXRenderer(HWND hWnd) : _hWnd(hWnd)
{
}

void SpikeRenderer::DirectXRenderer::InitRenderer()
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = _hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(SpikeConfig::Config::Instance().GetWindow().GetClientWidth());
	viewport.Height = static_cast<FLOAT>(SpikeConfig::Config::Instance().GetWindow().GetClientHeight());

	devcon->RSSetViewports(1, &viewport);
}

void SpikeRenderer::DirectXRenderer::RenderFrame(float r, float g, float b)
{
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(r, g, b, 1.0f));

	// Render code here

	swapchain->Present(0, 0);
}

void SpikeRenderer::DirectXRenderer::ShutdownRenderer()
{
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}
