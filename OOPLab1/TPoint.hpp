
namespace KHAS {

	template <typename TColor, typename T2>
	void KHAS::tPoint::setColor(TColor&& color) {
		color_ = std::forward<TColor>(color);
	}
}