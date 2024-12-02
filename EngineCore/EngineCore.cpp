#include "PreCompile.h"
#include "EngineCore.h"

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::EngineInit(HINSTANCE _Inst)
{
	MainWindow.Init(_Inst);
	MainWindow.MessageRoop();
}
