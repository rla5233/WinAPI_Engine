#include "ContentsCore.h"

#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

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

	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Res");
	std::list<UEngineFile> NewList = Dir.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : NewList)
	{
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	}

	CreateLevel<TestLevel>("TestLevel");
	ChangeLevel("TestLevel");
}

void UContentsCore::WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath)
{
	_OutWindowTitle = "Title";
}
