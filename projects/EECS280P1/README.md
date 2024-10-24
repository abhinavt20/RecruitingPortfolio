# README

Link to project: https://eecs280staff.github.io/p1-stats/

## Overview
This project implements a program to compute descriptive statistics and perform two-sample analysis on a given dataset. The program reads an input file (CSV or TSV), extracts specific columns based on user input, and computes various statistics such as mean, median, standard deviation, and percentiles. Additionally, it can compare two groups in the dataset and provide a 95% confidence interval for the difference in means using bootstrap resampling.

## How to Build and Run

### Prerequisites:

- **C++ Compiler**
- **Makefile** (included in the project)

### Running the Code:

1. Ensure all project files, including `two_sample.cpp`, `stats.cpp`, and `Makefile`, are in the same directory.
2. Compile the code by running the following command in the terminal:
   ```bash
   make two_sample.exe
   ```

3. Run the two-sample analysis program with the following command:
   ```bash
   ./two_sample.exe <filename> <filter_column> <group_A_value> <group_B_value> <data_column>
   ```
   Example:
   ```bash
   ./two_sample.exe HCMST_ver_3.04.tsv q24_met_online 1 0 ppage
   ```

4. The program will output descriptive statistics for both groups and the 95% confidence interval for the difference in means.

### Architecture and Technology Overview
This project is designed to perform flexible statistical analysis on datasets, allowing you to analyze data and compare two different groups. Bootstrap resampling is used to calculate confidence intervals, making it robust for comparing two populations.

### Key Components:
- `two_sample.cpp`: Contains the main logic for handling the two-sample statistical analysis, including reading the file, performing computations, and displaying results.
- `stats.cpp`: Implements core statistical functions like `mean()`, `median()`, `stdev()`, and `percentile()`.
- `Makefile`: Used to build and test the project efficiently.

### Technologies:
- **C++**: The core programming language for the project.
- **Bootstrap Resampling**: Used for statistical analysis to generate confidence intervals in a computational manner.

### Assumptions 
- **Input Format**: The input file is assumed to be in CSV or TSV format with headers to identify the columns.
- **Data Handling**: The program assumes that data is clean, and any irregularities like missing values must be handled before passing to the program.
- **Confidence Interval**: The 95% confidence interval is computed using bootstrap resampling, ensuring robust estimates even for non-parametric data.

### Next Steps
- **Support Larger Datasets**: Implement optimizations to handle larger datasets more efficiently.
- **Improve Error Handling**: Add more sophisticated handling of edge cases such as missing data or incorrect formatting in the input file.
