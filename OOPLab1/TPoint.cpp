#include "TPoint.h"
#include "Functions.h"
#include <sstream>
#include <random>

namespace KHAS {


	tPoint::tPoint(RECT max_rect)
		: pos_x_()
		, pos_y_()
		, max_rect_(max_rect)
		, color_() {
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_lr(static_cast<int>(max_rect_.left), static_cast<int>(max_rect_.right));
		std::uniform_int_distribution dist_tb(static_cast<int>(max_rect_.top), static_cast<int>(max_rect_.bottom));
		std::uniform_int_distribution dist_color(0, 255);

		pos_x_ = dist_lr(gen);
		pos_y_ = dist_tb(gen);
		color_.setRandom();
	}

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

	std::pair<int, int> tPoint::getPosition() const
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

	void tPoint::setPosition(int x, int y)
	{
		pos_x_ = x;
		pos_y_ = y;
	}


	void tPoint::draw(const HDC& hdc) {
		SetPixel(hdc, getPositionX() - 1, getPositionY(), colorToCRef(getColor()));
		SetPixel(hdc, getPositionX() + 1, getPositionY(), colorToCRef(getColor()));
		SetPixel(hdc, getPositionX(), getPositionY() + 1, colorToCRef(getColor()));
		SetPixel(hdc, getPositionX(), getPositionY() - 1, colorToCRef(getColor()));
		SetPixel(hdc, getPositionX(), getPositionY(), colorToCRef(getColor()));
	}

	void tPoint::move(const HDC& hdc, directionOfMovementOfPoints dmp) {
		switch (dmp)
		{
		case KHAS::directionOfMovementOfPoints::LEFT:
			--pos_x_;
			break;
		case KHAS::directionOfMovementOfPoints::RIGHT:
			++pos_x_;
			break;
		case KHAS::directionOfMovementOfPoints::TOP:
			++pos_y_;
			break;
		case KHAS::directionOfMovementOfPoints::BOTTOM:
			--pos_y_;
			break;
		case KHAS::directionOfMovementOfPoints::TOPLEFT:
			++pos_y_;
			--pos_x_;
			break;
		case KHAS::directionOfMovementOfPoints::TOPRIGHT:
			++pos_x_;
			++pos_y_;
			break;
		case KHAS::directionOfMovementOfPoints::BOTTOMLEFT:
			--pos_x_;
			--pos_y_;
			break;
		case KHAS::directionOfMovementOfPoints::BOTTOMRIGHT:
			++pos_x_;
			--pos_y_;
			break;
		default:
			break;
		}
		draw(hdc);
	}



}