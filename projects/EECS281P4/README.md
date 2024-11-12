# README - Project 4: Among Us

Link to project: [https://eecs281staff.github.io/p4-among-us/](https://eecs281staff.github.io/p4-among-us/)

## Project Overview
This project simulates a solution to an Among Us-inspired problem involving complex graph operations on x-y coordinate points. The program reads vertices (representing rooms) and calculates a minimum spanning tree (MST), an approximate solution to the Travelling Salesperson Problem (TSP), and an optimal TSP solution.

## Features

### MST Calculation
- Calculates an MST for connecting vertices at the lowest possible cost.
- Determines efficient paths between rooms based on given rules.

### TSP Approximation
- Uses heuristics to approximate an efficient route visiting all vertices in the graph.

### Optimal TSP Calculation
- Implements a branch-and-bound algorithm to find the shortest possible path to visit all vertices in the graph.

## File Structure
- `amongUs.cpp`: Main implementation of the MST, TSP approximation, and optimal TSP calculations.
- `Makefile`: For building the project.

## Requirements
- C++ Compiler supporting C++11 or later.
- GNU Make for compiling.

## How to Build and Run

### Build
```bash
make -R -r
```

### Run

#### MST Mode
```bash
./amongus --mode MST < inputFile.txt
```

#### FASTTSP Mode
```bash
./amongus --mode FASTTSP < inputFile.txt
```

#### OPTTSP Mode
```bash
./amongus --mode OPTTSP < inputFile.txt
```

## Sample Commands
To run different modes:

1. **MST Calculation:** `./amongus --mode MST < inputFile.txt`
2. **TSP Approximation:** `./amongus --mode FASTTSP < inputFile.txt`
3. **Optimal TSP Calculation:** `./amongus --mode OPTTSP < inputFile.txt`
