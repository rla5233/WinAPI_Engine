#pragma once
#include <EngineCore/EngineCore.h>

// Contents Core Class
class ContentsCore : public EngineCore
{
public:
	// constructor destructor
	ContentsCore();
	~ContentsCore();
	
	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

protected:

private:

};

