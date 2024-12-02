#include "PreCompile.h"
#include "EngineCore.h"

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	LEAKCHECK;

	MainWindow.Init(_Inst);

	MainWindow.MessageRoop();
}
