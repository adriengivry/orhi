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

**OpenRHI** — *orhi* — is a simple, permissive (MIT license), cross-platform **Render Hardware Interface** written in C++20.

Write hardware-agnostic code once, and ship it to multiple platforms using different graphics APIs.

## Supported Graphics APIs
The primary target for **OpenRHI** is **desktop platforms**, but its [API](include/orhi/api/) is designed to be flexible enough to support any backend your product may require.

Target platforms are:
- Windows 🪟
- Linux 🐧
- MacOS 🍎

### Implementation Status

| API | Target Platforms | Status | Next Steps |
|-|-|-|-|
| Mock (Headless) | 🪟🐧🍎 | ✅ Production Ready | - |
| OpenGL 4.5 | 🪟🐧 | ✅ Production Ready | Compute & geometry shaders |
| Vulkan | 🪟🐧 | 📅 Planned | - |
| DirectX | 🪟 | ❓ TBD | - |
| Metal | 🍎 | ❓ TBD | - |
| Software | 🪟🐧🍎 | ❓ TBD | - |

> ⚠️ **OpenRHI** [API](include/orhi/api/) is expected to undergo significant changes as support for additional graphics backends is added, in order to accommodate the requirements and design philosophies of each backend.

## Features

**OpenRHI is...**

- 🐣 **Simple:** easy to understand and extend, and extremely quick to integrate.
- ⚡ **Fast:** minimal overhead, template-based design.
- ⛓️‍💥 **Standalone:** comes with everything you need, requires no additional libraries.
- 📃 **Documented:** fully documented source code.
- 💻 **Cross-platform:** supports Windows, MacOS, and Linux.
- ⚙️ **Modern** leveraging the power of C++20.

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
	--compile-opengl
	--compile-mock
```

**CMake:**
```powershell
cmake
	-DORHI_COMPILE_OPENGL=ON 
	-DORHI_COMPILE_MOCK=ON
```

### Using Graphics APIs Explicitely
Compiled backends are always available through their respective headers, and objects from multiple backends can live together in the same application.
```cpp
// Include some OpenGL headers...
#include <orhi/impl/gl/Backend.h>
#include <orhi/impl/gl/Framebuffer.h>

// Include some Mock headers...
#include <orhi/impl/mock/Backend.h>
#include <orhi/impl/mock/ShaderProgram.h>

int main()
{
	// Create OpenGL objects
	orhi::impl::gl::Backend glBackend;
	orhi::impl::gl::Framebuffer glFramebuffer;

	// Create Mock objects
	orhi::impl::mock::Backend mockBackend;
	orhi::impl::mock::ShaderProgram mockShader;

	return 0;
}
```

### Selecting Default Graphics API
A default graphics API can be selected by defining one of the following defines to your project:
- `ORHI_SELECT_OPENGL` (also requires `ORHI_COMPILE_OPENGL` to be defined)
- `ORHI_SELECT_MOCK` (also requires `ORHI_COMPILE_MOCK` to be defined)

**Premake5:**
```lua
defines { "ORHI_SELECT_OPENGL", "ORHI_COMPILE_OPENGL" }
-- or
defines { "ORHI_SELECT_MOCK", "ORHI_COMPILE_MOCK" }
```
**CMake:**
```cmake
add_compile_definitions(ORHI_SELECT_OPENGL ORHI_COMPILE_OPENGL)
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
#include <orhi/Framebuffer.h>
#include <orhi/ShaderProgram.h>

// Can also be combined with explicitely included backends
#include <orhi/impl/mock/Backend.h>

int main()
{
	// Create objects using the default graphics API.
	// i.e. if OpenGL is selected, orhi::Backend will resolve to orhi::impl::gl::Backend
	orhi::Backend backend; 
	orhi::Framebuffer framebuffer;
	orhi::ShaderProgram shader;

	// And also create graphics API-specific objects
	orhi::impl::mock::Backend backend;

	return 0;
}
```

## In Practice
**OpenRHI** aims to **reduce boilerplate** and **simplify tedious tasks**, while maintaining a **consistent design** throughout its [API](include/orhi/api/).

### Creating Shader Program
```cpp
const std::string vertexSource = /* ... */;
const std::string fragmentSource = /* ... */;

orhi::ShaderStage vs(orhi::types::EShaderType::VERTEX);
vs.Upload(vertexSource);
vs.Compile();

orhi::ShaderStage fs(orhi::types::EShaderType::FRAGMENT);
fs.Upload(fragmentSource);
fs.Compile();

orhi::ShaderProgram program;
program.Attach(vs);
program.Attach(fs);
program.Link();
```

### Creating Vertex Array (Mesh Data)
```cpp
const Vertex vertices[] = { /* ... */ };
const uint32_t indices[] = { /* ... */ };

orhi::VertexBuffer vb;
vb.Allocate(sizeof(vertices), orhi::types::EAccessSpecifier::STATIC_DRAW);
vb.Upload(vertices);

orhi::IndexBuffer ib;
ib.Allocate(sizeof(indices), orhi::types::EAccessSpecifier::STATIC_DRAW);
ib.Upload(indices);

orhi::VertexArray va;
va.SetLayout(
	std::to_array<orhi::data::VertexAttribute>({
		{ orhi::types::EDataType::FLOAT, 3 }, // Position
		{ orhi::types::EDataType::FLOAT, 2 }, // UV
		{ orhi::types::EDataType::FLOAT, 3 }  // Normals
	}), vb, ib
);
```
### Creating Framebuffer
```cpp
// Texture creation (framebuffer color attachment)
std::shared_ptr<orhi::Texture> colorBuffer = std::make_shared<orhi::Texture>(
	orhi::types::ETextureType::TEXTURE_2D
);
colorBuffer->Allocate(orhi::data::TextureDesc{
	.width = 800,
	.height = 600,
	.internalFormat = orhi::types::EInternalFormat::RGBA32F,
	.useMipMaps = false,
	.mutableDesc = orhi::data::MutableTextureDesc{
		.format = orhi::types::EFormat::RGBA,
		.type = orhi::types::EPixelDataType::FLOAT
	}
});

// Renderbuffer creation (framebuffer depth attachment)
std::shared_ptr<orhi::Renderbuffer> depthBuffer = std::make_shared<orhi::Renderbuffer>();
depthBuffer->Allocate(800, 600, orhi::types::EInternalFormat::DEPTH_COMPONENT);

orhi::Framebuffer framebuffer;
framebuffer.Attach(colorBuffer, orhi::types::EFramebufferAttachment::COLOR);
framebuffer.Attach(depthBuffer, orhi::types::EFramebufferAttachment::DEPTH);
assert(framebuffer.Validate());
```

## Building & Running Examples (Premake)
### Windows Quick Start (Visual Studio 2022)
> ⚡ Clone, build, and run **OpenRHI** examples in less than 2 minutes!

From the command-line:
```powershell
# Clone orhi and navigate to the repository root
git clone https://github.com/adriengivry/orhi
cd .\orhi\

# Generate example projects and open in Visual Studio
.\gen_examples.bat
.\examples\orhi-examples.sln
```
> ℹ️ You can edit `gen_examples.bat` to modify the options used to generate the projects, such as:
> - `--compile-opengl` compile OpenGL backend 
> - `--compile-mock` compile Mock backend
> - `--gfxapi=opengl` set OpenGL as the default graphics API

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
> ℹ️ If premake hasn't been added to PATH, use the path to downloaded executable instead
```powershell
premake5				
	[action*]
	--compile-opengl	# compile OpenGL backend 
	--compile-mock		# compile Mock backend
	--gfxapi=opengl		# sets OpenGL as the default graphics API
```
**for a full list of available actions, check-out: [Premake5/Using-Premake](https://premake.github.io/docs/Using-Premake/).*

## Adding OpenRHI to Your Project
**OpenRHI** is setup to work with `premake5` and `CMake` out of the box.

> ⚠️ **OpenRHI** only supports static linking at the moment, so you cannot build it as a shared library. You'll need to add `orhi` to your project files instead.

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
	defines { "ORHI_SELECT_OPENGL", "ORHI_COMPILE_OPENGL" }
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
add_compile_definitions(ORHI_SELECT_OPENGL ORHI_COMPILE_OPENGL)
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

*By contributing, you agree that your contributions will be licensed under the [MIT License](LICENSE).*


## License
**OpenRHI** is licensed under the [MIT License](LICENSE).

You are free to use, modify, and distribute this project with proper attribution. See the license file for more details.