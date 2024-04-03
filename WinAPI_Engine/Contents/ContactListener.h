#pragma once

#include "ThirdParty/Box2D/include/box2d.h"

// Ό³Έν :
class ContactListener : public b2ContactListener
{
public:
	// constructor destructor
	ContactListener();
	~ContactListener();

	// delete Function
	ContactListener(const ContactListener& _Other) = delete;
	ContactListener(ContactListener&& _Other) noexcept = delete;
	ContactListener& operator=(const ContactListener& _Other) = delete;
	ContactListener& operator=(ContactListener&& _Other) noexcept = delete;

protected:

private:
	void PlayerGroundOnCheck(b2Contact* _Contact);
	void PlayerGroundOffCheck(b2Contact* _Contact);

private:
	void EndContact(b2Contact*_Contact) override;
	void BeginContact(b2Contact* _Contact) override;

};
