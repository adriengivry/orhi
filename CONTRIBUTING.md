# Contributing to OpenRHI
First of all, thank you for your interest in OpenRHI! Any contribution is welcome, including:
- Reporting a bug
- Submitting a fix
- Proposing new features
- Improving code quality

## We Develop with GitHub
We use GitHub to host code, track issues, submit feature requests, and manage pull requests.

## Creating a Pull Request
1. Fork the repository.
2. Create your branch from the `main` branch.
3. Review your code before submitting (conduct build and quality checks).
4. Create a pull request targeting the `main` branch.

## Any contributions you make will be under the MIT Software License
When you submit code changes, your contributions are understood to be under the same [MIT License](http://choosealicense.com/licenses/mit/) that covers the project.

## Coding Conventions
### File Header
Every file must include the following header:
```cpp
/**
* @project: orhi (OpenRHI)
* @author: {your name here}
* @licence: MIT
*/
```

### Naming
| | |
|-|-|
| N.1 | Folders and namespaces use the `lower_snake_case` notation. |
| N.2 | Custom Types (*structs*, *classes*, *enums*, *typedefs*) use the `UpperCamelCase` notation. |
| N.3 | Functions & methods use the `UpperCamelCase` notation. |
| N.4 | Variables use the `lowerCamelCase` notation (unless specified otherwise, see below). |
| N.5 | Private member variables are prefixed with `m_` (e.g. `m_elapsedTime`). |
| N.6 | Function parameters are prefixed with `p_` (e.g. `p_enabled` ). |
| N.7 | Compile-time constants (`constexpr`) are prefixed with `k_` (e.g. `k_pi`). |
| N.8 | Do not use abbreviations. |
| N.9 | Interfaces are prefixed with `I`, abstract classes with `A`, templated classes with `T`, and enum types with `E`. |
| N.10 | Enum values are in `SHOUT_CASE`. |

### Formatting
| | |
|-|-|
| F.1 | Curly braces must be placed on their own lines, except for the opening brace of lambdas. |
| F.2 | Code must be indented using tabs. |
| F.3 | Keep a low indentation level (use early returns, split functionalities, reduce complexity). |
| F.4 | Always use braces for scopes (*if*, *for*, *while*, etc.). |
| F.5 | Avoid single line `if` statements (e.g. `if (condition) return 0;`). |
| F.6 | Always end your files with an empty line. |
| F.7 | Avoid aligning variable names and values using tabulations. |

### Classes
| | |
|-|-|
| C.1 | Members are ordered by access level (`public`, `protected`, `private`). |
| C.2 | Methods always come first, followed by member variables. |

### Includes
| | |
|-|-|
| I.1 | Includes are ordered by category:<br>&nbsp;&nbsp;&nbsp;&nbsp;1. Main Header (for .cpp file implementing .h)<br>&nbsp;&nbsp;&nbsp;&nbsp;2. Project/Local Headers<br>&nbsp;&nbsp;&nbsp;&nbsp;3. Third-Party Library Headers<br>&nbsp;&nbsp;&nbsp;&nbsp;4. System/Standard Library Headers |
| I.2 | Includes in the same group are in lexicographic order, with lowercase precedence (e.g. `aa`, `aA`, `Aa`, `AA`). |
| I.3 | Included file paths are fully specialized (`project/namespace/File.h`). |
| I.4 | Include statements use brackets (`<>`) over quotation marks (`""`). |

### Documentation
| | |
|-|-|
| D.1 | Document public types, methods, and functions using the [Javadoc style](https://en.wikipedia.org/wiki/Javadoc). |

### General
| | |
|-|-|
| G.1 | Almost always avoid *macros*. Use `constexpr` whenever possible. |
| G.2 | Always use forward slashes when it comes to paths. |
| G.3 | Prefer anonymous functions over private methods when possible. |
| G.4 | Avoid declaring multiple classes in a single header file. |
| G.5 | Prefer stack allocations over heap allocations. |
| G.6 | Almost always avoid manual heap allocations (`malloc`, `new`, `delete`). |
| G.7 | Avoid raw pointers (use smart pointers when required). |
| G.8 | Use `std::array` over dynamic collections (e.g. `std::vector`) when the size is fixed. |
| G.9 | Use `std::string_view`, `std::span`, and *const references* whenever possible. |
| G.10| Prefer composition over inheritance. |
| G.11| Use assertions to validate inputs when type checks aren't sufficient. |

*Note: Some coding conventions may have been overlooked during the writing of this document, so always refer to the existing codebase.*
