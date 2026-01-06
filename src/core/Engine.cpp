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

        renderer = std::make_unique<Renderer>(*window, *vulkanContext);
    }

    void Engine::loop() {

        double lastTime = window->getTime();
        int frameCount = 0;

        while (!window->shouldClose())
        {   
            window->pollEvents();
            renderer->drawFrame();

            //FPS COUNTER
            double currentTime = window->getTime();
            frameCount++;

            if (currentTime - lastTime >= 1.0) {
                double msPerFrame = 1000.0 / static_cast<double>(frameCount);
                
                std::string newTitle = "Ockham Engine - " + std::to_string(frameCount) + " FPS / " + std::to_string(msPerFrame) + "ms";
                window->setTitle(newTitle);

                frameCount = 0;
                lastTime = currentTime;
            }
            //
        }
        renderer->waitIdle();
    }

    void Engine::cleanup() {
        //Smart pointers die on close
        std::cout << "Ockham Engine Shutting Down" << std::endl;
    }
}