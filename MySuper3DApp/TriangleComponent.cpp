#include "TriangleComponent.h"

TriangleComponent::TriangleComponent() {

}

void TriangleComponent::Initialize() {
	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };
	ID3DBlob* errorPixelCode;
	ID3DBlob* errorVertexCode = nullptr;

	// Compile pixel shader
	Game::instance->SetRes(
		D3DCompileFromFile(
			L"./Shaders/MyVeryFirstShader.hlsl",
			Shader_Macros /*macros*/,
			nullptr /*include*/,
			"PSMain",
			"ps_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
			0,
			&pixelShaderByteCode,
			&errorPixelCode
		)
	);

	// Compile vertex shader
	Game::instance->SetRes(
		D3DCompileFromFile(
			L"./Shaders/MyVeryFirstShader.hlsl",
			nullptr /*macros*/,
			nullptr /*include*/,
			"VSMain",
			"vs_5_0", // Shader target (Pixel / Vertex)
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // Different flags (for example code translation)
			0,
			&vertexShaderByteCode,
			&errorVertexCode
		)
	);

	if (FAILED(Game::instance->GetRes())) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
			MessageBox(Game::instance->GetDisplay()->GetHWnd(), L"MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);

		return;
	}

	Game::instance->GetDevice()->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader
	);

	Game::instance->GetDevice()->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader
	);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA, // Per vertex or per instance
			0
		}
	};

	Game::instance->GetDevice()->CreateInputLayout(
		inputElements,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		&layout
	);

	// Creating set of points
	pointsAmount = 8;
	points = new DirectX::XMFLOAT4[pointsAmount];
	points[0] = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	points[1] = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	points[2] = DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f);
	points[3] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	points[4] = DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f);
	points[5] = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	points[6] = DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f);
	points[7] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * pointsAmount;

	vertexData = {};
	vertexData.pSysMem = points;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Game::instance->GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &vb);

	int indeces[] = { 0, 1, 2, 1, 0, 3 };
	indexBufDesc = {};
	indexBufDesc.ByteWidth = sizeof(int) * std::size(indeces);
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;

	indexData = {};
	indexData.pSysMem = indeces;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Game::instance->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &ib);

	rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE; // Try to change
	rastDesc.FillMode = D3D11_FILL_SOLID; // Try to change

	Game::instance->SetRes(Game::instance->GetDevice()->CreateRasterizerState(&rastDesc, &rastState));
	Game::instance->GetContext()->RSSetState(rastState);

	strides[0] = 32;
	offsets[0] = 0;
}

void TriangleComponent::Update() {
	Game::instance->GetContext()->IASetInputLayout(layout);
	Game::instance->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Game::instance->GetContext()->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
	Game::instance->GetContext()->IASetVertexBuffers(0, 1, &vb, strides, offsets);

	Game::instance->GetContext()->VSSetShader(vertexShader, nullptr, 0);
	Game::instance->GetContext()->PSSetShader(pixelShader, nullptr, 0);

	Game::instance->GetContext()->RSSetState(rastState);
}

void TriangleComponent::Draw() {
	Game::instance->GetContext()->DrawIndexed(6, 0, 0); // Main function for draw (DrawCall)
}

void TriangleComponent::Reload() {

}

void TriangleComponent::DestroyResources() {

}
