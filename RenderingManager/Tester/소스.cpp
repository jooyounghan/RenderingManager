#include "BufferManager.h"
#include "SRVOption.h"
#include "RTVOption.h"
#include "UAVOption.h"
#include "DSVOption.h"
#include "Texture2DInstance.h"
#include "VertexShader.h"
int main()
{
	VertexShader vs({});
	vs.CreateShader(L"", "", "", nullptr);

	BufferManager bufferManager;
	GUID guid =	bufferManager.RegisterConstantBuffer(nullptr, 0, 0, nullptr);

	return 0;
}