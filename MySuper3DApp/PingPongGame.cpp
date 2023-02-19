#include "PingPongGame.h"

/*
* Call Game::MessageHandler for base logic
* Handle player input specifically for this game
*/
LRESULT PingPongGame::MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	Game::MessageHandler(hwnd, umessage, wparam, lparam);

	switch (umessage) {
	case WM_KEYDOWN: {
		auto key = static_cast<unsigned int>(wparam);
		
		// Input of left player
		HandleLeftPlayerKeyDown(key);

		// Input of right player
		HandleRightPlayerKeyDown(key);

		return 0;
	}
	case WM_KEYUP: {
		auto key = static_cast<unsigned int>(wparam);

		// Input of left player
		HandleLeftPlayerKeyUp(key);

		// Input of right player
		HandleRightPlayerKeyUp(key);

		return 0;
	}
	}
}

PingPongGame::PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) :
	Game(name, screenWidth, screenHeight, windowed) {
	leftPlayerOffset = std::make_shared<DirectX::SimpleMath::Vector4>();
	rightPlayerOffset = std::make_shared<DirectX::SimpleMath::Vector4>();
}

/*
* Call Game::Update() for base logic
* Handle input player here because of better time control
*/
void PingPongGame::Update() {
	Game::Update();

	// Input of left player
	if (inputDevice->IsKeyDown(Keys::A))
		*leftPlayerOffset -= {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::D))
		*leftPlayerOffset += {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::W))
		*leftPlayerOffset += {0.0f, 0.25f * deltaTime, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::S))
		*leftPlayerOffset -= {0.0f, 0.25f * deltaTime, 0.0f, 0.0f};

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
* Handle left player input when he pressed control keys
*/
void PingPongGame::HandleLeftPlayerKeyDown(unsigned int key) {
	if (!inputDevice)
		return;

	if (key == 65)
		inputDevice->AddPressedKey(Keys::A);

	if (key == 68)
		inputDevice->AddPressedKey(Keys::D);

	if (key == 87)
		inputDevice->AddPressedKey(Keys::W);

	if (key == 83)
		inputDevice->AddPressedKey(Keys::S);
}

/*
* Handle left player input when he stopped pressing control keys
*/
void PingPongGame::HandleLeftPlayerKeyUp(unsigned int key) {
	if (key == 65)
		inputDevice->RemovePressedKey(Keys::A);

	if (key == 68)
		inputDevice->RemovePressedKey(Keys::D);

	if (key == 87)
		inputDevice->RemovePressedKey(Keys::W);

	if (key == 83)
		inputDevice->RemovePressedKey(Keys::S);
}

/*
* Handle right player input when he pressed control keys
*/
void PingPongGame::HandleRightPlayerKeyDown(unsigned int key) {
	if (!inputDevice)
		return;

	if (key == 37)
		inputDevice->AddPressedKey(Keys::Left);
	
	if (key == 39)
		inputDevice->AddPressedKey(Keys::Right);
	
	if (key == 38)
		inputDevice->AddPressedKey(Keys::Up);
	
	if (key == 40)
		inputDevice->AddPressedKey(Keys::Down);
}

/*
* Handle right player input when he stopped pressing control keys
*/
void PingPongGame::HandleRightPlayerKeyUp(unsigned int key) {
	if (key == 37)
		inputDevice->RemovePressedKey(Keys::Left);

	if (key == 39)
		inputDevice->RemovePressedKey(Keys::Right);

	if (key == 38)
		inputDevice->RemovePressedKey(Keys::Up);

	if (key == 40)
		inputDevice->RemovePressedKey(Keys::Down);
}

/*
* There is no public access to constructor because of "Singleton" pattern
* Need to use this method to create Game::instance (PingPongGame)
*/
void PingPongGame::CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) {
	if (!instance)
		instance = new PingPongGame(name, screenWidth, screenHeight, windowed);
}
