#pragma once

#include <EngineCore/Actor.h>

class b2Body;

// Ό³Έν :
class Chain : public AActor
{
public:
	// constrcuter destructer
	Chain();
	~Chain();

	// delete Function
	Chain(const Chain& _Other) = delete;
	Chain(Chain&& _Other) noexcept = delete;
	Chain& operator=(const Chain& _Other) = delete;
	Chain& operator=(Chain&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collision = nullptr;
	b2Body* Body = nullptr;

};

