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

	*camera->transform->localPosition += {0.0f, 15.0f, 20.0f};

	float yPlanetsOffset = 10.0f;
	Sun->transform->localPosition->y += yPlanetsOffset;
	Mercury->transform->localPosition->y += yPlanetsOffset;
	Venus->transform->localPosition->y += yPlanetsOffset;
	Earth->transform->localPosition->y += yPlanetsOffset;
	Moon->transform->localPosition->y += yPlanetsOffset;
	Mars->transform->localPosition->y += yPlanetsOffset;
	Jupiter->transform->localPosition->y += yPlanetsOffset;
}

void SolarSystem::Update() {
	Game::Update();

	if (Game::instance->inputDevice->IsKeyDown(Keys::D1)) {
		camera->orbitMode = true;
		camera->transform->parent = Sun->transform;
	}
}

void SolarSystem::FixedUpdate() {
	Game::FixedUpdate();
}

void SolarSystem::Run() {
	ConfigureGameObjects();
	Game::Run();
}

void SolarSystem::ConfigureGameObjects() {
	Color gridColor(0.75f, 0.75f, 0.75f);

	SolarSystemGameObjectDescription SunDescription = {};
	SunDescription.localRotationSpeed = 0.5f;
	SunDescription.localRotationAxis = Vector3::Up;
	SunDescription.rotateAroundSpeed = 0.0f;
	SunDescription.rotateAroundAxis = Vector3::Up;
	SunDescription.orbitRadius = 0.0f;
	SunDescription.fillMode = D3D11_FILL_SOLID;
	SunDescription.radius = 5.0f;
	SunDescription.sliceCount = 32;
	SunDescription.stackCount = 32;
	SunDescription.topColor = { 1.0f, 1.0f, 0.0f };
	SunDescription.bottomColor = { 1.0f, 1.0f, 1.0f };
	Sun = std::make_shared<SolarSystemGameObject>(SunDescription);

	SolarSystemGameObjectDescription MercuryDescription = {};
	MercuryDescription.localRotationSpeed = 0.5f;
	MercuryDescription.localRotationAxis = Vector3::Up;
	MercuryDescription.rotateAroundSpeed = 1.0f;
	MercuryDescription.rotateAroundAxis = Vector3::Up;
	MercuryDescription.orbitRadius = 10.0f;
	MercuryDescription.fillMode = D3D11_FILL_SOLID;
	MercuryDescription.radius = 2.5f;
	MercuryDescription.sliceCount = 20;
	MercuryDescription.stackCount = 20;
	MercuryDescription.topColor = { 0.61f, 0.45f, 0.29f };
	MercuryDescription.bottomColor = { 1.0f, 1.0f, 1.0f };
	Mercury = std::make_shared<SolarSystemGameObject>(MercuryDescription);
	//Mercury->transform->parent = Sun->transform;

	SolarSystemGameObjectDescription VenusDescription = {};
	VenusDescription.localRotationSpeed = 1.0f;
	VenusDescription.localRotationAxis = Vector3::Up;
	VenusDescription.rotateAroundSpeed = 2.0f;
	VenusDescription.rotateAroundAxis = Vector3::Right;
	VenusDescription.orbitRadius = 20.0f;
	VenusDescription.fillMode = D3D11_FILL_SOLID;
	VenusDescription.radius = 2.0f;
	VenusDescription.sliceCount = 20;
	VenusDescription.stackCount = 20;
	VenusDescription.topColor = { 0.75f, 0.75f, 0.75f };
	VenusDescription.bottomColor = { 1.0f, 1.0f, 1.0f };
	Venus = std::make_shared<SolarSystemGameObject>(VenusDescription);
	//Venus->transform->parent = Sun->transform;

	SolarSystemGameObjectDescription EarthDescription = {};
	EarthDescription.localRotationSpeed = 1.0f;
	EarthDescription.localRotationAxis = Vector3::Up;
	EarthDescription.rotateAroundSpeed = 0.5f;
	EarthDescription.rotateAroundAxis = Vector3::Up;
	EarthDescription.orbitRadius = 30.0f;
	EarthDescription.fillMode = D3D11_FILL_SOLID;
	EarthDescription.radius = 2.0f;
	EarthDescription.sliceCount = 20;
	EarthDescription.stackCount = 20;
	EarthDescription.topColor = { 0.42f, 0.6f, 0.8f };
	EarthDescription.bottomColor = { 0.4f, 0.8f, 0.0f };
	Earth = std::make_shared<SolarSystemGameObject>(EarthDescription);
	//Earth->transform->parent = Sun->transform;

	SolarSystemGameObjectDescription MoonDescription = {};
	MoonDescription.localRotationSpeed = 1.0f;
	MoonDescription.localRotationAxis = Vector3::Up;
	MoonDescription.rotateAroundSpeed = 1.0f;
	MoonDescription.rotateAroundAxis = Vector3::Right;
	MoonDescription.orbitRadius = 7.5f;
	MoonDescription.fillMode = D3D11_FILL_SOLID;
	MoonDescription.radius = 0.5f;
	MoonDescription.sliceCount = 20;
	MoonDescription.stackCount = 20;
	MoonDescription.topColor = { 0.5f, 0.5f, 0.5f };
	MoonDescription.bottomColor = { 0.75f, 0.75f, 0.75f };
	Moon = std::make_shared<SolarSystemGameObject>(MoonDescription);
	Moon->transform->parent = Earth->transform;

	SolarSystemGameObjectDescription MarsDescription = {};
	MarsDescription.localRotationSpeed = 2.5f;
	MarsDescription.localRotationAxis = Vector3::Right;
	MarsDescription.rotateAroundSpeed = 1.5f;
	MarsDescription.rotateAroundAxis = Vector3::Up + Vector3::Right;
	MarsDescription.orbitRadius = 40.0f;
	MarsDescription.fillMode = D3D11_FILL_SOLID;
	MarsDescription.radius = 1.75f;
	MarsDescription.sliceCount = 20;
	MarsDescription.stackCount = 20;
	MarsDescription.topColor = { 0.48f, 0.25f, 0.0f };
	MarsDescription.bottomColor = { 0.52f, 0.26f, 0.12f };
	Mars = std::make_shared<SolarSystemGameObject>(MarsDescription);
	//Mars->transform->parent = Sun->transform;

	SolarSystemGameObjectDescription JupiterDescription = {};
	JupiterDescription.localRotationSpeed = 2.5f;
	JupiterDescription.localRotationAxis = Vector3::Right;
	JupiterDescription.rotateAroundSpeed = 0.75f;
	JupiterDescription.rotateAroundAxis = Vector3::Up;
	JupiterDescription.orbitRadius = 50.0f;
	JupiterDescription.fillMode = D3D11_FILL_SOLID;
	JupiterDescription.radius = 2.5f;
	JupiterDescription.sliceCount = 20;
	JupiterDescription.stackCount = 20;
	JupiterDescription.topColor = { 0.85f, 0.53f, 0.1f };
	JupiterDescription.bottomColor = { 0.86f, 0.58f, 0.44f };
	Jupiter = std::make_shared<SolarSystemGameObject>(JupiterDescription);
	//Jupiter->transform->parent = Sun->transform;

	SolarSystem::instance->gameObjects.push_back(grid);
	SolarSystem::instance->gameObjects.push_back(Sun);
	SolarSystem::instance->gameObjects.push_back(Mercury);
	SolarSystem::instance->gameObjects.push_back(Venus);
	SolarSystem::instance->gameObjects.push_back(Earth);
	SolarSystem::instance->gameObjects.push_back(Moon);
	SolarSystem::instance->gameObjects.push_back(Mars);
	SolarSystem::instance->gameObjects.push_back(Jupiter);

	std::shared_ptr<LineRenderComponent> gridRender = std::make_shared<LineRenderComponent>(gridColor);
	gridRender->AddGrid(50, 2, gridColor);
	grid->AddComponent(gridRender);

	Sun->Configure();
	Mercury->Configure();
	Venus->Configure();
	Earth->Configure();
	Moon->Configure();
	Mars->Configure();
	Jupiter->Configure();
}
