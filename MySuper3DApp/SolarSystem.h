#pragma once
#include "Game.h"

class SolarSystem : public Game {
private:
	SolarSystem(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	void ConfigureGameObjects();

public:
	static void CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed);

	void Run() override;
};
