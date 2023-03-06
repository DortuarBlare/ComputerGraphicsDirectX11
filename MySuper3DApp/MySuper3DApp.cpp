#include "pch.h"
#include "SolarSystem.h"

int main() {
	SolarSystem::CreateInstance(L"Solar System", 1920, 1080, true);
	//SolarSystem::CreateInstance(L"Solar System", 1280, 720, true);
	SolarSystem::instance->Run();
}
