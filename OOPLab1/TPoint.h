#ifndef TPOINT__
#define TPOINT__


#include <Windows.h>
#include <utility>
#include "Color.h"
#include "Enums.h"

namespace KHAS {

	class tPoint {
	private:
		int pos_x_;
		int pos_y_;
		RECT max_rect_;
		KHAS::Color color_;

	public:

		tPoint() = delete;
		tPoint(RECT max_rect);

		Color getColor() const;
		int getPositionX() const;
		int getPositionY() const;
		std::pair<int, int> getPosition() const;

		template <typename TColor, typename = std::enable_if_t<std::is_same_v<TColor, KHAS::Color>>>
		void setColor(TColor&& color);

		void setPositionX(int x);
		void setPositionY(int y);
		void setPosition(int x, int y);
		void draw(const HDC& hdc);
		void move(const HDC& hdc, directionOfMovementOfPoints dmp);


	};

}

#include "TPoint.hpp"





#endif