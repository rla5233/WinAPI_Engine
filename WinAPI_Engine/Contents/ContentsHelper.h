#pragma once
#include <EngineCore\EngineCore.h>

// Ό³Έν :
class ContentsHelper
{
public:
	static FVector GetWindowScale();
	static float GetDistace(const FVector& _Pos1, const FVector& _Pos2);
	static float GetVecSize(const FVector& _Vec);


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

};

