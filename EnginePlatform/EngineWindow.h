#pragma once

// Ό³Έν :
class UEngineWindow
{
public:
	// constructor destructor
	UEngineWindow();
	~UEngineWindow();
	
	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

public:
	static void Init(HINSTANCE _Inst);
	static int MessageRoop();

private:
	static void MyRegisterClass(HINSTANCE _Inst);
	static LRESULT CALLBACK WndProc(HWND _Hwnd, UINT _Message, WPARAM _WParam, LPARAM _LParam);
	static bool InitInstance(HINSTANCE _Inst);


private:
	static HINSTANCE hInstance;
	static LPCWCHAR szTitle;
	static LPCWSTR szWindowClass;

};