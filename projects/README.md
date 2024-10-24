# Projects Overview

This folder contains a collection of key projects I have worked on throughout my academic and professional journey. Each project showcases my skills in data science, machine learning, and natural language processing. Below is a brief description of some notable projects included in this folder:

## 1) Crisp-Data-Wrangling

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


