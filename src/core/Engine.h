#pragma once
#include "Window.h"
#include "../graphics/backend/VulkanContext.h"
#include "../graphics/Renderer.h"
#include <memory>

namespace Ockham {
    class Engine {
        public:
            void run();

        private:
            void init();
            void loop();
            void cleanup();

        std::unique_ptr<Window> window;
        std::unique_ptr<VulkanContext> vulkanContext;
        std::unique_ptr<Renderer> renderer;
    };
}