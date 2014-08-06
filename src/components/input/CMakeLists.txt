SET(TRYINPUT_SOURCES
    base.h
    inputmanager.cpp
    keyboardlistener.cpp
    mouselistener.cpp
    joysticklistener.cpp
    input.h
)

ADD_LIBRARY(TryInput SHARED ${TRYINPUT_SOURCES})

TARGET_LINK_LIBRARIES(TryInput
    ${GLFW_LIBRARIES}
    TryCore
)
