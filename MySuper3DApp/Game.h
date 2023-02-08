#pragma once
#include <windows.h>
#include <WinUser.h>
#include <wrl.h>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "GameComponent.h"
#include "TriangleComponent.h"
#include "DisplayWin32.h"
#include <iostream>
#include <chrono>
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class Game {
private:
	static Game* instance; // Singleton

	DisplayWin32* display;
	std::vector<GameComponent*> components;

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	D3D_FEATURE_LEVEL featureLevel[1]; // Array
	DXGI_SWAP_CHAIN_DESC swapDesc;
	HRESULT res;
	ID3D11Texture2D* backTex;

	MSG msg;
	bool isExitRequested;
	float totalTime;
	unsigned int frameCount;

	Game() { 
		CreateBackBuffer();
	}

public:
	ID3D11RenderTargetView* rtv; // Back buffer?
	static Game* GetInstance();


	void CreateBackBuffer();
	void Initialize();
	void Update();
	void UpdateInternal();
	void Draw();
	void Run();
	void PrepareFrame();
	void MessageHandler();
	void DestroyResources();
	void EndFrame();
	void Exit();
	void PrepareResources();
	void RestoreTargets();


	// Getters and setters
	DisplayWin32& GetDisplay();

	Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice();

	ID3D11DeviceContext& GetContext();

	IDXGISwapChain* GetSwapChain();

	HRESULT GetRes();
	void SetRes(HRESULT res);

	ID3D11RenderTargetView* GetRTV();

	float GetTotalTime();
	void SetTotalTime(float totalTime);

	unsigned int GetFrameCount();
	void SetFrameCount(unsigned int frameCount);
};
