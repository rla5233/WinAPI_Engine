#pragma once
#include <EngineCore/Level.h>

class b2World;
class Ground;
class Player;
class Box;

// Ό³Έν :
class TestLevel : public ULevel
{
public:
	// constructor destructor
	TestLevel();
	~TestLevel();
	
	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

	void ResetPlayer();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

public:
	b2World* World = nullptr;

	Player* APlayer = nullptr;

	Ground* GroundBox = nullptr;
	Box* ABox = nullptr;
};

