# UT Battleship 🚢

A classic console-based Battleship game implemented in pure C, featuring multiple AI difficulty levels and special gameplay mechanics like tactical nuclear strikes. This project was developed as the primary computer programming assignment during my first semester at the University of Tehran. (Fall 2023)

## 🌟 Features

- **Interactive Console UI:** Real-time side-by-side rendering of your fleet's status and your strategic radar map.
- **Dynamic Ship Placement:** Supports custom positioning of various ship sizes with built-in orientation validation (`U`p, `D`own, `R`ight, `L`eft).
- **Special Weaponry:** Each player has access to one **Tactical Nuclear Bomb** per round, dealing devastating $3 \times 3$ area-of-effect damage.
- **Persistent Scoreboard:** Tracks match scores dynamically across multiple consecutive rounds.
- **4 AI Difficulty Levels:**
  - `easy`: The computer fires completely random shots across the map.
  - `normal`: Features a balanced $\frac{1}{3}$ probability of targeting your exact ship coordinates and a $\frac{2}{3}$ chance of random firing.
  - `hard`: High threat tracking with a $\frac{2}{3}$ probability of finding your remaining ships.
  - `unbeatable`: An advanced algorithmic opponent that calculates maximum probability density matrices for nuclear placement and tracks ship positions with absolute precision.

---

## 🎮 Game Rules & Symbology

The game is played on a dual $10 \times 10$ grid system using the following visual indicators:
- `-` : Unexplored fog of war / open ocean.
- `S` : Your active Ship segments.
- `O` : Missed bomb locations.
- `X` : Successfully destroyed ship segments.

### Fleet Composition
Every round, both players deploy a total of 10 ships consisting of **20 total structural segments**:
- $1 \times$ Carrier (4 segments)
- $2 \times$ Battleships (3 segments)
- $3 \times$ Destroyers (2 segments)
- $4 \times$ Patrol Boats (1 segment)
