#include <map>
#include <Windows.h>

namespace KHAS {

	template <typename TColor, typename T2_>
	COLORREF
		colorToCRef(TColor&& color) {
		TColor new_color{ std::forward<TColor>(color) };
		return rgbToCRef(new_color.R, new_color.G, new_color.B);
	}

	template <typename TColors, typename T2_>
	COLORREF
		colorsToCRef(TColors&& color) {
		using tc = std::decay_t<TColors>;

		std::map<tc, COLORREF> base{
			{ tc::Black, rgbToCRef(0, 0, 0) }
			, { tc::White, rgbToCRef(255, 255, 255) }
			, { tc::Red, rgbToCRef(255, 0, 0) }
			, { tc::Green, rgbToCRef(0, 255, 0) }
			, { tc::Blue, rgbToCRef(0, 0, 255) }
		};
		return base[color];
	}

}