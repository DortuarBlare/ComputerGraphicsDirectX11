#pragma once
#include "Game.h"
#include "../GameObjects/Components/Render/RectangleRenderComponent.h"
#include "../GameObjects/Components/Colliders/BoxColliderComponent.h"

class PingPongGame : public Game {
private:
	PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Initialize() override;
	void Update() override;

	void ConfigureGameObjects();

public:
	std::shared_ptr<GameObject> leftPlayer;
	std::shared_ptr<GameObject> rightPlayer;
	std::shared_ptr<GameObject> ball;
	std::shared_ptr<GameObject> centralInvisibleWall;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;
};
