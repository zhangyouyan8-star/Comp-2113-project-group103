# Snake Game - ENGG1340/COMP2113 Course Project

## Team Members
* **Name:** Zhang Wuyan | **UID:** 3036590049
* **Name:** Ma Chenhan | **UID:** 3036590087

## Project Description
This is a classic text-based Snake Game implemented in C++, specifically optimized for **Linux terminal environments** (such as the HKU CS Academy Server). The game utilizes low-level terminal I/O control to provide a smooth, real-time gaming experience. Players control the snake using 'WASD' keys to consume fruit ('*'), increase their score, and grow in length while avoiding boundaries and self-collision.

## Implementation of Coding Requirements
Our project strictly fulfills the five essential coding elements required by the course:

1.  **Generation of Random Events**: 
    * The fruit's spawn coordinates are generated using `rand()` and `srand(time(0))`. A new fruit is placed at a random valid location whenever the snake consumes the current one[cite: 4, 6].
2.  **Data Structures for Storing Data**: 
    * We employ `std::vector<int>` to store the X and Y coordinates of the snake's tail segments. This allows for flexible tracking of the snake's body as it grows[cite: 3, 6].
3.  **Dynamic Memory Management**: 
    * By using `std::vector::push_back()`, the program dynamically allocates and manages memory on the heap to accommodate the snake's increasing length during gameplay[cite: 4, 6].
4.  **File Input/Output (Loading/Saving Data)**: 
    * The game features a persistent high-score system. It reads the record from `highscore.txt` upon initialization and updates the file if the player achieves a new record before exiting[cite: 4, 6].
5.  **Program Codes in Multiple Files**: 
    * The source code is modularized into three distinct files for better maintainability:
        * `snake.h`: Class definitions and game constants[cite: 3, 6].
        * `snake.cpp`: Core game logic, terminal I/O handling, and rendering[cite: 1, 6].
        * `main.cpp`: Entry point, difficulty selection menu, and main game loop[cite: 2, 6].

## Technical Highlights
* **Linux Terminal Control**: Uses `<termios.h>` and `<fcntl.h>` to implement non-blocking keyboard input (`kbhit`) and raw input mode (`getch`).
* **ANSI Escape Codes**: Utilizes escape sequences for flicker-free rendering (refreshing the screen without clearing) and hiding/showing the console cursor[cite: 1].
* **Adjustable Difficulty**: Provides three speed settings (Slow, Normal, Hard) managed via `usleep()`[cite: 2, 4].

## Compilation and Execution Instructions
The project is intended to be compiled and run on the **HKU CS Academy Server**.

1. **Compile**: Use the provided `Makefile` by running:
   ```bash
   make
