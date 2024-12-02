#pragma once

// ContentsCore Parent Class
class UUserCore
{
public:
	// constructor destructor
	UUserCore();
	~UUserCore();
	
	// delete Function
	UUserCore(const UUserCore& _Other) = delete;
	UUserCore(UUserCore&& _Other) noexcept = delete;
	UUserCore& operator=(const UUserCore& _Other) = delete;
	UUserCore& operator=(UUserCore&& _Other) noexcept = delete;


};

