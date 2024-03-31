#include "Ground.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale({ 2000.0f, 50.0f });
}

void Ground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	
}
