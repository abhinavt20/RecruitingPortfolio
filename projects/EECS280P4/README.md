# EECS 280 Project 4: Web

Link to project: https://eecs280staff.github.io/p4-web/

## Project Overview

This project involves the implementation of a web server for managing an office hours queue system. The main task is to create a doubly-linked list data structure in C++ that manages the queue. The project introduces Container ADTs, Dynamic Memory, Linked Lists, and Iterators. Additionally, there is an optional component to implement a REST API for interacting with the queue.

## Features

1. **Doubly-Linked List:**
   - Implements a templated doubly-linked list with dynamic memory allocation.
   - Includes support for common operations such as insertion, deletion, traversal, and access via iterators.

2. **REST API (Optional):**
   - Provides a REST API for managing the office hours queue.
   - Supports the following operations:
     - `GET /api/queue/`: Retrieves the entire queue.
     - `POST /api/queue/tail/`: Adds a new person to the queue.
     - `GET /api/queue/head/`: Retrieves the person at the head of the queue.
     - `DELETE /api/queue/head/`: Removes the person at the head of the queue.

3. **Unit Testing:**
   - The project includes comprehensive unit tests for the doubly-linked list using a testing framework.
   - Tests cover edge cases such as empty lists, inserting at the head/tail, removing elements, and proper memory management.

4. **Dynamic Memory Management:**
   - Proper use of C++ dynamic memory operations (`new`, `delete`).
   - Implementation of the Big Three (copy constructor, assignment operator, destructor) to ensure memory is managed without leaks.

## File Structure

- **`List.hpp`**: Contains the implementation of the templated doubly-linked list.
- **`List_tests.cpp`**: Unit tests for the `List` class using the unit test framework.
- **`api.cpp`** (Optional): Implements the web API that interacts with the queue through HTTP requests.
- **`server.py`**: A Python script that runs the web server and forwards requests to the `api.cpp` program.
- **`index.html`**: Basic HTML page for testing the web server.

## Requirements

### Software
- C++ Compiler (supports C++11 or later)
- Python 3.x (for running the web server)
- Make (for building the project)

### Libraries
- `json.hpp`: A JSON parsing library for handling requests and responses in the API.
- Unit Testing Framework (provided by the course).

## How to Build

To build and test the doubly-linked list:

```bash
make List_tests.exe
./List_tests.exe
```

(Optional) To build and run the web server:

```bash
make api.exe
python3 server.py
```

## How to Run Tests

Unit tests for the linked list can be run using the following commands:

```bash
make List_tests.exe
./List_tests.exe
```

To test the web API:

```bash
make api.exe
./api.exe < test01.in
```

You can use the provided input files (e.g., `test01.in`) to simulate API requests.

## REST API Usage (Optional)

### `POST /api/queue/tail/`
- Adds a person to the queue.
- Request Body (JSON):
  ```json
  {
      "uniqname": "uniqname_here",
      "location": "location_here"
  }
  ```
- Example Response (JSON):
  ```json
  {
      "uniqname": "uniqname_here",
      "location": "location_here",
      "position": 1
  }
  ```

### `GET /api/queue/`
- Retrieves the entire queue.
- Example Response (JSON):
  ```json
  {
      "count": 3,
      "results": [
          {
              "uniqname": "student1",
              "location": "Table 1",
              "position": 1
          },
          {
              "uniqname": "student2",
              "location": "Table 2",
              "position": 2
          }
      ]
  }
  ```

### `GET /api/queue/head/`
- Retrieves the person at the head of the queue.
- Example Response (JSON):
  ```json
  {
      "uniqname": "student1",
      "location": "Table 1",
      "position": 1
  }
  ```

### `DELETE /api/queue/head/`
- Removes the person at the head of the queue.
- Response: No content (HTTP 204).

## Key Concepts

- **Container ADTs**: A doubly-linked list implementation allows for efficient insertion and deletion at both ends.
- **Dynamic Memory**: Proper memory management through manual allocation and deallocation (`new`/`delete`).
- **Big Three**: Implementation of the copy constructor, assignment operator, and destructor to prevent memory leaks.
- **Iterators**: Custom iterator implementation for traversing the doubly-linked list.
- **REST API**: Optional API for interacting with the queue through HTTP requests.

## Acknowledgments

This project was developed as part of the EECS 280 course at the University of Michigan. The original project specification and starter files were provided by the course instructors.

