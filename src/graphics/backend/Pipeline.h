#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace Ockham {

    //Holds fixed function settings, allows sharing settings over different pipelines easier
    struct PipelineConfigInfo {
        VkPipelineViewportStateCreateInfo viewportInfo{};
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
        VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
        VkPipelineMultisampleStateCreateInfo multisampleInfo{};
        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo{};
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class Pipeline {
        public:
            //Constructor
            Pipeline(VkDevice device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
            //Destructor 
            ~Pipeline();

            //Delete copy constructors to avoid accidental double deletion of the pipeline handle
            Pipeline(const Pipeline&) = delete;
            Pipeline& operator=(const Pipeline&) = delete;

            //Binds the pipeline to the command buffer.
            void bind(VkCommandBuffer commandBuffer);
            //Helps generate default settings
            static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

        private:
            static std::vector<char> readFile(const std::string& filepath);
            void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);

            void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

            VkDevice logicalDevice;
            VkPipeline graphicsPipeline; 
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;

    };
}