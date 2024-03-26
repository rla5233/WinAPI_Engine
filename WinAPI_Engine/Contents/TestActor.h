#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class TestActor : public AActor
{
public:
	// constructor destructor
	TestActor();
	~TestActor();
	
	// delete Function
	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

