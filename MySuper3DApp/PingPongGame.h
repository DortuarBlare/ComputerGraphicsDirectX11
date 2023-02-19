#pragma once
#include "Game.h"
#include "GameObject.h"
#include "SquareRenderComponent.h"

class PingPongGame : public Game {
private:
	void HandleLeftPlayerKeyDown(unsigned int key);
	void HandleLeftPlayerKeyUp(unsigned int key);
	void HandleRightPlayerKeyDown(unsigned int key);
	void HandleRightPlayerKeyUp(unsigned int key);

	PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Update() override;

public:
	std::shared_ptr<GameObject> leftPlayer;
	std::shared_ptr<GameObject> rightPlayer;

	LRESULT MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) override;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;
	void ConfigureGameObjects();
};
