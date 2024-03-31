#pragma once

#include "EngineCore/Actor.h"

class Player;

enum class EAimState
{
	None,
	Idle,
	Shoot,
	Hook
};

// Ό³Έν :
class Aim : public AActor
{
	friend Player;

public:
	// constructor destructor
	Aim();
	~Aim();
	
	// delete Function
	Aim(const Aim& _Other) = delete;
	Aim(Aim&& _Other) noexcept = delete;
	Aim& operator=(const Aim& _Other) = delete;
	Aim& operator=(Aim&& _Other) noexcept = delete;

	void PosUpdate();

	void StateChange(EAimState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart();
	void Idle(float _DeltaTime);

	void ShootStart();
	void Shoot(float _DeltaTime);

	void HookStart();
	void Hook(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UCollision* Collision = nullptr;

	EAimState State = EAimState::None;
};

