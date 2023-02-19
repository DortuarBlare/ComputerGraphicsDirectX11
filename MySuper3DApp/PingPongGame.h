#pragma once
#include "Game.h"

class PingPongGame : public Game {
private:
	void HandleLeftPlayerKeyDown(unsigned int key);
	void HandleLeftPlayerKeyUp(unsigned int key);
	void HandleRightPlayerKeyDown(unsigned int key);
	void HandleRightPlayerKeyUp(unsigned int key);

	PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Update() override;

public:
	std::shared_ptr<DirectX::SimpleMath::Vector4> leftPlayerOffset;
	std::shared_ptr<DirectX::SimpleMath::Vector4> rightPlayerOffset;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	LRESULT MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) override;
};
