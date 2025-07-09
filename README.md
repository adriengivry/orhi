# OpenRHI

**OpenRHI** — *orhi* — is a simple, permissive (MIT licensed), cross-platform **Render Hardware Interface** built with modern C++20.

Write hardware-agnostic graphics code once, then deploy it seamlessly across multiple platforms and graphics APIs.

**OpenRHI** is...
- 🧩 **Simple:** Easy to understand and extend
- ⚡ **Fast:** Minimal runtime overhead with template-based design
- ⛓️‍💥 **Standalone:** Zero external dependencies
- 📃 **Documented:** Comprehensive source code documentation
- 🌈 **Cross-platform:** Native support for Windows, macOS, and Linux
- 🚀 **Modern:** Harnesses the full power of C++20
- ⚙️ **Build-ready:** Quick setup with [Premake5](https://premake.github.io/) or [CMake](https://cmake.org/)

## Supported Graphics APIs

**OpenRHI** primarily targets **desktop platforms**, with an [API](include/orhi/api/) architecture designed for maximum flexibility to support any backend your application needs.

**Target platforms:** Windows (🪟), Linux (🐧), and macOS (🍎)

### Implementation Status

| Graphics API | Platforms | Status |
|-|-|-|
| Vulkan | 🪟🐧 | 🌓 Partial |
| DirectX 12 | 🪟 | 📅 Planned |
| Mock (Headless) | 🪟🐧🍎 | 📅 Planned |
| Metal | 🍎 | 📅 Planned  |
| OpenGL | 🪟🐧 | ☠️ Deprecated — Moved to [BareGL](https://github.com/adriengivry/baregl) |

> [!WARNING] Early Development Stage
> **OpenRHI** is actively evolving as support for additional graphics backends is added. The [API](include/orhi/api/) may change to accommodate the unique requirements and design philosophies of each backend. Implementation details are also subject to refinement as the project works toward production-quality standards.

## Build Configuration
| Option | C++ Define | CMake Option | Premake5 Option |
| - | - | - | - |
| Compile Vulkan backend | `ORHI_COMPILE_VULKAN` | `DORHI_COMPILE_VULKAN` |  `--compile-vulkan` |
| Compile Mock backend | `ORHI_COMPILE_MOCK` | `DORHI_COMPILE_MOCK` | `--compile-mock` |
| Set Vulkan as the default backend | `ORHI_SELECT_VULKAN` | - | - |
| Set Mock as the default backend | `ORHI_SELECT_MOCK` | - | - |

> [!NOTE]
> **OpenRHI** currently builds only as a static library.

## Multi-Backend Architecture
**OpenRHI** supports compiling with multiple graphics APIs simultaneously.

You can also choose which graphics API serves as the default backend for API-agnostic objects, while still having access to backend-specific implementations when needed.

### Using the Default Graphics API
```cpp
// Include the API-agnostic header
// Requires ORHI_SELECT_{API} to be defined
#include <orhi/Buffer.h>

// Create a buffer using your selected graphics API
// (e.g., Vulkan when ORHI_SELECT_VULKAN is defined)
orhi::Buffer buffer{};
```

### Using Specific Graphics APIs
```cpp
// Include Vulkan-specific headers
// Requires ORHI_COMPILE_VULKAN to be defined
#include <orhi/impl/vk/Buffer.h>

// Include Mock backend headers
// Requires ORHI_COMPILE_MOCK to be defined
#include <orhi/impl/mock/Buffer.h>

orhi::impl::vk::Buffer vulkanBuffer{};
orhi::impl::mock::Buffer mockBuffer{};
```

## Examples
**OpenRHI** comes with a set of [examples](examples/) for you to try.

## Contributing
All contributions to **OpenRHI** are welcome — from bug reports and feature suggestions to code improvements and documentation enhancements.

Feel free to open issues or submit pull requests for review. Every contribution helps make **OpenRHI** better!

For more information on contributing, check out [CONTRIBUTING.md](CONTRIBUTING.md).

*By contributing, you agree that your contributions will be licensed under the [MIT License](LICENSE).*


## License
**OpenRHI** is licensed under the [MIT License](LICENSE).

You are free to use, modify, and distribute this project with proper attribution. See the license file for more details.