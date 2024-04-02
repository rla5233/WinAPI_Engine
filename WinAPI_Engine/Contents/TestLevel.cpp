#include "TestLevel.h"

#include "ContentsHelper.h"
#include "Ground.h"
#include "Player.h"
#include "Box.h"

#include "ThirdParty/Box2d/include/box2d.h"

TestLevel::TestLevel()
{
	
}

TestLevel::~TestLevel()
{
	delete World;
}

void TestLevel::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	
	// World Setting
	b2Vec2 gravity(0.0f, 20.0f);
	World = new b2World(gravity);
		
	// Player Spawn
	APlayer = SpawnActor<Player>();

	// GroundBox Spawn
	GroundBox = SpawnActor<Ground>();

	GEngine->EngineDebugSwitch();
}

void TestLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	World->Step(_DeltaTime, 6, 2);

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
}
