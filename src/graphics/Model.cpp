#include "Model.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#include <cstring>
#include <iostream>

namespace Ockham
{

    Model::Model(VulkanContext &context, VmaAllocator allocator, const std::vector<Vertex> &vertices)
        : context(context), allocator(allocator)
    {
        createVertexBuffers(vertices);
    }

    Model::~Model()
    {
        vmaDestroyBuffer(allocator, vertexBuffer, vertexBufferAllocation);
    }

    void Model::createVertexBuffers(const std::vector<Vertex> &vertices)
    {
        vertexCount = static_cast<uint32_t>(vertices.size());
        assert(vertexCount >= 3 && "Vertex count must be at least 3");

        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

        VkBuffer stagingBuffer;
        VmaAllocation stagingBufferAllocation;

        // CPU buffer
        VkBufferCreateInfo stagingBufferInfo{};
        stagingBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        stagingBufferInfo.size = bufferSize;
        stagingBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

        VmaAllocationCreateInfo stagingAllocInfo{};
        stagingAllocInfo.usage = VMA_MEMORY_USAGE_CPU_ONLY;

        if (vmaCreateBuffer(allocator, &stagingBufferInfo, &stagingAllocInfo, &stagingBuffer, &stagingBufferAllocation, nullptr) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create vertex buffer!");
        }

        void *data;
        vmaMapMemory(allocator, stagingBufferAllocation, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vmaUnmapMemory(allocator, stagingBufferAllocation);

        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = bufferSize;
        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

        // Fast GPU Buffer
        VmaAllocationCreateInfo allocInfo{};
        allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

        if (vmaCreateBuffer(allocator, &bufferInfo, &allocInfo, &vertexBuffer, &vertexBufferAllocation, nullptr) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create vertex buffer!");
        }

        //Copy from staging to Vertex
        VkCommandBuffer commandBuffer = context.beginSingleTimeCommands();

        VkBufferCopy copyRegion{};
        copyRegion.size = bufferSize;
        vkCmdCopyBuffer(commandBuffer, stagingBuffer, vertexBuffer, 1, &copyRegion);

        context.endSingleTimeCommands(commandBuffer);

        vmaDestroyBuffer(allocator, stagingBuffer, stagingBufferAllocation);
    }

    void Model::bind(VkCommandBuffer commandBuffer)
    {
        VkBuffer buffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
    }

    void Model::draw(VkCommandBuffer commandBuffer)
    {
        vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
    }

    std::vector<VkVertexInputBindingDescription> Model::Vertex::getBindingDescriptions()
    {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> Model::Vertex::getAttributeDescriptions()
    {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; // 2 floats
        attributeDescriptions[0].offset = offsetof(Vertex, position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT; // 3 floats
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
}