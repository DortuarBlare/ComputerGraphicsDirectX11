#include "pch.h"
#include "SolarSystem.h"
#include "TransformComponent.h"

SolarSystem::SolarSystem(LPCWSTR name) : Game(name) {
	grid = std::make_shared<GameObject>();
}

void SolarSystem::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<SolarSystem>(new SolarSystem(name));
}

void SolarSystem::Initialize() {
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
	MoonDescription.rotateAroundSpeed = 5.0f;
	MoonDescription.rotateAroundAxis = Vector3::Up + Vector3::Right;
	MoonDescription.orbitRadius = 3.0f;
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
	JupiterDescription.radius = 3.5f;
	JupiterDescription.sliceCount = 20;
	JupiterDescription.stackCount = 20;
	JupiterDescription.topColor = { 0.85f, 0.53f, 0.1f };
	JupiterDescription.bottomColor = { 0.86f, 0.58f, 0.44f };
	Jupiter = std::make_shared<SolarSystemGameObject>(JupiterDescription);
	//Jupiter->transform->parent = Sun->transform;

	SolarSystemGameObjectDescription SaturnDescription = {};
	SaturnDescription.localRotationSpeed = 2.5f;
	SaturnDescription.localRotationAxis = Vector3::Right;
	SaturnDescription.rotateAroundSpeed = 1.25f;
	SaturnDescription.rotateAroundAxis = Vector3::Up;
	SaturnDescription.orbitRadius = 60.0f;
	SaturnDescription.fillMode = D3D11_FILL_SOLID;
	SaturnDescription.radius = 1.5f;
	SaturnDescription.sliceCount = 20;
	SaturnDescription.stackCount = 20;
	SaturnDescription.topColor = { 0.62f, 0.62f, 0.37f };
	SaturnDescription.bottomColor = { 0.82f, 0.82f, 0.57f };
	Saturn = std::make_shared<SolarSystemGameObject>(SaturnDescription);
	//Saturn->transform->parent = Sun->transform;

	SolarSystemGameObjectDescription UranusDescription = {};
	UranusDescription.localRotationSpeed = 2.5f;
	UranusDescription.localRotationAxis = Vector3::Right;
	UranusDescription.rotateAroundSpeed = 1.0f;
	UranusDescription.rotateAroundAxis = Vector3::Up + Vector3::Left;
	UranusDescription.orbitRadius = 70.0f;
	UranusDescription.fillMode = D3D11_FILL_SOLID;
	UranusDescription.radius = 1.75f;
	UranusDescription.sliceCount = 20;
	UranusDescription.stackCount = 20;
	UranusDescription.topColor = { 0.64f, 0.93f, 0.83f };
	UranusDescription.bottomColor = { 0.64f, 0.86f, 0.82f };
	Uranus = std::make_shared<SolarSystemGameObject>(UranusDescription);
	//Uranus->transform->parent = Sun->transform;

	SolarSystemGameObjectDescription NeptuneDescription = {};
	NeptuneDescription.localRotationSpeed = 2.5f;
	NeptuneDescription.localRotationAxis = Vector3::Right;
	NeptuneDescription.rotateAroundSpeed = 0.25f;
	NeptuneDescription.rotateAroundAxis = Vector3::Up;
	NeptuneDescription.orbitRadius = 80.0f;
	NeptuneDescription.fillMode = D3D11_FILL_SOLID;
	NeptuneDescription.radius = 3.0f;
	NeptuneDescription.sliceCount = 20;
	NeptuneDescription.stackCount = 20;
	NeptuneDescription.topColor = { 0.19f, 0.39f, 0.65f };
	NeptuneDescription.bottomColor = { 0.2f, 0.2f, 0.8f };
	Neptune = std::make_shared<SolarSystemGameObject>(NeptuneDescription);
	//Neptune->transform->parent = Sun->transform;

	SolarSystem::instance->gameObjects.push_back(grid);
	SolarSystem::instance->gameObjects.push_back(Sun);
	SolarSystem::instance->gameObjects.push_back(Mercury);
	SolarSystem::instance->gameObjects.push_back(Venus);
	SolarSystem::instance->gameObjects.push_back(Earth);
	SolarSystem::instance->gameObjects.push_back(Moon);
	SolarSystem::instance->gameObjects.push_back(Mars);
	SolarSystem::instance->gameObjects.push_back(Jupiter);
	SolarSystem::instance->gameObjects.push_back(Saturn);
	SolarSystem::instance->gameObjects.push_back(Uranus);
	SolarSystem::instance->gameObjects.push_back(Neptune);

	std::shared_ptr<LineRenderComponent> gridRender = std::make_shared<LineRenderComponent>(L"Textures/White.jpg");
	gridRender->AddGrid(50, 2, gridColor);
	grid->AddComponent(gridRender);

	Game::Initialize();

	*camera->transform->localPosition += {0.0f, 15.0f, 20.0f};

	float yPlanetsOffset = 10.0f;
	Sun->transform->localPosition->y += yPlanetsOffset;
	Mercury->transform->localPosition->y += yPlanetsOffset;
	Venus->transform->localPosition->y += yPlanetsOffset;
	Earth->transform->localPosition->y += yPlanetsOffset;
	Mars->transform->localPosition->y += yPlanetsOffset;
	Jupiter->transform->localPosition->y += yPlanetsOffset;
	Saturn->transform->localPosition->y += yPlanetsOffset;
	Uranus->transform->localPosition->y += yPlanetsOffset;
	Neptune->transform->localPosition->y += yPlanetsOffset;
}

void SolarSystem::Update() {
	Game::Update();

	if (inputDevice->IsKeyDown(Keys::P))
		camera->perspective = true;
	if (inputDevice->IsKeyDown(Keys::O))
		camera->perspective = false;

	if (Game::Instance()->inputDevice->IsKeyDown(Keys::A)) {
		camera->Translate(camera->velocity * Time::DeltaTime() * (camera->Right() * -1));
		camera->Detach();
	}
	if (Game::Instance()->inputDevice->IsKeyDown(Keys::D)) {
		camera->Translate(camera->velocity * Time::DeltaTime() * camera->Right());
		camera->Detach();
	}
	if (Game::Instance()->inputDevice->IsKeyDown(Keys::W)) {
		camera->Translate(camera->velocity * Time::DeltaTime() * camera->Forward());
		camera->Detach();
	}
	if (Game::Instance()->inputDevice->IsKeyDown(Keys::S)) {
		camera->Translate(camera->velocity * Time::DeltaTime() * (camera->Forward() * -1));
		camera->Detach();
	}

	if (Game::Instance()->inputDevice->IsKeyDown(Keys::Space)) {
		camera->Translate(camera->velocity * Time::DeltaTime() * Vector3::Up);
		camera->Detach();
	}
	if (Game::Instance()->inputDevice->IsKeyDown(Keys::LeftShift)) {
		camera->Translate(camera->velocity * Time::DeltaTime() * Vector3::Down);
		camera->Detach();
	}

	if (Game::instance->inputDevice->IsKeyDown(Keys::D0))
		camera->AttachTo(Sun->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D1))
		camera->AttachTo(Mercury->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D2))
		camera->AttachTo(Venus->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D3))
		camera->AttachTo(Earth->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D4))
		camera->AttachTo(Mars->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D5))
		camera->AttachTo(Jupiter->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D6))
		camera->AttachTo(Saturn->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D7))
		camera->AttachTo(Uranus->transform);
	else if (Game::instance->inputDevice->IsKeyDown(Keys::D8))
		camera->AttachTo(Neptune->transform);
}

void SolarSystem::FixedUpdate() {
	Game::FixedUpdate();
}

void SolarSystem::Run(int screenWidth, int screenHeight, bool fullscreen) {
	Game::Run(screenWidth, screenHeight, fullscreen);
}
