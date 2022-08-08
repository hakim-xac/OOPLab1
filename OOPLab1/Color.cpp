#include "Color.h"
#include <random>

namespace KHAS {

	void Color::setRandom()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_color(0, 255);
		R = dist_color(gen);
		G = dist_color(gen);
		B = dist_color(gen);
	}
}
