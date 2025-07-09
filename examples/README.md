# OpenRHI Examples

This directory contains practical examples demonstrating **OpenRHI** functionalities.

> [!IMPORTANT]
> **Dependencies Required:** Examples depend on [GLFW](https://github.com/glfw/glfw) and [GLM](https://github.com/g-truc/glm), which are included as Git submodules. Initialize submodules before building examples.

All example projects use [Premake5](https://premake.github.io/) for cross-platform project generation.

## Quick Start

### Windows (Visual Studio 2022)
For Windows development, a `premake5.exe` executable is bundled with **OpenRHI**. Generate Visual Studio 2022 project files instantly:

```bash
.\gen_examples.bat
```

### Other Platforms (Linux, macOS, etc.)

#### Prerequisites
1. Initialize Git submodules:
   ```bash
   git submodule update --init --recursive
   ```
2. Install [Premake5](https://premake.github.io/) for your platform

#### Build Configuration
Navigate to the `examples/` directory and run:
```bash
premake5 [action] [options...]
```

**Available Options:**
- `--compile-vulkan` — Enable Vulkan backend compilation
- `--compile-mock` — Enable Mock (headless) backend compilation  
- `--gfxapi=vulkan` — Set Vulkan as the default graphics API
- `--gfxapi=mock` — Set Mock as the default graphics API

**Example:**
```bash
premake5 gmake2 --compile-vulkan --gfxapi=vulkan
```

> [!TIP]
> For a complete list of available actions, see the [Premake5 documentation](https://premake.github.io/docs/Using-Premake/).
