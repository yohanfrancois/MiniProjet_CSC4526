file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}  "Game.h" "Game.cpp" "Interactible.h" "Interactible.cpp" "Shark.h")
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC sfml-graphics)
