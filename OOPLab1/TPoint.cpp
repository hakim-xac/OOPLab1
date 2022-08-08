#include "TPoint.h"
#include <sstream>

namespace KHAS {


	tPoint::tPoint()
		: pos_x_()
		, pos_y_()
		, color_()
		, name_() {}

	Color tPoint::getColor() const
	{
		return color_;
	}

	int tPoint::getPositionX() const
	{
		return pos_x_;
	}

	int tPoint::getPositionY() const
	{
		return pos_y_;
	}

	std::pair<int, int> tPoint::getPositionXY() const
	{
		return { pos_x_, pos_y_ };
	}

	void tPoint::setPositionX(int x)
	{
		pos_x_ = x;
	}

	void tPoint::setPositionY(int y)
	{
		pos_y_ = y;
	}

	void tPoint::setPositionXY(int x, int y)
	{
		pos_x_ = x;
		pos_y_ = y;
	}



}