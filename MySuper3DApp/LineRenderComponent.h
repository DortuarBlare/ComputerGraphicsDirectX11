#pragma once
#include "RenderComponent.h"

using namespace DirectX::SimpleMath;

class LineRenderComponent : public RenderComponent {
public:
	LineRenderComponent() = delete;
	LineRenderComponent(LPCWSTR textureFileName);

	void Initialize() override;
	void Draw() override;

	void AddLine(Vector4 firstPoint, Vector4 secondPoint, Color color);
	void AddGrid(int gridSize, float cellSize, Color color);
};
