#include "Hook.h"

#include "ContentsHelper.h"
#include "ThirdParty/Box2d/include/box2d.h"
#include "TestLevel.h"

#include "Player.h"

#include <EnginePlatform/EngineInput.h>


Hook::Hook()
{
}

Hook::~Hook()
{
}

void Hook::BeginPlay()
{
	AActor::BeginPlay();

	StateChange(EHookState::Hook);
}

void Hook::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Hook::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EHookState::Shoot:
		break;
	case EHookState::Hook:
		Hooked(_DeltaTime);
		break;
	}
}

void Hook::HookStart()
{
	HookSetting();
	JointSetting();
}

void Hook::Hooked(float _DeltaTime)
{




	if (UEngineInput::IsUp(VK_LBUTTON))
	{
		TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
		Level->World->DestroyJoint(Joint);
		Joint = nullptr;

		Level->World->DestroyBody(Body);
		Body = nullptr;

		Collision->Destroy();
		Collision = nullptr;

		StateChange(EHookState::None);
	}
}

void Hook::HookSetting()
{
	// Actor Setting
	FVector MousePos = GEngine->MainWindow.GetMousePosition();
	SetActorLocation(MousePos);

	// Body Create
	b2BodyDef BodyDef;
	BodyDef.type = b2_staticBody;										// 정적 객체로 설정 (중력의 영향을 받음)
	BodyDef.position.Set(GetActorLocation().X / 30.0f, GetActorLocation().Y / 30.0f);	// 첫 번째 상자의 위치 (x는 -5, y는 5)
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	Body = Level->World->CreateBody(&BodyDef);

	// Body Setting
	b2PolygonShape dynamicBox;
	FVector BoxScale = { 10.0f, 10.0f };
	dynamicBox.SetAsBox((BoxScale.X * 0.5f) / 30.0f, (BoxScale.Y * 0.5f) / 30.0f);	 // 가로 10, 세로 10인 상자 생성
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;			// 밀도 설정
	fixtureDef.friction = 0.3f;		// 마찰력 설정
	Body->CreateFixture(&fixtureDef);

	// Collision Setting
	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale(BoxScale);
}

void Hook::JointSetting()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());

	b2DistanceJointDef jointDef;
	jointDef.Initialize(Body, Level->APlayer->Body, Body->GetPosition(), Level->APlayer->Body->GetPosition());
	//jointDef.minLength = 0.0f;
	jointDef.collideConnected = true;	
	Joint = (b2DistanceJoint*)Level->World->CreateJoint(&jointDef);
}

void Hook::StateChange(EHookState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EHookState::Shoot:
			break;
		case EHookState::Hook:
			HookStart();
			break;
		}
	}

	State = _State;
}