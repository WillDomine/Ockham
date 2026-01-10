#pragma once

#include "../src/graphics/vk_mem_alloc.h"
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include <optional>

namespace Ockham
{

    class Window;

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class VulkanContext
    {
    public:
        VulkanContext();
        ~VulkanContext();

        void init(Window &window);

        // Getters needed by the Renderer
        VkInstance getInstance() const { return instance; }
        VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
        VkDevice getDevice() const { return logicalDevice; }
        VkSurfaceKHR getSurface() const { return surface; }
        VkQueue getGraphicsQueue() const { return graphicsQueue; }
        VkQueue getPresentQueue() const { return presentQueue; }
        VmaAllocator getAllocator() const { return allocator; }

        //Runs for single time commands the will move from CPU -> GPU
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        // Helper for other classes (like Renderer) to check queue indices
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    private:
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice logicalDevice;
        VkSurfaceKHR surface;
        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VmaAllocator allocator;

        const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
        const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        //Stores the Commands from the CPU
        VkCommandPool transientCommandPool;
        void createCommandPool();

        void createInstance();
        void setupDebugMessenger();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createAllocator();

        bool checkValidationLayerSupport();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);
    };
}