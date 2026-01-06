#pragma once

#include "backend/VulkanContext.h"
#include "backend/Swapchain.h"
#include "backend/Pipeline.h"
#include "../core/Window.h"
#include "Model.h"
#include <memory>
#include <vector>

namespace Ockham {

    class Renderer {
    public:
        Renderer(Window& window, VulkanContext& context);
        ~Renderer();

        // The master function to draw the frame
        void drawFrame();
        
        // Wait for GPU to finish (used when closing)
        void waitIdle();

    private:
        Window& window;
        VulkanContext& context;

        // Core Rendering Components
        std::unique_ptr<Swapchain> swapchain;
        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;

        // Command Buffers
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        // Synchronization
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        //Keeps track of the current frame
        uint32_t currentFrame = 0;

        // Framebuffers
        std::vector<VkFramebuffer> swapChainFramebuffers;

        //Triangle Storage
        std::unique_ptr<Model> model;

        // Initialization Functions
        void createSwapChain();
        void createRenderPass();
        void createPipeline();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();

        // Helper to record draw commands
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t ageIndex);
        void loadModels();
    };
}