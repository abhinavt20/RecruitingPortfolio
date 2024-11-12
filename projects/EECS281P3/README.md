# README - Project 3: SillyQL

## Project Overview
This project implements a simplified relational database model with a custom structured query language called "SillyQL." The database is built to store and manage data tables with commands resembling SQL syntax, such as creating tables, inserting rows, and printing or joining table data. The project reinforces understanding of data structures and efficient data handling techniques for database-like applications.

## Key Features
- Create, insert, delete, and query data in tables.
- Supports JOIN operations across tables and indexed searching with hash and bst indices.

## Features
### Table Creation
- Allows for the creation of tables with specified column types (int, double, bool, and string) and column names.
- Ensures each table’s structure is customizable and column names are unique.

### Data Insertion
- Supports inserting multiple rows into specified tables.
- Validates the types of inserted values to match each column’s type.

### Basic Data Commands
- **PRINT**: Prints specific columns from a table based on filtering conditions or prints all rows if no filter is specified.
- **DELETE**: Deletes rows in a table based on specified conditions.

### Table Join
- Supports joining two tables on a specified column from each table and printing the result based on column selection.

### Indexing
- Allows indexing on a specified column using either a hash-based or binary search tree (BST) approach to optimize query performance.
- Ensures that any previous index on the table is discarded if a new one is created.

## File Structure
- `silly.cpp`: Main implementation of the SillyQL relational database engine.
- `TableEntry.cpp`: Handles entries within tables.
- `TableEntry.h`: Defines the `TableEntry` class for handling table rows.
- `Makefile`: Builds the project.
- `spec-input.txt`: Example input commands for the database.
- `spec-output.txt`: Expected output for the example input commands.

## Requirements
### Software
- C++ Compiler (supporting C++11 or later)
- Make: For compiling and running the database shell.

## How to Build and Run
To compile the project:
```bash
make -R -r
```

To run the program:
```bash
./silly
```

## Sample Commands
After running the program, you can interact with the shell by typing commands. Here are a few sample commands:

### Creating a table:
```plaintext
CREATE my_table 3 int string bool age name is_student
```

### Inserting data:
```plaintext
INSERT INTO my_table 2 ROWS
21 John true
22 Jane false
```

### Printing all rows:
```plaintext
PRINT FROM my_table ALL
```

### Deleting rows:
```plaintext
DELETE FROM my_table WHERE age > 21
```

### Joining tables:
```plaintext
JOIN table1 AND table2 WHERE col1 = col2 AND PRINT 3 col1 1 col3 2 col2 1
```

### Generating an index:
```plaintext
GENERATE FOR my_table hash INDEX ON age
```

## Example Usage
```plaintext
CREATE students 3 int string bool id name is_enrolled
INSERT INTO students 2 ROWS
1 Alice true
2 Bob false
PRINT FROM students ALL
DELETE FROM students WHERE is_enrolled = false
```

