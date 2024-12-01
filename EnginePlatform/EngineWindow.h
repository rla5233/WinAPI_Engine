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

protected:

private:


};