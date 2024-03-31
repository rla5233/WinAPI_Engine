#pragma once

// Ό³Έν :
class Playe
{
public:
	// constructor destructor
	Playe();
	~Playe();
	
	// delete Function
	Playe(const Playe& _Other) = delete;
	Playe(Playe&& _Other) noexcept = delete;
	Playe& operator=(const Playe& _Other) = delete;
	Playe& operator=(Playe&& _Other) noexcept = delete;


protected:

private:

};

