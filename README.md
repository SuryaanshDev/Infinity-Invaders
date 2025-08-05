# 🚀 Infinity Invaders

![Game Banner](/images/🚀Infinity_Invaders.png)

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/SuryaanshDev/Infinity-Invaders)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![SFML](https://img.shields.io/badge/SFML-2.5+-green.svg)](https://www.sfml-dev.org/)

A classic Space Invaders inspired arcade game built entirely in **C++** using the **SFML** library. This project serves as a learning experience to deepen understanding of C++ programming and game development fundamentals.

## 📋 Table of Contents

- [Features](#-features)
- [Screenshots](#-screenshots)
- [System Requirements](#-system-requirements)
- [Installation](#-installation)
- [How to Play](#-how-to-play)
- [Game Controls](#-game-controls)
- [Contributing](#-contributing)
- [License](#-license)
- [Acknowledgments](#-acknowledgments)

## ✨ Features

- **Classic Space Invaders Gameplay** - Shoot enemies and achieve high scores
- **Screen Wrapping** - Move seamlessly from left to right edges (Pac-Man style)
- **Health System** - Take damage from enemy contact and projectiles
- **Menu Navigation** - Clean main menu with instructions
- **Handcrafted Assets** - All sprites created using Aseprite
- **Sound Effects** - Immersive audio experience
- **Score Tracking** - Compete for the highest score

## 📸 Screenshots

### Main Menu
![Game Menu](/images/Menu.png)

### Instructions
![Instructions](/images/Instructions.png)

### Gameplay
![Playing](/images/Playing.png)

### Game Over
![Game Over](/images/Game%20Over.png)

## 🖥️ System Requirements

- **Operating System**: Windows, macOS, or Linux
- **C++ Compiler**: Supporting C++17 or later
- **SFML**: Version 2.5 or higher
- **CMake**: Version 3.10 or higher
- **RAM**: 512 MB minimum
- **Storage**: 50 MB available space

## 🔧 Installation

### Option 1: Download Release Build (Recommended)
1. Go to the [Releases section](https://github.com/SuryaanshDev/Infinity-Invaders/releases/tag/Game)
2. Download the latest release build
3. Extract and run the executable

### Option 2: Build from Source

#### Prerequisites
- Install SFML library on your system
- Ensure CMake is installed
- Have a C++17 compatible compiler

#### Building Steps
```bash
# Clone the repository
git clone https://github.com/SuryaanshDev/Infinity-Invaders.git
cd Infinity-Invaders

# Create build directory
mkdir build
cd build

# Configure with CMake (Release mode)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build the project
cmake --build .

# Run the game
./InfinityInvaders
```

**Note**: This project is configured for Release builds. If you need to build in Debug mode, modify the CMakeLists.txt file accordingly.

## 🎮 How to Play

1. **Objective**: Destroy enemy UFOs and achieve the highest score possible
2. **Health System**: You lose health when hit by enemies or their projectiles
3. **Screen Wrapping**: Move off one edge of the screen to appear on the opposite side
4. **Scoring**: Earn points by destroying enemy spacecraft
5. **Game Over**: When your health reaches zero, the game ends

## 🕹️ Game Controls

### Menu Navigation
- **W, A, S, D**: Navigate menu options
- **Enter**: Select menu option
- **Esc**: Return to main menu / Exit current screen

### In-Game Controls
- **W**: Move up
- **S**: Move down
- **A**: Move left
- **D**: Move right
- **Spacebar**: Shoot
- **Esc**: Pause game / Return to menu

## 🎨 Assets

All visual assets (sprites, animations) were handcrafted using **Aseprite** to maintain a consistent pixel art aesthetic throughout the game.

**Audio**: Sound effects sourced from [Mixkit](https://mixkit.co/free-sound-effects/game/)

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Future Features (Roadmap)
- Power-ups and special weapons
- Multiple enemy types
- Level progression system
- Local high score persistence
- Enhanced visual effects

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **SFML Community** - For the excellent multimedia library
- **Mixkit** - For providing free sound effects
- **Aseprite** - For the pixel art creation tool
- **Space Invaders** - For the original game inspiration

---

⭐ **Enjoyed the game?** Give this repository a star and share it with fellow game developers!

**Developer**: [Suryaansh Dev](https://github.com/SuryaanshDev)  
**Contact**: Feel free to open an issue for questions or suggestions!