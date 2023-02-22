#pragma once
#include "Game.h"
#include "../GameObjects/Components/Render/SquareRenderComponent.h"

class PingPongGame : public Game {
private:
	PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void ConfigureGameObjects();
	void Update() override;

public:
	std::shared_ptr<GameObject> leftPlayer;
	std::shared_ptr<GameObject> rightPlayer;
	std::shared_ptr<GameObject> ball;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;
};
