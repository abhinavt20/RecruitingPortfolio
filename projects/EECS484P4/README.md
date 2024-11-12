
# Project 4: Grace Hash Join

Link to project: [https://eecs484db.github.io/f24/p4-ghj](https://eecs484db.github.io/f24/p4-ghj)

## Project Overview
This project focuses on implementing the Grace Hash Join (GHJ) database algorithm in C++. GHJ is used to perform joins between two database relations by dividing the process into a two-phase operation: partitioning and probing. In this project, you will implement the `partition` and `probe` functions in `Join.cpp` to simulate database joining processes.

## Key Features
- **Partition Phase**: Divides records from the left and right relations into buckets based on hash values.
- **Probe Phase**: Uses a hash table to find matching records from the two relations in each partition.
- **Data Emulation**: Utilizes emulated disk and memory for record storage and processing.
- **Testing**: Supports testing via provided text files (`left_rel.txt` and `right_rel.txt`).

## File Structure
- `Record.hpp` / `Record.cpp`: Defines the structure and hash functions for records.
- `Page.hpp` / `Page.cpp`: Manages pages containing records.
- `Disk.hpp` / `Disk.cpp`: Emulates disk storage for records.
- `Mem.hpp` / `Mem.cpp`: Emulates memory for loading and processing records.
- `Bucket.hpp` / `Bucket.cpp`: Defines buckets used in the partition phase.
- `Join.hpp` / `Join.cpp`: Contains the core `partition` and `probe` functions to be implemented.
- `constants.hpp`: Defines constants used across the project.
- `main.cpp`: Main file to execute and test the GHJ.
- `Makefile`: Compiles and runs the GHJ program.

## Requirements
- **Software**: Linux environment with GCC 5.4.0 or higher, C++14 standard.
- **Libraries**: Standard C++ libraries only.

## How to Build and Run the Code
1. Compile the project:
   ```bash
   make
   ```
2. Run the executable:
   ```bash
   ./GHJ left_rel.txt right_rel.txt
   ```
3. Clean up generated files:
   ```bash
   make clean
   ```

## Example Usage
After building the project, running `./GHJ left_rel.txt right_rel.txt` will execute the Grace Hash Join and display the output of joined records from the two relations based on matching keys.

