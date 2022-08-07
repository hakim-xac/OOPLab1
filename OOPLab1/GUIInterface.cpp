#include "GUIInterface.h"
#include "Functions.h"
#include "Button.h"
#include <Windows.h>
#include <vector>
#include <string_view>
#include <iostream>


namespace KHAS {

    GUIInterface::GUIInterface(short width, short height)
        : width_(width)
        , height_(height)
        , rect_()
        , hwnd_(GetConsoleWindow())
        , hdc_(GetDC(hwnd_)) {

            setSelfWindow();
            GetClientRect(hwnd_, &rect_);
            rect_.right += 17;
        }

    void GUIInterface::setSelfWindow() {


        setWindowPosition(width_, height_);
        setBufferWindowSize();
        disableSelectionInConsole();
        deletePropertiesFromSystemMenu();
        updateStyleWindow();
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

    void GUIInterface::showMenu(HDC& hdc) const
    {
        Button bt_static{ hdc
            , 150, rect_.bottom - 160, 300, 40
            , "Показать статическую модель"
            , Color{100, 100, 100}, Color{0, 0, 0} };

        Button bt_dinamyc{ hdc
            , 150, rect_.bottom - 110, 300, 40
            , "Показать динамическую модель"
            , Color{100, 100, 100}, Color{0, 0, 0} };

        Button bt_random{ hdc
            , 150, rect_.bottom - 60, 300, 40
            , "Показать модель с эффектом случайности"
            , Color{100, 100, 100}, Color{0, 0, 0} };

    }

    std::string GUIInterface::delimiter(char del) const
    {                 
        return std::string(width_, del);
    }

    void GUIInterface::loop() const
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


            BitBlt(hdc_, 0, 0, x, y, memDC, 0, 0, SRCCOPY);
            DeleteDC(memDC);
            DeleteObject(memBM);
            Sleep(5);
        }
        
    }

}
