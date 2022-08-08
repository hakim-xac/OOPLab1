#ifndef GUIInterface__
#define GUIInterface__

#include <Windows.h>
#include <string_view>
#include <vector>
#include "TPoint.h"

namespace KHAS {

    class GUIInterface {

    private:
        short width_;
        short height_;
        RECT rect_;
        HWND hwnd_;
        HDC hdc_; 
        std::vector<tPoint> tPoints_;

    private:

        std::string delimiter(char del)         const;
        void setSelfWindow()                    const;
        void hideCursor()                       const;
        void showHeader(HDC& hdc)               const;
        void showMenu(HDC& hdc)                 const;
        void showStaticModel()                  const;
        void showDinamycModel()                 const;
        void showRandomModel()                  const;
        void clearModel()                       const;
        void setBufferWindowSize()              const;
        void disableSelectionInConsole()        const;
        void updateStyleWindow()                const;
        void deletePropertiesFromSystemMenu()   const;
        void setWindowPosition()                const;

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