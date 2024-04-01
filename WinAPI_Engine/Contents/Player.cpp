#include "Player.h"

#include "ContentsHelper.h"
#include "TestLevel.h"
#include "ThirdParty/Box2d/include/box2d.h"

#include <EnginePlatform/EngineInput.h>

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
	b2BodyDef box1BodyDef;
	box1BodyDef.type = b2_dynamicBody;										// 동적 객체로 설정 (중력의 영향을 받음)
	box1BodyDef.position.Set(GetActorLocation().X, GetActorLocation().Y);	// 첫 번째 상자의 위치 (x는 -5, y는 5)
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	Body = Level->World->CreateBody(&box1BodyDef);

	// Body Setting
	b2PolygonShape dynamicBox1;
	FVector BoxScale = { 10.0f, 10.0f };
	dynamicBox1.SetAsBox(BoxScale.X * 0.5f, BoxScale.Y * 0.5f);	 // 가로 10, 세로 10인 상자 생성
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &dynamicBox1;
	fixtureDef1.density = 1.0f;			// 밀도 설정
	fixtureDef1.friction = 0.3f;		// 마찰력 설정
	Body->CreateFixture(&fixtureDef1);

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
		break;
	}
}

void Player::MoveCheck()
{
	if (UEngineInput::IsPress('A'))
	{
		b2Vec2 CurVel = Body->GetLinearVelocity();
		CurVel.x = -100.0f;
		Body->SetLinearVelocity(CurVel);
	}

	if (UEngineInput::IsPress('D'))
	{
		b2Vec2 CurVel = Body->GetLinearVelocity();
		CurVel.x = 100.0f;
		Body->SetLinearVelocity(CurVel);
	}

	float X = Body->GetPosition().x;
	float Y = Body->GetPosition().y;
	SetActorLocation({ X, Y });
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
			break;
		}
	}

	State = _State;
}
