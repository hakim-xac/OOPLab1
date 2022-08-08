
#include "Functions.h"

namespace KHAS {

	template <typename TName, typename TRect, typename TBrushColor, typename TPenColor, typename TFunc, typename T5>
	Button::Button(const HDC& hdc
		, TRect&& rect
		, TName&& name
		, TBrushColor&& brush_color, TPenColor&& pen_color
		, TFunc func) {

		std::string new_name;
		if constexpr (std::is_same_v<TName, std::string>) {
			std::tie(new_name) = std::forward<TName>(name);
		}
		else {
			new_name = std::move(std::string(std::forward<TName>(name)));
		}
		TRect r{ std::forward<TRect>(rect) };

		Color new_brush_color{ std::forward<TBrushColor>(brush_color) };
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, colorToCRef(std::move(new_brush_color)));	

		Rectangle(hdc, r.left, r.top, r.left + r.right, r.top + r.bottom);

		Color new_pen_color{ std::forward<TBrushColor>(pen_color) };
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, colorToCRef(std::move(new_pen_color)));
		int new_name_len{ static_cast<int>(new_name.length()) };
		int text_x{ r.left + (r.right >> 1) - (8 * new_name_len >> 1) + 8 };
		int text_y{ r.top + (r.bottom >> 1) - 8 };

		TextOut(hdc, text_x, text_y, new_name.c_str(), new_name_len);

		auto&& [mouse_pos_x, mouse_pos_y] { getCursorPos() };

		GetAsyncKeyState(VK_LBUTTON); // сброс, если была нажата ранее, но не в области для нажатия
		static bool state{};
		if (mouse_pos_x >= r.left && mouse_pos_x <= r.left + r.right
			&& mouse_pos_y >= r.top && mouse_pos_y <= r.top + r.bottom) {
			if (GetAsyncKeyState(VK_LBUTTON) && !state) {	
				state = true;			
				func();
				Sleep(300);
				state = false;
			}
		}
		
	}
}