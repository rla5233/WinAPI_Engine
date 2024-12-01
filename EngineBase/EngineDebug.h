#pragma once

namespace UEngineDebug
{
	#define LEAKCHECK _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

}