
#include "Functions.h"

namespace KHAS {

	template <typename TName, typename TBrushColor, typename TPenColor, typename T4>
	Button::Button(const HDC& hdc
		, int x, int y, int right, int bottom
		, TName&& name
		, TBrushColor&& brush_color, TPenColor&& pen_color) {

		std::string new_name;
		if constexpr (std::is_same_v<TName, std::string>) {
			std::tie(new_name) = std::forward<TName>(name);
		}
		else {
			new_name = std::move(std::string(std::forward<TName>(name)));
		}

		Color new_brush_color{ std::forward<TBrushColor>(brush_color) };
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, colorToCRef(std::move(new_brush_color)));		
		Rectangle(hdc, x, y, x + right, y + bottom);

		Color new_pen_color{ std::forward<TBrushColor>(pen_color) };
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, colorToCRef(std::move(new_pen_color)));
		int new_name_len{ static_cast<int>(new_name.length()) };
		int text_x{ x + (right >> 1) - (8 * new_name_len >> 1) + 8 };
		int text_y{ y + (bottom >> 1) - 8 };

		TextOut(hdc, text_x, text_y, new_name.c_str(), new_name_len);

		auto&& [mouse_pos_x, mouse_pos_y] { getCursorPos() };

		GetAsyncKeyState(VK_LBUTTON);
		if (mouse_pos_x >= x && mouse_pos_x <= x + right
			&& mouse_pos_y >= y && mouse_pos_y <= y + bottom) {
			if (GetAsyncKeyState(VK_LBUTTON)) {
				
			}
		}
		
	}
}