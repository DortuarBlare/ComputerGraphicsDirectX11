#pragma once
#include "RenderComponent.h"

class SphereRenderComponent : public RenderComponent {
private:
	float radius;
	int sliceCount;
	int stackCount;
	Color topColor;
	Color bottomColor;

	void ConfigureSphere();

public:
	SphereRenderComponent() = delete;
	SphereRenderComponent(
		D3D11_FILL_MODE fillMode,
		float radius,
		int sliceCount,
		int stackCount,
		Color topColor,
		Color bottomColor
	);

	void Initialize() override;
};
