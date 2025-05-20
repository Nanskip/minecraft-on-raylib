# Minecraft Clone

A simple Minecraft clone using Raylib and C.

## Prerequisites

- CMake (version 3.11 or higher)
- MinGW-w64 (for Windows)
- Git

## Building the Project

### Windows (One-Click Build)

Simply double-click `build.bat` to build the project. This will:
1. Create a build directory
2. Configure the project with CMake
3. Build the project
4. Show you where to find the executable

### Manual Build

If you prefer to build manually:

```powershell
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build . --config Release

# Run the game
./Release/Minecraft.exe
```

### Linux/macOS

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .

# Run the game
./Minecraft
```

## Project Structure

- `src/` - Source code files
- `resources/` - Game resources (textures, sounds, etc.)
- `CMakeLists.txt` - CMake build configuration
- `build.ps1` - PowerShell build script
- `build.bat` - Windows batch file for one-click building
- `build/` - Build directory (created during build process)

## Dependencies

- Raylib 4.5.0 (automatically downloaded during build) 