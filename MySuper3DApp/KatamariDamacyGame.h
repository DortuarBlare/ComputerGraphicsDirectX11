#pragma once
#include "Game.h"
#include "KatamariDamacyGameObject.h"
#include "LineRenderComponent.h"
#include "RectangleRenderComponent.h"

class KatamariDamacyGame : public Game {
private:
	std::shared_ptr<GameObject> ground;
	std::shared_ptr<GameObject> grid;
	std::shared_ptr<KatamariDamacyGameObject> player;

	KatamariDamacyGame(LPCWSTR name);

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

public:
	static void CreateInstance(LPCWSTR name);

	void Run(int screenWidth, int screenHeight, bool fullscreen) override;
};
