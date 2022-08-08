#include "GUIInterface.h"
#include "Functions.h"
#include "Button.h"
#include "TPoint.h"
#include <Windows.h>
#include <vector>
#include <string_view>
#include <iostream>


namespace KHAS {

    GUIInterface::GUIInterface(short width, short height)
        : width_(width)
        , height_(height)
        , rect_()
        , drawing_rectangle_()
        , hwnd_(GetConsoleWindow())
        , hdc_(GetDC(hwnd_))
        , tPoints_() {

            setSelfWindow();

            GetClientRect(hwnd_, &rect_);
            rect_.right += 17;
            drawing_rectangle_ = std::move(RECT{ 0, 180, rect_.right, rect_.bottom - 280 });
        }

    void GUIInterface::setSelfWindow() const {

        setWindowPosition();
        setBufferWindowSize();
        disableSelectionInConsole();
        deletePropertiesFromSystemMenu();
        updateStyleWindow();
    }

    void GUIInterface::setBufferWindowSize() const
    {
        CONSOLE_SCREEN_BUFFER_INFO csi;
        GetConsoleScreenBufferInfo(hwnd_, &csi);
        short y{ csi.srWindow.Bottom - csi.srWindow.Top + 1 };
        SetConsoleScreenBufferSize(hwnd_, { csi.dwSize.X, y });
    }

    void GUIInterface::hideCursor() const
    {
        HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };        
        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(handle, &structCursorInfo);
        if (structCursorInfo.bVisible) {
            structCursorInfo.bVisible = false;
            SetConsoleCursorInfo(handle, &structCursorInfo);
        }
    }

    void GUIInterface::showHeader(HDC& hdc) const
    {
        std::vector<std::string> base{
            generationString("Дисциплина:", std::string(16, ' '), "Объектно-ориентированное программирование")
            , generationString("Лабораторная работа:", " ", "№ 1")
            , generationString("Тема:", std::string(29, ' '), "Принцип инкапсуляции. Описание класса.")
            , generationString("Студент:", std::string(23, ' '), "Хакимов А.С.")
            , generationString("Вариант:", std::string(23, ' '), "№1")
            , generationString("Группа:", std::string(25, ' '), "ПБ-11")
        };

        SetBkMode(hdc, TRANSPARENT);
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, rgbToCRef(100, 100, 100)); 
        for (int step{}; auto && elem : base) {           
            TextOut(hdc, 100, (step += 20), elem.c_str(), static_cast<int>(elem.length()));
        }

        auto del{ delimiter('=') };
        TextOut(hdc, 0, 160, del.c_str(), static_cast<int>(del.length()));
    }

    void GUIInterface::showMenu(HDC& hdc)
    {
        auto del{ delimiter('=') };
        TextOut(hdc, 0, rect_.bottom - 260, del.c_str(), static_cast<int>(del.length()));

        Button bt_static{ hdc
            , RECT{ 150, rect_.bottom - 210, 310, 40 }
            , "Показать статическую модель"
            , Color{100, 100, 100}, Color{0, 0, 0}
            , [&]() { showStaticModel(); } };

        Button bt_dinamyc{ hdc
            , RECT{ 150, rect_.bottom - 160, 310, 40 }
            , "Показать управляемую модель"
            , Color{100, 100, 100}, Color{0, 0, 0}
            , [&]() { showDinamycModel();  } };

        Button bt_random{ hdc
            , RECT{ 150, rect_.bottom - 110, 310, 40 }
            , "Показать модель со случайным движением"
            , Color{100, 100, 100}, Color{0, 0, 0}
            , [&]() { showRandomModel();  } };

        Button bt_clear{ hdc
            , RECT{ 150, rect_.bottom - 60, 310, 40 }
            , "Очистить поле"
            , Color{100, 100, 100}, Color{0, 0, 0}
            , [&]() { clearModel();  } };



    }

    void GUIInterface::updateStyleWindow() const
    {
        LONG_PTR style_ptr{ SetWindowLongPtr(hwnd_, GWL_STYLE
            , WS_SIZEBOX & ~WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION) };
        SetWindowPos(hwnd_, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
        ShowWindow(hwnd_, SW_SHOW);
    }

    void GUIInterface::deletePropertiesFromSystemMenu() const
    {
        HMENU hMenu{ GetSystemMenu(hwnd_, false) };
        DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
    }

    void GUIInterface::disableSelectionInConsole() const
    {
        HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
        DWORD prevConsoleMode = 0;
        GetConsoleMode(hConsole, &prevConsoleMode);
        SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS |
            (prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE));
    }

    void GUIInterface::showTPoints()
    {
        std::for_each(tPoints_.begin(), tPoints_.end(), [&hdc = hdc_](auto&& elem) {
            elem.draw(hdc);
            });
    }

    void GUIInterface::setWindowPosition() const
    {
        HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
        auto window_pos_x{ (GetSystemMetrics(SM_CXSCREEN) >> 1) - (width_ >> 1) };
        auto window_pos_y{ (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height_ >> 1) };
        MoveWindow(hwnd_, window_pos_x, window_pos_y, width_, height_, TRUE);
    }

    void GUIInterface::fillTPoints() {
        tPoints_.clear();
        const int size{ 100 };
        tPoints_.reserve(size);
        for (int i{}, ie{ size }; i != ie; ++i) {
            tPoints_.emplace_back(tPoint(drawing_rectangle_));
        }
    }

    void GUIInterface::showStaticModel()
    {
        fillTPoints();
        showTPoints();
    }

    void GUIInterface::showDinamycModel()
    {
        fillTPoints();
        showTPoints();
    }

    void GUIInterface::showRandomModel()
    {
        fillTPoints();
        showTPoints();
        //randomMovement();
    }

    void GUIInterface::clearModel()
    {
        std::cout << "clear";
    }

    std::string GUIInterface::delimiter(char del) const
    {                 
        return std::string(width_, del);
    }

    void GUIInterface::loop()
    {       

        while (GetKeyState(VK_ESCAPE) >= 0) {
            hideCursor();
            HDC memDC{ CreateCompatibleDC(hdc_) };
            auto x{ rect_.right - rect_.left };
            auto y{ rect_.bottom - rect_.top };
            HBITMAP memBM{ CreateCompatibleBitmap(hdc_, x, y) };
            SelectObject(memDC, memBM);
            FillRect(memDC, &rect_, CreateSolidBrush(rgbToCRef(255, 255, 255)));

            showHeader(memDC);
            showMenu(memDC);
            showTPoints();

            BitBlt(hdc_, 0, 0, x, y, memDC, 0, 0, SRCCOPY);
            DeleteDC(memDC);
            DeleteObject(memBM);
        }
        
    }

}
