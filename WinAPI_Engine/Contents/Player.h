#pragma once

#include <EngineCore/Actor.h>

enum class EPlayerState
{
	None,
	Idle,
	Walking,
	Jump,
	Run,
	Shoot,
	Swing,
	Falling,
};

enum class EPlayerDir
{
	None,
	Left,
	Right
};

struct b2Vec2;
class b2Body;
class Hook;

// Ό³Έν :
class Player : public AActor
{
public:
	// constructor destructor
	Player();
	virtual ~Player();
	
	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

public:
	void PosUpdate();
	void CameraPosUpdate();
	void DebugUpdate();

	void StateChange(EPlayerState _State);

public:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

public:
	void IdleStart();
	void Idle(float _DeltaTime);

public:
	void JumpStart();
	void Jump(float _DeltaTime);
	void JumpMoveCheck();

public:
	void WalkingStart();
	void Walking(float _DeltaTime);
	void FallCheck();

public:
	void SwingStart();
	void Swing(float _DeltaTime);
	void MaxSpeedCheck();
	void SwingMoveCheck();

	b2Vec2 GetClockVec(const b2Vec2& _Vec, bool _IsClock);

public:
	void FallingStart();
	void Falling(float _DeltaTime);
	void FallingSpeedDown();
	void FallingMoveCheck();
	void OnGroundCheck();

public:
	UCollision* Collision = nullptr;
	b2Body* Body = nullptr;
	float MaxSpeed = 50.0f;

	Hook* AHook = nullptr;

	int IsOnGroundValue = false;
	EPlayerDir Dir = EPlayerDir::None;
	EPlayerState State = EPlayerState::None;
};