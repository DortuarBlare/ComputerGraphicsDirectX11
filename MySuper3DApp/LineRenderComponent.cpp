#include "pch.h"
#include "LineRenderComponent.h"

LineRenderComponent::LineRenderComponent(LPCWSTR textureFileName) :
	RenderComponent(textureFileName, D3D11_FILL_SOLID) {}

void LineRenderComponent::Initialize() {
	RenderComponent::Initialize();
}

void LineRenderComponent::Draw() {
	if (enabled) {
		//Game::Instance()->renderSystem->context->IASetInputLayout(layout.Get());
		//Game::Instance()->renderSystem->context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		//Game::Instance()->renderSystem->context->IASetIndexBuffer(indexBuf.Get(), DXGI_FORMAT_R32_UINT, 0);
		//Game::Instance()->renderSystem->context->IASetVertexBuffers(0, 1, vertexBuf.GetAddressOf(), strides, offsets);

		//Game::Instance()->renderSystem->context->VSSetShader(vertexShader.Get(), nullptr, 0);
		//Game::Instance()->renderSystem->context->PSSetShader(pixelShader.Get(), nullptr, 0);

		//Game::Instance()->renderSystem->context->PSSetShaderResources(0, 1, textureView.GetAddressOf());
		//Game::Instance()->renderSystem->context->PSSetSamplers(0, 1, samplerState.GetAddressOf());

		//Game::Instance()->renderSystem->context->RSSetState(rastState.Get());

		//// Use constant buffer for offset
		//*constBufMatrix = Game::Instance()->camera->GetCameraMatrix().Transpose();

		//Game::Instance()->renderSystem->context->UpdateSubresource(constBuf.Get(), 0, nullptr, constBufMatrix.get(), 0, 0);
		//Game::Instance()->renderSystem->context->VSSetConstantBuffers(0, 1, constBuf.GetAddressOf());

		//Game::Instance()->renderSystem->context->DrawIndexed(indexes.size(), 0, 0);
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
	float yOffset = 0.1f;

	for (int i = 0; i < nPoints; i++) {
		for (int j = 0; j < nPoints; j++) {
			points.push_back({ cellSize * i + offset, yOffset, cellSize * j + offset, 1 });
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

	/*AddLine({ 0, 0, 0, 1 }, { cellSize, 0, 0, 1 }, { 1, 0, 0 });
	AddLine({ 0, 0, 0, 1 }, { 0, cellSize, 0, 1 }, { 0, 1, 0 });
	AddLine({ 0, 0, 0, 1 }, { 0, 0, cellSize, 1 }, { 0, 0, 1 });*/

	AddLine({ 0, yOffset, 0, 1 }, { cellSize, yOffset, 0, 1 }, { 0, 0, 0 });
	AddLine({ 0, yOffset, 0, 1 }, { 0, yOffset, cellSize, 1 }, { 0, 0, 0 });
}
