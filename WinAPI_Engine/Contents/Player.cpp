#include "Player.h"

#include "ContentsHelper.h"
#include "TestLevel.h"
#include "Hook.h"
#include "ThirdParty/Box2d/include/box2d.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineDebug.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	AActor::BeginPlay();

	// Actor Setting
	FVector WinScale = ContentsHelper::GetWindowScale();
	SetActorLocation(WinScale.Half2D());
	
	// Body Create
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;										// 동적 객체로 설정 (중력의 영향을 받음)
	BodyDef.position.Set(GetActorLocation().X / 30.0f, GetActorLocation().Y / 30.0f);	// 첫 번째 상자의 위치 (x는 -5, y는 5)
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	Body = Level->World->CreateBody(&BodyDef);

	// Body Setting
	b2PolygonShape dynamicBody;
	FVector BoxScale = { 10.0f, 10.0f };
	dynamicBody.SetAsBox((BoxScale.X * 0.5f) / 30.0f, (BoxScale.Y * 0.5f) / 30.0f);	 // 가로 10, 세로 10인 상자 생성
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBody;
	fixtureDef.density = 1.0f;			// 밀도 설정
	fixtureDef.friction = 0.3f;		// 마찰력 설정
	Body->CreateFixture(&fixtureDef);

	// Collision Setting
	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale(BoxScale);

	StateChange(EPlayerState::Idle);
}

void Player::IdleStart()
{
}

void Player::Idle(float _DeltaTime)
{
	MoveCheck();
	PosUpdate();
	CameraPosUpdate();

	if (UEngineInput::IsPress(VK_LBUTTON))
	{
		StateChange(EPlayerState::Swing);
	}
}

void Player::SwingStart()
{
	AHook = GetWorld()->SpawnActor<Hook>();
}

void Player::Swing(float _DeltaTime)
{
	PosUpdate();
	SwingMoveCheck();
	CameraPosUpdate();

	if (UEngineInput::IsUp(VK_LBUTTON))
	{
		StateChange(EPlayerState::Idle);
	}
}

void Player::SwingMoveCheck()
{
	if (UEngineInput::IsDown(VK_SHIFT))
	{
		b2Vec2 HookPos = AHook->Body->GetPosition();
		b2Vec2 PlayerPos = Body->GetPosition();
		b2Vec2 DirVec = GetClockVec(PlayerPos - HookPos, false);
		DirVec *= 0.3f;
		Body->ApplyLinearImpulseToCenter(DirVec, true);
	}

	if (UEngineInput::IsPress('A'))
	{
		b2Vec2 HookPos = AHook->Body->GetPosition();
		b2Vec2 PlayerPos = Body->GetPosition();
		b2Vec2 DirVec = GetClockVec(PlayerPos - HookPos, true);
		DirVec *= 0.004f;
		Body->ApplyLinearImpulseToCenter(DirVec, true);
	}

	if (UEngineInput::IsPress('D'))
	{
		b2Vec2 HookPos = AHook->Body->GetPosition();
		b2Vec2 PlayerPos = Body->GetPosition();
		b2Vec2 DirVec = GetClockVec(PlayerPos - HookPos, false);
		DirVec *= 0.004f;
		Body->ApplyLinearImpulseToCenter(DirVec, true);
	}
}

b2Vec2 Player::GetClockVec(const b2Vec2& _Vec, bool _IsClock)
{
	b2Vec3 Norm = { 0.0f, 0.0f, 1.0f };
	b2Vec3 HtoP = { _Vec.x, _Vec.y, 0.0f };

	b2Vec3 Result = { 0.0f, 0.0f, 0.0f };
	Result.x = { (HtoP.y * Norm.z) - (HtoP.z * Norm.y) };
	Result.y = { (HtoP.z * Norm.x) - (HtoP.x * Norm.z) };
	Result.z = { (HtoP.x * Norm.y) - (HtoP.y * Norm.x) };

	if (true == _IsClock)
	{
		Result *= -1;
	}

	return { Result.x, Result.y };
}

void Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Player::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayerState::Swing:
		Swing(_DeltaTime);
		break;
	}
}

void Player::MoveCheck()
{
	if (UEngineInput::IsPress('A'))
	{
		Body->ApplyLinearImpulseToCenter({ -0.05f, 0.0f }, true);
	}

	if (UEngineInput::IsPress('D'))
	{
		Body->ApplyLinearImpulseToCenter({ 0.05f, 0.0f }, true);
	}

	if (UEngineInput::IsUp('A') || UEngineInput::IsUp('D'))
	{
		b2Vec2 CurVel = Body->GetLinearVelocity();
		CurVel.x = 0.0f;
		Body->SetLinearVelocity(CurVel);
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		//b2Vec2 CurVel = Body->GetLinearVelocity();
		//CurVel.y = -1.0f;
		Body->ApplyLinearImpulseToCenter({ 0.0f, -1.0f }, true);
	}
}

void Player::PosUpdate()
{
	float X = Body->GetPosition().x;
	float Y = Body->GetPosition().y;
	SetActorLocation({ X * 30.0f, Y * 30.0f });

	DebugUpdate();
}

void Player::CameraPosUpdate()
{
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector CurPos = GetActorLocation();

	Level->SetCameraPos({ CurPos.X - WinScale.hX(), 0.0f});
}

void Player::DebugUpdate()
{
	b2Vec2 Vel = Body->GetLinearVelocity();
	std::string VelX = "V.x : " + std::to_string(Vel.x);
	std::string VelY = "V.y : " + std::to_string(Vel.y);

	UEngineDebug::DebugTextPrint("[Player Body]", 20);
	UEngineDebug::DebugTextPrint(VelX, 20);
	UEngineDebug::DebugTextPrint(VelY, 20);


}

void Player::StateChange(EPlayerState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayerState::Idle:
			IdleStart();
			break;
		case EPlayerState::Swing:
			SwingStart();
			break;
		}
	}

	State = _State;
}
