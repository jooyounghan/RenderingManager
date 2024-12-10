#pragma once
#include "AShader.h"

class PixelShader : public AShader
{
public:
	PixelShader() = default;

protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

protected:
	virtual void CreateShaderImpl(
		const std::wstring& shaderPath,
		const std::string& entryPoint,
		const std::string& targetVersion,
		ID3D11Device* device
	) override;

public:
	virtual void SetShader(
		ID3D11DeviceContext* deviceContext
	) const override;
	virtual void SetSamplerState(
		ID3D11DeviceContext* deviceContext,
		const std::vector<ID3D11SamplerState*>& samplerStates
	) override;
	virtual void ResetShader(ID3D11DeviceContext* deviceContext) const override;
	virtual void ResetSamplerState(ID3D11DeviceContext* deviceContext) const override;
};

