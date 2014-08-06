SET(TRYGRAHPICS_SOURCES
    base.h
    rendercontext.cpp
    renderwindow.cpp
    graphicsmanager.cpp
    scenetransformable.cpp
    model3d.cpp
    cameracontroller.cpp
    lightemitter.cpp
    particlesemitter.cpp
    graphics.h
)

ADD_LIBRARY(TryGraphics SHARED ${TRYGRAHPICS_SOURCES})

TARGET_LINK_LIBRARIES(TryGraphics
    ${Horde3D_LIBRARIES}
    ${GLFW_LIBRARIES}
    TryCore
)
