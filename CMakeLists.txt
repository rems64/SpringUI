# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)
project ("SpringUI")


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(GLEW_STATIC  ON)
add_subdirectory ( "lib/glfw" )

include_directories ( "lib/glfw/include" "Include/" )


#find_package(OpenGL REQUIRED COMPONENTS OpenGL)
#if(NOT OPENGL_FOUND)
#	message("Error: OpenGL was not found")
#endif(NOT OPENGL_FOUND)
#set(GL_LIBRARY GL GLU X11)

set(SRCS
	"src/SpringUI.cpp"
	"src/Core/Shader.cpp"
	"src/Debug.cpp"
	"src/Renderer.cpp"
	"src/Core/VertexBuffer.cpp"
	"src/Core/IndexBuffer.cpp"
	"src/Core/VertexBufferLayout.cpp"
	"src/Core/VertexArray.cpp"
	 "src/UI/UIElement.cpp")

find_package(OpenGL REQUIRED)

#set(CMAKE_PREFIX_PATH "lib/glew")
#set(CMAKE_LIBRARY_PATH "lib/glew")
#set(GLEW_INCLUDE_DIRS "lib/glew/include")
#set(GLEW_LIBRARY "lib/glew/lib")

#if(GLEW_FOUND)
#include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARY})
#set(GLEW_DIR "C:/Program Files/GLEW")
list(APPEND CMAKE_PREFIX_PATH "C:/Program Files/GLEW")
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
message("Glew found!")
#endif()

#include_directories ( "lib/glew/include" )

# Incluez les sous-projets.
#add_subdirectory ("src")
add_executable(output ${SRCS})

target_link_libraries(output glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})
target_link_libraries(output ${GLEW_LIBRARIES})
#target_link_libraries(output "lib/glew/glew32")
#target_link_libraries(output lib/glew/lib/glew32)
target_link_libraries(output OpenGL::GL)