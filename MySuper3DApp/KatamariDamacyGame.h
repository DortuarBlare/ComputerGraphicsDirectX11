#pragma once
#include "Game.h"
#include "KatamariDamacyGameObject.h"
#include "LineRenderComponent.h"
#include "RectangleRenderComponent.h"

class KatamariDamacyGame : public Game {
private:
	std::shared_ptr<GameObject> ground;
	std::shared_ptr<KatamariDamacyGameObject> player;
	std::shared_ptr<KatamariDamacyGameObject> testObject;

	KatamariDamacyGame(LPCWSTR name);

	void Initialize() override;
	void Update() override;

public:
	static void CreateInstance(LPCWSTR name);
};
