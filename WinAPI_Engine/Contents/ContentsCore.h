#pragma once
#include <EngineCore\EngineCore.h>

// Ό³Έν :
class UContentsCore : public UEngineCore
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

protected:
	void BeginPlay() override;
	void WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath) override;

private:

};

