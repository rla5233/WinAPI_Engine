#pragma once
#include <EngineCore\EngineCore.h>

struct b2Vec2;

// Ό³Έν :
class ContentsHelper
{
public:
	static FVector GetWindowScale();
	static float GetDistace(const FVector& _Pos1, const FVector& _Pos2);
	static float GetVecSize(const FVector& _Vec);

	static FVector b2Vec2toFVector(const b2Vec2& _Vec);
	static b2Vec2 FVectortob2Vec2(const FVector& _Vec);

	static FVector GetPosBoxtoWorld(const b2Vec2& _Vec);
	static b2Vec2 GetPosWorldtoBox(const FVector& _Vec);

	static FVector GetScaleBoxtoWorld(const b2Vec2& _Vec);
	static b2Vec2 GetScaleWorldtoBox(const FVector& _Vec);

public:
	// constructor destructor
	ContentsHelper();
	~ContentsHelper();
	
	// delete Function
	ContentsHelper(const ContentsHelper& _Other) = delete;
	ContentsHelper(ContentsHelper&& _Other) noexcept = delete;
	ContentsHelper& operator=(const ContentsHelper& _Other) = delete;
	ContentsHelper& operator=(ContentsHelper&& _Other) noexcept = delete;

protected:

private:
	static float ChangeScale;
};

