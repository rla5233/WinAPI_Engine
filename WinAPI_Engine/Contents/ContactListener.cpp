#include "ContactListener.h"

#include "Player.h"
#include "Ground.h"

#include <functional>

ContactListener::ContactListener()
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* _Contact)
{
	PlayerGroundOnCheck(_Contact);
}

void ContactListener::EndContact(b2Contact* _Contact)
{
	PlayerGroundOffCheck(_Contact);
}

void ContactListener::PlayerGroundOnCheck(b2Contact* _Contact)
{
	uintptr_t FixA = _Contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	uintptr_t FixB = _Contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	
	Player* APlayer = reinterpret_cast<Player*>(FixA);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixB);
		if (nullptr != AGround)
		{
			++(APlayer->IsOnGroundValue);
			return;
		}
	}

	APlayer = reinterpret_cast<Player*>(FixB);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixA);
		if (nullptr != AGround)
		{
			++(APlayer->IsOnGroundValue);
			return;
		}
	}
}

void ContactListener::PlayerGroundOffCheck(b2Contact* _Contact)
{
	uintptr_t FixA = _Contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	uintptr_t FixB = _Contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	Player* APlayer = reinterpret_cast<Player*>(FixA);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixB);
		if (nullptr != AGround)
		{
			--(APlayer->IsOnGroundValue);
			return;
		}
	}

	APlayer = reinterpret_cast<Player*>(FixB);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixA);
		if (nullptr != AGround)
		{
			--(APlayer->IsOnGroundValue);
			return;
		}
	}
}
