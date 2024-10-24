# README

Link to project: https://eecs280staff.github.io/p2-cv/

## Overview
This project is focused on building a content-aware image resizing program using a seam-carving algorithm. Seam carving allows for resizing images by intelligently removing or adding "seams" – paths of low importance pixels – while preserving important content. This project is an exercise in image processing, matrix manipulation, and abstract data types in C++. 

The primary goal is to write and test several modules:
- **Matrix**: A matrix abstract data type (ADT) used for storing and manipulating 2D arrays of integers.
- **Image**: An image ADT where images are stored as three matrices representing red, green, and blue color channels.
- **Processing**: Functions that implement seam carving and other image processing techniques like rotating images.
- **Resize**: A command-line tool to resize images by removing seams.

The seam carving algorithm is a dynamic programming approach that finds and removes the seams that pass through the least important pixels of an image based on pixel "energy."

## How to Build and Run

### Prerequisites:

- **C++ Compiler**: Ensure you have a C++ compiler installed.
- **Makefile**: The project is structured with a Makefile to automate the build process.

### Running the Code:

1. **Build the project**: Navigate to the directory with the project files and run the following command in the terminal:
   ```bash
   make resize.exe
   ```

2. **Resize an image**: Once compiled, run the program with the following command:
   ```bash
   ./resize.exe <input_filename> <output_filename> <new_width> <new_height>
   ```
   Example:
   ```bash
   ./resize.exe horses.ppm horses_400x250.ppm 400 250
   ```

3. **View results**: The output image will be saved to the file specified by `<output_filename>`.

### Architecture and Technology Overview
This project is organized into several modules, each responsible for a different part of the image processing and resizing algorithm.

### Key Components:
- **Matrix.cpp**: Implements a matrix abstract data type (ADT) for handling 2D arrays of integers. Functions include matrix initialization, element access, and utility functions.
- **Image.cpp**: Implements an image ADT, where images are stored as three matrices representing the red, green, and blue color channels.
- **processing.cpp**: Contains functions for image manipulation, including seam carving, energy matrix computation, and image rotation.
- **resize.cpp**: A command-line interface that ties everything together, handling user input and resizing images using the seam carving algorithm.

### Technologies:
- **C++**: The primary programming language for this project.
- **Makefile**: Used to automate the building process.
- **Seam Carving Algorithm**: The core of the resizing functionality, which intelligently removes low-importance seams from an image.

### Assumptions 
- **Input Format**: Images are expected to be in PPM format. Ensure that the input image is a valid PPM file with the correct format.
- **Error Handling**: The program checks for valid command-line arguments and ensures that the input and output files can be opened.

### Next Steps
- **Optimize for Performance**: Add optimizations to the seam carving algorithm for large images to reduce processing time.
- **Support for JPEG Images**: Implement support for reading and writing JPEG images in addition to PPM.


