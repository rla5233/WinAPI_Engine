#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale({ 100.0f, 50.0f });
}

void Box::Tick(float _DeltaTime)
{	
	AActor::Tick(_DeltaTime);

}
