# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("OOPLab1")
set (CMAKE_CXX_STANDARD 20)

# Включите подпроекты.
add_subdirectory ("OOPLab1")
