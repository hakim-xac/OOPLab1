#include "Color.h"

namespace KHAS {
	std::ostream& operator<<(std::ostream& out, const Color& color)
	{
		out << "class Color{ R: " << color.R << "; "
			<< "G: " << color.G << "; "
			<< "B: " << color.B << "; "
			<< "}";
		return out;
	}
}
