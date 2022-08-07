#ifndef Functions__
#define Functions__

#include <Windows.h>
#include "Enums.h"
#include "Color.h"

namespace KHAS {

	template <typename TColor, typename = std::enable_if_t<std::is_same_v<std::decay_t<TColor>, Color>>>
	COLORREF colorToCRef(TColor&& color);

	template <typename TColors, typename = std::enable_if_t<std::is_same_v<std::decay_t<TColors>, Colors>>>
	COLORREF colorsToCRef(TColors&& color);

	COLORREF rgbToCRef(int r, int g, int b);

	std::pair<int, int> getCursorPos();

	void updateStyleWindow();

	void deletePropertiesFromSystemMenu();

	void disableSelectionInConsole();

	void setBufferWindowSize();

	void setWindowPosition(int width, int height);
}

#include "Functions.hpp"


#endif