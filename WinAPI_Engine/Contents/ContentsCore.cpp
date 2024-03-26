#include "ContentsCore.h"

#include <EngineBase/EngineDirectory.h>

#include "TestLevel.h"

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::BeginPlay()
{
	UEngineCore::BeginPlay();

	MainWindow.SetWindowScale({ 1280, 720 });
	SetFrame(60);

	CreateLevel<TestLevel>("TestLevel");
	ChangeLevel("TestLevel");
}

void UContentsCore::WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath)
{
	_OutWindowTitle = "Title";
}
