#pragma once
#include <EngineCore/EngineCore.h>

// Contents Core Class
class UContentsCore : public UUserCore
{
public:
	// constructor destructor
	UContentsCore();
	~UContentsCore();
	
	// delete Function
	UContentsCore(const UContentsCore& _Other) = delete;
	UContentsCore(UContentsCore&& _Other) noexcept = delete;
	UContentsCore& operator=(const UContentsCore& _Other) = delete;
	UContentsCore& operator=(UContentsCore&& _Other) noexcept = delete;

public:


private:



};

