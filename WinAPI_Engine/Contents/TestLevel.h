#pragma once
#include <EngineCore/Level.h>

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

	Player* GetPlayer() const
	{
		return APlayer;
	}

	void ResetPlayer();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	Ground* GroundBox = nullptr;
	Player* APlayer = nullptr;
	Box* ABox = nullptr;
};

