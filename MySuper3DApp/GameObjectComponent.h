#pragma once
#include "pch.h"
#include "Game.h" // For using Singleton
#include "GameObject.h"

class GameObject;

class GameObjectComponent {
public:
	std::shared_ptr<GameObject> owner;
	bool enabled = true;

	virtual void Initialize() {};
	virtual void Update();
	virtual void Draw();
	virtual void Reload() {};
	virtual void DestroyResources() {};
};
