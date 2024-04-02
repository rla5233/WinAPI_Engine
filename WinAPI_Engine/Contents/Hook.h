#pragma once

#include <EngineCore/Actor.h>

enum class EHookState
{
	None,
	Shoot,
	Hook
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

	void StateChange(EHookState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

public:
	void HookStart();
	void Hooked(float _DeltaTime);

	void HookSetting();
	void JointSetting();

public:
	UCollision* Collision = nullptr;
	b2Body* Body = nullptr;
	b2DistanceJoint* Joint = nullptr;

	EHookState State = EHookState::None;
};
