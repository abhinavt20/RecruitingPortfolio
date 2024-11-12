
# EECS 281 Project 1: Rescue the Countess

Link to project: [https://eecs281staff.github.io/p1-rescue-the-countess/](https://eecs281staff.github.io/p1-rescue-the-countess/)

## Project Overview

This project involves creating a path-finding algorithm to help the character Marco navigate a maze-like castle to rescue Countess Cherry. Implemented in C++, this project explores data structures and algorithm efficiency through two routing schemes (stack-based and queue-based) to guide Marco through rooms while avoiding walls, enemies, and invalid locations.

## Features

1. **Path-finding Algorithms**:
   - Implemented both queue-based and stack-based routing schemes.
   - Each scheme employs breadth-first and depth-first search approaches to find a viable path to the Countess.

2. **Map Input Handling**:
   - Supports two input modes: Map (M) for room layouts and Coordinate List (L) for specifying only key elements.
   - Parses and processes input to construct a multi-room castle representation.

3. **Warp Pipes Navigation**:
   - Recognizes and processes warp pipes (0-9) for inter-room travel.
   - Tracks positions across rooms to avoid loops and invalid locations.

4. **Output Modes**:
   - Outputs path taken either as a map or in a coordinate list format, as specified by command-line arguments.
   - If no path exists, outputs a clear "No solution" message with the number of tiles discovered.

5. **Error Handling and Testing**:
   - Comprehensive error handling for invalid characters, room sizes, and coordinates.
   - Allows for flexible testing through different input files and test scenarios.

## File Structure

- **`rescue.h`**: Header file with declarations for data structures and helper functions.
- **`rescue.cpp`**: Contains implementation for path-finding algorithms and helper functions.
- **`main.cpp`**: Main program logic managing command-line arguments and execution flow.
- **`Makefile`**: Builds the project with flags for optimization and debugging.

## Requirements

### Software
- **C++ Compiler**: GCC with support for C++11 or later (tested with GCC 6.2.0)
- **Make**: For compiling and running tests

### Libraries
- Standard Template Library (STL) for data structures such as `deque`, `vector`, and `string`.

## How to Build and Run

1. **To build the project**:
    ```bash
    make
    ```

2. **To run with stack-based routing**:
    ```bash
    ./superMarco --stack < infile > outfile
    ```

3. **To run with queue-based routing**:
    ```bash
    ./superMarco --queue < infile > outfile
    ```

4. **To specify output format (Map or List)**:
    ```bash
    ./superMarco --stack --output M < infile > outfile
    ```

## Example Usage

```bash
./superMarco --queue --output L < sample_input.txt > sample_output.txt
```

