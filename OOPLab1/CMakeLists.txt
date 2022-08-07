# CMakeList.txt: проект CMake для OOPLab1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (OOPLab1 "OOPLab1.cpp"  "Color.h" "TPoint.cpp" "TPoint.hpp" "Color.cpp" "GUIInterface.h" "Enums.h" "Functions.h" "Functions.cpp" "Functions.hpp" "GUIInterface.cpp" "GUIInterface.hpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
