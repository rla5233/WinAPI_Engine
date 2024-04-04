#include "Ground.h"

#include "ContentsHelper.h"
#include "TestLevel.h"
#include "ThirdParty/Box2d/include/box2d.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::BeginPlay()
{
	AActor::BeginPlay();
}

void Ground::CreateBody(const FVector& Scale)
{
	// Body Create
	b2BodyDef groundBodyDef;
	b2Vec2 pos = ContentsHelper::GetPosWorldtoBox(GetActorLocation());
	groundBodyDef.position.Set(pos.x, pos.y); // 바닥의 위치 (x는 0, y는 -10)
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	Body = Level->World->CreateBody(&groundBodyDef);
	Body->GetUserData().pointer = reinterpret_cast<unsigned __int64>(this);

	// Body Setting
	b2PolygonShape groundBox;
	b2Vec2 scale = ContentsHelper::GetScaleWorldtoBox(Scale);
	groundBox.SetAsBox(scale.x, scale.y); // 가로 600, 세로 20인 상자 생성
	Body->CreateFixture(&groundBox, 0.0f); // 밀도는 0으로 설정

	// Collision Setting
	Collision = CreateCollision(0);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale(Scale);
}

void Ground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
