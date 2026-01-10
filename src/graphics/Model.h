#pragma once

#include "backend/VulkanContext.h"
#include "vk_mem_alloc.h"
#include <glm/glm.hpp>
#include <vector>

namespace Ockham {

    class Model {
        public:
            struct Vertex {
                glm::vec2 position;
                glm::vec3 color;

                static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
                static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
            };

            Model(VulkanContext& context, VmaAllocator allocator, const std::vector<Vertex>& vertices);
            ~Model();

            Model(const Model&) = delete;
            Model& operator=(const Model&) = delete;

            void bind(VkCommandBuffer commandBuffer);
            void draw(VkCommandBuffer commandBuffer);

        private:
            VulkanContext& context;
            VmaAllocator allocator;

            VkBuffer vertexBuffer;
            VmaAllocation vertexBufferAllocation;
            uint32_t vertexCount;

            void createVertexBuffers(const std::vector<Vertex>& vertices);
    };

}