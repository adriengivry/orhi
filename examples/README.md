# OpenRHI Examples

This directory contains practical examples demonstrating **OpenRHI** functionalities.

> [!IMPORTANT]
> **Dependencies Required:** Examples depend on [glfw](https://github.com/glfw/glfw), [glm](https://github.com/g-truc/glm), and [stb](https://github.com/nothings/stb), which are included as Git submodules. Initialize submodules before building examples.

All example projects use [CMake](https://cmake.org/) for cross-platform project generation.

## Quick Start

### Building Examples with CMake

To build the examples, you need to enable the `ORHI_GENERATE_EXAMPLES` option in CMake.

#### Prerequisites
1. Initialize Git submodules:
   ```bash
   git submodule update --init --recursive
   ```
2. Install [CMake](https://cmake.org/) for your platform

#### Windows (Visual Studio)

```pwsh
# From the root project directory
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DORHI_GENERATE_EXAMPLES=ON -DORHI_COMPILE_VULKAN=ON ..
```

Then open the generated solution file (`orhi.sln`) in Visual Studio.

#### Linux/macOS

```bash
# From the root project directory
mkdir build
cd build
cmake -DORHI_GENERATE_EXAMPLES=ON -DORHI_COMPILE_VULKAN=ON ..
make
```

### Configuration Options

For the examples, you can configure the following CMake options:

- `ORHI_GENERATE_EXAMPLES` — Enable building the examples (must be ON to build examples)
- `ORHI_COMPILE_VULKAN` — Enable Vulkan backend compilation
- `ORHI_COMPILE_MOCK` — Enable Mock (headless) backend compilation
- `ORHI_EXAMPLES_GFX_API` — Set the graphics API to use for examples (values: "vulkan", "mock")
- `ORHI_WINDOW_SYSTEM` — Select the window system or use headless mode (values: "xlib", "xcb", "wayland", "none")
