#pragma once
#include "Game.h"
#include "KatamariDamacyGameObject.h"
#include "SphereColliderComponent.h"

class KatamariDamacyGame : public Game {
private:
	std::shared_ptr<KatamariDamacyGameObject> player;

	KatamariDamacyGame(LPCWSTR name);

	void Initialize() override;
	void Update() override;

public:
	static void CreateInstance(LPCWSTR name);
};
