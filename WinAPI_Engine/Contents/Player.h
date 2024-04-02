#pragma once

#include <EngineCore/Actor.h>

enum class EPlayerState
{
	None,
	Idle,
	Swing
};

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
	void MoveCheck();
	void PosUpdate();

	void StateChange(EPlayerState _State);

public:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

public:
	void IdleStart();
	void Idle(float _DeltaTime);

public:
	void SwingStart();
	void Swing(float _DeltaTime);
	
	void SwingMoveCheck();

public:
	UCollision* Collision = nullptr;
	b2Body* Body = nullptr;

	Hook* AHook = nullptr;

	EPlayerState State = EPlayerState::None;
};