#include "pch.h"
#include "SolarSystem.h"

int main() {
	SolarSystem::CreateInstance(L"Solar System");
	SolarSystem::Instance()->Run(1920, 1080, false);
}
