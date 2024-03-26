#include "ContentsCore.h"

#include <EngineBase/EngineDirectory.h>

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::BeginPlay()
{
	UEngineCore::BeginPlay();

	MainWindow.SetClearColor(Color8Bit(2, 2, 27, 255));
	MainWindow.SetWindowScale({ 1920, 1080 });
	SetFrame(60);

	//CreateLevel<Opening>("Opening");
	//ChangeLevel("Opening");
}

void UContentsCore::WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath)
{
	_OutWindowTitle = "Title";
}
