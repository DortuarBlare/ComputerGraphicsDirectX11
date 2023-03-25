#pragma once
#include "DisplayWin32.h"
#include "GameObject.h"

using namespace Microsoft::WRL;

class RenderSystem {
private:
	void PrepareFrame();
	void DrawInternal(std::vector<std::shared_ptr<GameObject>>& gameObjects);
	void EndFrame();

public:
	std::unique_ptr<DisplayWin32> display; // WinApi display

	std::unique_ptr<D3D11_VIEWPORT> viewport; // Defines the dimensions of a viewport
	ComPtr<ID3D11Device> device; // The device interface represents a virtual adapter and it is used to create resources
	ComPtr<ID3D11DeviceContext> context; // Interface represents a device context which generates rendering commands
	ComPtr<IDXGISwapChain> swapChain; // Interface implements one or more "IDXGISurface" for storing rendered data before presenting it to an output
	ComPtr<ID3D11Texture2D> backTex; // 2D texture interface manages texel data, which is structured memory
	ComPtr<ID3D11RenderTargetView> rtv; // Identifies the render-target subresources that can be accessed during rendering (Back buffer?)
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ComPtr<ID3D11DepthStencilView> depthStencilView;

	RenderSystem(LPCWSTR name, int clientWidth, int clientHeight, bool fullscreen, WNDPROC wndProc);

	void Draw(std::vector<std::shared_ptr<GameObject>>& gameObjects);
};
