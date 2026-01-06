#pragma once
#include <string>
#include <vulkan/vulkan.h>

// Pointer of Implementation
struct GLFWwindow;

namespace Ockham {
    class Window {
        public:
            //Constructor
            Window(int width, int height, std::string title);

            //Destructor
            ~Window();

            //Checks if the user click X on the window.
            bool shouldClose();

            //Talks to the OS to get keys/mouse events.
            void pollEvents();

            //Creates the Surface for the linker between the window and vulkan
            void createSurface(VkInstance instance, VkSurfaceKHR* surface);

            //Getter to the raw pointer of the Window
            GLFWwindow* getNativeWindow() const { return window; }

            void setTitle(const std::string& newTitle);
            double getTime() const;
        
        private:
            //The stored pointer to the Window
            GLFWwindow* window;

            //Args for constructor
            int width;
            int height;
            std::string title;

            //Initalizer
            void init();

    };
}