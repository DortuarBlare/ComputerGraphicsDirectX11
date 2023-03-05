#include "pch.h"
#include "LineRenderComponent.h"

LineRenderComponent::LineRenderComponent(Color color) : RenderComponent(color, D3D11_FILL_SOLID) {}

void LineRenderComponent::Initialize() {
	// Something with lines
	RenderComponent::Initialize();
}

void LineRenderComponent::Draw() {
	if (enabled) {
		Game::instance->GetContext()->IASetInputLayout(layout.Get());
		Game::instance->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		Game::instance->GetContext()->IASetIndexBuffer(indexBuf.Get(), DXGI_FORMAT_R32_UINT, 0);
		Game::instance->GetContext()->IASetVertexBuffers(0, 1, vertexBuf.GetAddressOf(), strides, offsets);

		Game::instance->GetContext()->VSSetShader(vertexShader.Get(), nullptr, 0);
		Game::instance->GetContext()->PSSetShader(pixelShader.Get(), nullptr, 0);

		Game::instance->GetContext()->RSSetState(rastState.Get());

		// Use constant buffer for offset
		//Game::instance->GetContext()->UpdateSubresource(constBuf.Get(), 0, nullptr, constBufMatrix.get(), 0, 0);
		Game::instance->GetContext()->VSSetConstantBuffers(0, 1, constBuf.GetAddressOf());

		Game::instance->GetContext()->DrawIndexed(indexes.size(), 0, 0);
	}
}

void LineRenderComponent::AddLine(Vector4 firstPoint, Vector4 secondPoint, Color color) {
	points.push_back(firstPoint);
	points.push_back(color);
	int firstPointIndex = points.size() / 2 - 1;
	points.push_back(secondPoint);
	points.push_back(color);
	
	indexes.push_back(firstPointIndex);
	indexes.push_back(firstPointIndex + 1);
}

void LineRenderComponent::AddGrid(int gridSize, float cellSize, Color color) {
	int firstPointIndex = points.size() / 2;
	int nPoints = gridSize * 2 + 1;
	float offset = -(nPoints / 2) * cellSize;

	for (int i = 0; i < nPoints; i++) {
		for (int j = 0; j < nPoints; j++) {
			points.push_back({ cellSize * i + offset, 0, cellSize * j + offset, 1 });
			points.push_back(color);

			if (i == nPoints / 2 && j == nPoints / 2)
				continue;
			if (j < nPoints - 1) {
				indexes.push_back(firstPointIndex + i * nPoints + j);
				indexes.push_back(firstPointIndex + i * nPoints + j + 1);
			}
			if (i < nPoints - 1) {
				indexes.push_back(firstPointIndex + i * nPoints + j);
				indexes.push_back(firstPointIndex + i * nPoints + j + nPoints);
			}
		}
	}

	AddLine({ 0, 0, 0, 1 }, { cellSize, 0, 0, 1 }, { 1, 0, 0 });
	AddLine({ 0, 0, 0, 1 }, { 0, cellSize, 0, 1 }, { 0, 1, 0 });
	AddLine({ 0, 0, 0, 1 }, { 0, 0, cellSize, 1 }, { 0, 0, 1 });
}
