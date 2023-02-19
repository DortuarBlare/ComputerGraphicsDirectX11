#pragma once
#include <vector>
#include "GameObjectComponent.h"

class GameObject {
public:
	std::vector<GameObjectComponent*> components;

	virtual ~GameObject() = default;

	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Draw();
	virtual void Reload();
	virtual void DestroyResources();
};
