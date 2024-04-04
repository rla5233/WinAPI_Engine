#pragma once

#include <EngineCore/Actor.h>

enum class EHookState
{
	None,
	Shoot,
	Return,
	Hooked
};

class b2Body;
class b2DistanceJoint;

// Ό³Έν :
class Hook : public AActor
{
public:
	// constructor destructor
	Hook();
	~Hook();

	// delete Function
	Hook(const Hook& _Other) = delete;
	Hook(Hook&& _Other) noexcept = delete;
	Hook& operator=(const Hook& _Other) = delete;
	Hook& operator=(Hook&& _Other) noexcept = delete;

	void PosUpdate();
	void StateChange(EHookState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

private:
	void ShootStart();
	void Shooting(float _DeltaTime);
	void HookSetting();
	void HookShoot();
	void HookReturnCheck();

	FVector ShootDir = FVector::Zero;
	float ShootSpeed = 20.0f;
	float MaxLength = 200.0f;

private:
	void ReturnStart();
	void Return(float _DeltaTime);
	void HookVelChange();
	void ReturnEndCheck();

	float MinLength = 20.0f;

private:
	void HookedStart();
	void Hooked(float _DeltaTime);
	void HookedEndCheck();
	void HookRelease();

	void JointSetting();

public:
	UCollision* Collision = nullptr;
	b2Body* Body = nullptr;
	b2DistanceJoint* Joint = nullptr;

	EHookState State = EHookState::None;
};
