#include "TestLevel.h"

#include "ContentsHelper.h"
#include "ContactListener.h"
#include "Ground.h"
#include "Player.h"
#include "Box.h"
#include "Hook.h"

#include "ThirdParty/Box2d/include/box2d.h"

TestLevel::TestLevel()
{
	
}

TestLevel::~TestLevel()
{
	delete World;
	delete Contact;
}

void TestLevel::BeginPlay()
{
	ULevel::BeginPlay();

	FVector WinScale = ContentsHelper::GetWindowScale();
	
	// World Setting
	b2Vec2 gravity(0.0f, 20.0f);
	World = new b2World(gravity);
	

	Contact = new ContactListener();
	World->SetContactListener(Contact);
		
	// Player Spawn
	APlayer = SpawnActor<Player>();

	// GroundBox Spawn
	AllGround.push_back(SpawnActor<Ground>());
	AllGround[0]->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.8f });
	AllGround[0]->CreateBody();

	AllGround.push_back(SpawnActor<Ground>());
	AllGround[1]->SetActorLocation({ WinScale.hX() + WinScale.X * 0.7f, WinScale.Y * 0.8f });
	AllGround[1]->CreateBody();

	AllGround.push_back(SpawnActor<Ground>());
	AllGround[2]->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.2f });
	AllGround[2]->CreateBody();

	AllGround.push_back(SpawnActor<Ground>());
	AllGround[3]->SetActorLocation({ WinScale.hX() + WinScale.X * 0.7f, WinScale.Y * 0.2f });
	AllGround[3]->CreateBody();

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
	World->DestroyBody(APlayer->Body);
	APlayer->Destroy();

	if (nullptr != APlayer->AHook)
	{
		APlayer->AHook->Destroy();
		APlayer->AHook = nullptr;
	}

	APlayer = SpawnActor<Player>();
}
