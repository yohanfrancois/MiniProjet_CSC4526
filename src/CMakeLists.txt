file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}  "Game.h" "Game.cpp" "Interactible.h" "Interactible.cpp" "Shark.h" "EventManager.h" "Baby.h" "Baby.cpp" "LightFish.h" "LightFish.cpp" "fsm.h" "Utils.cpp" "airBubbles.h" "airBubbles.cpp")
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC sfml-graphics)
