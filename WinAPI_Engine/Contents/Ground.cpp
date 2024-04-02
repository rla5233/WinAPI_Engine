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

	// Actor Setting
	FVector WinScale = ContentsHelper::GetWindowScale();
	SetActorLocation({ WinScale.hX(), WinScale.Y * 0.8f });

	// Body Create
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(GetActorLocation().X / 30.0f, GetActorLocation().Y / 30.0f); // 바닥의 위치 (x는 0, y는 -10)
	TestLevel* Level = dynamic_cast<TestLevel*>(GetWorld());
	Body = Level->World->CreateBody(&groundBodyDef);

	// Body Setting
	b2PolygonShape groundBox;
	FVector GroundScale = { 800.0f, 10.0f };
	groundBox.SetAsBox((GroundScale.X * 0.5f) / 30.0f, (GroundScale.Y * 0.5f) / 30.0f); // 가로 600, 세로 20인 상자 생성
	Body->CreateFixture(&groundBox, 0.0f); // 밀도는 0으로 설정

	// Collision Setting
	Collision = CreateCollision(0);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetScale(GroundScale);
}

void Ground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
