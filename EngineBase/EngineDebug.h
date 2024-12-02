#pragma once

namespace UEngineDebug
{
	#define LEAKCHECK _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	#define MsgBoxAssert(_ErrorText) { \
	std::wstring ErrorText = std::wstring(_ErrorText); \
	MessageBoxW(nullptr, ErrorText.c_str(), L"Fatal Error", MB_OK); \
	assert(false); }



}