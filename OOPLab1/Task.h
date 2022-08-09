#ifndef Task__
#define Task__
#include <functional>

namespace KHAS {
	struct Task {
		std::function<void()> f;
	};
}

#endif // !Task__
