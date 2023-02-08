#pragma once
#include "Game.h"

class GameComponent {
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Reload() = 0;
	virtual void DestroyResources() = 0;
};
