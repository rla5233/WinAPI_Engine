#pragma once

#include <EngineCore/Actor.h>

class b2Body;

// Ό³Έν :
class Ground : public AActor
{
public:
	// constructor destructor
	Ground();
	virtual ~Ground();
	
	// delete Function
	Ground(const Ground& _Other) = delete;
	Ground(Ground&& _Other) noexcept = delete;
	Ground& operator=(const Ground& _Other) = delete;
	Ground& operator=(Ground&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collision = nullptr;
	b2Body* Body = nullptr;
};