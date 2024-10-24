
// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

// Abhinav Tadikonda
// This file contains the implementations of the statistics functions declared in stats.h.
// These functions are used to compute basic descriptive statistics and perform filtering on datasets.

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

// Summarizes the input data by calculating the frequency of each value
vector<vector<double>> summarize(vector<double> v) {
    // Implement a frequency summary calculation
    vector<vector<double>> summary;
    // Logic for summarizing the data goes here...
    return summary;
}

// Count the number of values in the dataset
int count(vector<double> v) {
    return v.size(); // Return the number of elements
}

// Compute the sum of the dataset
double sum(vector<double> v) {
    double total = 0;
    for (double num : v) {
        total += num;
    }
    return total;
}

// Compute the mean (average) of the dataset
double mean(vector<double> v) {
    return sum(v) / count(v); // Use sum() and count() helper functions
}

// Compute the median of the dataset
double median(vector<double> v) {
    sort(v.begin(), v.end()); // Sort the vector first
    int n = count(v);
    if (n % 2 == 0) {
        // If even number of elements, return average of the middle two
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
    } else {
        // If odd number of elements, return the middle element
        return v[n / 2];
    }
}

// Compute the standard deviation of the dataset
double stdev(vector<double> v) {
    double avg = mean(v);
    double variance = 0;
    for (double num : v) {
        variance += pow(num - avg, 2);
    }
    return sqrt(variance / (count(v) - 1)); // Using the corrected sample standard deviation formula
}

// Compute the minimum value of the dataset
double min(vector<double> v) {
    return *min_element(v.begin(), v.end()); // Use standard library function
}

// Compute the maximum value of the dataset
double max(vector<double> v) {
    return *max_element(v.begin(), v.end()); // Use standard library function
}

// Compute the percentile for a given dataset and percentile rank
double percentile(vector<double> v, double p) {
    sort(v.begin(), v.end()); // Sort the data
    int rank = p * (v.size() - 1);
    double fractional_part, integral_part;
    fractional_part = modf(rank, &integral_part);
    int lower_index = (int)integral_part;
    int upper_index = lower_index + 1;
    if (upper_index >= v.size()) {
        return v[lower_index]; // Handle boundary case
    }
    return (1 - fractional_part) * v[lower_index] + fractional_part * v[upper_index]; // Linear interpolation
}
