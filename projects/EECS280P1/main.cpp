
// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

// Abhinav Tadikonda
// This file is the main entry point for the statistics project.
// It reads a column from a dataset file, calculates descriptive statistics, and displays the results.

#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    // Step 1: Read the filename and column name from user input
    string fileName;
    cout << "Enter a filename:" << endl;
    cin >> fileName;

    string colName;
    cout << "Enter a column name:" << endl;
    cin >> colName;

    // Step 2: Extract column data from the file
    cout << "Reading column " << colName << " from " << fileName << endl;
    vector<double> columnData = extract_column(fileName, colName);

    // Step 3: Summarize the column data and display the summary
    cout << "Summary (value: frequency)" << endl;
    vector<vector<double>> summaryVec = summarize(columnData);
    for (size_t i = 0; i < summaryVec.size() / 2; i++) {
        cout << summaryVec[i][0] << ": " << summaryVec[i][1] << endl;
    }

    cout << endl;

    // Step 4: Display descriptive statistics
    cout << "count = " << count(columnData) << endl;
    cout << "sum = " << sum(columnData) << endl;
    cout << "mean = " << mean(columnData) << endl;
    cout << "stdev = " << stdev(columnData) << endl;
    cout << "median = " << median(columnData) << endl;
    cout << "mode = " << mode(columnData) << endl;
    cout << "min = " << min(columnData) << endl;
    cout << "max = " << max(columnData) << endl;
    cout << "  0th percentile = " << percentile(columnData, 0.0) << endl;
    cout << " 25th percentile = " << percentile(columnData, 0.25) << endl;
    cout << " 50th percentile = " << percentile(columnData, 0.50) << endl;
    cout << " 75th percentile = " << percentile(columnData, 0.75) << endl;
    cout << "100th percentile = " << percentile(columnData, 1.0) << endl;

    return 0;
}
