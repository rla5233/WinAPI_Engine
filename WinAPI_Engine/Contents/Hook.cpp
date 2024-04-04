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

	StateChange(EHookState::Shoot);
}

void Hook::ShootStart()
{
	HookSetting();
	HookShoot();
}

void Hook::Shooting(float _DeltaTime)
{
	PosUpdate();

	if (true == IsHooked)
	{
		StateChange(EHookState::Hooked);
	}	

	HookReturnCheck();
}

void Hook::HookSetting()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());

	// Actor Setting
	FVector PlayerPos = Level->APlayer->GetActorLocation();
	SetActorLocation(PlayerPos);

	// ShootVec Setting
	ShootDir = GEngine->MainWindow.GetMousePosition();
	ShootDir += Level->GetCameraPos();
	ShootDir -= PlayerPos;
	ShootDir.Normalize2D();

	// Body Create
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	BodyDef.gravityScale = 0.0f;
	b2Vec2 pos = ContentsHelper::GetPosWorldtoBox(GetActorLocation());
	BodyDef.position.Set(pos.x, pos.y);
	Body = Level->World->CreateBody(&BodyDef);
	Body->GetUserData().pointer = reinterpret_cast<unsigned __int64>(this);
		
	// Body Setting
	b2PolygonShape dynamicBox;
	FVector BoxScale = { 10.0f, 10.0f };
	dynamicBox.SetAsBox((BoxScale.X * 0.5f) / 30.0f, (BoxScale.Y * 0.5f) / 30.0f);	 // 가로 10, 세로 10인 상자 생성
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;		// 밀도 설정
	fixtureDef.friction = 0.0f;		// 마찰력 설정
	Body->CreateFixture(&fixtureDef);

	// Collision Setting
	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale(BoxScale);
}

void Hook::HookShoot()
{
	b2Vec2 Dir = ContentsHelper::FVectortob2Vec2(ShootDir);
	Body->SetLinearVelocity({ Dir.x * ShootSpeed, Dir.y * ShootSpeed });
}

void Hook::HookReturnCheck()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	FVector PlayerPos = Level->APlayer->GetActorLocation();

	float Diff = ContentsHelper::GetDistace(GetActorLocation(), PlayerPos);
	if (MaxLength < Diff)
	{
		StateChange(EHookState::Return);
	}
}

void Hook::ReturnStart()
{
	HookVelChange();
	Body->GetFixtureList()->SetSensor(false);
}

void Hook::Return(float _DeltaTime)
{
	ReturnVelUpdate();
	PosUpdate();
	ReturnEndCheck();
}

void Hook::HookVelChange()
{
	b2Vec2 CurVel = Body->GetLinearVelocity();
	CurVel *= -1;
	Body->SetLinearVelocity(CurVel);
}

void Hook::ReturnVelUpdate()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	FVector PlayerPos = Level->APlayer->GetActorLocation();
	FVector Dir = PlayerPos - GetActorLocation();
	b2Vec2 dir = ContentsHelper::FVectortob2Vec2(Dir);
	dir.Normalize();
	b2Vec2 CurVel = Body->GetLinearVelocity();
	Body->SetLinearVelocity({ dir.x * CurVel.Length(), dir.y * CurVel.Length() });
}

void Hook::ReturnEndCheck()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	FVector PlayerPos = Level->APlayer->GetActorLocation();

	float Diff = ContentsHelper::GetDistace(GetActorLocation(), PlayerPos);
	if (MinLength > Diff)
	{
		HookRelease();
		Level->APlayer->StateChange(EPlayerState::Idle);
	}
}

void Hook::HookedStart()
{
	Body->SetLinearVelocity({ 0.0f, 0.0f });
	HookedPos = ContentsHelper::b2Vec2toFVector(Body->GetPosition());
	JointSetting();	
}

void Hook::Hooked(float _DeltaTime)
{
	HookedPosUpdate();
	HookedEndCheck();
}

void Hook::HookedEndCheck()
{
	if (UEngineInput::IsUp(VK_LBUTTON))
	{
		HookRelease();
	}
}

void Hook::JointSetting()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	Level->APlayer->StateChange(EPlayerState::Swing);

	b2DistanceJointDef jointDef;
	jointDef.Initialize(Body, Level->APlayer->Body, Body->GetPosition(), Level->APlayer->Body->GetPosition());
	//jointDef.minLength = 0.0f;
	//jointDef.maxLength = 1.0f;
	jointDef.collideConnected = true;	
	Joint = (b2DistanceJoint*)Level->World->CreateJoint(&jointDef);
}

void Hook::HookedPosUpdate()
{
	Body->SetLinearVelocity({ 0.0f, 0.0f });
	b2Vec2 Pos = ContentsHelper::FVectortob2Vec2(HookedPos);
	Body->SetTransform(Pos, 0.0f);
	PosUpdate();
}

void Hook::PosUpdate()
{
	FVector Pos = ContentsHelper::GetPosBoxtoWorld(Body->GetPosition());
	SetActorLocation(Pos);
}

void Hook::HookRelease()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());

	if (nullptr != Joint)
	{
		Level->World->DestroyJoint(Joint);
		Joint = nullptr;
	}

	Level->World->DestroyBody(Body);
	Body = nullptr;

	Collision->Destroy();
	Collision = nullptr;

	StateChange(EHookState::None);
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
		Shooting(_DeltaTime);
		break;
	case EHookState::Return:
		Return(_DeltaTime);
		break;
	case EHookState::Hooked:
		Hooked(_DeltaTime);
		break;
	}
}

void Hook::StateChange(EHookState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EHookState::Shoot:
			ShootStart();
			break;
		case EHookState::Return:
			ReturnStart();
			break;
		case EHookState::Hooked:
			HookedStart();
			break;
		}
	}

	State = _State;
}