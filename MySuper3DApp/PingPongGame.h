#pragma once
#include "Game.h"
#include "PingPongGameObject.h"
#include "PingPongRacket.h"
#include "PingPongBall.h"

class PingPongGame : public Game {
private:
	unsigned int leftPlayerScore;
	unsigned int rightPlayerScore;
	std::shared_ptr<PingPongRacket> leftPlayer;
	std::shared_ptr<PingPongRacket> rightPlayer;
	std::shared_ptr<PingPongBall> ball;
	std::shared_ptr<PingPongGameObject> centralInvisibleWall;
	std::shared_ptr<PingPongGameObject> upInvisibleWall;
	std::shared_ptr<PingPongGameObject> downInvisibleWall;
	std::shared_ptr<PingPongGameObject> leftInvisibleWall;
	std::shared_ptr<PingPongGameObject> rightInvisibleWall;

	PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	void ConfigureGameObjects();

	void RestartRound();
public:
	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;
};
