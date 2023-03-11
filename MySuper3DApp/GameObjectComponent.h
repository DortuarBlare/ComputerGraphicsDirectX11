#pragma once
#include "pch.h"
#include "Game.h" // For using Singleton
#include "GameObject.h"

class GameObject;

class GameObjectComponent {
public:
	std::shared_ptr<GameObject> owner;
	bool enabled = true;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Reload() = 0;
	virtual void DestroyResources() = 0;
};
