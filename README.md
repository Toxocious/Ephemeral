<div align="center">
  <!-- <img src="./app/images/Assets/banner.png" title="Pokemon Ephemeral Logo" alt="Pokemon Ephemeral Logo" /> -->
  <h1 align="center">Pok&eacute;mon Ephemeral</h1>

  **Pok&eacute;mon Ephemeral** is a heavy work-in-progress Pok&eacute;mon MMORPG, custom built from the ground up.

  <img src="https://img.shields.io/github/issues/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <img src="https://img.shields.io/github/forks/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <img src="https://img.shields.io/github/stars/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <br />
  <img src="https://img.shields.io/github/license/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <a href="https://visitorbadge.io/status?path=https%3A%2F%2Fgithub.com%2FToxocious%Ephemeral">
    <img src="https://api.visitorbadge.io/api/visitors?path=https%3A%2F%2Fgithub.com%2FToxocious%Ephemeral&countColor=%2337d67a" />
  </a>
  <br /><br />

  Check us out on Discord and consider starring the repository if you liked it!

  <a href="https://discord.gg/XMsJqZJJeT" target="_blank">
    <img src="https://discord.com/api/guilds/1122601344839188582/widget.png?style=banner2" alt="Discord Banner" />
  </a>
</div>



# Table of Contents
- [Table of Contents](#table-of-contents)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Project Setup](#project-setup)
  - [Project Dependencies](#project-dependencies)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)



# Getting Started
## Prerequisites
[Premake](https://premake.github.io/) and [Vulkan](https://www.vulkan.org/) are required to generate project files and to also run the application once compiled.

Without Premake, you will not be able to generate the necessary project files.

Without Vulkan, the applications will not be able to run.

Be sure to install both of them and to add them to your operating system's PATH before continuing.

## Project Setup
Clone the repository recursively so that all required submodules are downloaded.

```bash
git clone --recursive https://github.com/Toxocious/Ephemeral.git
```

After cloning the repository onto your system, you can compile the project by running the [compile.sh](./compile.sh) script.

## Project Dependencies
We have chosen a number of third-party dependencies to use.

- [GLFW](https://github.com/TheCherno/glfw)
  - GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development. It provides a simple, platform-independent API for creating windows, contexts and surfaces, reading input, handling events, etc.
- [GLM](https://github.com/g-truc/glm)
  - OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
- [Dear ImGui](https://github.com/ocornut/imgui/)
  - Dear ImGui is a bloat-free graphical user interface library for C++.
- [ImGuizmo](https://github.com/thecherno/imguizmo)
  - ImGizmo is a small library built on-top of Dear ImGui that allows you to manipulate 4x4 float matrices.
- [SpdLog](https://github.com/gabime/spdlog)
  - A very fast, header-only/compiled, C++ logging library.



# Project Structure
We want to uphold a clean and organized structure, which looks like this.

Each part of the project contains a README containing further information about what it does, how it works, etc.

```
.
├── core/
│   ├── src/
│   │   └── ...
│   ├── Build-Core.lua
│   ├── Makefile
│   └── README.md
├── discord/
│   ├── src/
│   │   └── ...
│   └── README.md
├── docs/
│   └── CODE_OF_CONDUCT.md
│   └── CONTRIBUTING.md
│   └── FEATURES.md
├── editor/
│   ├── src/
│   │   └── ...
│   ├── Build-Editor.lua
│   ├── Makefile
│   └── README.md
├── game/
│   ├── src/
│   │   └── ...
│   ├── Build-Game.lua
│   ├── Makefile
│   └── README.md
└── server/
    ├── src/
    │   └── ...
    └── README.md
```



# Contributing
If you're interested in contributing to Ephemeral, please check out [CONTRIBUTING.md](docs/CONTRIBUTING.md) for more information.



# License
This project is licensed under MIT.

For more information about the license, check out the [LICENSE](LICENSE).
