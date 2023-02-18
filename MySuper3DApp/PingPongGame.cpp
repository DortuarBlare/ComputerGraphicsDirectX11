#include "PingPongGame.h"

LRESULT PingPongGame::MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	Game::MessageHandler(hwnd, umessage, wparam, lparam);

	switch (umessage) {
	case WM_KEYDOWN: {
		auto key = static_cast<unsigned int>(wparam);

		// Input of left player
		HandleLeftPlayerInput(key);

		// Input of right player
		HandleRightPlayerInput(key);

		return 0;
	}
	}
}

PingPongGame::PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) :
	Game(name, screenWidth, screenHeight, windowed) {
	leftPlayerOffset = std::make_shared<DirectX::SimpleMath::Vector4>();
	rightPlayerOffset = std::make_shared<DirectX::SimpleMath::Vector4>();
}

void PingPongGame::HandleLeftPlayerInput(unsigned int key) {
	if (!inputDevice)
		return;

	if (key == 65)
		inputDevice->AddPressedKey(Keys::A);
	else
		inputDevice->RemovePressedKey(Keys::A);

	if (key == 68)
		inputDevice->AddPressedKey(Keys::D);
	else
		inputDevice->RemovePressedKey(Keys::D);

	if (key == 87)
		inputDevice->AddPressedKey(Keys::W);
	else
		inputDevice->RemovePressedKey(Keys::W);

	if (key == 83)
		inputDevice->AddPressedKey(Keys::S);
	else
		inputDevice->RemovePressedKey(Keys::S);

	// Input of left player
	if (inputDevice->IsKeyDown(Keys::A))
		*leftPlayerOffset -= {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::D))
		*leftPlayerOffset += {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::W))
		*leftPlayerOffset += {0.0f, 0.25f * deltaTime, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::S))
		*leftPlayerOffset -= {0.0f, 0.25f * deltaTime, 0.0f, 0.0f};
}

void PingPongGame::HandleRightPlayerInput(unsigned int key) {
	if (!inputDevice)
		return;

	if (key == 37)
		inputDevice->AddPressedKey(Keys::Left);
	else
		inputDevice->RemovePressedKey(Keys::Left);

	if (key == 39)
		inputDevice->AddPressedKey(Keys::Right);
	else
		inputDevice->RemovePressedKey(Keys::Right);

	if (key == 38)
		inputDevice->AddPressedKey(Keys::Up);
	else
		inputDevice->RemovePressedKey(Keys::Up);

	if (key == 40)
		inputDevice->AddPressedKey(Keys::Down);
	else
		inputDevice->RemovePressedKey(Keys::Down);

	// Input of right player
	if (inputDevice->IsKeyDown(Keys::Left))
		*rightPlayerOffset -= {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::Right))
		*rightPlayerOffset += {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::Up))
		*rightPlayerOffset += {0.0f, 0.25f * deltaTime, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::Down))
		*rightPlayerOffset -= {0.0f, 0.25f * deltaTime, 0.0f, 0.0f};
}

/*
* There is no public access to constructor because of "Singleton" pattern
* Need to use this method to create Game::instance (PingPongGame)
*/
void PingPongGame::CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) {
	if (!instance)
		instance = new PingPongGame(name, screenWidth, screenHeight, windowed);
}
