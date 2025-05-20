# Create build directory if it doesn't exist
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build"
}

# Change to build directory
Set-Location -Path "build"

# Configure with CMake using MinGW
Write-Host "Configuring project with CMake..."
cmake .. -G "MinGW Makefiles"

# Build the project
Write-Host "Building project..."
cmake --build . --config Release

# Check if build was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful!"
    Write-Host "You can run the game from: build\Release\Minecraft.exe"
} else {
    Write-Host "Build failed!"
}

# Return to original directory
Set-Location -Path ".." 