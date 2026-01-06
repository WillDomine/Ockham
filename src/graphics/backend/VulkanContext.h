#pragma once

#include "Pipeline.h"
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include <optional>
#include <memory>

namespace Ockham {

    class Window;
    class Swapchain;

    struct QueueFamilyIndicies {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class VulkanContext {
        public:
            //Constructor
            VulkanContext();
            //Destructor
            ~VulkanContext();
            //Initalizer
            void init(Window& window);

            //Getters for utilizing the GPU and Driver
            VkInstance getInstance() const { return instance; }
            VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }

            //Getting the logical device
            VkDevice getDevice() const { return logicalDevice; }

            //Get the render pass
            VkRenderPass getRenderPass() const { return renderPass; }

        private:
            //Handles Vulkan Libary
            VkInstance instance;

            //Handles the debug callback system
            VkDebugUtilsMessengerEXT debugMessenger;

            //The actual device aka Graphics Card or Integrated Graphics
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            //Logical device the ability to talk to the physical device
            VkDevice logicalDevice;

            //The surface for the window
            VkSurfaceKHR surface;

            //The Queue where we submit draw commands
            VkQueue graphicsQueue;

            //Presents the Images to the monitor
            VkQueue presentQueue;

            //The render pass tells vulkan about the images we draw to
            VkRenderPass renderPass;

            //Swap Chain Pointer
            std::unique_ptr<Swapchain> swapchain;

            //Pipeline Layout
            VkPipelineLayout pipelineLayout;

            //Pipeline Pointer
            std::unique_ptr<Pipeline> pipeline;

            

            //Validation Layer to help check code for errors
            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

            //Device Extensions
            const std::vector<const char*> deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            //Set up functions
            void createInstance();
            void setupDebugMessenger();
            void pickPhysicalDevice();
            void createLogicalDevice();
            void createSwapChain(Window& window);
            void createRenderPass();
            void createPipelineLayout();
            void createGraphicsPipeline();

            bool checkValidationLayerSupport();
            bool isDeviceSuitable(VkPhysicalDevice device);
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);

            //Finds the familes for the specific device
            QueueFamilyIndicies findQueueFamilies(VkPhysicalDevice device);
        
    };
}