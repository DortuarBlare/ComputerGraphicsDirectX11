#pragma once
#include "pch.h"
#include "GameObjectComponent.h"

class ColliderComponent : public GameObjectComponent {
public:
	virtual void Initialize() override {};
	virtual void Update() override {};
};
