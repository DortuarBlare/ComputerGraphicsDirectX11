#include "Game.h"

Game* Game::GetInstance() {
	if (!instance)
		instance = new Game();

	return instance;
}

void Game::CreateBackBuffer() {
	display = new DisplayWin32();

	featureLevel[0] = { D3D_FEATURE_LEVEL_11_1 };

	swapDesc = {}; // SwapChain Descriptor
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = display->GetScreenWidth();
	swapDesc.BufferDesc.Height = display->GetScreenHeight();
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = display->GetHWnd();
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // Main feature
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1; // Only with DXGI_SWAP_EFFECT_DISCARD
	swapDesc.SampleDesc.Quality = 0;

	res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc, // Descriptor
		&swapChain,
		&device,
		nullptr, // Feature level for device
		&context
	);

	if (FAILED(res)) {
		// Well, that was unexpected
	}

	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);	// __uuidof(ID3D11Texture2D)
	res = device->CreateRenderTargetView(backTex, nullptr, &rtv);
}

void Game::Initialize() {
	// Push back all GameComponents that we need
	components.push_back(new TriangleComponent());

	// Compile shaders
	for (auto component : components)
		component->Initialize();
}

void Game::Update() {
	for (auto component : components)
		component->Update();
}

void Game::UpdateInternal() {

}

void Game::Draw() {
	for (auto component : components)
		component->Draw();
}

void Game::Run() {
	totalTime = 0;
	frameCount = 0;
	msg = {};
	isExitRequested = false;
	std::chrono::time_point<std::chrono::steady_clock> PrevTime = std::chrono::steady_clock::now();
	
	while (!isExitRequested) {
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}

		Update();

		// Maybe move this to TriangleComponent?
		auto curTime = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - PrevTime).count() / 1000000.0f;
		PrevTime = curTime;

		totalTime += deltaTime;
		frameCount++;

		if (totalTime > 1.0f) {
			float fps = frameCount / totalTime;

			totalTime -= 1.0f;

			WCHAR text[256];
			swprintf_s(text, TEXT("FPS: %f"), fps);
			SetWindowText(display->GetHWnd(), text);

			frameCount = 0;
		}
		//

		Draw();
	}
	
	// End of main cycle
	std::cout << "Hello World!\n";
}

void Game::PrepareFrame() {

}

void Game::MessageHandler() {

}

void Game::DestroyResources() {

}

void Game::EndFrame() {

}

void Game::Exit() {

}

void Game::PrepareResources() {

}

void Game::RestoreTargets() {

}


DisplayWin32& Game::GetDisplay() {
	return *display;
}

HRESULT Game::GetRes() {
	return res;
}

void Game::SetRes(HRESULT res) {
	this->res = res;
}

Microsoft::WRL::ComPtr<ID3D11Device>& Game::GetDevice() {
	return device;
}

ID3D11RenderTargetView* Game::GetRTV() {
	return rtv;
}

IDXGISwapChain* Game::GetSwapChain() {
	return swapChain;
}

ID3D11DeviceContext& Game::GetContext() {
	return *context;
}

float Game::GetTotalTime() {
	return totalTime;
}

void Game::SetTotalTime(float totalTime) {
	this->totalTime = totalTime;
}

unsigned int Game::GetFrameCount() {
	return frameCount;
}

void Game::SetFrameCount(unsigned int frameCount) {
	this->frameCount = frameCount;
}
