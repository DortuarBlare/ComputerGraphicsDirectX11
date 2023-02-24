#pragma once
#include "Game.h"
#include "../GameObjects/Components/Render/RectangleRenderComponent.h"
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
	std::shared_ptr<GameObject> leftPlayer;
	std::shared_ptr<GameObject> rightPlayer;
	std::shared_ptr<GameObject> ball;
	DirectX::SimpleMath::Vector4 ballDirection;
	std::shared_ptr<GameObject> centralInvisibleWall;
	std::shared_ptr<GameObject> upInvisibleWall;
	std::shared_ptr<GameObject> downInvisibleWall;
	std::shared_ptr<GameObject> leftInvisibleWall;
	std::shared_ptr<GameObject> rightInvisibleWall;

	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;

	void RestartRound();
};
