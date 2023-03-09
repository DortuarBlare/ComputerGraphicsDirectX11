#include "pch.h"
#include "KatamariDamacyGame.h"
#include "SolarSystem.h"

int main() {
	SolarSystem::CreateInstance(L"Solar System");
	SolarSystem::Instance()->Run(1920, 1080, false);
	/*KatamariDamacyGame::CreateInstance(L"Katamari Damacy");
	KatamariDamacyGame::Instance()->Run(1920, 1080, false);*/
}
