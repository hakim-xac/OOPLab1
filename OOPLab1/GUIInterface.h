#ifndef GUIInterface__
#define GUIInterface__

#include <Windows.h>
#include <string_view>
#include <vector>
#include <queue>
#include <functional>
#include "TPoint.h"
#include "Task.h"

namespace KHAS {

    class GUIInterface {

    private:
        short width_;
        short height_;
        RECT rect_;
        RECT drawing_rectangle_;
        HWND hwnd_;
        HDC hdc_; 
        std::vector<tPoint> tPoints_;
        std::queue<Task> queue_;

    private:

        std::string delimiter(char del)         const;
        void setSelfWindow()                    const;
        void hideCursor()                       const;
        void showHeader(HDC& hdc)               const;
        void setBufferWindowSize()              const;
        void disableSelectionInConsole()        const;
        void updateStyleWindow()                const;
        void deletePropertiesFromSystemMenu()   const;
        void setWindowPosition()                const;
        inline bool isKeyDown(int key)          const;
        void showTPoints()                           ;
        void showMenu(HDC& hdc)                      ;
        void showMenuIfRandomMove()                  ;
        void showMenuIfDynamicMove()                 ;
        void showStaticModel()                       ;
        void showDinamycModel()                      ;
        void showRandomModel()                       ;
        void clearModel()                            ; 
        void fillTPoints()                           ;
        void readQueue()                             ;
        void exitToMain()                            ;
        void draw(std::function<void()> func)        ;
        void movePoints(DirectionOfMoveOfPoints dmp = DirectionOfMoveOfPoints::EMPTY);

        DirectionOfMoveOfPoints createmovePoints() const;

        template <typename ... TString, typename = std::enable_if_t<
            (std::is_convertible_v<std::decay_t<TString>, std::string> && ...) >>
        constexpr std::string generationString(TString&& ... str) const;
    public:

        GUIInterface() = delete;
        GUIInterface(short width, short height);
        void loop();
    };

}

#include "GUIInterface.hpp"

#endif