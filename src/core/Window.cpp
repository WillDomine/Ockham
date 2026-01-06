#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Ockham {
    Window::Window(int width, int height, std::string title) : width(width), height(height), title(title) {
        init();
    }

    Window::~Window() {
        //Destorys the window
        glfwDestroyWindow(window);

        //Kills the GLFW Libary Process
        glfwTerminate();
    }

    void Window::init() {
        //Init the GLFW libary
        if(!glfwInit()) {
            throw std::runtime_error("Failed to Initalize GLFW");
        }

        //Tells the window not to create in an OPENGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // Will make creating the swap chain easier to begin, since you have to destroy and rebuild on window resized.
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (!window)
        {
            //Kills the GLFW Libary Process
            glfwTerminate();
            throw std::runtime_error("Failed to create Window");
        }
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::pollEvents() {
        //Fills queue with events
        glfwPollEvents();
    }

    void Window::createSurface(VkInstance instance, VkSurfaceKHR* surface) {
        if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface");
        }
    }

    void Window::setTitle(const std::string& newTitle) {
        glfwSetWindowTitle(window, newTitle.c_str());
    }

    double Window::getTime() const {
        return glfwGetTime();
    }

}