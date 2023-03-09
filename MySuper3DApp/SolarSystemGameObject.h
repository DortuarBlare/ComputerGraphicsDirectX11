#pragma once
#include "GameObject.h"
#include "SphereRenderComponent.h"

struct SolarSystemGameObjectDescription {
	float localRotationSpeed;
	Vector3 localRotationAxis;

	float rotateAroundSpeed;
	Vector3 rotateAroundAxis;
	float orbitRadius;

	D3D11_FILL_MODE fillMode;
	float radius;
	int sliceCount;
	int stackCount;
	Color topColor;
	Color bottomColor;
};

class SolarSystemGameObject : public GameObject {
private:
	float localRotationSpeed;
	Vector3 localRotationAxis;

	float rotateAroundSpeed;
	Vector3 rotateAroundAxis;
	float orbitRadius;
	Vector3 offset;

	std::shared_ptr<SphereRenderComponent> mesh;

public:
	SolarSystemGameObject(SolarSystemGameObjectDescription description);

	void Initialize() override;
	virtual void FixedUpdate();
};
