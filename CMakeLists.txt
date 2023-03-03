cmake_minimum_required(VERSION 3.22)
project(QJSEngine_playground)

set(CMAKE_CXX_STANDARD 20)
find_package(Qt5 REQUIRED COMPONENTS Core Qml)

qt5_wrap_cpp(SOURCES myjsfunc.h)

add_executable(QJSEngine_playground main.cc myjsfunc.h ${SOURCES})

# On ubuntu the package name for Qml is `qtdeclarative5-dev`
target_link_libraries(QJSEngine_playground PRIVATE Qt5::Core Qt5::Qml)
