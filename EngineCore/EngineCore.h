#pragma once

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


protected:

private:

};

//#define ENGINESTART() \
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
//	_In_opt_ HINSTANCE hPrevInstance, \
//	_In_ LPWSTR    lpCmdLine, \
//	_In_ int       nCmdShow) \
//{ \
//	LEAKCHECK; \
//
//}