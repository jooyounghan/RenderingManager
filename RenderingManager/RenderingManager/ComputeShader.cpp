#include "pch.h"
#include "ComputeShader.h"

using namespace std;

void ComputeShader::CreateShaderImpl(
	const wstring& shaderPath,
	const string& entryPoint,
	const string& targetVersion,
	ID3D11Device* device
)
{
	device->CreateComputeShader(
		shaderByteCode->GetBufferPointer(),
		shaderByteCode->GetBufferSize(),
		NULL, m_computeShader.GetAddressOf()
	);
}

void ComputeShader::SetShader(ID3D11DeviceContext* deviceContext) const
{
	deviceContext->CSSetShader(m_computeShader.Get(), NULL, NULL);
}

void ComputeShader::SetSamplerState(
	ID3D11DeviceContext* deviceContext,
	const std::vector<ID3D11SamplerState*>& samplerStates
) const
{
	deviceContext->CSSetSamplers(0, static_cast<UINT>(samplerStates.size()), samplerStates.data());
}
