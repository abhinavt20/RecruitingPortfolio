# EECS 280 Project 5: Machine Learning

Link to project: https://eecs280staff.github.io/p5-ml/

## Project Overview

This project aims to classify EECS 280 Piazza posts by using machine learning and natural language processing techniques. You will implement a "bag of words" model using a custom-built Map and Binary Search Tree (BST) data structures to store and analyze word frequencies for different categories.

The classifier will be trained on labeled Piazza posts and will predict the most likely topic of new posts based on the frequency of words in each topic.

## Features

1. **Binary Search Tree (BST):**
   - Implements a templated binary search tree.
   - Supports common operations such as insertion, deletion, traversal, and finding elements.
   - Includes a recursive design with proper handling of memory using dynamic allocation and the Big Three (copy constructor, assignment operator, destructor).

2. **Map ADT:**
   - Implements a Map data structure (key-value pairs) using the BST.
   - Supports insertion, lookup, and modification of values by key.
   - Utilizes a custom comparator for sorting key-value pairs.

3. **Naive Bayes Classifier:**
   - Uses the "bag of words" model to classify Piazza posts based on the presence or absence of words.
   - Predicts the most likely label for a post by calculating log-probability scores based on training data.

4. **Unit Testing:**
   - Comprehensive unit tests for the BST and Map ADTs.
   - Tests edge cases such as empty trees, insertion order, and memory management.
  
5. **CSV Parsing:**
   - Reads and processes CSV files for training and testing using `csvstream.hpp`.
   - Supports various Piazza post datasets for testing the classifier.

## File Structure

- **`BinarySearchTree.hpp`**: Contains the implementation of the binary search tree with all necessary operations.
- **`BinarySearchTree_tests.cpp`**: Unit tests for the binary search tree.
- **`Map.hpp`**: Implementation of the Map data structure based on the binary search tree.
- **`Map_tests.cpp`**: Unit tests for the Map ADT.
- **`main.cpp`**: The main program that runs the classifier, reads the training and test data, and predicts the label for each post.
- **`csvstream.hpp`**: CSV parsing library used for handling training and test data files.

## Requirements

### Software
- **C++ Compiler** (supporting C++11 or later)
- **Make**: For compiling and running tests

### Libraries
- `csvstream.hpp`: For reading CSV files.
- Unit Testing Framework (provided by the course).

## How to Build and Run

1. **To build the Binary Search Tree tests:**
    ```bash
    make BinarySearchTree_tests.exe
    ./BinarySearchTree_tests.exe
    ```

2. **To build the Map tests:**
    ```bash
    make Map_tests.exe
    ./Map_tests.exe
    ```

3. **To build and run the classifier:**
    ```bash
    make main.exe
    ./main.exe <train_data.csv> <test_data.csv> [--debug]
    ```

4. **To test on small datasets:**
    ```bash
    ./main.exe train_small.csv test_small.csv --debug
    ```

## Example Usage

```bash
./main.exe train_small.csv test_small.csv --debug
