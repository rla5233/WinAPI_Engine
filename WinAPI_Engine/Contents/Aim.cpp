#include "Aim.h"

#include "TestLevel.h"
#include "Player.h"

#include <EngineCore/EngineCore.h>

Aim::Aim()
{
}

Aim::~Aim()
{
}

void Aim::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale({ 10.0f, 10.0f });

	StateChange(EAimState::Idle);
}

void Aim::IdleStart()
{

}

void Aim::Idle(float _DeltaTime)
{
	PosUpdate();

	if (UEngineInput::IsDown(VK_LBUTTON))
	{
		StateChange(EAimState::Hook);
	}
}

void Aim::PosUpdate()
{
	FVector MouseLocation = GEngine->MainWindow.GetMousePosition();
	SetActorLocation(MouseLocation);
}

void Aim::ShootStart()
{

}

void Aim::Shoot(float _DeltaTime)
{

}

void Aim::HookStart()
{
	TestLevel* world = dynamic_cast<TestLevel*>(GetWorld());
	if (nullptr != world)
	{
		world->GetPlayer()->StateChange(EPlayerState::Swing);
	}
}

void Aim::Hook(float _DeltaTime)
{


	if (UEngineInput::IsUp(VK_LBUTTON))
	{
		StateChange(EAimState::Idle);
	}
}

void Aim::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Aim::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EAimState::Idle:
		Idle(_DeltaTime);
		break;
	case EAimState::Shoot:

		break;
	case EAimState::Hook:
		Hook(_DeltaTime);
		break;
	}
}

void Aim::StateChange(EAimState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EAimState::Idle:
			IdleStart();
			break;
		case EAimState::Shoot:
			
			break;
		case EAimState::Hook:
			HookStart();
			break;
		}
	}
	
	State = _State;
}
