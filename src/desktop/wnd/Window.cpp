
#include "..\util\Exception.h"
#include "Window.h"



Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(101),
		IMAGE_ICON, 32, 32, 0
	));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = (LPCWSTR)GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(101),
		IMAGE_ICON, 16, 16, 0
	));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass((LPCWSTR)wndClassName, GetInstance());
}

LPCWSTR Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


// Window Stuff
Window::Window(int width, int height, LPCWSTR name)
	:
	width(width),
	height(height)
{

	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw Exception("Windows Size Exception", __FILE__, __LINE__);
	}
	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	if (hWnd == nullptr)
	{
		throw Exception("Invalid Windows Handle", __FILE__, __LINE__);
	}

	





	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::SetTitle(const std::string& title)
{
	if (SetWindowText(hWnd, (LPCWSTR)title.c_str()) == 0)
	{
		throw Exception("Error While changing Title", __FILE__, __LINE__);
	}
}

int Window::ProcessMessages() noexcept
{
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (msg.message == WM_QUIT)
		{
			return (int)msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	const POINTS pt = MAKEPOINTS(lParam);
	
	const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
	std::wstring str = L"Message :";
	str.append(std::to_wstring(pt.x)).append(L"\t|").append(std::to_wstring(pt.y)).append(L"\t|").append(std::to_wstring(delta)).append(L"\n");
	OutputDebugString(str.c_str());

	switch (msg)
	{
	
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KILLFOCUS:
		break;
	case WM_SIZE:
#ifndef NDEBUG
		OutputDebugString(L"Window::HandleMessage\n");
#endif // !NDEBUG

		break;
		/*********** KEYBOARD MESSAGES ***********/
	case WM_KEYDOWN:
		//Key Down Messages
	case WM_SYSKEYDOWN:
		//Win System Keys

		break;
	case WM_KEYUP:
		break;
	case WM_SYSKEYUP:

		break;
	case WM_CHAR:

		break;
		/*********** END KEYBOARD MESSAGES ***********/

		/************* MOUSE MESSAGES ****************/
	case WM_MOUSEMOVE:
	{

		

		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetForegroundWindow(hWnd);

		

		break;
	}
	case WM_RBUTTONDOWN:
	{

		

		break;
	}
	case WM_LBUTTONUP:
	{

	


		break;
	}
	case WM_RBUTTONUP:
	{

		

		break;
	}
	case WM_MOUSEWHEEL:
	{

		

		break;
	}
	/************** END MOUSE MESSAGES **************/
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

