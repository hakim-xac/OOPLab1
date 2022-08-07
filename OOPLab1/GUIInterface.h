#ifndef GUIInterface__
#define GUIInterface__

#include <Windows.h>
#include <string_view>

namespace KHAS {

    class GUIInterface {

    private:
        short width_ {};
        short height_ {};
        RECT rect_{};
        HWND hwnd_{ nullptr };
        HDC hdc_{ nullptr }; 

    private:

        void setSelfWindow();
        void hideCursor() const;
        void showHeader(HDC& hdc) const;
        void showMenu(HDC& hdc) const;
        std::string delimiter(char del) const;

        template <typename ... TString, typename = std::enable_if_t<
            (std::is_convertible_v<std::decay_t<TString>, std::string> && ...) >>
        constexpr std::string generationString(TString&& ... str) const;
    public:

        GUIInterface() = delete;
        GUIInterface(short width, short height);
        void loop() const;
    };

}

#include "GUIInterface.hpp"

#endif