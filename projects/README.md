# Projects Overview

This folder contains a collection of key projects I have worked on throughout my academic and professional journey. Each project showcases my skills in data science, machine learning, and natural language processing. Below is a brief description of some notable projects included in this folder:


## 1) Crisp Data-Wrangling

### Description: 
This project is designed to help you clean up and transform CSV data based on specified configuration rules. It reads an input CSV file, applies the transformations defined in a `config.json` file, and produces a new CSV file as the output. Any issues encountered (like invalid dates) are logged in `transform_errors.log`, allowing for easy troubleshooting.

### Technologies Used: 
- **Python 3.8+**
- **Pandas:** Used for efficient data manipulation.
- **JSON:** The transformation rules are stored in `config.json` for easy modification.

### Key Contributions:
- Developed a robust data transformation tool that successfully cleans and formats CSV data based on user-defined rules.
- Achieved an efficient processing pipeline that can handle standard CSV data inputs, producing transformed output while logging errors for further review.
- Implemented error handling mechanisms to log issues encountered during transformation, facilitating easier debugging.
- Planned future enhancements, including support for larger datasets through chunked processing and improved error handling strategies.


## 2) EECS 280 Project 1: Statistics

### Description: 
This project implements a program that computes descriptive statistics and performs two-sample analysis on a given dataset. The program reads a dataset, extracts specific columns, and computes essential statistics such as mean, median, standard deviation, and percentiles. It also performs a two-sample comparison to calculate a 95% confidence interval for the difference in means between two groups within the dataset.

### Technologies Used: 
- **C++:** Used for implementing the statistical functions and main program logic.
- **Makefile:** For compiling and running unit tests.
- **Vector and Algorithm Libraries:** Used for storing data and performing operations like sorting and filtering.
- **Bootstrap Resampling:** Utilized for calculating confidence intervals in two-sample analysis.

### Key Contributions:
- Developed a statistical analysis tool capable of handling descriptive statistics and two-sample comparisons.
- Implemented a suite of statistical functions (mean, median, standard deviation, etc.) in C++.
- Designed unit tests for each statistical function to ensure correctness.
- Implemented confidence interval estimation using bootstrap resampling.


## 3) EECS 280 Project 2: Computer Vision

### Description: 
This project implements a content-aware image resizing program using the seam carving algorithm. The program resizes images by intelligently removing "seams" – paths of least important pixels – while preserving key content. This project practices matrix manipulation, image processing, and abstract data types (ADT) in C++. The final tool takes in an image, resizes it based on user input, and outputs the resized version. The focus is on optimizing the seam carving algorithm to perform efficiently while maintaining image quality.

### Technologies Used: 
- **C++:** Used for the implementation of the seam carving algorithm, matrix and image modules.
- **Makefile:** Automates the build process, compiling and running unit tests.
- **Dynamic Programming:** Seam carving utilizes dynamic programming to find the optimal seam for removal.
- **PPM File Format:** Used for input/output of images.

### Key Contributions:
- Developed an image resizing tool that uses content-aware seam carving.
- Implemented matrix and image handling functionalities in C++.
- Designed unit tests for matrix and image modules to ensure correctness.
- Implemented the seam carving algorithm for intelligent resizing of images while minimizing visual distortion.


## 4) EECS 280 Project 3: Euchre
### Description:
This project implements a simulation of the card game Euchre using object-oriented programming in C++. The game features AI players and can also accommodate a human player via the command line interface. The project focuses on practicing Abstract Data Types (ADTs), Inheritance, Polymorphism, and Operator Overloading, offering a deeper understanding of object-oriented concepts and C++ programming techniques. The game includes both shuffling and non-shuffling modes, and uses a strategy-based AI to play a full game of Euchre.

### Technologies Used: 
- **C++:** For implementing game logic, AI strategy, and card deck operations.
- **Makefile:** To compile and run the game and its unit tests.
- **Object-Oriented Programming:** Using inheritance and polymorphism to implement the Player class.
- **Unit Test Framework:** For testing individual game components like cards, decks, and players.

### Key Contributions:
- Designed and implemented a complete game of Euchre, with support for both human and AI players.
- Developed AI players with a simple strategy for making trump, leading, and playing tricks.
- Implemented core ADTs for cards, deck (Pack), and player actions, emphasizing object-oriented design.
- Created comprehensive unit tests to validate the correctness of the game's components.


## 5) EECS 280 Project 4: Web

### Description:
This project implements a web server for an office hours queue system. The primary goal is to create a doubly-linked list and support a web API for managing the queue. The project introduces concepts such as Container ADTs, Dynamic Memory, Linked Lists, and Iterators in C++. 

### Technologies Used:
- **C++ (Templates):** For creating a doubly-linked list and managing memory with new/delete.
- **Unit Testing Framework:** For verifying the functionality of the list with edge cases.
- **JSON Parsing Library (json.hpp):** Used for serializing and deserializing data in the web API.
- **Python (server.py):** Provides a Python script to run the server and handle web requests.

### Key Contributions:
- Implemented a fully functional doubly-linked list with iterators.
- Developed unit tests to validate the list's functionality and memory management.
- Optionally designed a REST API to interact with the office hours queue using HTTP methods like GET, POST, and DELETE.


## 6) EECS 280 Project 5: Machine Learning

### Description:
This project focuses on building a machine learning classifier that can automatically identify the subject of EECS 280 Piazza posts using natural language processing (NLP) and a "bag of words" model. The project reinforces key concepts such as Binary Search Trees (BST), Templates, Comparators, and Recursive Algorithms. This project also utilizes dynamic memory management and Map data structures while implementing a Multi-Variate Bernoulli Naive Bayes Classifier.

### Technologies Used:
- **C++ (Templates):** Used for creating a Binary Search Tree and Map ADTs, which serve as the core data structures.
- **Unit Testing Framework:** To verify the correctness of BST and Map implementations.
- **csvstream.hpp:** A CSV parsing library used for reading training and testing data.
- **Supervised Machine Learning:** Implementation of a probabilistic model for classification using labeled Piazza posts.

### Key Contributions:
- Developed a recursive Binary Search Tree supporting efficient data storage and retrieval.
- Implemented a custom Map ADT using a BST, handling key-value pairs.
- Built a Naive Bayes Classifier to categorize Piazza posts into topics based on word frequency.
- Developed unit tests for Binary Search Tree and Map to ensure correct functionality.
- Implemented command-line interface for training and testing the classifier with CSV data.

  
## 7) EECS 281 Project 1: Rescue the Countess

### Description:
This project is designed to build a path-finding solution for a maze-like castle layout. The objective is to help Marco rescue Countess Cherry using efficient algorithms in C++. Key concepts include breadth-first and depth-first search, managing multi-room navigation, and ensuring program efficiency with restricted memory usage.

### Technologies Used:
- **C++ STL**: For data management with `deque`, `vector`, `string`, etc.
- **Pathfinding Algorithms**: Breadth-first and depth-first searches adapted for stack and queue routing schemes.
- **Optimization Tools**: Valgrind for memory leak detection and runtime optimization.

### Key Contributions:
- Developed an efficient map parsing system supporting two distinct input modes.
- Implemented stack and queue-based routing schemes to explore two search methodologies.
- Designed warp pipe functionality for multi-room transitions, ensuring Marco’s path is accurately tracked.
- Integrated error-handling for invalid inputs and comprehensive testing through customized test cases.

  
## 8) EECS 281 Project 2: The Walking Deadline & Priority Queues

### Description:
This two-part project explores simulation and data structures. Part A, The Walking Deadline, simulates a player defending against zombies using priority queues. Part B involves implementing and testing multiple priority queue structures, offering insight into their efficiency and real-world applications.

### Technologies Used:
- **C++ STL**: Provides base structures like `std::priority_queue`, vectors, and comparators.
- **Mersenne Twister Random Generator**: Custom random generator for consistent zombie attributes in Part A.
- **Priority Queues**: Implemented various priority queues, including Binary Heap, Sorted Array, and Pairing Heap, for managing tasks efficiently.

### Key Contributions:
- Developed a zombie simulation game using priority-based actions to prioritize threats.
- Implemented custom priority queues to compare different queue structures.
- Handled complex edge cases with command-line options for verbose output, median tracking, and game statistics.



## 8) EECS 281 Project 3: SillyQL 

### Description
SillyQL is a simplified SQL-like database that allows for basic data manipulation and querying. The project is structured
to simulate a relational database where tables can be created, modified, and queried interactively. This project demonstrates the ability to simulate SQL database behavior using custom and STL data structures in C++.

### Technologies Used
- **C++** for efficient data structure management and logic.
- **STL Containers** like `std::map`, `std::unordered_map`, and `std::vector` for handling database components.

### Key Contributions
1. **Database Shell**: Created a command-line shell to interact with tables.
2. **Data Management**: Implemented table creation, insertion, deletion, and conditional selection.
3. **JOIN Operations**: Enabled data joining across tables for complex queries.
4. **Indexing**: Built hash and bst-based indexing for faster data retrieval on specific columns.


## 9) EECS 281 Project 4: Among Us

## Description
This project implements a set of graph algorithms for a game-like scenario inspired by "Among Us." It focuses on solving graph traversal problems in a spatial setup using Minimum Spanning Tree (MST) and Traveling Salesperson Problem (TSP) techniques. The project comprises three parts:
1. **MST Mode**: Calculates the Minimum Spanning Tree (MST) for connecting all locations at minimal distance.
2. **FASTTSP Mode**: Approximates a solution to the Traveling Salesperson Problem.
3. **OPTTSP Mode**: Finds an optimal TSP solution using branch and bound techniques.

## Technologies Used
- **C++ (Object-Oriented Design)**: Core language for implementing graph algorithms and game logic.
- **Graph Theory Algorithms**: Used MST and TSP solutions, with algorithms for Prim’s, Kruskal’s, branch and bound, and various heuristic techniques.
- **STL Containers**: Employed standard containers such as vectors, priority queues, and sets for efficient data management.
- **Mathematical Computations**: Utilized Euclidean distance calculations and efficient mathematical operations for spatial analysis.

## Key Features
- Implements MST calculation with algorithms like Prim's or Kruskal's.
- Approximates a TSP solution with heuristics to achieve near-optimal results.
- Provides a branch-and-bound approach to determine an optimal TSP path.
- Utilizes efficient data structures and algorithms for spatial graphs.


## 9) EECS 484 Project 1: Fakebook Database

## Description
This project focuses on creating a database schema and loading data for the social media platform "Fakebook." The tasks include designing an ER Diagram, writing SQL scripts for table creation, data loading, and view creation. The project also involves enforcing constraints through SQL triggers and validating the schema against a public dataset.

## Technologies Used
- **SQL**: For writing DDL and DML statements to manage the database.
- **SQL*Plus**: Oracle's command-line tool for executing SQL scripts.
- **Oracle Database**: The relational database system used to store and query Fakebook data.
- **Database Design Concepts**: Including normalization, primary and foreign key constraints, and relationships between entities.

## Key Contributions
- Developed an ER Diagram representing Users, Messages, Photos, Albums, and Events.
- Created SQL scripts for setting up tables with primary keys, foreign keys, and custom constraints.
- Loaded data from the public dataset and created views that replicate the schema of the public tables.
- Implemented triggers to enforce complex constraints, such as managing bidirectional friendships in Fakebook.


## 9) EECS 484 Project 2: Fakebook JDBC

## Project Overview
In Project 2, you will develop a Java application that interfaces with a relational database, executing SQL queries to manage and process data for the Fakebook platform. 
The project provides experience in both database query structuring and application-level data processing.

## Project Goals
1. Implement SQL queries in Java using JDBC.
2. Manipulate query results to populate custom data structures.
3. Practice writing efficient and optimized SQL queries that run within set time constraints.
4. Ensure proper resource management and exception handling within JDBC operations.

## Technologies Used
- **Java**: Main programming language used for application logic.
- **JDBC (Java Database Connectivity)**: Manages SQL connections and query execution.
- **Oracle SQL**: Database query language for relational data access.
- **Makefile**: Used for automating compilation, running, and cleaning of the project.


