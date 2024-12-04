#include "BufferManager.h"
#include "SRVOption.h"
#include "RTVOption.h"
#include "UAVOption.h"
#include "DSVOption.h"
#include <Texture2DInstance.h>

int main()
{
	Texture2DInstance<SRVOption, RTVOption, UAVOption, DSVOption> test(nullptr);
	D3D11_BIND_FLAG t = test.GetBindFlags();

	BufferManager bufferManager;
	GUID guid =	bufferManager.RegisterConstantBuffer(nullptr, 0, 0, nullptr);

	return 0;
}