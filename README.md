<div align="center">
  <!-- <img src="./app/images/Assets/banner.png" title="Pokemon Ephemeral Logo" alt="Pokemon Ephemeral Logo" /> -->
  <h1 align="center">Pok&eacute;mon Ephemeral</h1>

  **Pok&eacute;mon Ephemeral** intends to be a handcrafted game engine, game server, and more, all of which will come together to create a Pok&eacute;mon MMO.

  Development of this project will take a great amount of time given the desired scope, but we'll get there.

  <img src="https://img.shields.io/github/issues/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <img src="https://img.shields.io/github/forks/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <img src="https://img.shields.io/github/stars/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <br />
  <img src="https://img.shields.io/github/license/Toxocious/Ephemeral?style=for-the-badge&logo=appveyor" />
  <a href="https://visitorbadge.io/status?path=https%3A%2F%2Fgithub.com%2FToxocious%Ephemeral">
    <img src="https://api.visitorbadge.io/api/visitors?path=https%3A%2F%2Fgithub.com%2FToxocious%Ephemeral&countColor=%2337d67a" />
  </a>
  <br /><br />

  Check us out on Discord if you like this project and/or want to contribute in any way.

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
[Premake](https://premake.github.io/) is required to generate project files (Windows) and executables (Linux).

Without Premake, you will not be able to generate the necessary project files.

Be sure to install and to add it to your operating system's PATH before continuing.

## Project Setup
Clone the repository.

```bash
git clone https://github.com/Toxocious/Ephemeral.git
```

After cloning the repository onto your system, you can compile the project by running the [Compile.sh](./Compile.sh) script.

## Project Dependencies
We have chosen a number of third-party dependencies to use, which you can read more about in our [DEPENDENCIES](Docs/DEPENDENCIES.md) documentation.

## Project Structure
We want to uphold a clean and organized structure, which looks like this.

Each part of the project contains a README containing further information about what it does, how it works, etc.

```
.
├── Build/
│   └── Compiled binary and object files
├── Docs/
│   └── CODE_OF_CONDUCT.md
│   └── CONTRIBUTING.md
│   └── DEPENDENCIES.md
│   └── FEATURES.md
├── Generated/
│   └── Generated Visual Studio project files
├── Libraries/
│   ├── glad/
│   ├── glfw/
│   ├── glm/
│   ├── imgui/
│   ├── mathgeolib/
│   ├── spdlog/
│   ├── stb_image/
├── Projects/
│   ├── Core/
│   │   └── Include/
│   │   └── Source/
│   ├── Editor/
│   │   └── Include/
│   │   └── Source/
└────── README.md
```



# Contributing
If you're interested in contributing to Ephemeral, please check out [CONTRIBUTING.md](Docs/CONTRIBUTING.md) for more information.



# License
This project is licensed under MIT.

For more information about the license, check out the [LICENSE](LICENSE).
