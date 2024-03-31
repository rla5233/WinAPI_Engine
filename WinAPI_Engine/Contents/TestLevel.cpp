#include "TestLevel.h"

#include "ContentsHelper.h"
#include "Ground.h"
#include "Player.h"
#include "Box.h"

TestLevel::TestLevel()
{
	
}

TestLevel::~TestLevel()
{
}

void TestLevel::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	GroundBox = SpawnActor<Ground>();
	GroundBox->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.9f });

	ABox = SpawnActor<Box>();
	ABox->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.4f });

	APlayer = SpawnActor<Player>();
	APlayer->SetActorLocation({ WinScale.X * 0.25f, WinScale.Y * 0.5f });

	GEngine->EngineDebugSwitch();
}

void TestLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('P'))
	{
		GEngine->EngineDebugSwitch();
	}

	if (UEngineInput::IsDown('R'))
	{
		ResetPlayer();
	}
}

void TestLevel::ResetPlayer()
{
	APlayer->Destroy();

	FVector WinScale = ContentsHelper::GetWindowScale();
	APlayer = SpawnActor<Player>();
	APlayer->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.5f });
}
