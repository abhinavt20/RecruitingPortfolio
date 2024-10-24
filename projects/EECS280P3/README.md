# README

Link to project: https://eecs280staff.github.io/p3-euchre/

## Overview
This project implements a simulation of the Euchre card game in C++. Euchre is a popular trick-taking game, especially in Michigan. 
The project supports four players: AI players or human-controlled players via the command line. 
The program allows users to specify various game settings, including shuffling the deck and the number of points required to win.

The key learning goals include practicing Object-Oriented Programming (OOP) principles such as abstract data types (ADTs), inheritance, polymorphism, and operator overloading in C++.

## How to Build and Run

### Prerequisites:
- **C++ Compiler (g++ or clang)**
- Makefile (included for building)

### Running the Code:

1. Clone the repository or download the project files.
2. Open a terminal in the project directory.
3. Run the following command to build the game:
   ```
   make euchre.exe
   ```
4. Once the game is compiled, run the following command to start the game:
   ```
   ./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple
   ```

The above example runs a game of Euchre with four AI players named Adi, Barbara, Chi-Chih, and Dabbala, with no shuffle, and 1 point needed to win.

### Architecture and Technology Overview
This program is built in C++ and follows an object-oriented design with abstract data types, inheritance, and polymorphism.
The game of Euchre is modeled with various classes, including `Card`, `Pack`, `Player`, and the game driver. There are two types of players: human-controlled and AI-controlled.

### Key Components:
- **Card:** An ADT representing a card with a suit and rank.
- **Pack:** Represents a deck of cards, with shuffling and dealing functionality.
- **Player:** Abstract class for both human and AI players. 
  - The AI player uses a basic strategy to make decisions during the game.
- **euchre.cpp:** The main game driver that coordinates the game flow.

### Technologies:
- **C++:** Used for the core game logic, object-oriented design, and inheritance.
- **Makefile:** Automates the building process of the project and the associated tests.
- **Unit Test Framework:** Included for testing each component of the game.

### Assumptions:
- Input files are well-formed, and the user will input valid commands during gameplay.
- The program assumes that all game participants will adhere to the rules of Euchre.
- Shuffling is optional and can be turned on or off via the command line.
  
### Next Steps:
1. **Enhance AI:** Improve the AI decision-making to use more advanced strategies.
2. **Multiplayer Support:** Add networking support for real-time multiplayer games.

