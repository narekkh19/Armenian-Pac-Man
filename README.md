# Armenian-Pac-Man
Armenian Pac-Man 🇦🇲
A classic Pac-Man arcade game with a unique Armenian twist, built from scratch in C++ using the SFML multimedia library. This project features the complete gameplay loop, including four ghosts with their own distinct AI behaviors.

(Feel free to replace this placeholder link with your own gameplay screenshot or GIF!)

Features
Classic Pac-Man Gameplay: Navigate the maze, eat all the pellets, and avoid the ghosts!
Unique Armenian Theme:
The maze walls are built from Tuf (տուֆ), a famous Armenian volcanic rock.
Pac-Man collects Dram (֏), the currency of Armenia, instead of standard pellets.
Four Unique Ghosts: Each ghost has its own canonical targeting AI implemented:
🔴 Blinky: The chaser, who directly targets Pac-Man.
🌸 Pinky: The ambusher, who targets a space in front of Pac-Man.
💧 Inky: The flanker, whose target is based on the positions of both Pac-Man and Blinky.
🍊 Clyde: The unpredictable one, who chases Pac-Man when far away but retreats to his corner when close.
Animated Sprites: Smooth, animated sprites for Pac-Man and all ghosts, with directional graphics.
UI Manager: Clean game over and win screens with animated text that grows to fill the window.
Score Tracking: A persistent score is displayed on screen.
Tech Stack
Language: C++20
Library: SFML (Simple and Fast Multimedia Library) for graphics, windowing, and input.
Build System: make
Prerequisites
Before you can build and run the project, you need to have a C++ compiler and the SFML library installed on your system.

Installing SFML
On Debian/Ubuntu:
Bash

sudo apt-get install libsfml-dev
On macOS (using Homebrew):
Bash

brew install sfml
On Windows: Download the appropriate SFML package from the official website and follow their setup tutorials to configure it with your compiler (e.g., MinGW, Visual Studio).
Installation & Building
You can easily clone and build the project using the included Makefile.

Clone the repository:
Bash

git clone https://github.com/narekkh19/Armenian-Pac-Man.git
Navigate to the project directory:
Bash

cd Armenian-Pac-Man
Compile the project:
Bash

make
This will compile all the source files and create an executable named app.
How to Play
After building the project, run the game with:

Bash

make run
Alternatively, you can run the executable directly:

Bash

./app
Controls:

W: Move Up
A: Move Left
S: Move Down
D: Move Right
Ctrl + W: Quit the game instantly.
Cleaning Up
To remove the compiled object files and the executable, run:

Bash

make clean
