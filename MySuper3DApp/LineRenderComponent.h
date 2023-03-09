#pragma once
#include "RenderComponent.h"

using namespace DirectX::SimpleMath;

class LineRenderComponent : public RenderComponent {
public:
	LineRenderComponent() = delete;
	LineRenderComponent(Color color);
	LineRenderComponent(LPCWSTR textureFileName, Color color);

	void Initialize() override;
	void Draw() override;

	void AddLine(Vector4 firstPoint, Vector4 secondPoint, Color color);
	void AddGrid(int gridSize, float cellSize, Color color);
};
