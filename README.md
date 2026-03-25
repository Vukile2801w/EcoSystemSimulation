# 🌿 EcoSystem Simulation

A high-performance, interactive ecosystem simulation engine built in C++ that models evolutionary dynamics and organism interactions in real-time with visual rendering.

## 🎯 Overview

EcoSystemSimulation is a sophisticated C++ application that simulates complex ecological systems and their evolutionary progress. It combines physics-based movement, resource management, and real-time visualization to create an engaging ecosystem sandbox where organisms interact, compete, and evolve within a dynamic environment.

**Language:** C++ | **License:** AGPL-3.0 | **Status:** Active Development

## ✨ Features

- **Real-Time Ecosystem Simulation**: Watch organisms interact in a living, breathing ecosystem
- **Visual Rendering**: Real-time graphics using Raylib for interactive visualization
- **2D Tilemap System**: Grid-based environment with dynamic terrain interactions
- **Physics Engine**: Custom math library for accurate movement and collision detection
- **Camera Control**: Pan and zoom through your ecosystem with intuitive camera controls
- **Input Handling**: Keyboard and mouse controls for interactive simulation management
- **Modular Architecture**: Clean separation of concerns with dedicated systems for graphics, physics, input, and timing

## 📁 Project Structure

```
EcoSystemSimulation/
├── include/                    # Header files
│   ├── camera.hpp             # Camera management
│   ├── colors.hpp             # Color definitions and palette
│   ├── engine.hpp             # Core engine interface
│   ├── graphics.hpp           # Graphics rendering system
│   ├── input.hpp              # Input handling (keyboard/mouse)
│   ├── math.hpp               # Mathematical utilities and vectors
│   ├── texture.hpp            # Texture management
│   ├── tilemap.hpp            # Tilemap system for environments
│   ├── time.hpp               # Timing and frame management
│   └── raylib/                # Raylib library headers
├── src/                        # Implementation files
│   ├── main.cpp               # Application entry point
│   ├── camera.cpp             # Camera implementation
│   ├── graphics.cpp           # Rendering implementation
│   ├── input.cpp              # Input system implementation
│   ├── math.cpp               # Math utilities implementation
│   ├── tilemap.cpp            # Tilemap system implementation
│   ├── time.cpp               # Timing implementation
│   └── raylib/                # Raylib library binaries
├── assets/                     # Game assets and resources
├── CMakeLists.txt             # CMake build configuration
├── rebuild                    # Rebuild script (bash)
├── run                        # Run script (bash)
└── LICENSE                    # AGPL-3.0 License
```

## 🚀 Getting Started

### Prerequisites

- **C++17 or higher**
- **CMake 3.10+**
- **Linux/macOS** (Windows support may require additional configuration)

### Build Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Vukile2801w/EcoSystemSimulation.git
   cd EcoSystemSimulation
   ```

2. **Build using CMake:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

   **Or use the provided rebuild script:**
   ```bash
   ./rebuild
   ```

3. **Run the simulation:**
   ```bash
   ./run
   ```

## 🎮 Controls & Usage

### Camera Navigation
- **Arrow Keys / WASD**: Move camera
- **Scroll / +/-**: Zoom in/out
- **Mouse Movement**: Pan view

### Simulation
- **Space**: Play/Pause simulation
- **R**: Reset ecosystem
- **ESC**: Exit application

*For detailed control mappings, see `include/input.hpp`*

## 🔧 System Architecture

### Core Systems

- **Graphics System** (`graphics.hpp/cpp`): Handles all visual rendering using Raylib
- **Physics Engine** (`math.hpp/cpp`): Custom vector mathematics and physics calculations
- **Tilemap Manager** (`tilemap.hpp/cpp`): Manages the environment grid and terrain
- **Camera System** (`camera.hpp/cpp`): 2D camera with pan and zoom capabilities
- **Input Handler** (`input.hpp/cpp`): Unified input processing for keyboard and mouse
- **Time Manager** (`time.hpp/cpp`): Frame timing and deltatime calculations

### Dependencies

- **Raylib**: A simple and easy-to-use graphics library for visualization
- **CMake**: For cross-platform build management

## 📊 Simulation Features

- **Entity Management**: Efficient handling of multiple organisms
- **Resource Distribution**: Dynamic food and energy systems
- **Collision Detection**: Physics-based interactions between entities
- **Environmental Dynamics**: Time-based environmental changes
- **Visual Feedback**: Real-time color coding and status indicators

## 🤝 Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/YourFeature`)
3. Commit your changes (`git commit -m 'Add YourFeature'`)
4. Push to the branch (`git push origin feature/YourFeature`)
5. Open a Pull Request

Please ensure code follows the existing style and includes appropriate comments.

## 📝 License

This project is licensed under the **GNU Affero General Public License v3.0** (AGPL-3.0). See the [LICENSE](LICENSE) file for details.

This means:
- You can use, modify, and distribute this software freely
- If you provide this software as a service, you must share the source code
- All derivative works must also be licensed under AGPL-3.0

## 🗺️ Roadmap

- [ ] Advanced organism AI and behavior trees
- [ ] Genetic evolution and mutation systems
- [ ] Multi-threaded simulation for better performance
- [ ] Save/load ecosystem states
- [ ] Advanced graphics and particle effects
- [ ] Configuration files for custom simulation parameters
- [ ] Network multiplayer support
- [ ] Web-based visualization dashboard

## 🐛 Known Issues & TODO

- See [Issues](https://github.com/Vukile2801w/EcoSystemSimulation/issues) for current bugs and planned features

## 📚 Resources & References

- [Raylib Documentation](https://www.raylib.com/)
- [C++ Standard Library](https://en.cppreference.com/)
- Ecosystem Simulation Research Papers (see `/docs` if available)

## 👤 Author

**Vukile2801w**

- GitHub: [@Vukile2801w](https://github.com/Vukile2801w)
- Project Repository: [EcoSystemSimulation](https://github.com/Vukile2801w/EcoSystemSimulation)

## ⭐ Support

If you find this project helpful, please consider:
- Giving it a star ⭐
- Opening issues for bugs or feature requests
- Contributing code improvements
- Sharing with others interested in simulations and C++

---

**Last Updated:** March 25, 2026