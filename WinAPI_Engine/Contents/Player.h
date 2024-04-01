#pragma once

#include <EngineCore/Actor.h>

enum class EPlayerState
{
	None,
	Idle,
	Swing
};

class Aim;

// Ό³Έν :
class Player : public AActor
{
public:
	// constructor destructor
	Player();
	~Player();
	
	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void GravityUpdate(float _DeltaTime);
	void InputCheck(float _DeltaTime);
	void PosUpdate(float _DeltaTime);

	void ChainAction(float _DeltaTime);

	void StateChange(EPlayerState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart();
	void Idle(float _DeltaTime);

	void SwingStart();
	void Swing(float _DeltaTime);

	void FindTheta(const FVector& _Vec1, const FVector& _Vec2);
	void ThetaUpdate();
	void SwingVelocityUpdate(float _DeltaTime);
	void SwingPosUpdate(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UCollision* Collision = nullptr;
	float Gravity = 500.0f;
	float Swing_G = 10000.0f;

	Aim* MouseAim = nullptr;
	FVector HookPos = FVector::Zero;
	float Theta = 0.0f;
	float Max_Theta = 0.0f;
	float RopeLength = 0.0f;

	FVector Velocity = { 0.0f , 0.0f };

	EPlayerState State = EPlayerState::None;
};

