#include "pch.h"
#include "Game.h"

std::unique_ptr<Game> Game::instance = nullptr;

Game::Game(LPCWSTR name) {
	this->name = name;
	camera = std::make_unique<CameraGameObject>();
}

// Access to Game::instance
std::unique_ptr<Game>& Game::Instance() {
	if (!instance)
		Game::CreateInstance(L"Default name");

	return instance;
}

// For creating Game::instance
void Game::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<Game>(new Game(name));
}


// Initialize all "GameComponent" items in vector
void Game::Initialize() {
	for (auto& component : gameObjects)
		component->Initialize();

	camera->Initialize();
}

/*
* Update all "GameComponent" items in vector
* For logic
*/
void Game::Update() {
	for (auto& gameObject : gameObjects)
		gameObject->Update();

	camera->Update();

	// Handle ESC button to break main while cycle
	if (inputDevice->IsKeyDown(Keys::Escape))
		PostQuitMessage(0);

}

/*
* Protected method
* Update all items
* Call each frame
*/
void Game::UpdateInternal() {
	Time::Update();
	Update();
	renderSystem->Draw(gameObjects);
}

void Game::DestroyResources() {
	for (auto& gameObject : gameObjects)
		gameObject->DestroyResources();
}


// Main method for starting game with initializatio
void Game::Run(int clientWidth, int clientHeight, bool fullscreen) {
	renderSystem = std::make_unique<RenderSystem>(name, clientWidth, clientHeight, fullscreen, WndProc);
	inputDevice = std::make_unique<InputDevice>();
	Initialize();

	Time::startTime = steady_clock::now();
	Time::prevTime = Time::startTime;
	
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		// Handle the windows messages.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			UpdateInternal();
	}
	
	DestroyResources();
}

// Exit game with destroying resources
void Game::Exit() {
	DestroyResources();
}


// Static method for handling user input
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	return Game::Instance()->MessageHandler(hwnd, umessage, wparam, lparam);
}

LRESULT Game::MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {
	case WM_INPUT: {
		UINT dwSize = 0;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];

		if (lpb == nullptr)
			return 0;

		if (GetRawInputData((HRAWINPUT)lparam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

		RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);

		if (raw->header.dwType == RIM_TYPEKEYBOARD) {
			//printf(" Kbd: make=%04i Flags:%04i Reserved:%04i ExtraInformation:%08i, msg=%04i VK=%i \n",
			//	raw->data.keyboard.MakeCode,
			//	raw->data.keyboard.Flags,
			//	raw->data.keyboard.Reserved,
			//	raw->data.keyboard.ExtraInformation,
			//	raw->data.keyboard.Message,
			//	raw->data.keyboard.VKey);

			inputDevice.get()->OnKeyDown({
				raw->data.keyboard.MakeCode,
				raw->data.keyboard.Flags,
				raw->data.keyboard.VKey,
				raw->data.keyboard.Message
				});
		}
		else if (raw->header.dwType == RIM_TYPEMOUSE) {
			//printf(" Mouse: X=%04d Y:%04d \n", raw->data.mouse.lLastX, raw->data.mouse.lLastY);
			inputDevice->OnMouseMove({
				raw->data.mouse.usFlags,
				raw->data.mouse.usButtonFlags,
				static_cast<int>(raw->data.mouse.ulExtraInformation),
				static_cast<int>(raw->data.mouse.ulRawButtons),
				static_cast<short>(raw->data.mouse.usButtonData),
				raw->data.mouse.lLastX,
				raw->data.mouse.lLastY
				});
		}

		delete[] lpb;
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	default: {
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	}
}
