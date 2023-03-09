#include "pch.h"
#include "RenderSystem.h"

RenderSystem::RenderSystem(LPCWSTR name, int clientWidth, int clientHeight, bool fullscreen, WNDPROC wndProc) {
	display = std::make_unique<DisplayWin32>(name, clientWidth, clientHeight, wndProc);

	viewport = std::make_unique<D3D11_VIEWPORT>();

	// Initialize viewport parameters
	viewport->TopLeftX = 0; // X position of the left hand side of the viewport
	viewport->TopLeftY = 0; // Y position of the top of the viewport
	viewport->Width = static_cast<float>(display->GetClientWidth()); // Width of the viewport
	viewport->Height = static_cast<float>(display->GetClientHeight()); // Height of the viewport
	viewport->MinDepth = 0; // Minimum depth of the viewport. Ranges between 0 and 1
	viewport->MaxDepth = 1.0f; // Maximum depth of the viewport. Ranges between 0 and 1

	// Descriptor, that describes swap chain
	DXGI_SWAP_CHAIN_DESC swapDesc = {};

	// BufferDesc describes the backbuffer display mode
	swapDesc.BufferDesc.Width = display->GetClientWidth(); // Resolution width
	swapDesc.BufferDesc.Height = display->GetClientHeight(); // Resolution height
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Display format (32-bit unsigned normalized integer format supporting 8 bits per channel, including the alpha channel)
	swapDesc.BufferDesc.RefreshRate.Numerator = 60; // Refresh rate in hertz numerator
	swapDesc.BufferDesc.RefreshRate.Denominator = 1; // Refresh rate in hertz denominator (for representing integer it = 1)
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // Scanline drawing mode (indicating the method the raster uses to create an image on a surface)
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // Scaling mode (indicating how an image is stretched to fit a given monitor's resolution)

	/*
	* SampleDesc describes multi - sampling parameters for a resource
	* The default sampler mode, with no anti-aliasing, has a count of 1 and a quality level of 0
	*/
	swapDesc.SampleDesc.Count = 1; // Number of multisamples per pixel
	swapDesc.SampleDesc.Quality = 0; // The image quality level. The higher the quality, the lower the performance

	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Describes the surface usage and CPU access options for the back buffer
	swapDesc.BufferCount = 2; // Number of buffers in the swap chain (double or triple buffering)
	swapDesc.OutputWindow = display->GetHWnd(); // Handle to the output window. This member must not be NULL.
	swapDesc.Windowed = !fullscreen;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // Describes options for handling the contents of the presentation buffer after presenting a surface
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Options for swap-chain behavior

	const int featureLevelsNumber = 1;
	D3D_FEATURE_LEVEL featureLevels[featureLevelsNumber] = { D3D_FEATURE_LEVEL_11_1 };

	// Creates a device that represents the display adapter and a swap chain used for rendering
	HRESULT res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevels, // Determine the order of feature levels to attempt to create
		featureLevelsNumber, // The number of elements in feature levels array
		D3D11_SDK_VERSION,
		&swapDesc,
		swapChain.GetAddressOf(),
		device.GetAddressOf(),
		nullptr, // Feature level for device
		context.GetAddressOf()
	);

	if (FAILED(res)) {
		// Well, that was unexpected
	}

	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backTex.GetAddressOf()); // Accesses one of the buffers of the back buffer chain
	res = device->CreateRenderTargetView(backTex.Get(), nullptr, rtv.GetAddressOf());

	D3D11_TEXTURE2D_DESC depthStencilDesc = {};

	depthStencilDesc.Width = display->GetClientWidth();
	depthStencilDesc.Height = display->GetClientHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	res = device->CreateTexture2D(&depthStencilDesc, nullptr, depthStencilBuffer.GetAddressOf());
	res = device->CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, depthStencilView.GetAddressOf());
}

/*
* Prepare next frame
* Clear states and render targets
*/
void RenderSystem::PrepareFrame() {
	context->ClearState(); // Reset parameters to default

	context->OMSetRenderTargets(1, rtv.GetAddressOf(), depthStencilView.Get());

	float backgroundColor[] = { 0.0f, 0.7f, 0.93f };
	context->RSSetViewports(1, viewport.get());
	context->ClearRenderTargetView(rtv.Get(), backgroundColor);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RenderSystem::DrawInternal(std::vector<std::shared_ptr<GameObject>>& gameObjects) {
	for (auto& gameObject : gameObjects)
		gameObject->Draw();
}

void RenderSystem::EndFrame() {
	context->OMSetRenderTargets(0, nullptr, nullptr);

	swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}

void RenderSystem::Draw(std::vector<std::shared_ptr<GameObject>>& gameObjects) {
	PrepareFrame();
	DrawInternal(gameObjects);
	EndFrame();
}
