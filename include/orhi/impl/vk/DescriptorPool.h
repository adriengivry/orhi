/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorPool.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/DescriptorSet.h>
#include <orhi/impl/vk/Device.h>

#include <deque>

namespace orhi::impl::vk
{
	struct DescriptorPoolContext
	{
		Device& device;
		std::deque<DescriptorSet> descriptorSets;
	};

	using DescriptorPool = api::TDescriptorPool<BackendTraits>;
}
