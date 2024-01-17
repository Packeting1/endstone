<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="https://static.wikia.nocookie.net/minecraft_gamepedia/images/4/43/End_Stone_JE3_BE2.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Endstone</h3>

  <p align="center">
    Write your plugins in Python and C++ for Bedrock Dedicated Servers.
  </p>
</div>

## 📄 Table of Contents

- [📖 Introduction](#-introduction-)
- [🛠️ Installation](#%EF%B8%8F-installation-)
- [🙌 Contributing](#-contributing-)
- [🎫 License](#-license-)

## 📖 Introduction [🔝](#-table-of-contents)

Wre are excited to announce the Endstone project. Endstone offers a plugin API for Bedrock Dedicated Servers, supporting
both Python and C++ languages. This allows developers to enhance Bedrock Dedicated Servers with various features and
functionalities.

### Build Status

| System         | Build Status                                                                                                                                                                           |
|----------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Windows x86_64 | [![Endstone CI (Windows)](https://github.com/EndstoneMC/endstone/actions/workflows/ci-windows.yml/badge.svg)](https://github.com/EndstoneMC/endstone/actions/workflows/ci-windows.yml) |
| Linux x86_64   | [![Endstone CI (Linux)](https://github.com/EndstoneMC/endstone/actions/workflows/ci-linux.yml/badge.svg)](https://github.com/EndstoneMC/endstone/actions/workflows/ci-linux.yml)       |

## 🛠️ Installation [🔝](#-table-of-contents)

Before proceeding with the installation process, verify that you are using one of the following compatible operating
systems:

- Windows 10 or higher
- Windows Server 2019 or higher
- Debian 11 or higher
- Ubuntu 20.04 or higher

Please also ensure you have **Python 3.9 or higher** installed on your system.

There are several ways to install Endstone:

### PyPi

Endstone can be installed from PyPi using pip. Open your terminal and execute the following command to install:

```shell
pip install endstone
```

### Build locally from Source

You also have the option to build Endstone locally from the source.

First, clone the repository:

```shell
git clone https://github.com/EndstoneMC/endstone.git
cd endstone
```

After successfully cloning the repository to your local system, the next step will involve the installation of required
tools and setting up your environment.

```shell
pip install conan
conan export third_party/funchook --version 1.1.3
conan install . --build=missing
pip install .
```

Building from source requires cmake and ninja. These must be installed in order to proceed.

For **Windows** users, MSVC 2019 or higher is required for this process to work; nevertheless, it is highly recommended
to use MSVC 2022 for optimal performance.

For **Linux** users, Clang 5 or higher is needed; Clang 15 is however recommended for the best experience. Furthermore,
make sure to install libc++. It's important to note that all the operations mentioned must be flawlessly completed to
ensure the proper functionality of Endstone.

### Docker

To try Endstone from a Docker image, use the following command:

```shell
docker run --rm -it endstone/endstone
```

or

```shell
docker run --rm -it ghcr.io/endstonemc/endstone
```

This will pull the latest Endstone image and run it interactively in your terminal.

## 🙌 Contributing [🔝](#-table-of-contents)

We warmly welcome contributions to the Endstone project! If you're enthusiastic about enhancing Bedrock Dedicated
Servers with Python and C++ and have ideas on how to improve Endstone, here are a few ways you can contribute:

### Reporting Bugs

If you encounter any bugs while using Endstone, please open an [issue](https://github.com/EndstoneMC/endstone/issues) in
our GitHub repository. Ensure to include a detailed description of the bug and steps to reproduce it.

### Submitting a Pull Request

We appreciate code contributions. If you've fixed a bug or implemented a new feature, please submit a pull request!
Please ensure your code follows our coding standards and include tests where possible.

## 🎫 License [🔝](#-table-of-contents)

The Endstone project is licensed under the [Apache-2.0 license](LICENSE).
