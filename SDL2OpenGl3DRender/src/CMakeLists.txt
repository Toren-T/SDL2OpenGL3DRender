include_directories(${PROJECT_SOURCE_DIR}/SDL2OpenGl3DRender)

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    link_libraries(SDL2::SDL2)
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(glm REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
    link_libraries(${GLM_LIBRARIES})
endif()


add_executable(SDL2OpenGl3DRender main.cpp
    GameWindow.cpp GameWindow.h
    ShaderManager.cpp ShaderManager.h
    FillShader.cpp FillShader.h
    CubeShader.cpp CubeShader.h
    ViewPort.cpp ViewPort.h
    GameLogic.cpp GameLogic.h)
target_link_libraries(SDL2OpenGl3DRender)
