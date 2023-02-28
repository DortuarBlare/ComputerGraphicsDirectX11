#pragma once
#include "Game.h"
#include "../GameObjects/PingPongRacket.h"
#include "../GameObjects/PingPongBall.h"
#include "../GameObjects/Components/Render/RectangleRenderComponent.h"
#include "../GameObjects/Components/Render/CircleRenderComponent.h"
#include "../GameObjects/Components/Colliders/BoxColliderComponent.h"

class PingPongGame : public Game {
private:
	unsigned int leftPlayerScore;
	unsigned int rightPlayerScore;

	PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	void ConfigureGameObjects();

public:
	std::shared_ptr<PingPongRacket> leftPlayer;
	std::shared_ptr<PingPongRacket> rightPlayer;
	std::shared_ptr<PingPongBall> ball;
	std::shared_ptr<PingPongGameObject> centralInvisibleWall;
	std::shared_ptr<PingPongGameObject> upInvisibleWall;
	std::shared_ptr<PingPongGameObject> downInvisibleWall;
	std::shared_ptr<PingPongGameObject> leftInvisibleWall;
	std::shared_ptr<PingPongGameObject> rightInvisibleWall;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;

	void RestartRound();
};
