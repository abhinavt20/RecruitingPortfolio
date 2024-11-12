
# EECS 281 Project 2: The Walking Deadline & Priority Queues

Link to project: [https://eecs281staff.github.io/p2-walking-deadline/](https://eecs281staff.github.io/p2-walking-deadline/)

## Project Overview

This project consists of two parts. Part A (The Walking Deadline) involves simulating a zombie attack using a priority queue for decision-making, allowing the player to prioritize zombie threats based on distance, health, and speed. Part B involves implementing various priority queue data structures (Sorted Array, Binary Heap, Pairing Heap, and Unordered Fast PQ) to be used as the underlying structures for prioritizing actions in Part A.

## Features

### Part A - The Walking Deadline

1. **Zombie Attack Simulation**:
   - Implements a zombie attack sequence where zombies approach the player over multiple rounds.
   - Zombies are prioritized based on their Estimated Time of Arrival (ETA), calculated using distance and speed.

2. **Priority Queue Usage**:
   - Uses STL’s `std::priority_queue` in Part A to manage zombies dynamically, based on ETA, health, and name.

3. **Dynamic Statistics and Outputs**:
   - Handles multiple command-line options to display verbose output, statistics, and median zombie active times.
   - Provides a comprehensive simulation output, detailing actions per round.

4. **Random Zombie Generation**:
   - Utilizes a custom Mersenne Twister-based random number generator to produce unique zombie attributes.

### Part B - Priority Queue Implementations

1. **Binary Heap Priority Queue (BinaryPQ)**:
   - Implements a max-heap-based priority queue using binary tree properties.

2. **Sorted Array Priority Queue (SortedPQ)**:
   - Maintains a sorted vector to allow efficient access to the highest priority element.

3. **Pairing Heap Priority Queue (PairingPQ)**:
   - Utilizes a pairing heap data structure, enabling efficient insertion and removal operations with dynamic priority updates.

4. **Unordered Fast Priority Queue (UnorderedFastPQ)**:
   - Stores elements in an unordered vector, optimized for quick `top` and `pop` operations, relying on fast lookups for priority.

## File Structure

- **gameplay.cpp**: Implements the zombie simulation logic for Part A.
- **P2random.cpp & P2random.h**: Defines the random zombie generation functions.
- **BinaryPQ.h**: Defines the Binary Heap-based priority queue for Part B.
- **Eecs281PQ.h**: Interface file defining base priority queue class and methods.
- **PairingPQ.h**: Implements the Pairing Heap-based priority queue.
- **SortedPQ.h**: Implements the Sorted Array-based priority queue.
- **UnorderedFastPQ.h**: Implements an unordered vector-based priority queue.

## Requirements

### Software
- **C++ Compiler**: GCC 11.3.0 or later, optimized with `-O3`.
- **Make**: For compiling the project.

### Libraries
- **Standard Template Library (STL)**: Utilized for vectors, deques, and other fundamental structures.

## How to Build and Run

### Part A - The Walking Deadline

1. **To compile**:
    ```bash
    make -f Makefile_A
    ```

2. **To run the simulation**:
    ```bash
    ./zombbb --verbose --statistics <num> < infile.txt > outfile.txt
    ```

### Part B - Priority Queue Implementations

1. **To compile**:
    ```bash
    make -f Makefile_B
    ```

2. **To test individual priority queues**:
    Use `project2b.cpp` as a testing driver to verify the behavior of each implemented priority queue.

## Example Usage

```bash
./zombbb --median < infile.txt > outfile.txt
```

