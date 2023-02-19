#pragma once
#include "Game.h"
#include "GameObjectComponent.h"

class Game;

class RenderComponent : public GameObjectComponent {
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Reload() = 0;
	virtual void DestroyResources() = 0;
};
