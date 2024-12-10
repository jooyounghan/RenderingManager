#pragma once
#include "PSOObject.h"
#include "IRenderable.h"
#include <unordered_map>

struct SRenderingOption
{
	PSOObject* psoObject;
	std::vector<RTVOption*> renderTargetViews;
	DSVOption* depthStencilView;
	AViewable* viewable;
};

class IRenderable;

class RenderingManager
{
public:
	RenderingManager() = default;

private:
	std::unordered_map<SRenderingOption, std::vector<IRenderable*>> m_optionsToRenderables;

public:
	void Render(ID3D11DeviceContext* deviceContext);
};

