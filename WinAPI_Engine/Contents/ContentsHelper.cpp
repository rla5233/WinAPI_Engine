#include "ContentsHelper.h"

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
