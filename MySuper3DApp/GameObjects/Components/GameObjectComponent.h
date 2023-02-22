#pragma once
#include "../../Games/Game.h"

class Game;

class GameObjectComponent {
public:

	bool enabled = true;

	virtual ~GameObjectComponent() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Reload() = 0;
	virtual void DestroyResources() = 0;
};
