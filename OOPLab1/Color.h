#ifndef COLOR__
#define COLOR__

#include <ostream>
namespace KHAS {

	struct Color {
		int R;
		int G;
		int B;
		explicit Color(int r = 0, int g = 0, int b = 0)
			: R(r)
			, G(g)
			, B(b) {}
	};

}




#endif