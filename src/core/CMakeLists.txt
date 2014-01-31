SET(TRYCORE_SOURCES
    alias.h
    str.cpp
    vector2.cpp
    vector3.cpp
    vector4.cpp
    matrix3.cpp
    matrix4.cpp
    quaternion.cpp
    aabbox.h
    transformable.h
    listenable.h
    exception.cpp
    try.h
    singleton.h
    message.cpp
    property.cpp
    object.cpp
    behavior.cpp
    state.cpp
    fsm.cpp
    task.cpp
    taskscheduler.cpp
    logger.cpp
)

ADD_LIBRARY(TryCore SHARED ${TRYCORE_SOURCES})

TARGET_LINK_LIBRARIES(TryCore
    boost_thread-mt
)
