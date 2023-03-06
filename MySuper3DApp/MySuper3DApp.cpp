#include "pch.h"
#include "SolarSystem.h"

int main() {
	//SolarSystem::CreateInstance(L"Solar System", 1000, 1000, true);
	SolarSystem::CreateInstance(L"Solar System", 1280, 720, true);
	SolarSystem::instance->Run();
}
