#include "Functions.h"

namespace KHAS {


	COLORREF rgbToCRef(int r, int g, int b)
	{
		return (r | (g << 8) | (b << 16));
	}

	std::pair<int, int> getCursorPos()
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(GetConsoleWindow(), &pt);
		return { pt.x, pt.y };
	}

	void updateStyleWindow()
	{
		HWND handle{ GetConsoleWindow() };
		LONG_PTR style_ptr{ SetWindowLongPtr(handle, GWL_STYLE
			, WS_SIZEBOX & ~WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION) };
		SetWindowPos(handle, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
		ShowWindow(handle, SW_SHOW);
	}

	void deletePropertiesFromSystemMenu()
	{
		HMENU hMenu = GetSystemMenu(GetConsoleWindow(), false);
		DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
	}

	void disableSelectionInConsole()
	{
		HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
		DWORD prevConsoleMode = 0;
		GetConsoleMode(hConsole, &prevConsoleMode);
		SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS |
			(prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE));
	}

	void setBufferWindowSize()
	{
		auto handle{ GetConsoleWindow() };
		CONSOLE_SCREEN_BUFFER_INFO csi;
		GetConsoleScreenBufferInfo(handle, &csi);
		short y{ csi.srWindow.Bottom - csi.srWindow.Top + 1 };
		SetConsoleScreenBufferSize(handle, { csi.dwSize.X, y });
	}

	void setWindowPosition(int width, int height)
	{
		HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
		auto window_pos_x{ (GetSystemMetrics(SM_CXSCREEN) >> 1) - (width >> 1) };
		auto window_pos_y{ (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height >> 1) };
		MoveWindow(GetConsoleWindow(), window_pos_x, window_pos_y, width, height, TRUE);
	}

}