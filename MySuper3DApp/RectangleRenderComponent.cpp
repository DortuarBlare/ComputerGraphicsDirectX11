#include "pch.h"
#include "RectangleRenderComponent.h"

RectangleRenderComponent::RectangleRenderComponent(
	LPCWSTR textureFileName,
	D3D11_FILL_MODE fillMode,
	XMFLOAT3 extents
) : RenderComponent(textureFileName, fillMode) {
	this->extents = extents;
}

void RectangleRenderComponent::Initialize() {
	points.insert(points.end(),
		{
			/* Vertex position										*/ /* Texture coordinates							  */
			XMFLOAT4(0.0f + extents.x,  0.0f + extents.y, 0.0f, 1.0f), XMFLOAT4(extents.x / 4,	extents.y / 4,	0.0f, 0.0f),
			XMFLOAT4(0.0f - extents.x,  0.0f - extents.y, 0.0f, 1.0f), XMFLOAT4(0.0f,			0.0f,			0.0f, 0.0f),
			XMFLOAT4(0.0f + extents.x,  0.0f - extents.y, 0.0f, 1.0f), XMFLOAT4(extents.x / 4,	0.0f,			0.0f, 0.0f),
			XMFLOAT4(0.0f - extents.x,  0.0f + extents.y, 0.0f, 1.0f), XMFLOAT4(0.0f,			extents.y / 4,	0.0f, 0.0f)
		}
	);

	indexes.insert(indexes.end(), { 0, 1, 2, 1, 0, 3 });

	RenderComponent::Initialize();
}