#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent() {
	fillColor = { 0.0f, 0.0f, 0.0f };
	fillMode = D3D11_FILL_SOLID;

	rastDesc = std::make_shared<CD3D11_RASTERIZER_DESC>();

	vertexBufDesc = std::make_shared<D3D11_BUFFER_DESC>();
	vertexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	indexBufDesc = std::make_shared<D3D11_BUFFER_DESC>();
	indexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	constBufDesc = std::make_shared<D3D11_BUFFER_DESC>();
	constData = std::make_shared<D3D11_SUBRESOURCE_DATA>();
	constBufMatrix = std::make_shared<Matrix>();
}

RenderComponent::RenderComponent(Color fillColor, D3D11_FILL_MODE fillMode) {
	this->fillColor = fillColor;
	this->fillMode = fillMode;

	rastDesc = std::make_shared<CD3D11_RASTERIZER_DESC>();

	vertexBufDesc = std::make_shared<D3D11_BUFFER_DESC>();
	vertexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	indexBufDesc = std::make_shared<D3D11_BUFFER_DESC>();
	indexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	constBufDesc = std::make_shared<D3D11_BUFFER_DESC>();
	constData = std::make_shared<D3D11_SUBRESOURCE_DATA>();
	constBufMatrix = std::make_shared<Matrix>();
}

/*
* Compiling pixel and vertex shaders
* Creating pixel, shader and constant buffers
* Configure rasterizer for the object
*/
void RenderComponent::Initialize() {
	ID3DBlob* errorPixelCode = nullptr;
	ID3DBlob* errorVertexCode = nullptr;

	// Compile pixel shader
	Game::instance->res = D3DCompileFromFile(
		L"./Shaders/MyVeryFirstShader.hlsl",
		nullptr /*macros*/,
		nullptr /*include*/,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		pixelShaderByteCode.GetAddressOf(),
		&errorPixelCode
	);

	// Compile vertex shader
	Game::instance->res = D3DCompileFromFile(
		L"./Shaders/MyVeryFirstShader.hlsl",
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0", // Shader target (Pixel / Vertex)
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // Different flags (for example code translation)
		0,
		vertexShaderByteCode.GetAddressOf(),
		&errorVertexCode
	);

	if (FAILED(Game::instance->res)) {
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
		nullptr,
		pixelShader.GetAddressOf()
	);

	Game::instance->GetDevice()->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr,
		vertexShader.GetAddressOf()
	);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION", // HLSL semantic associated with this element in a shader input-signature
			0, // Semantic index modifies a semantic, with an integer index number
			DXGI_FORMAT_R32G32B32A32_FLOAT, // Data type of the element data
			0, // Integer value that identifies the input-assembler. Valid values are between 0 and 15
			0, // Offset (in bytes) from the start of the vertex (Optional)
			D3D11_INPUT_PER_VERTEX_DATA, // Identifies the input data class for a single input slot
			0 // The number of instances to draw using the same per-instance data before advancing in the buffer by one element
		},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	Game::instance->GetDevice()->CreateInputLayout(
		inputElements,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		layout.GetAddressOf()
	);

	vertexBufDesc->ByteWidth = sizeof(XMFLOAT4) * points.size();
	vertexBufDesc->Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc->BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc->CPUAccessFlags = 0;
	vertexBufDesc->MiscFlags = 0;
	vertexBufDesc->StructureByteStride = 0;

	vertexData->pSysMem = points.data();
	vertexData->SysMemPitch = 0;
	vertexData->SysMemSlicePitch = 0;

	Game::instance->GetDevice()->CreateBuffer(vertexBufDesc.get(), vertexData.get(), vertexBuf.GetAddressOf());

	indexBufDesc->ByteWidth = sizeof(int) * indexes.size();
	indexBufDesc->Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc->BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc->CPUAccessFlags = 0;
	indexBufDesc->MiscFlags = 0;
	indexBufDesc->StructureByteStride = 0;

	indexData->pSysMem = indexes.data();
	indexData->SysMemPitch = 0;
	indexData->SysMemSlicePitch = 0;

	Game::instance->GetDevice()->CreateBuffer(indexBufDesc.get(), indexData.get(), indexBuf.GetAddressOf());

	// Create const buffer
	constBufDesc->ByteWidth = sizeof(Matrix);
	constBufDesc->Usage = D3D11_USAGE_DYNAMIC;
	constBufDesc->BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufDesc->CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constBufDesc->MiscFlags = 0;
	constBufDesc->StructureByteStride = 0;

	constData->pSysMem = constBufMatrix.get();
	constData->SysMemPitch = 0;
	constData->SysMemSlicePitch = 0;

	Game::instance->GetDevice()->CreateBuffer(constBufDesc.get(), constData.get(), constBuf.GetAddressOf());

	rastDesc->CullMode = D3D11_CULL_NONE; // Cull None | Cull Front | Cull Back
	rastDesc->FillMode = fillMode; // Solid or wireframe

	Game::instance->res = Game::instance->GetDevice()->CreateRasterizerState(rastDesc.get(), rastState.GetAddressOf());
	Game::instance->GetContext()->RSSetState(rastState.Get());

	strides[0] = 32; // Position and color in one structure, so array with one value - 32 (2 float4)
	offsets[0] = 0;
}

void RenderComponent::Update() {
	*constBufMatrix = Game::instance->camera->GetCameraMatrix();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Game::instance->GetContext()->Map(constBuf.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, constBufMatrix.get(), sizeof(constBufMatrix));
	Game::instance->GetContext()->Unmap(constBuf.Get(), 0);
}

void RenderComponent::FixedUpdate() {}

void RenderComponent::Draw() {
	if (enabled) {
		Game::instance->GetContext()->IASetInputLayout(layout.Get());
		Game::instance->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Game::instance->GetContext()->IASetIndexBuffer(indexBuf.Get(), DXGI_FORMAT_R32_UINT, 0);
		Game::instance->GetContext()->IASetVertexBuffers(0, 1, vertexBuf.GetAddressOf(), strides, offsets);

		Game::instance->GetContext()->VSSetShader(vertexShader.Get(), nullptr, 0);
		Game::instance->GetContext()->PSSetShader(pixelShader.Get(), nullptr, 0);

		Game::instance->GetContext()->RSSetState(rastState.Get());

		//Game::instance->GetContext()->UpdateSubresource(constBuf.Get(), 0, nullptr, constBufMatrix.get(), 0, 0);
		Game::instance->GetContext()->VSSetConstantBuffers(0, 1, constBuf.GetAddressOf());

		Game::instance->GetContext()->DrawIndexed(indexes.size(), 0, 0);
	}
}

void RenderComponent::Reload() {}

void RenderComponent::DestroyResources() {}
