#!/bin/bash

set -e

echo "PongGame - Dependency Installer and Build Helper"
echo "Detected OS: $(uname -s), Architecture: $(uname -m)"

# --- Function: Install packages on Debian/Ubuntu ---
install_debian_packages() {
    echo "Checking and installing required packages on Debian/Ubuntu..."

    REQUIRED_PACKAGES=(
        build-essential
        cmake
        libsdl2-dev
        libsdl2-image-dev
        libsdl2-ttf-dev
        libfreetype6-dev
    )

    for pkg in "${REQUIRED_PACKAGES[@]}"; do
        if dpkg -s "$pkg" >/dev/null 2>&1; then
            echo "✓ $pkg already installed"
        else
            echo "→ Installing $pkg"
            sudo apt-get update
            sudo apt-get install -y "$pkg"
        fi
    done
}

# --- Function: Warn for unsupported OS ---
unsupported_os_warning() {
    echo "⚠️ Unsupported or untested OS detected: $1"
    echo "Please manually install SDL2, SDL2_image, and SDL2_ttf libraries."
}

# --- Detect OS and route to correct installer ---
case "$(uname -s)" in
    Linux)
        if [ -f /etc/debian_version ]; then
            install_debian_packages
        elif [ -f /etc/arch-release ]; then
            echo "Detected Arch Linux"
            echo "→ Use: sudo pacman -S sdl2 sdl2_image sdl2_ttf cmake base-devel"
        elif [ -f /etc/fedora-release ]; then
            echo "Detected Fedora"
            echo "→ Use: sudo dnf install SDL2 SDL2_image SDL2_ttf cmake gcc-c++"
        else
            unsupported_os_warning "Linux (non-Debian)"
        fi
        ;;
    Darwin)
        echo "Detected macOS"
        echo "→ Use: brew install sdl2 sdl2_image sdl2_ttf cmake"
        ;;
    FreeBSD)
        echo "Detected FreeBSD"
        echo "→ Use: pkg install sdl2 sdl2_image sdl2_ttf cmake gmake"
        ;;
    *)
        unsupported_os_warning "$(uname -s)"
        ;;
esac

# --- Build ---
echo ""
echo "Starting project build..."
./build.sh
