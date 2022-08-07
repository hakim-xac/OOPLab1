#ifndef Button__
#define Button__
#include <Windows.h>
#include "Color.h"
#include "Functions.h"
#include <string>
namespace KHAS {

	class Button {
	private:
		int x_{};
		int y_{};
		int right_{};
		int bottom_{};
		std::string name_{};
		Color color_{};

	public:
		Button() = delete;

		template <typename TName, typename TBrushColor, typename TPenColor, typename = std::enable_if_t<
			std::is_convertible_v<std::decay_t<TName>, std::string>
			&& std::is_same_v<TBrushColor, Color>
			&& std::is_same_v<TPenColor, Color>
			>>
			Button(const HDC& hdc
				,int x, int y, int right, int bottom
				, TName&& name
				, TBrushColor&& brush_color
				, TPenColor&& pen_color);
	};
}

#include "Button.hpp"


#endif 
