#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class Box : public AActor
{
public:
	// constructor destructor
	Box();
	~Box();
	
	// delete Function
	Box(const Box& _Other) = delete;
	Box(Box&& _Other) noexcept = delete;
	Box& operator=(const Box& _Other) = delete;
	Box& operator=(Box&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collision = nullptr;

};

