#include "pch.h"
#include "SolarSystem.h"

SolarSystem::SolarSystem(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) :
	Game(name, screenWidth, screenHeight, windowed) {

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

void SolarSystem::ConfigureGameObjects() {

}

void SolarSystem::CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) {
	if (!instance)
		instance = std::unique_ptr<SolarSystem>(new SolarSystem(name, screenWidth, screenHeight, windowed));
}

void SolarSystem::Run() {
	ConfigureGameObjects();
	Game::Run();
}
