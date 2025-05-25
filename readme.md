# Sentinel Safe Filesystem Project

*This readme.md is right now written by chatgpt, I will correct it later, it's not finished.*

Sentinel is a C++ application that [**TODO: Briefly describe what your project does here. e.g., "manages files and performs cryptographic operations."**].

This document provides instructions on how to build the Sentinel project from source on various operating systems.

## Prerequisites

Before you begin, ensure you have the following installed on your system:

1.  **CMake**: Version 3.15 or higher.
    *   **All OS**: Download from [cmake.org/download](https://cmake.org/download/) or use your system's package manager.
    *   Verify installation: `cmake --version`

2.  **A C++ Compiler supporting C++23**:
    *   **Linux**: GCC (g++) 12.x or later, or Clang 15.x or later.
        *   Install: `sudo apt update && sudo apt install g++` (Debian/Ubuntu) or `sudo yum install gcc-c++` (Fedora/CentOS).
    *   **macOS**: Apple Clang (comes with Xcode Command Line Tools).
        *   Install: `xcode-select --install`
    *   **Windows**:
        *   **MSVC**: Visual Studio 2022 (Community edition is free) with the "Desktop development with C++" workload. Ensure the C++23 standard is supported by your MSVC version.
        *   **MinGW-w64**: Provides GCC for Windows. (e.g., via MSYS2 or standalone installer).
        *   **Clang**: Can be used on Windows (e.g., with Visual Studio or standalone).

3.  **Git**: Required by CMake's `FetchContent` to download `googletest` and `nlohmann/json`.
    *   **All OS**: Download from [git-scm.com/downloads](https://git-scm.com/downloads) or use your system's package manager.
    *   Verify installation: `git --version`

4.  **OpenSSL**: Development libraries.
    *   **Linux (Debian/Ubuntu)**:
        ```bash
        sudo apt update
        sudo apt install libssl-dev
        ```
    *   **Linux (Fedora/CentOS/RHEL)**:
        ```bash
        sudo yum install openssl-devel
        # or
        sudo dnf install openssl-devel
        ```
    *   **macOS**:
        OpenSSL is available, but Apple's version is deprecated for development. It's recommended to install a newer version via Homebrew:
        ```bash
        brew install openssl@3 # Or openssl@1.1 if your project specifically needs it
        ```
        You might need to tell CMake where to find it if it's not in the default paths (see Build Instructions).
    *   **Windows**:
        *   **Option 1: vcpkg (Recommended for consistency)**
            If you use vcpkg: `vcpkg install openssl:x64-windows` (or `openssl:x86-windows`).
        *   **Option 2: Pre-built Binaries**
            Download pre-compiled OpenSSL binaries for Windows. Several providers exist (e.g., [Shining Light Productions](https://slproweb.com/products/Win32OpenSSL.html) - choose a "developer" version that includes headers and libraries). Ensure the installed version's `bin` directory is in your system `PATH`, and that CMake can find the headers and libraries (you might need to set `OPENSSL_ROOT_DIR`).
        *   **Option 3: Chocolatey**
            ```powershell
            choco install openssl --params "/Full" # Installs headers and libs
            ```
            You may still need to help CMake find it.

5.  **Boost**: Version 1.70.0 or higher (specifically the `system` component).
    *   **Linux (Debian/Ubuntu)**:
        ```bash
        sudo apt update
        sudo apt install libboost-system-dev # This usually brings other common Boost dev libs too
        ```
        To ensure a specific version (if system default is too old/new), you might need to build from source or use a PPA.
    *   **Linux (Fedora/CentOS/RHEL)**:
        ```bash
        sudo yum install boost-devel
        # or
        sudo dnf install boost-devel
        ```
    *   **macOS (Homebrew)**:
        ```bash
        brew install boost
        ```
    *   **Windows**:
        *   **Option 1: vcpkg (Recommended for consistency)**
            If you use vcpkg: `vcpkg install boost-system:x64-windows` (or `:x86-windows`).
        *   **Option 2: Pre-built Binaries**
            Download pre-compiled Boost binaries for Windows from the official Boost website ([boost.org](https://www.boost.org/users/download/)). Choose a version compatible with your compiler (MSVC). Extract and ensure CMake can find them (you might need to set `BOOST_ROOT` or `Boost_INCLUDE_DIR` and `Boost_LIBRARY_DIR` environment variables or CMake variables).
        *   **Option 3: Chocolatey**
            ```powershell
            choco install boost-msvc-14.3 # Adjust for your MSVC version (14.3 is for VS2022)
            ```

## Build Instructions

1.  **Clone the Repository**:
    ```bash
    git clone [URL_OF_YOUR_REPOSITORY]
    cd sentinel # Or your project's root directory
    ```

2.  **Configure with CMake**:
    Create a build directory (out-of-source builds are recommended).

    *   **General (Linux/macOS)**:
        ```bash
        mkdir build
        cd build
        cmake ..
        ```
        *   **macOS (If Homebrew OpenSSL/Boost isn't found automatically)**:
            You might need to provide hints to CMake if you installed OpenSSL or Boost via Homebrew and they aren't in standard system paths:
            ```bash
            # Example for openssl@3 installed via brew
            cmake -DOpenSSL_ROOT_DIR=$(brew --prefix openssl@3) ..
            # Example for boost installed via brew
            cmake -DBOOST_ROOT=$(brew --prefix boost) ..
            # Combine them if needed:
            cmake -DOpenSSL_ROOT_DIR=$(brew --prefix openssl@3) -DBOOST_ROOT=$(brew --prefix boost) ..
            ```

    *   **Windows (Visual Studio)**:
        Open a "Developer Command Prompt for VS 2022" (or your VS version).
        ```bash
        mkdir build
        cd build
        cmake .. -G "Visual Studio 17 2022" # Adjust generator for your VS version
        ```
        If you installed OpenSSL/Boost manually or via Chocolatey and CMake doesn't find them, you may need to set environment variables like `OPENSSL_ROOT_DIR` and `BOOST_ROOT` before running CMake, or pass them as `-D` options:
        ```bash
        # Example
        cmake .. -G "Visual Studio 17 2022" -DOpenSSL_ROOT_DIR="C:/path/to/openssl" -DBOOST_ROOT="C:/path/to/boost_1_XX_0"
        ```

    *   **Windows (MinGW)**:
        Ensure your MinGW `bin` directory is in your `PATH`.
        ```bash
        mkdir build
        cd build
        cmake .. -G "MinGW Makefiles"
        ```
        Similar to MSVC, you might need to provide `OPENSSL_ROOT_DIR` and `BOOST_ROOT` if they are not found automatically.

    *   **Building Tests**:
        To enable building the test suite, add `-DBUILD_TESTING=ON` to your `cmake` command:
        ```bash
        cmake .. -DBUILD_TESTING=ON
        # Or for Windows with VS generator:
        cmake .. -G "Visual Studio 17 2022" -DBUILD_TESTING=ON
        ```

3.  **Build the Project**:
    After CMake has successfully configured the project:

    *   **Linux/macOS (or MinGW on Windows)**:
        (Still inside the `build` directory)
        ```bash
        make -j$(nproc)  # nproc for Linux, use appropriate core count for macOS
        # or simply:
        make
        ```
    *   **Windows (Visual Studio)**:
        (Still inside the `build` directory)
        ```bash
        cmake --build . --config Release  # Or Debug
        ```
        Alternatively, open the generated `sentinel.sln` file in Visual Studio and build from there.

4.  **Run the Executable**:
    The executable `sentinel` (and `sentinel_tests` if `BUILD_TESTING` was ON) will be located in the `build` directory (or a subdirectory like `build/Debug` or `build/Release` for multi-config generators like Visual Studio).

    *   **Linux/macOS**:
        ```bash
        ./sentinel
        # To run tests:
        ./sentinel_tests
        ```
    *   **Windows**:
        ```bash
        .\Release\sentinel.exe  # Adjust path based on build type (Release/Debug)
        # To run tests:
        .\Release\sentinel_tests.exe
        ```

## Troubleshooting

*   **CMake `find_package` errors for OpenSSL or Boost**:
    *   Ensure the development packages (headers and libraries) are installed, not just the runtime libraries.
    *   Verify that the installed versions meet the minimum requirements (Boost 1.70.0).
    *   On Windows or macOS (with Homebrew), you might need to explicitly tell CMake where these libraries are installed using `OpenSSL_ROOT_DIR` and `BOOST_ROOT` CMake variables (e.g., `-DOpenSSL_ROOT_DIR=/path/to/openssl`) or environment variables.
    *   Check CMake's error messages carefully; they often provide clues (e.g., paths searched).
*   **Compiler Errors**: Ensure your C++ compiler fully supports C++23. Update your compiler if necessary.
*   **Linker Errors**:
    *   Could indicate missing development libraries for OpenSSL or Boost.
    *   On Windows, ensure you're linking against the correct architecture (x86/x64) and runtime libraries (MD/MT, MDd/MTd) consistent with how OpenSSL/Boost were built. vcpkg handles this well.

---

**TODO: Add a section on "How to Use" the application if applicable.**
**TODO: Add a "Contributing" section if you plan to accept contributions.**
**TODO: Add a "License" section (e.g., MIT, GPL, etc.).**

