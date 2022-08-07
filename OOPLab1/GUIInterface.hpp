#include <vector>
#include <iostream>
#include <algorithm>
namespace KHAS {

    template<typename ...TString, typename T2>
    constexpr inline std::string KHAS::GUIInterface::generationString(TString&& ...str) const
    {
        std::vector lst{ std::string(std::forward<TString>(str))... };
        std::string ret{};
        std::for_each(std::begin(lst), std::end(lst), [&ret](auto&& elem) {
            ret += std::move(elem) + " ";
            });

        return ret;
    }


}
