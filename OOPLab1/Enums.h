#ifndef Enums__
#define Enums__

#include "Color.h"

namespace KHAS {
	enum class Colors {
		Black
		, White
		, Red
		, Green
		, Blue
	};

	enum class DirectionOfMoveOfPoints{
		LEFT
		, RIGHT
		, TOP
		, BOTTOM
		, TOPLEFT
		, TOPRIGHT
		, BOTTOMLEFT
		, BOTTOMRIGHT
		, EMPTY
	};

}


#endif