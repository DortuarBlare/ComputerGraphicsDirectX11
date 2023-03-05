#include "pch.h"
#include "SolarSystem.h"

SolarSystem::SolarSystem(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) :
	Game(name, screenWidth, screenHeight, windowed) {

}

void SolarSystem::CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) {
	if (!instance)
		instance = std::unique_ptr<SolarSystem>(new SolarSystem(name, screenWidth, screenHeight, windowed));
}

void SolarSystem::Initialize() {
	Game::Initialize();


}

void SolarSystem::Update() {
	Game::Update();


}

void SolarSystem::FixedUpdate() {
	Game::FixedUpdate();


}

void SolarSystem::Run() {
	ConfigureGameObjects();
	Game::Run();
}

void SolarSystem::ConfigureGameObjects() {
	DirectX::SimpleMath::Color debugColor(1.0f, 0.0f, 0.0f);
	std::shared_ptr<GameObject> grid = std::make_shared<GameObject>();

	SolarSystem::instance->gameObjects.push_back(grid);

	std::shared_ptr<LineRenderComponent> gridRender = std::make_shared<LineRenderComponent>(debugColor);
	gridRender->AddGrid(10, 2, debugColor);
	grid->AddComponent(gridRender);
}
