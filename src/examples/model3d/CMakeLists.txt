ADD_EXECUTABLE(TryModel3DExample
    application.cpp
    main.cpp
)

TARGET_LINK_LIBRARIES(TryModel3DExample
    TryCore
    TryGraphics
)

FILE(COPY data DESTINATION .)
