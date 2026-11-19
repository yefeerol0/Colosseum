# **Colosseum - A Turn-Based RPG in C++** 

<img width="500" height="248" alt="ColosseumGIF" src="https://github.com/user-attachments/assets/f3a1df0c-15a7-42b0-b259-3050e229d208" />

## **ℹ️ Overview**

* **Colosseum** is a turn-based RPG roguelike that is played on Console.
* The player is a gladiator who tries to win the Grand Tournament for regaining his freedom.

## ❗ **Development Objectives**

* I built *Colosseum* to practice C++ on a small-scoped project.

* My previous C++ projects were all built using Unreal Engine 5's framework. Therefore, I wanted to work on a *native C++ project* to master fundamentals and code architecture.

* This project is designed as a *technical showcase/code sample*. As a result, I prioritized polishing the code and project structure over game design.

## ⌨️ **Controls**

* *1-5 number keys* to select action and stat to upgrade.

* Not mandatorily, *any other key* while entering your gladiator's name.

* *ENTER* to confirm gladiator name.

* *ESC* to quit game.

## 🚩 **How to Play?**

1. Download the latest build from "*Releases*" section and extract the ZIP.

2. To build from the source firstly, "*cmake -S . -B build*" then, "*cmake --build build*" commands can be used.

3. The game loop is "*Fight, Upgrade, Repeat*" until the player beats 20 enemy gladiators and wins the game.

4. The distribution of stats is the biggest factor of success. Try different approaches and find your way to the top of the Colosseum!

## 🔌 **Technical Details**

* It is fully written in *C++* and built via *CMake*.

* Currently, it is playable on *64-bit Windows* systems.

* A *data-driven approach* is used for enemy stats (Enemies.json) and numeric balance (GameTuning.h).

* Enemy AI uses a *utility AI system* while calculating the most suitable option (EnemyBehavior.cpp).

* The project architecture follows a "*GameManager → CombatManager → CombatActions*" flow, with other classes helping.

## ⚠️ **AI Disclosure**

* All source code in this project is handwritten. Until the "*Code Review*" commit, no AI was used in any part of the project.

* While code reviewing, I used Claude Code's assistance to spot the consistency issues, dead code, bugs and other issues to solve them myself.

* During balancing, Claude Code simulated *\~100,000+ test runs* and provided data about the win rates of different builds, scenarios resulting in a stall and the unbalanced enemies. Balancing the game using these information, significantly sped the process up.

## 🔑 **Credits**

* ***nlohmann/json v3.12.0*** by Niels Lohmann (MIT License)
