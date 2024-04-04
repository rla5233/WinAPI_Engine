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
	BodyDef.type = b2_dynamicBody;		// 동적 객체로 설정 (중력의 영향을 받음)
	b2Vec2 pos = ContentsHelper::GetPosWorldtoBox(GetActorLocation());
	BodyDef.position.Set(pos.x, pos.y);	// 첫 번째 상자의 위치 (x는 -5, y는 5)
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	Body = Level->World->CreateBody(&BodyDef);
	Body->GetUserData().pointer = reinterpret_cast<unsigned __int64>(this);
	
	// Body Setting
	b2PolygonShape dynamicBody;
	FVector BoxScale = { 20.0f, 20.0f };
	b2Vec2 scale = ContentsHelper::GetScaleWorldtoBox(BoxScale);
	dynamicBody.SetAsBox(scale.x, scale.y);	 // 가로 10, 세로 10인 상자 생성
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBody;
	fixtureDef.density = 1.0f;			// 밀도 설정
	fixtureDef.friction = 0.0f;			// 마찰력 설정
	Body->CreateFixture(&fixtureDef);

	// Collision Setting
	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale(BoxScale);

	StateChange(EPlayerState::Falling);
	Dir = EPlayerDir::Right;
}

void Player::IdleStart()
{
	Body->SetLinearVelocity({ 0.0f, 0.0f });
}

void Player::Idle(float _DeltaTime)
{
	PosUpdate();
	CameraPosUpdate();
	ShootCheck();

	if (UEngineInput::IsPress('A') || UEngineInput::IsPress('D'))
	{
		StateChange(EPlayerState::Walking);
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayerState::Jump);
	}
}

void Player::WalkingStart()
{
	if (UEngineInput::IsPress('A'))
	{
		Dir = EPlayerDir::Left;
		Body->SetLinearVelocity({ -10.0f, 0.0f });
	}

	if (UEngineInput::IsPress('D'))
	{
		Dir = EPlayerDir::Right;
		Body->SetLinearVelocity({ 10.0f, 0.0f });
	}
}

void Player::Walking(float _DeltaTime)
{
	PosUpdate();
	CameraPosUpdate();
	WalkingFallCheck();
	ShootCheck();

	if (UEngineInput::IsUp('A') || UEngineInput::IsUp('D'))
	{
		StateChange(EPlayerState::Idle);
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayerState::Jump);
	}
}

void Player::WalkingFallCheck()
{
	if (0 == IsOnGroundValue)
	{
		StateChange(EPlayerState::Falling);
	}
}

void Player::JumpStart()
{
	Body->ApplyLinearImpulseToCenter({ 0.0f, -8.0f }, true);
}

void Player::Jump(float _DeltaTime)
{
	PosUpdate();
	CameraPosUpdate();
	JumpMoveCheck();
	ShootCheck();

	if (0.0f <= Body->GetLinearVelocity().y)
	{
		StateChange(EPlayerState::Falling);
	}
}

void Player::JumpMoveCheck()
{
	if (UEngineInput::IsPress('A'))
	{
		b2Vec2 CurVec = Body->GetLinearVelocity();
		Body->SetLinearVelocity({ -10.0f, CurVec.y });
	}

	if (UEngineInput::IsUp('A'))
	{
		b2Vec2 CurVec = Body->GetLinearVelocity();
		Body->SetLinearVelocity({ 0.0f, CurVec.y });
	}

	if (UEngineInput::IsPress('D'))
	{
		b2Vec2 CurVec = Body->GetLinearVelocity();
		Body->SetLinearVelocity({ 10.0f, CurVec.y });
	}

	if (UEngineInput::IsUp('D'))
	{
		b2Vec2 CurVec = Body->GetLinearVelocity();
		Body->SetLinearVelocity({ 0.0f, CurVec.y });
	}
}

void Player::ShootCheck()
{
	if (UEngineInput::IsDown(VK_LBUTTON))
	{
		StateChange(EPlayerState::Shoot);
	}
}

void Player::ShootStart()
{
	AHook = GetWorld()->SpawnActor<Hook>();
}

void Player::Shoot(float _DeltaTime)
{
	PosUpdate();
	CameraPosUpdate();
}


void Player::SwingStart()
{
}

void Player::Swing(float _DeltaTime)
{
	SwingMoveCheck();
	MaxSpeedCheck();
	PosUpdate();
	CameraPosUpdate();

	if (UEngineInput::IsUp(VK_LBUTTON))
	{
		StateChange(EPlayerState::Falling);
	}
}

void Player::MaxSpeedCheck()
{
	float CurSpeed = Body->GetLinearVelocity().Length();
	if (MaxSpeed < CurSpeed)
	{
		float Ratio = MaxSpeed / CurSpeed;
		b2Vec2 NewVelocity = Ratio * Body->GetLinearVelocity();
		Body->SetLinearVelocity(NewVelocity);
	}
}

void Player::SwingMoveCheck()
{
	if (UEngineInput::IsDown(VK_SHIFT))
	{
		bool isclock = false;
		if (UEngineInput::IsPress('A'))
		{
			isclock = true;
			Dir = EPlayerDir::Left;
		}

		if (UEngineInput::IsPress('D'))
		{
			isclock = false;
			Dir = EPlayerDir::Right;
		}

		b2Vec2 HookPos = AHook->Body->GetPosition();
		b2Vec2 PlayerPos = Body->GetPosition();
		b2Vec2 DirVec = GetClockVec(PlayerPos - HookPos, isclock);
		DirVec *= 1.0f;
		Body->ApplyLinearImpulseToCenter(DirVec, true);
	}

	if (UEngineInput::IsPress('A'))
	{
		b2Vec2 HookPos = AHook->Body->GetPosition();
		b2Vec2 PlayerPos = Body->GetPosition();
		b2Vec2 DirVec = GetClockVec(PlayerPos - HookPos, true);
		DirVec *= 0.008f;
		Body->ApplyLinearImpulseToCenter(DirVec, true);
	}

	if (UEngineInput::IsPress('D'))
	{
		b2Vec2 HookPos = AHook->Body->GetPosition();
		b2Vec2 PlayerPos = Body->GetPosition();
		b2Vec2 DirVec = GetClockVec(PlayerPos - HookPos, false);
		DirVec *= 0.008f;
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

void Player::FlyStart()
{
}

void Player::Flying(float _DeltaTime)
{
}

void Player::FallingStart()
{

}

void Player::Falling(float _DeltaTime)
{
	FallingSpeedDown();
	FallingMoveCheck();
	MaxSpeedCheck();
	OnGroundCheck();
	PosUpdate();
	CameraPosUpdate();
	ShootCheck();
}

void Player::FallingSpeedDown()
{
	b2Vec2 CurVel = Body->GetLinearVelocity();

	if (0.0f > CurVel.y)
	{
		CurVel.y *= 0.9f;
	}

	if (0.0f <= abs(CurVel.x))
	{
		if (0.0f < CurVel.x)
		{
			CurVel.x -= 1.0f;
			if (0.0f > CurVel.x)
			{
				CurVel.x = 0.0f;
			}

			Body->SetLinearVelocity(CurVel);
			return;
		}

		if (0.0f > CurVel.x)
		{
			CurVel.x += 1.0f;
			if (0.0f < CurVel.x)
			{
				CurVel.x = 0.0f;
			}

			Body->SetLinearVelocity(CurVel);
			return;
		}
	}
}

void Player::FallingMoveCheck()
{
	if (UEngineInput::IsPress('A'))
	{
		b2Vec2 CurVec = Body->GetLinearVelocity();
		if (0.0f >= CurVec.x && -10.0f <= CurVec.x )
		{
			Body->SetLinearVelocity({ -10.0f, CurVec.y });
		}
	}

	if (UEngineInput::IsPress('D'))
	{
		b2Vec2 CurVec = Body->GetLinearVelocity();
		if (0.0f <= CurVec.x && 10.0f >= CurVec.x)
		{
			Body->SetLinearVelocity({ 10.0f, CurVec.y });
		}
	}
}

void Player::OnGroundCheck()
{
	if (0 < IsOnGroundValue)
	{
		StateChange(EPlayerState::Idle);
	}
}

void Player::PosUpdate()
{
	FVector Pos = ContentsHelper::GetPosBoxtoWorld(Body->GetPosition());
	SetActorLocation(Pos);
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
	b2Vec2 Pos = Body->GetPosition();
	std::string VelX = "V.x : " + std::to_string(Vel.x);
	std::string VelY = "V.y : " + std::to_string(Vel.y);
	std::string speed = "Speed : " + std::to_string(Vel.Length());
	std::string PosX = "Pos.x : " + std::to_string(Pos.x);
	std::string PosY = "Pos.y : " + std::to_string(Pos.y);
	std::string state = "None";
	std::string dir = "";
	std::string friction = "Friction : " + std::to_string(Body->GetFixtureList()->GetFriction());
	std::string ground = "Ground : " + std::to_string(IsOnGroundValue);

	switch (State)
	{
	case EPlayerState::Idle:
		state = "Idle";
		break;
	case EPlayerState::Walking:
		state = "Walking";
		break;
	case EPlayerState::Jump:
		state = "Jump";
		break;
	case EPlayerState::Run:
		state = "Run";
		break;
	case EPlayerState::Shoot:
		state = "Shoot";
		break;
	case EPlayerState::Swing:
		state = "Swing";
		break;
	case EPlayerState::Falling:
		state = "Falling";
		break;
	}
	switch (Dir)
	{
	case EPlayerDir::Left:
		dir += "Left";
		break;
	case EPlayerDir::Right:
		dir += "Right";
		break;
	}

	UEngineDebug::DebugTextPrint("[Player Body]", 20);
	UEngineDebug::DebugTextPrint(VelX, 20);
	UEngineDebug::DebugTextPrint(VelY, 20);
	UEngineDebug::DebugTextPrint(speed, 20);
	UEngineDebug::DebugTextPrint(PosX, 20);
	UEngineDebug::DebugTextPrint(PosY, 20);
	UEngineDebug::DebugTextPrint(state, 20);
	UEngineDebug::DebugTextPrint(dir, 20);
	UEngineDebug::DebugTextPrint(friction, 20);
	UEngineDebug::DebugTextPrint(ground, 20);
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
	case EPlayerState::Walking:
		Walking(_DeltaTime);
		break;
	case EPlayerState::Jump:
		Jump(_DeltaTime);
		break;
	case EPlayerState::Run:
		break;
	case EPlayerState::Shoot:
		Shoot(_DeltaTime);
		break;
	case EPlayerState::Swing:
		Swing(_DeltaTime);
		break;
	case EPlayerState::Falling:
		Falling(_DeltaTime);
		break;
	}
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
		case EPlayerState::Walking:
			WalkingStart();
			break;
		case EPlayerState::Jump:
			JumpStart();
			break;
		case EPlayerState::Run:
			break;
		case EPlayerState::Shoot:
			ShootStart();
			break;
		case EPlayerState::Swing:
			SwingStart();
			break;
		case EPlayerState::Falling:
			FallingStart();
			break;
		}
	}

	State = _State;
}
