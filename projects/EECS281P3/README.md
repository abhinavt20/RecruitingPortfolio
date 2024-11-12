# Project 3: SillyQL

Link to project: [https://eecs281staff.github.io/p3-sillyql/](https://eecs281staff.github.io/p3-sillyql/)

## Project Overview
This project implements a simplified relational database using a basic subset of SQL-like commands.
It allows for table creation, data insertion, and data querying with conditional filters.

## Key Features
- Create, insert, delete, and query data in tables.
- Supports JOIN operations across tables and indexed searching with hash and bst indices.

## File Structure
- `silly.cpp`: Main implementation of the SillyQL relational database engine.
- `TableEntry.cpp`: Handles entries within tables.
- `TableEntry.h`: Defines the `TableEntry` class for handling table rows.
- `Makefile`: Builds the project.
- `spec-input.txt`: Example input commands for the database.
- `spec-output.txt`: Expected output for the example input commands.

## Requirements
- GCC 11.3.0 (or compatible version)
- CAEN Linux Environment (recommended)

## How to Build and Run
```bash
make -R -r  # Compile the project
./silly     # Run the database shell
```

## Example Usage
Refer to `spec-input.txt` and `spec-output.txt` for a demonstration of commands and expected output.

