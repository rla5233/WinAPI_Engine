#include "ContentsHelper.h"

#include "ThirdParty/Box2D/inc/box2d.h"

float ContentsHelper::ChangeScale = 30.0f;

ContentsHelper::ContentsHelper()
{
}

ContentsHelper::~ContentsHelper()
{
}

FVector ContentsHelper::GetWindowScale()
{
	return GEngine->MainWindow.GetWindowScale();
}

float ContentsHelper::GetDistace(const FVector& _Pos1, const FVector& _Pos2)
{
	float Result = 0;

	float diff_X = _Pos1.X - _Pos2.X;
	float diff_Y = _Pos1.Y - _Pos2.Y;

	diff_X = diff_X * diff_X;
	diff_Y = diff_Y * diff_Y;

	Result = std::sqrtf(diff_X + diff_Y);

	return Result;
}

float ContentsHelper::GetVecSize(const FVector& _Vec)
{
	float Result = 0;
	Result = powf(_Vec.X, 2) + powf(_Vec.Y, 2);
	Result = std::sqrtf(Result);
	return Result;
}

FVector ContentsHelper::b2Vec2toFVector(const b2Vec2& _Vec)
{
	FVector Result = { _Vec.x, _Vec.y };
	return Result;
}

b2Vec2 ContentsHelper::FVectortob2Vec2(const FVector& _Vec)
{
	b2Vec2 Result = { _Vec.X, _Vec.Y };
	return Result;
}

FVector ContentsHelper::GetPosBoxtoWorld(const b2Vec2& _Vec)
{
	FVector Result = { _Vec.x * ChangeScale, _Vec.y * ChangeScale };
	return Result;
}

b2Vec2 ContentsHelper::GetPosWorldtoBox(const FVector& _Vec)
{
	b2Vec2 Result = { _Vec.X / ChangeScale, _Vec.Y / ChangeScale };
	return Result;
}

FVector ContentsHelper::GetScaleBoxtoWorld(const b2Vec2& _Vec)
{
	FVector Result = { _Vec.x, _Vec.y };
	return Result;
}

b2Vec2 ContentsHelper::GetScaleWorldtoBox(const FVector& _Vec)
{
	b2Vec2 Result = { (_Vec.X * 0.5f) / 30.0f, (_Vec.Y * 0.5f) / 30.0f };
	return Result;
}
