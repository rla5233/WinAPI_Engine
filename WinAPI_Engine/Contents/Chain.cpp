#include "Chain.h"

#include "ContentsHelper.h"
#include "ThirdParty/Box2d/inc/box2d.h"

#pragma comment(lib, "box2d.lib")

Chain::Chain()
{
}

Chain::~Chain()
{
}

void Chain::BeginPlay()
{
	AActor::BeginPlay();



	// Collision Setting
	Collision = CreateCollision();
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale({ 5.0f, 5.0f });
}

void Chain::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


}
