#include "ContactListener.h"

#include "Player.h"
#include "Ground.h"
#include "Hook.h"

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
	HookedCheck(_Contact);
}

void ContactListener::EndContact(b2Contact* _Contact)
{
	PlayerGroundOffCheck(_Contact);
}

void ContactListener::PlayerGroundOnCheck(b2Contact* _Contact)
{
	uintptr_t FixA = _Contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	uintptr_t FixB = _Contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	
	AActor* Actor = reinterpret_cast<Player*>(FixA);
	Player* APlayer = dynamic_cast<Player*>(Actor);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixB);
		if (nullptr != dynamic_cast<Ground*>(AGround))
		{
			++(APlayer->IsOnGroundValue);
			return;
		}
	}

	Actor = reinterpret_cast<Player*>(FixB);
	APlayer = dynamic_cast<Player*>(Actor);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixA);
		if (nullptr != dynamic_cast<Ground*>(AGround))
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

	AActor* Actor = reinterpret_cast<Player*>(FixA);
	Player* APlayer = dynamic_cast<Player*>(Actor);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixB);
		if (nullptr != dynamic_cast<Ground*>(AGround))
		{
			--(APlayer->IsOnGroundValue);
			return;
		}
	}

	Actor = reinterpret_cast<Player*>(FixB);
	APlayer = dynamic_cast<Player*>(Actor);
	if (nullptr != APlayer)
	{
		Ground* AGround = reinterpret_cast<Ground*>(FixA);
		if (nullptr != dynamic_cast<Ground*>(AGround))
		{
			--(APlayer->IsOnGroundValue);
			return;
		}
	}
}

void ContactListener::HookedCheck(b2Contact* _Contact)
{
	uintptr_t FixA = _Contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	uintptr_t FixB = _Contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	AActor* Actor = reinterpret_cast<Hook*>(FixA);
	Hook* AHook = dynamic_cast<Hook*>(Actor);
	if (nullptr != AHook)
	{
		AActor* AGround = reinterpret_cast<Ground*>(FixB);
		if (nullptr != dynamic_cast<Ground*>(AGround))
		{
			AHook->IsHooked = true;
			return;
		}
	}

	Actor = reinterpret_cast<Hook*>(FixB);
	AHook = dynamic_cast<Hook*>(Actor);
	if (nullptr != AHook)
	{
		AActor* AGround = reinterpret_cast<Ground*>(FixA);
		if (nullptr != dynamic_cast<Ground*>(AGround))
		{
			AHook->IsHooked = true;
			return;
		}
	}

}
