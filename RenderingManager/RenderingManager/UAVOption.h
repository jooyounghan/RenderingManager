#pragma once
#include "ITextureOption.h"

class UAVOption : public ITextureOption
{
public:
	UAVOption() = default;

protected:
	constexpr static D3D11_BIND_FLAG GetBindFlag()
	{
		return D3D11_BIND_UNORDERED_ACCESS;
	}

protected:
	virtual void InitializeByOption(ID3D11Resource* resource, ID3D11Device* device) override;

protected:
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_uav;

public:
	ID3D11UnorderedAccessView* GetUAV() const { return m_uav.Get(); }
};