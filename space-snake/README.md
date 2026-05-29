# Real-Time Multiplayer Snake: Terminal & SDL2 Graphical Editions 🐍🎮

A high-performance, real-time multiplayer implementation of the classic Snake game featuring two distinct operation modes: a lightweight **Windows Console Edition** and a fully-immersive **SDL2 Graphical Edition**. Developed as the final capstone project for the Fundamentals of Computing & Programming course at the **University of Tehran** (Spring 2025).

The project elevates the core principles of structural programming in C (using arrays, pointers, memory buffers, and custom structural state-tracking) into a real-time, event-driven interactive system.

---

## 🌟 Core Features & Gameplay Mechanics

- **Real-Time Multiplayer Grid:** Supports two simultaneous players sharing the same keyboard buffer without rendering lag or blocking inputs.
  - **Player 1 (Snake 'O'):** Controlled via `W`, `A`, `S`, `D` keys.
  - **Player 2 (Snake 'X'):** Controlled via standard Keyboard Arrow Keys.
- **Dynamic Food & Growth Spawns:** Consuming food (`$`) instantly awards $10$ points and increases the respective snake's segment length by $1$. Food positions are generated using validated pseudo-random coordinate hashing to prevent spawning inside snake bodies.
- **Match Timer (50-Second Threshold):** Built-in game loop counter tracking real-time match progression. If both players survive beyond 50 seconds, the engine evaluates active performance and declares the player with the highest score as the winner.
- **Strict Collision Bounds:** Immediate match termination occurs if a snake collides with the outer boundary walls, its own growing segments, or the opponent's body.

---

## 🖥️ Edition 1: Windows Console Mode (`terminal-version.c`)

Optimized for minimum CPU footprint, this version utilizes native Windows OS handles to manage a non-blocking execution pipeline.

- **Non-Blocking Key Capturing:** Utilizes standard `GetAsyncKeyState()` API to track multiple concurrent keystrokes asynchronously, bypassing the traditional blocking constraints of `getch()`.
- **Cursor Optimization:** Custom sub-routine calls `hide_cursor()` via `<windows.h>` handles (`CONSOLE_CURSOR_INFO`) to completely eliminate terminal flickering during high-frequency screen updates.
- **Visual Grid Representation:** Renders custom symbols to dynamically track game actors across a matrix layout.

---

## 🎨 Edition 2: SDL2 Graphical Mode (`main.c`)

A custom, modern gaming experience that scales the underlying logic into a full 2D hardware-accelerated rendering environment using **Simple DirectMedia Layer (SDL2)**.

- **Asynchronous Event Loop:** Implements `SDL_PollEvent` to catch window close actions, keyboard downstream releases (`SDL_KEYDOWN`, `SDL_KEYUP`), and player vectors.
- **Custom Visual Identity:** Features bespoke user-interface layouts, custom icons designed from scratch, and AI-assisted atmospheric background themes seamlessly loaded into the display context.
- **Hardware-Accelerated Frame Syncing:** Leverages double-buffered rendering sequences (`SDL_RenderClear`, `SDL_RenderFillRect`, `SDL_RenderPresent`) operating with structured macro delays (`SDL_Delay`) to enforce constant frame rates and buttery smooth movement transitions.

