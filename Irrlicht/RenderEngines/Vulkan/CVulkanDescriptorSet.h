#pragma once

#include "CVulkanUtility.h"
#include "CVulkanResources.h"

namespace irr
{
    namespace video
    {
        /** @addtogroup Vulkan
         *  @{
         */

         /** Wrapper for the Vulkan descriptor set object. */
        class VulkanDescriptorSet : public CVulkanDeviceResource
        {
        public:
            VulkanDescriptorSet(CVulkanDriver* owner, VkDescriptorSet set, VkDescriptorPool pool);
            virtual ~VulkanDescriptorSet();

            /** Returns a handle to the Vulkan descriptor set object. */
            VkDescriptorSet getHandle() const { return mSet; }

            /** Updates the descriptor set with the provided values. */
            void write(VkWriteDescriptorSet* entries, u32 count);

            // Inherited via CVulkanDeviceResource
            virtual void OnDeviceLost(CVulkanDriver * device) _IRR_OVERRIDE_;
            virtual void OnDeviceRestored(CVulkanDriver * device) _IRR_OVERRIDE_;
            virtual void OnDeviceDestroy(CVulkanDriver* device) _IRR_OVERRIDE_ {}

        protected:
            VkDescriptorSet mSet;
            VkDescriptorPool mPool;
        };

        /** @} */
    }
}