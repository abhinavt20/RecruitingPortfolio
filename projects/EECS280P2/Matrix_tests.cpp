
// Matrix_tests.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

// This file contains the unit tests for Matrix ADT (Abstract Data Type).
// The tests validate the Matrix module functions such as Matrix_at, Matrix_init, and others, ensuring they behave as expected.

#include "Matrix.h"
#include <cassert>
#include <iostream>

using namespace std;

// Test for Matrix initialization
void test_matrix_init() {
    cout << "Running test_matrix_init" << endl;
    Matrix mat;
    Matrix_init(&mat, 3, 3); // Initialize a 3x3 matrix
    assert(Matrix_height(&mat) == 3); // Validate height
    assert(Matrix_width(&mat) == 3);  // Validate width
    cout << "PASS!" << endl;
}

// Test for Matrix_at to access elements
void test_matrix_at() {
    cout << "Running test_matrix_at" << endl;
    Matrix mat;
    Matrix_init(&mat, 2, 2); // Initialize a 2x2 matrix
    *Matrix_at(&mat, 0, 0) = 42; // Set top-left element to 42
    assert(*Matrix_at(&mat, 0, 0) == 42); // Verify element value
    cout << "PASS!" << endl;
}

// Run all Matrix tests
int main() {
    test_matrix_init();
    test_matrix_at();
    return 0;
}
