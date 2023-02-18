#pragma once
#include "Game.h"

class PingPongGame : public Game {
private:
	void HandleLeftPlayerInput(unsigned int key);
	void HandleRightPlayerInput(unsigned int key);

	PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

public:
	std::shared_ptr<DirectX::SimpleMath::Vector4> leftPlayerOffset;
	std::shared_ptr<DirectX::SimpleMath::Vector4> rightPlayerOffset;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	LRESULT MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) override;
};
