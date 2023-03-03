#pragma once
#include "pch.h"

#include "GameObject.h"
#include "DisplayWin32.h"
#include "InputDevice.h"

class InputDevice;
class GameObject;

class Game {
protected:
	LPCWSTR	name; // Name of the game application
	int clientWidth;
	int clientHeight;
	bool windowed;
	
	std::shared_ptr<DisplayWin32> display; // WinApi display
	std::shared_ptr<D3D11_VIEWPORT> viewport; // Defines the dimensions of a viewport
	Microsoft::WRL::ComPtr<ID3D11Device> device; // The device interface represents a virtual adapter and it is used to create resources
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context; // Interface represents a device context which generates rendering commands
	std::shared_ptr<DXGI_SWAP_CHAIN_DESC> swapDesc; // Descriptor, that describes swap chain
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain; // Interface implements one or more "IDXGISurface" for storing rendered data before presenting it to an output
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backTex; // 2D texture interface manages texel data, which is structured memory
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv; // Identifies the render-target subresources that can be accessed during rendering (Back buffer?)

	Game(LPCWSTR name, int clientWidth, int clientHeight, bool windowed);

	virtual void UpdateInternal();
	virtual void DestroyResources();
	virtual void PrepareResources();
	virtual void Initialize();
	virtual void PrepareFrame();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Draw();
	virtual void EndFrame();

public:
	static std::unique_ptr<Game> instance; // Singleton
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::shared_ptr<InputDevice> inputDevice; // For input handling
	std::shared_ptr<std::chrono::time_point<std::chrono::steady_clock>> startTime;
	std::shared_ptr<std::chrono::time_point<std::chrono::steady_clock>> prevTime;
	HRESULT res; // Used for return codes from "Direct3D 11" functions
	float totalTime; // Better move to some "Time" class
	float deltaTime; // Better move to some "Time" class
	unsigned int frameCount;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void RestoreTargets();
	virtual void Run();
	void Exit();

	LRESULT MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);


	std::shared_ptr<DisplayWin32> GetDisplay();

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice();

	Microsoft::WRL::ComPtr <ID3D11DeviceContext> GetContext();

	Microsoft::WRL::ComPtr <IDXGISwapChain> GetSwapChain();

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV();
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
