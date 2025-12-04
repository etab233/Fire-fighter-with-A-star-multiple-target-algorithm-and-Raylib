# Fire Fighter Simulation with A* Algorithm and Raylib
## Overview
An advanced firefighting simulation using a multi-target A* algorithm with an interactive graphical interface built with Raylibز

### Key Features
Artificial Intelligence
*Multi-target A algorithm**: Finds optimal paths for fire truck movement

Intelligent path planning: Selects nearest fire

Smart resource management: Optimizes water usage for fire extinguishing

### Graphical Interface
Raylib graphics engine: Simplified 2D visualization

Detailed buildings: Realistic building designs with windows, doors, and roofs

Animated fire effects: Dynamic fire and spark animations with visual effects

Interactive fire truck: Detailed vehicle with wheels, lights, and body details

Intuitive UI: Well-organized information display and controls

### Game Mechanics
Water resource management: Strategic use of water to extinguish fires

Building protection: Preventing fire spread to adjacent buildings

Multiple win/loss conditions:

Win: Extinguish all fires while maintaining resources

Loss: Exhaust resources or buildings with sum(importance) > 5 destroyed

### Project Structure
text
Fire-fighter-with-A-star-multiple-target-algorithm-and-Raylib/
├── include/                  # Header files
│   ├── fireState.h           # Fire state definitions
│   ├── fire_problem.h        # Problem definition
│   ├── fire_spread.h         # Fire spread logic
│   └── visualizer.h          # Visualization interface
├── src/                      # Source code
│   ├── main.cpp             # Main function
│   ├── fireState.cpp        # Fire state implementation
│   ├── visualizer.cpp       # Scene rendering
│   ├── a_star.cpp           # A* algorithm implementation
│   ├── actions.cpp          # Action implementations
│   ├── fire_problem.cpp     # Problem implementation
│   └── fire_spread.cpp      # Fire spread implementation
├── .gitignore               # Git ignore file
├── Makefile                 # Build script
└── README.md                # This file

### Installation & Running
Prerequisites
C++17 compiler (g++ 9.0 or newer)

Raylib library (Version 5.0 or newer)

Windows/Linux/macOS system

Installation Steps
Windows
bash
# 1. Install Raylib
# Download from https://raylib.com

# 2. Clone the project
git clone https://github.com/etab233/Fire-fighter-with-A-star-multiple-target-algorithm-and-Raylib.git
cd Fire-fighter-with-A-star-multiple-target-algorithm-and-Raylib

# 3. Compile
g++ -std=c++17 -IC:/raylib/include -I./include src/main.cpp src/visualizer.cpp src/fireState.cpp src/actions.cpp src/a_star.cpp src/fire_problem.cpp src/fire_spread.cpp -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o fire_simulation.exe

# 4. Run
fire_simulation.exe
Linux
bash
# 1. Install Raylib
sudo apt-get install libraylib-dev

# 2. Clone and compile
git clone https://github.com/etab233/Fire-fighter-with-A-star-multiple-target-algorithm-and-Raylib.git
cd Fire-fighter-with-A-star-multiple-target-algorithm-and-Raylib

make
./fire_simulation
macOS
bash
# 1. Install Raylib
brew install raylib

# 2. Clone and compile
git clone https://github.com/etab233/Fire-fighter-with-A-star-multiple-target-algorithm-and-Raylib.git
cd Fire-fighter-with-A-star-multiple-target-algorithm-and-Raylib

make
./fire_simulation
Simplified Makefile
makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: fire_simulation.exe

fire_simulation.exe: src/*.cpp
	$(CXX) $(CXXFLAGS) -Iinclude src/*.cpp $(LDFLAGS) -o $@

clean:
	del fire_simulation.exe 2>nul || rm -f fire_simulation.exe


### Game Rules
Objective: Extinguish all fires before they spread and destroy buildings

Resources: You have limited water, use it wisely

Buildings: Each destroyed building reduces your score

Planning: Choose optimal paths to reach fires quickly

Winning Strategies
Pre-plan paths using A* algorithm

Extinguish fires closest to buildings first

Anticipate fire spread and prevent it

Keep some water for emergencies

### Advanced A* Algorithm
Technical Features
Custom cost function: Considers distance, fire intensity, building proximity

Multi-target selection: Dynamically chooses best target

Memory optimization: Efficient data structures

Obstacle avoidance: Navigates around grid obstacles

### Implementation
cpp
// Code example
vector<Point> AStarPathfinding(const FireState& state, 
                               const Point& start, 
                               const vector<Point>& targets) {
    // A* implementation with multiple criteria
    return optimal_path;
}
### Graphics Design
Buildings
Simplified 3D design

Animated windows (light on/off)

Detailed doors with knobs

Realistic roofs and foundations

Color variety for each building

Fire Effects
Three-layer fire effects (red, orange, yellow)

Random flying sparks

Dynamic flame spread

Glow around fire area

User Interface
Clear top information panel

Graphical resource indicators

Animated win/loss messages

Interactive control instructions

### Technical Analysis
Performance
Memory: Smart use of graphical resources

Performance: Smooth updates even on mid-range devices

Responsiveness: Immediate vehicle control response

Scalability
Add new fire types

Integrate multiple fire vehicles

Add obstacles and difficulty levels

Support networking (multiplayer)

🔧 Customization
Difficulty Adjustment
cpp
// In fireState.h
const int INITIAL_WATER = 100;  // Increase/decrease water
const int FIRE_SPREAD_RATE = 2; // Change fire spread speed
const int BUILDING_COUNT = 10;  // Number of buildings
Graphics Enhancement
cpp
// In visualizer.cpp
const int CELL_SIZE = 80;       // Cell size
const int FIRE_ANIMATION_SPEED = 5;  // Fire animation speed
🚀 Future Improvements
Development Roadmap
Multiple levels with increasing difficulty

Weather effects support (wind, rain)

Different vehicle types

Online scoring system

Built-in level editor

Research & Development
Develop more advanced pathfinding algorithms

Integrate machine learning for fire spread prediction

Enhance graphics using shaders

👥 Contributing
How to Contribute
Fork the project

Create your feature branch (git checkout -b feature/AmazingFeature)

Commit your changes (git commit -m 'Add some AmazingFeature')

Push to the branch (git push origin feature/AmazingFeature)

Open a Pull Request

Code Standards
Follow existing code style

Add explanatory comments for new functions

Test changes before pushing

Ensure compilation without errors

📝 License
This project is licensed under the MIT License - see the LICENSE file for details.

👤 Author
Etab - GitHub

🙏 Acknowledgments
Raylib team for the excellent graphics library

C++ community for tools and libraries

All contributors and testers

📞 Contact
For inquiries or suggestions:

📧 Email: etabmwanos@gmail.com

💬 GitHub Issues


⭐ If you like this project, don't forget to give it a star on GitHub! ⭐
