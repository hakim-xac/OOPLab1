#ifndef TPOINT__
#define TPOINT__


#include <utility>
#include <string>
#include "Color.h"

namespace KHAS {

	class tPoint {
	private:
		int pos_x_;
		int pos_y_;
		KHAS::Color color_;
		std::string name_;

	public:

		tPoint();

		Color getColor() const;
		int getPositionX() const;
		int getPositionY() const;
		std::pair<int, int> getPositionXY() const;

		template <typename TColor, typename = std::enable_if_t<std::is_same_v<TColor, KHAS::Color>>>
		void setColor(TColor&& color);
		void setPositionX(int x);
		void setPositionY(int y);
		void setPositionXY(int x, int y);


	};

}

#include "TPoint.hpp"





#endif