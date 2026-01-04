#pragma once
#include "Window.h"
#include "../graphics/backend/VulkanContext.h"
#include <memory>

namespace Ockham {
    class Engine {
        public:
            //Runs the game engine
            void run();

        private:
            void init();
            void loop();
            void cleanup();

        //Smart Pointer allow for when the engine dies the pointer will die as well.
        std::unique_ptr<Window> window;
        std::unique_ptr<VulkanContext> vulkanContext;
    };
}