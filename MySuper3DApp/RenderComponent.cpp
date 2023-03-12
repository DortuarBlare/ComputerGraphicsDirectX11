#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(D3D11_FILL_MODE fillMode) {
	this->textureFileName = L"Textures/Default.jpeg";
	this->fillMode = fillMode;

	vertexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	indexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	constBuffers = new ID3D11Buffer * [2];
}

RenderComponent::RenderComponent(LPCWSTR textureFileName, D3D11_FILL_MODE fillMode) {
	this->textureFileName = textureFileName;
	this->fillMode = fillMode;

	vertexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	indexData = std::make_shared<D3D11_SUBRESOURCE_DATA>();

	constBuffers = new ID3D11Buffer * [2];
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
	HRESULT res =
		D3DCompileFromFile(
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
	res =
		D3DCompileFromFile(
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

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
			MessageBox(Game::Instance()->renderSystem->display->GetHWnd(), L"MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);

		return;
	}

	Game::Instance()->renderSystem->device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr,
		pixelShader.GetAddressOf()
	);

	Game::Instance()->renderSystem->device->CreateVertexShader(
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
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	Game::Instance()->renderSystem->device->CreateInputLayout(
		inputElements,
		std::size(inputElements),
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		layout.GetAddressOf()
	);


	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.ByteWidth = sizeof(XMFLOAT4) * points.size();
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;

	vertexData->pSysMem = points.data();
	vertexData->SysMemPitch = 0;
	vertexData->SysMemSlicePitch = 0;

	Game::Instance()->renderSystem->device->CreateBuffer(&vertexBufDesc, vertexData.get(), vertexBuf.GetAddressOf());


	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.ByteWidth = sizeof(unsigned int) * indexes.size();
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;

	indexData->pSysMem = indexes.data();
	indexData->SysMemPitch = 0;
	indexData->SysMemSlicePitch = 0;

	Game::Instance()->renderSystem->device->CreateBuffer(&indexBufDesc, indexData.get(), indexBuf.GetAddressOf());


	D3D11_BUFFER_DESC constBufDescPerObject = {};
	constBufDescPerObject.ByteWidth = sizeof(PerObject);
	constBufDescPerObject.Usage = D3D11_USAGE_DEFAULT;
	constBufDescPerObject.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufDescPerObject.CPUAccessFlags = 0;
	constBufDescPerObject.MiscFlags = 0;
	constBufDescPerObject.StructureByteStride = 0;

	Game::Instance()->renderSystem->device->CreateBuffer(&constBufDescPerObject, nullptr, &constBuffers[0]);

	D3D11_BUFFER_DESC constBufDescPerScene = {};
	constBufDescPerScene.ByteWidth = sizeof(PerScene);
	constBufDescPerScene.Usage = D3D11_USAGE_DEFAULT;
	constBufDescPerScene.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufDescPerScene.CPUAccessFlags = 0;
	constBufDescPerScene.MiscFlags = 0;
	constBufDescPerScene.StructureByteStride = 0;

	Game::Instance()->renderSystem->device->CreateBuffer(&constBufDescPerScene, nullptr, &constBuffers[1]);


	res = CreateWICTextureFromFile(
		Game::Instance()->renderSystem->device.Get(),
		Game::Instance()->renderSystem->context.Get(),
		textureFileName,
		texture.GetAddressOf(),
		textureView.GetAddressOf()
	);

	D3D11_SAMPLER_DESC samplerStateDesc = {};
	samplerStateDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	res = Game::Instance()->renderSystem->device->CreateSamplerState(&samplerStateDesc, samplerState.GetAddressOf());


	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE; // Cull None | Cull Front | Cull Back
	rastDesc.FillMode = fillMode; // Solid or wireframe
	rastDesc.DepthClipEnable = true;

	res = Game::Instance()->renderSystem->device->CreateRasterizerState(&rastDesc, rastState.GetAddressOf());
	Game::Instance()->renderSystem->context->RSSetState(rastState.Get());

	strides[0] = 48; // Position and color in one structure, so array with one value - 48 (3 float4)
	offsets[0] = 0;

	perObject = {};
	perScene = {};
	perScene.lightDirection = { 1.0f, 1.0f, 1.0f, 0.0f };
	perScene.lightDirection.Normalize();
	perScene.lightColor = { 1.0f, 1.0f, 1.0f, 0.4f };
}

void RenderComponent::Update() {}

void RenderComponent::Draw() {
	if (enabled) {
		Game::Instance()->renderSystem->context->IASetInputLayout(layout.Get());
		Game::Instance()->renderSystem->context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Game::Instance()->renderSystem->context->IASetIndexBuffer(indexBuf.Get(), DXGI_FORMAT_R32_UINT, 0);
		Game::Instance()->renderSystem->context->IASetVertexBuffers(0, 1, vertexBuf.GetAddressOf(), strides, offsets);

		Game::Instance()->renderSystem->context->VSSetShader(vertexShader.Get(), nullptr, 0);
		Game::Instance()->renderSystem->context->PSSetShader(pixelShader.Get(), nullptr, 0);

		Game::Instance()->renderSystem->context->PSSetShaderResources(0, 1, textureView.GetAddressOf());
		Game::Instance()->renderSystem->context->PSSetSamplers(0, 1, samplerState.GetAddressOf());

		Game::Instance()->renderSystem->context->RSSetState(rastState.Get());

		perObject.constBufMatrix = owner->transform->GetModel() * Game::Instance()->camera->GetCameraMatrix();
		perObject.constBufMatrix.Transpose();
		perObject.invTrWorld = (Matrix::CreateScale(*owner->transform->scale) * Matrix::CreateFromQuaternion(owner->transform->GetRotation())).Invert().Transpose();

		perScene.viewDirectionSpecular =
			Vector4(
				Game::Instance()->camera->transform->localPosition->x - Game::Instance()->camera->target.x,
				Game::Instance()->camera->transform->localPosition->y - Game::Instance()->camera->target.y,
				Game::Instance()->camera->transform->localPosition->z - Game::Instance()->camera->target.z,
				0.0f
			);

		perScene.viewDirectionSpecular.Normalize();
		perScene.viewDirectionSpecular.w = 0.5f;

		Game::Instance()->renderSystem->context->UpdateSubresource(constBuffers[0], 0, nullptr, &perObject, 0, 0);
		Game::Instance()->renderSystem->context->UpdateSubresource(constBuffers[1], 0, nullptr, &perScene, 0, 0);
		Game::Instance()->renderSystem->context->VSSetConstantBuffers(0, 2, constBuffers);
		Game::Instance()->renderSystem->context->PSSetConstantBuffers(0, 2, constBuffers);

		Game::Instance()->renderSystem->context->DrawIndexed(indexes.size(), 0, 0);
	}
}

void RenderComponent::Reload() {}

void RenderComponent::DestroyResources() {}
