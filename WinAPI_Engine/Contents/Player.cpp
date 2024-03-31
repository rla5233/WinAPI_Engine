#include "Player.h"

#include "Ground.h"
#include "Aim.h"
#include "ContentsHelper.h"

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

	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale({ 50.0f, 50.0f });

	MouseAim = GetWorld()->SpawnActor<Aim>();

	StateChange(EPlayerState::Idle);
}

void Player::IdleStart()
{
	
}

void Player::Idle(float _DeltaTime)
{
	GravityUpdate(_DeltaTime);
	InputCheck(_DeltaTime);
	PosUpdate(_DeltaTime);
}

void Player::SwingStart()
{
	HookPos = MouseAim->GetActorLocation();

	LopeLength = ContentsHelper::GetDistace(HookPos, GetActorLocation());
	FVector DirVec = (HookPos - GetActorLocation()).Normalize2DReturn();
	FindTheta(DirVec, FVector::Up);
	
	Velocity = FVector::Zero;
}

void Player::Swing(float _DeltaTime)
{
	//PosUpdate(_DeltaTime);

	//GravityUpdate(_DeltaTime);

	ThetaUpdate();
	SwingVelocityUpdate(_DeltaTime);
	SwingPosUpdate(_DeltaTime);

	if (UEngineInput::IsUp(VK_LBUTTON))
	{
		StateChange(EPlayerState::Idle);
	}
}

void Player::FindTheta(const FVector& _Vec1, const FVector& _Vec2)
{
	float DotProduct = (_Vec1.X * _Vec2.X) + (_Vec1.Y * _Vec2.Y);
	float Len_V1 = sqrtf(powf(_Vec1.X, 2) + powf(_Vec1.Y, 2));
	float Len_V2 = sqrtf(powf(_Vec2.X, 2) + powf(_Vec2.Y, 2));
	
	float CrossProduct = (_Vec1.X * _Vec2.Y) - (_Vec1.Y * _Vec2.X);
	FVector N = { 0.0f, 0.0f, -1.0f, 0.0f };


	if (0.0f <= CrossProduct * N.Z)
	{
		Theta = acosf(DotProduct / (Len_V1 * Len_V2));
	}
	else
	{
		Theta = UEngineMath::PI2 - acosf(DotProduct / (Len_V1 * Len_V2));
	}
	
	//Theta *= UEngineMath::RToD;
}

void Player::ThetaUpdate()
{
	FVector DirVec = (HookPos - GetActorLocation()).Normalize2DReturn();
	FindTheta(DirVec, FVector::Up);
}

void Player::SwingVelocityUpdate(float _DeltaTime)
{
	float Acc_X = 100.0f * sinf(Theta) * cosf(Theta);
	float Acc_Y = 100.0f * sinf(Theta) * sinf(Theta);
	Velocity += { Acc_X* _DeltaTime, Acc_Y* _DeltaTime, };


	std::string theta = "Theta : " + std::to_string(Theta * UEngineMath::RToD);
	std::string accX = "AccX : " + std::to_string(Acc_X);
	std::string accY = "AccY : " + std::to_string(Acc_Y);
	std::string velX = "VelX : " + std::to_string(Velocity.X);
	std::string velY = "VelY : " + std::to_string(Velocity.Y);

	UEngineDebug::DebugTextPrint(theta, 20.0f);
	UEngineDebug::DebugTextPrint(accX, 20.0f);
	UEngineDebug::DebugTextPrint(velX, 20.0f);
	UEngineDebug::DebugTextPrint(accY, 20.0f);
	UEngineDebug::DebugTextPrint(velY, 20.0f);
}

void Player::SwingPosUpdate(float _DeltaTime)
{
	AddActorLocation(Velocity * _DeltaTime);

	float Distance = ContentsHelper::GetDistace(GetActorLocation(), HookPos);
	if (LopeLength < Distance)
	{
		float Diff = Distance - LopeLength;
		FVector DirVec = (HookPos - GetActorLocation()).Normalize2DReturn();

		FVector DiffPos = DirVec *= Diff;
		AddActorLocation(DiffPos);
	}
}

void Player::InputCheck(float _DeltaTime)
{
	if (UEngineInput::IsPress('A'))
	{
		AddActorLocation({ -300.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('D'))
	{
		AddActorLocation({ 300.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		Velocity.Y = -500.0f;
	}
}

void Player::PosUpdate(float _DeltaTime)
{
	AddActorLocation(Velocity * _DeltaTime);
}

void Player::GravityUpdate(float _DeltaTime)
{
	FVector NextPos = Velocity * _DeltaTime;
	std::vector<UCollision*> CollVec;

	if (Collision->CollisionCheck(0, CollVec, NextPos))
	{
		for (UCollision* Coll : CollVec)
		{
			if (nullptr == Coll)
			{
				MsgBoxAssert("Coll is nullptr");
			}

			Ground* ground = dynamic_cast<Ground*>(Coll->GetOwner());
			if (nullptr != ground)
			{
				FVector CurPos = GetActorLocation();
				FVector GroundPos = ground->GetActorLocation();

				SetActorLocation({ CurPos.X, GroundPos.Y - Coll->GetTransform().GetScale().Y });
				Velocity = { 0.0f, 0.0f };
				return;
			}
		}		
	}	

	Velocity.Y += Gravity * _DeltaTime;
	if (Gravity < Velocity.Y)
	{
		Velocity.Y = Gravity;
	}
}

void Player::ChainAction(float _DeltaTime)
{
	AddActorLocation({ 300.0f * _DeltaTime, 0.0f });
	Velocity.Y = 0.0f;
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
