# Fundamentals of Computing & Programming Portfolio 🚀

Welcome to my core programming repository! This repository compiles the comprehensive major assignments and capstone projects developed during my initial academic phase at the University of Tehran. 

It showcases a structured evolution in low-level and procedural software engineering—progressing from native Windows terminal state machines in **C**, to object-based data tokenization in **C++**, and ultimately to cross-platform 2D hardware-accelerated game engines using **SDL2**.

---

## 📂 Repository Architecture

The repository is organized chronologically by faculty coursework timelines and specialized architectural execution modes:

### 1. [UT Battleship (Terminal Edition)](./UT-Battleship)
* **Language:** Pure C (`<stdio.h>`, `<stdlib.h>`, `<unistd.h>`)
* **Academic Timeline:** Semester 1 (Faculty of Engineering - Mechanical Engineering Stream)
* **Core Concepts:** Multi-dimensional tracking matrices, procedural validation state-loops, user-input parsing, and deterministic game logic.
* **Highlight:** Features **4 distinct Artificial Intelligence (AI) difficulty tiers**, ranging from random coordinate hashing to an unconstrained, highly predictive `unbeatable` simulation matrix alongside custom tactical area-of-effect nuclear mechanics.

### 2. [Smart Story Genre Classifier](./Smart-Story-Genre-Classifier)
* **Language:** C++11 (`std::vector`, `std::string`, `std::stringstream`, file streams)
* **Academic Timeline:** Semester 1 Midterm Capstone
* **Core Concepts:** Comma-Separated Values (CSV) algorithmic file parsing, structured memory modeling (`struct`), string tokenization pipelines, and sorting optimization.
* **Highlight:** Implements a text-mining decision engine that automatically scans prose, aggregates weighted frequency scores against explicit genre vocabularies (*Sci-Fi, Fantasy, Mystery, Romance*), evaluates prediction confidence levels, and extracts top semantic indicators.

### 3. [Real-Time Multiplayer Snake (Dual-Mode Edition)](./space-snake)
* **Language:** Functional C backed by standard OS API layers and hardware abstraction graphics.
* **Academic Timeline:** Semester 1 (School of Electrical and Computer Engineering Stream - Spring 2025)
* **Core Concepts:** Non-blocking asynchronous input handling, hardware double-buffering, multi-entity collision loops, dynamic pointer trackers, and continuous coordinate optimization.
* **Highlight:** A complete multiplayer setup featuring **two distinct executable pipelines**:
    * **Windows Terminal Mode:** Utilizes direct OS kernel hooks (`GetAsyncKeyState()`) and low-level console handle parameters to bypass blocking `getch()` locks and eliminate screen refresh flickering.
    * **SDL2 Graphical Mode:** Employs hardware-accelerated standard 2D renderers (`SDL_Renderer`), custom visual sprite textures, and an asynchronous window loop running with rigid frame-rate constraints.

---

## 🛠️ Global Tools, Libraries, & Environment Setup

To compile and run any individual project locally from source, ensure your local workspace possesses:
* A robust C/C++ compiler toolchain supporting **C++11** or higher standards (e.g., **GCC/G++** or MinGW setup).
* Standard OS runtime binaries supporting specific cross-platform API calls.
* **Simple DirectMedia Layer 2.0 (SDL2)** development libraries including localized image mapping components (`SDL2_image`) for compiling the graphical edition of the capstone project.
