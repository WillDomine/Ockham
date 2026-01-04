#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

namespace Ockham {

    class Window;

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilites;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class Swapchain {
        public:
            //Constructor
            Swapchain(VkPhysicalDevice physicalDevice, VkDevice logicalDevice, VkSurfaceKHR surface, Window& window);
            //Destructor
            ~Swapchain();

            //Getters
            VkSwapchainKHR getSwapchain() const { return swapChain; }
            VkFormat getImageFormat() const { return swapChainImageFormat; }
            VkExtent2D getExtent() const { return swapChainExtent; }

            //Get the image views to attach them to the frame buffer;
            const std::vector<VkImageView>& getImageViews() const { return swapChainImageViews; }

        private:
            VkDevice logicalDevice;
            VkSwapchainKHR swapChain;

            //Images in the swapchain
            std::vector<VkImage> swapChainImages;

            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;

            //Views into the images
            std::vector<VkImageView> swapChainImageViews;

            void init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, Window& window);
            void createImageViews();

            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, Window& window);
    };

}