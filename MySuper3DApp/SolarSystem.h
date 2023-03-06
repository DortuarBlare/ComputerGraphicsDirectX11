#pragma once
#include "Game.h"
#include "LineRenderComponent.h"
#include "SolarSystemGameObject.h"

class SolarSystem : public Game {
private:
	std::shared_ptr<GameObject> grid;
	std::shared_ptr<SolarSystemGameObject> Sun;
	std::shared_ptr<SolarSystemGameObject> Mercury;
	std::shared_ptr<SolarSystemGameObject> Venus;
	std::shared_ptr<SolarSystemGameObject> Earth;
	std::shared_ptr<SolarSystemGameObject> Moon;
	std::shared_ptr<SolarSystemGameObject> Mars;
	std::shared_ptr<SolarSystemGameObject> Jupiter;
	std::shared_ptr<SolarSystemGameObject> Saturn;
	std::shared_ptr<SolarSystemGameObject> Uranus;
	std::shared_ptr<SolarSystemGameObject> Neptune;

	SolarSystem(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	void ConfigureGameObjects();

public:
	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;
};
