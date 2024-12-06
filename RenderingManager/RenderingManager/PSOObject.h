#pragma once
#include "AShader.h"
#include <memory>
#include <vector>

class PSOObject
{
public:
	PSOObject(
		ID3D11DepthStencilState* depthStencilState,
		ID3D11BlendState* blendState,
		ID3D11RasterizerState* rasterizerState,
		const vector<ID3D11SamplerState*>& samplerStates,
		const D3D11_PRIMITIVE_TOPOLOGY& topology, 
		const std::vector<std::shared_ptr<AShader>>& shaders
	);

protected:
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11BlendState* m_blendState;
	ID3D11RasterizerState* m_rasterizerState;
	vector<ID3D11SamplerState*> m_samplerStates;
	D3D11_PRIMITIVE_TOPOLOGY m_topology;
	std::vector<std::shared_ptr<AShader>> m_shaders;

public:
	void ApplyPSOObject(ID3D11DeviceContext* deviceContext);
	void ResetPSOObject();
};

