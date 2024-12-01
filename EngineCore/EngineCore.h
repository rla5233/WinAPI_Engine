#pragma once
#include <EnginePlatform/EngineWindow.h>

// EngineCore Class
class EngineCore
{
public:
	// constructor destructor
	EngineCore();
	~EngineCore();
	
	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

public:
	template<typename T>
	static void Start()
	{

	}

protected:

private:
	static UEngineWindow MainWindow;

};