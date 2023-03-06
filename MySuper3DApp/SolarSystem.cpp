#include "pch.h"
#include "SolarSystem.h"
#include "TransformComponent.h"

SolarSystem::SolarSystem(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) :
	Game(name, screenWidth, screenHeight, windowed) {
	grid = std::make_shared<GameObject>();
}

void SolarSystem::CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) {
	if (!instance)
		instance = std::unique_ptr<SolarSystem>(new SolarSystem(name, screenWidth, screenHeight, windowed));
}

void SolarSystem::Initialize() {
	Game::Initialize();

	*camera->transform->localPosition += {0.0f, 5.0f, 20.0f};
	Sun->transform->localPosition->y += 10.0f;
	//*Mercury->transform->localPosition += {10.0f, 10.0f, 0.0f};
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
	Color gridColor(1.0f, 1.0f, 1.0f);

	SolarSystemGameObjectDescription SunDescription = {};
	SunDescription.localRotationSpeed = 0.5f;
	SunDescription.localRotationAxis = Vector3::Up;
	SunDescription.fillMode = D3D11_FILL_SOLID;
	SunDescription.radius = 5.0f;
	SunDescription.sliceCount = 20;
	SunDescription.stackCount = 20;
	SunDescription.topColor = { 1.0f, 1.0f, 0.0f };
	SunDescription.bottomColor = { 1.0f, 1.0f, 1.0f };
	Sun = std::make_shared<SolarSystemGameObject>(SunDescription);

	SolarSystemGameObjectDescription MercuryDescription = {};
	MercuryDescription.localRotationSpeed = 0.5f;
	MercuryDescription.localRotationAxis = Vector3::Up;
	MercuryDescription.rotateAroundSpeed = 1.0f;
	MercuryDescription.fillMode = D3D11_FILL_WIREFRAME;
	MercuryDescription.radius = 2.0f;
	MercuryDescription.sliceCount = 20;
	MercuryDescription.stackCount = 20;
	MercuryDescription.topColor = { 0.61f, 0.45f, 0.29f };
	MercuryDescription.bottomColor = { 1.0f, 1.0f, 1.0f };
	Mercury = std::make_shared<SolarSystemGameObject>(MercuryDescription);
	Mercury->transform->parent = Sun->transform;

	SolarSystem::instance->gameObjects.push_back(grid);
	SolarSystem::instance->gameObjects.push_back(Sun);
	SolarSystem::instance->gameObjects.push_back(Mercury);

	std::shared_ptr<LineRenderComponent> gridRender = std::make_shared<LineRenderComponent>(gridColor);
	gridRender->AddGrid(50, 2, gridColor);
	grid->AddComponent(gridRender);

	Sun->Configure();
	Mercury->Configure();
}
