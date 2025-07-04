/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#define STRINGIFY_DETAIL(x) #x
#define STRINGIFY(x) STRINGIFY_DETAIL(x)

// Backend registry macros
#define ORHI_BACKEND_HEADER(backend, filename) STRINGIFY(orhi/impl/backend/filename.h)
#define ORHI_BACKEND_TYPE(backend, type) orhi::impl::backend::type

// Selection logic
#if defined(ORHI_SELECT_VULKAN)
#define ORHI_SELECTED_BACKEND vk
#elif defined(ORHI_SELECT_MOCK)
#define ORHI_SELECTED_BACKEND mock
#else
#error No backend selected
#endif

// Selected API macros
#define ORHI_SELECTED_API_HEADER_LOCATION(filename) \
	ORHI_BACKEND_HEADER(ORHI_SELECTED_BACKEND, filename)
#define ORHI_SELECTED_API_TYPE(type) \
	ORHI_BACKEND_TYPE(ORHI_SELECTED_BACKEND, type)

// Expose macros
#define ORHI_EXPOSE_SELECTED_TYPE(type) \
	namespace orhi { using type = ORHI_SELECTED_API_TYPE(type); }

#define ORHI_EXPOSE_BACKEND_TYPE(backend, type) \
	namespace orhi::impl::backend { using type = ORHI_BACKEND_TYPE(backend, type); }
