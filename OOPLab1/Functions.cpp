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


}