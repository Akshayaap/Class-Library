#pragma once
#include <Windows.h>
#include <string>
class Window
{
public:
private:
	class WindowClass
	{
	public:
		static LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass &) = delete;
		WindowClass &operator=(const WindowClass &) = delete;
		static constexpr LPCWSTR wndClassName = L"Basic Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

public:
	Window(int width, int height, LPCWSTR name);
	~Window();
	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;
	void SetTitle(const std::string &title);
	static int ProcessMessages() noexcept;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
private:
	int width;
	int height;
	HWND hWnd;
};
