
// stats_tests.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

// Abhinav Tadikonda
// This file contains the unit tests for each of the statistics functions implemented in stats.cpp.
// These tests validate the correctness of the statistical calculations.

#include "stats.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void test_count_small_data_set() {
    cout << "Running test: count_small_data_set" << endl;
    vector<double> data {1, 2, 3, 4, 5};
    assert(count(data) == 5);
    cout << "PASS!" << endl;
}

void test_sum_small_data_set() {
    cout << "Running test: sum_small_data_set" << endl;
    vector<double> data {1, 2, 3, 4, 5};
    assert(sum(data) == 15);
    cout << "PASS!" << endl;
}

void test_mean_small_data_set() {
    cout << "Running test: mean_small_data_set" << endl;
    vector<double> data {1, 2, 3, 4, 5};
    assert(mean(data) == 3);
    cout << "PASS!" << endl;
}

void test_median_small_data_set() {
    cout << "Running test: median_small_data_set" << endl;
    vector<double> data {1, 2, 3, 4, 5};
    assert(median(data) == 3);
    cout << "PASS!" << endl;
}

void test_stdev_small_data_set() {
    cout << "Running test: stdev_small_data_set" << endl;
    const double epsilon = 0.00001;
    vector<double> data {1, 2, 3, 4, 5};
    double expected_stdev = 1.581138;  // Pre-computed standard deviation
    assert(abs(stdev(data) - expected_stdev) < epsilon);
    cout << "PASS!" << endl;
}

void test_percentile_small_data_set() {
    cout << "Running test: percentile_small_data_set" << endl;
    vector<double> data {1, 2, 3, 4, 5};
    assert(percentile(data, 0.5) == 3);  // Median is the 50th percentile
    cout << "PASS!" << endl;
}

int main() {
    // Run all tests
    test_count_small_data_set();
    test_sum_small_data_set();
    test_mean_small_data_set();
    test_median_small_data_set();
    test_stdev_small_data_set();
    test_percentile_small_data_set();
    return 0;
}
