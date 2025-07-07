<p align="center">
    <a href="https://github.com/adriengivry/orhi-cmake-template"><img alt="cmake template" src="https://img.shields.io/badge/Create%20CMake%20Project-0068C7"/></a>
    <a href="https://github.com/adriengivry/orhi-premake5-template"><img alt="premake5 template" src="https://img.shields.io/badge/Create%20premake5%20Project-009F24"/></a>
    <br>
    <a href="https://github.com/adriengivry/orhi"><img alt="size" src="https://img.shields.io/github/repo-size/adriengivry/orhi"/></a>
    <a href="https://github.com/adriengivry/orhi/blob/main/LICENSE"><img alt="license" src="https://img.shields.io/github/license/adriengivry/orhi?color=green"/></a>
    <br>
    <a href="https://github.com/adriengivry/orhi/releases"><img alt="release" src="https://img.shields.io/github/v/release/adriengivry/orhi"/></a>
</p>

# OpenRHI

**OpenRHI** — *orhi* — is a simple, permissive (MIT licensed), cross-platform **Render Hardware Interface** written in C++20.

Write hardware-agnostic code once, and ship it to multiple platforms using different graphics APIs.

## Supported Graphics APIs

> [!IMPORTANT]
> **OpenRHI** [API](include/orhi/api/) is expected to undergo significant changes as support for additional graphics backends is added, in order to accommodate the requirements and design philosophies of each backend.

The primary target for **OpenRHI** is **desktop platforms**, but its [API](include/orhi/api/) is designed to be flexible enough to support any backend your product may require.

Target platforms are:
- Windows 🪟
- Linux 🐧
- MacOS 🍎

### Implementation Status

| API | Target Platforms | Status |
|-|-|-|
| Vulkan | 🪟🐧 | 🌓 Partial |
| DirectX 12 | 🪟 | 📅 Planned |
| Mock (Headless) | 🪟🐧🍎 | 📅 Planned |
| Metal | 🍎 | 📅 Planned  |
| OpenGL | 🪟🐧 | ☠️ Deprecated / Moved to [BareGL](https://github.com/adriengivry/baregl) |

## Features

**OpenRHI is...**

- 🐣 **Simple:** easy to understand and extend, and extremely quick to integrate.
- ⚡ **Fast:** minimal overhead, template-based design.
- ⛓️‍💥 **Standalone:** comes with everything you need, requires no additional libraries.
- 📃 **Documented:** fully documented source code.
- 💻 **Cross-platform:** supports Windows, MacOS, and Linux.
- ⚙️ **Modern:** leveraging the power of C++20.

## Template Projects

Skip the setup and start building your project in less than 5 minutes using one of these templates:
- [Premake5 Template Project](https://github.com/adriengivry/orhi-premake5-template)
- [CMake Template Project](https://github.com/adriengivry/orhi-cmake-template)

## Multi-Backend Philosophy
**OpenRHI** is designed to compile with as many graphics APIs as you want, all bundled into the final application.

If you need to bundle more than one graphics API into your project, you can achieve that by using the following options:

**Premake5:**
```powershell
premake5
    [action]
    --compile-vulkan
    --compile-mock
```

**CMake:**
```powershell
cmake
    -DORHI_COMPILE_VULKAN=ON 
    -DORHI_COMPILE_MOCK=ON
```

### Using Graphics APIs Explicitely
Compiled backends are always available through their respective headers, and objects from multiple backends can live together in the same application.
```cpp
// Include some Vulkan headers...
#include <orhi/impl/vk/Backend.h>

// Include some Mock headers...
#include <orhi/impl/vk/Backend.h>

int main()
{
    // Common to all backend
    orhi::data::BackendDesc backendDesc{
        .debug = true,
        .extensions = GetGlfwRequiredExtensions(),
        .win32_windowHandle = glfwGetWin32Window(window),
        .win32_instanceHandle = GetModuleHandle(nullptr)
    };

    // Create Vulkan and Mock backend side-by-side.
    orhi::impl::vk::Backend vkBackend { backendDesc };
    orhi::impl::mock::Backend mockBackend { backendDesc }

    return 0;
}
```

### Selecting Default Graphics API
A default graphics API can be selected by defining one of the following defines to your project:
- `ORHI_SELECT_VULKAN` (also requires `ORHI_COMPILE_VULKAN` to be defined)
- `ORHI_SELECT_MOCK` (also requires `ORHI_COMPILE_MOCK` to be defined)

**Premake5:**
```lua
defines { "ORHI_SELECT_VULKAN", "ORHI_COMPILE_VULKAN" }
-- or
defines { "ORHI_SELECT_MOCK", "ORHI_COMPILE_MOCK" }
```
**CMake:**
```cmake
add_compile_definitions(ORHI_SELECT_VULKAN ORHI_COMPILE_VULKAN)
# or
add_compile_definitions(ORHI_SELECT_MOCK ORHI_COMPILE_MOCK)
```

### Using Default Graphics API
Once a graphics API is selected, it can be included using agnostic headers:
```cpp
// Default Graphics API headers.
// Included symbols will vary depending on the selected graphics API.
// Agnostic aliases also get exposed, e.g. orhi::Backend, orhi::Framebuffer, etc.
#include <orhi/Backend.h>
#include <orhi/Buffer.h>

// Can also be combined with explicitely included backends
#include <orhi/impl/mock/Backend.h>

int main()
{
    // Create objects using the default graphics API.
    // i.e. if Vulkan is selected, orhi::Backend will resolve to orhi::impl::vk::Backend
    orhi::Backend backend{}; 

    // And also create graphics API-specific objects
    orhi::impl::mock::Backend backend{};

    return 0;
}
```

## Building & Running Examples (Premake)
> [!IMPORTANT]
> Example projects rely on [glfw](https://github.com/glfw/glfw) and [glm](https://github.com/g-truc/glm), which are included as submodules. Make sure to initialize submodules for example projects to function properly!

### Windows Quick Start (Visual Studio 2022)
From the command-line:
```powershell
# Clone orhi and navigate to the "examples" folder
git clone --recurse-submodules https://github.com/adriengivry/orhi
cd .\orhi\examples\

# Generate example projects and open in Visual Studio
.\gen_examples.bat
.\orhi-examples.sln
```
> [!TIP]
> You can edit `gen_examples.bat` to modify the options used to generate the projects, such as:
> - `--compile-vulkan` compile Vulkan backend 
> - `--compile-mock` compile Mock backend
> - `--gfxapi=vulkan` set Vulkan as the default graphics API

### Any Platform (Windows, MacOS, Linux)
1. Get [premake5](https://premake.github.io/download):
   * once downloaded, you can install the executable in a convenient location
   * from there, you can either:
      * *(recommended)* add the folder containing premake5 to your `PATH`
      * or you can refer to the executable using its path
2. Clone `orhi` and navigate to the `examples/` folder
```powershell
git clone https://github.com/adriengivry/orhi
cd orhi/examples/
```
1. From the command line, execute:
> [!NOTE]
> If premake hasn't been added to PATH, use the path to downloaded executable instead
```powershell
premake5				
    [action*]
    --compile-vulkan	# compile Vulkan backend 
    --compile-mock		# compile Mock backend
    --gfxapi=vulkan		# sets Vulkan as the default graphics API
```
**for a full list of available actions, check-out: [Premake5/Using-Premake](https://premake.github.io/docs/Using-Premake/).*

## Adding OpenRHI to Your Project
**OpenRHI** is setup to work with `premake5` and `CMake` out of the box.

> [!WARNING]
> **OpenRHI** only supports static linking at the moment, so you cannot build it as a shared library. You'll need to add `orhi` to your project files instead.

To get started, add `orhi` as a submodule to your repository:
```powershell
git submodule add https://github.com/adriengivry/orhi
```
...or clone the `orhi` repository inside of your project.

### Option 1: Premake5
In your workspace's `premake5.lua` file, add:
```lua
workspace "your-workspace-name"
    -- Your settings
    include "path/to/orhi"

    -- Default graphics API (⚠️ define only one)
    defines { "ORHI_SELECT_VULKAN", "ORHI_COMPILE_VULKAN" }
    -- or
    defines { "ORHI_SELECT_MOCK", "ORHI_COMPILE_MOCK" }
```
Then in your project's `premake5.lua`, add:
```lua
project "your-project-name"
    includedirs {
        "path/to/orhi/include/folder",
    }

    links {
        "orhi"
    }
```

### Option 2: CMake
In your project's `CMakeLists.txt` file:
```cmake
# Default graphics API (⚠️ define only one)
add_compile_definitions(ORHI_SELECT_VULKAN ORHI_COMPILE_VULKAN)
# or
add_compile_definitions(ORHI_SELECT_MOCK ORHI_COMPILE_MOCK)

# Add orhi's directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/path/to/orhi)

# Link against the orhi library.
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    orhi
)
```

## Contributing
All contributions to **OpenRHI** are welcomed — whether it's reporting bugs, suggesting new features, or submitting code improvements.

Feel free to open issues or submit pull requests (PRs) for review. Every bit of help makes a difference!

For more information on contributing, check out [CONTRIBUTING.md](CONTRIBUTING.md).

*By contributing, you agree that your contributions will be licensed under the [MIT License](LICENSE).*


## License
**OpenRHI** is licensed under the [MIT License](LICENSE).

You are free to use, modify, and distribute this project with proper attribution. See the license file for more details.