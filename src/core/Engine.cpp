#include "Engine.h"
#include <iostream>

namespace Ockham {

    void Engine::run() {
        init();
        loop();
        cleanup();
    }

    void Engine::init() {
        std::cout << "Init Ockham Engine" << std::endl;

        window = std::make_unique<Window>(800, 600, "Ockham Engine");

        vulkanContext = std::make_unique<VulkanContext>();
        vulkanContext->init(*window);
    }

    void Engine::loop() {
        while (!window->shouldClose())
        {   
            //Read Input
            window->pollEvents();

            //Physics will go here once I complete it

            //Render here once I complete it
        }
    
    }

    void Engine::cleanup() {
        std::cout << "Ockham Engine Shutting Down" << std::endl;
    }
}