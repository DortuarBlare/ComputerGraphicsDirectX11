#include "pch.h"
#include "KatamariDamacyGame.h"

KatamariDamacyGame::KatamariDamacyGame(LPCWSTR name) : Game(name) {
	grid = std::make_shared<GameObject>();
	player = std::make_shared<KatamariDamacyGameObject>();
}

void KatamariDamacyGame::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<KatamariDamacyGame>(new KatamariDamacyGame(name));
}

void KatamariDamacyGame::Initialize() {
	gameObjects.push_back(grid);
	gameObjects.push_back(player);

	std::shared_ptr<LineRenderComponent> gridRender = std::make_shared<LineRenderComponent>(Color(1.0f, 1.0f, 1.0f));
	gridRender->AddGrid(50, 2, Color(1.0f, 1.0f, 1.0f));
	grid->AddComponent(gridRender);

	Game::Initialize();
}

void KatamariDamacyGame::Update() {
	Game::Update();
}

void KatamariDamacyGame::FixedUpdate() {
	Game::FixedUpdate();
}

void KatamariDamacyGame::Run(int screenWidth, int screenHeight, bool fullscreen) {
	Game::Run(screenWidth, screenHeight, fullscreen);
}
