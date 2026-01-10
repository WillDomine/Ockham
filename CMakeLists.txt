cmake_minimum_required(VERSION 3.20)

project(Ockham VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)

add_executable(Ockham
    src/main.cpp
    src/core/Engine.cpp 
    src/core/Engine.h 
    src/core/Window.cpp 
    src/core/Window.h
    src/graphics/backend/VulkanContext.cpp
    src/graphics/backend/VulkanContext.h
    src/graphics/backend/Swapchain.cpp
    src/graphics/backend/Swapchain.h
    src/graphics/backend/Pipeline.cpp
    src/graphics/backend/Pipeline.h
    src/graphics/Renderer.cpp
    src/graphics/Renderer.h
    src/graphics/Model.cpp
    src/graphics/Model.h
    src/graphics/vk_mem_alloc.h
)

target_include_directories(
    Ockham PUBLIC src ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(Ockham PRIVATE Vulkan::Vulkan glfw)