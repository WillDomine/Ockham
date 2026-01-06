#pragma once

#include "backend/VulkanContext.h"
#include <vector>

namespace Ockham {

    class Model {
        public:
            struct Vertex {
                float x,y;
                float r,g,b;

                static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
                static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
            };

            Model(VulkanContext& context, const std::vector<Vertex>& vertices);
            ~Model();

            void bind(VkCommandBuffer commandBuffer);
            void draw(VkCommandBuffer commandBuffer);

        private:
            VulkanContext& context;
            VkBuffer vertexBuffer;
            VkDeviceMemory vertexBufferMemory;
            uint32_t vertexCount;

            void createVertexBuffers(const std::vector<Vertex>& vertices);

            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    };

}