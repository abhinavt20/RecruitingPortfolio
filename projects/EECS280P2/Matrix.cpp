
// Matrix.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

// This file contains the implementation of the Matrix ADT.
// The functions here provide operations to manipulate 2D matrices of integers.

#include "Matrix.h"
#include <vector>
#include <cassert>
#include <algorithm> // for std::sort

using namespace std;

// Initialize a matrix with given width and height
void Matrix_init(Matrix* mat, int width, int height) {
    assert(width > 0 && height > 0); // Ensure valid dimensions
    mat->width = width;
    mat->height = height;
    mat->data.assign(width * height, 0); // Fill matrix with zeros
}

// Return the height of the matrix
int Matrix_height(const Matrix* mat) {
    return mat->height;
}

// Return the width of the matrix
int Matrix_width(const Matrix* mat) {
    return mat->width;
}

// Return a pointer to the element at row, col
int* Matrix_at(Matrix* mat, int row, int col) {
    assert(0 <= row && row < mat->height); // Ensure valid row
    assert(0 <= col && col < mat->width);  // Ensure valid column
    return &mat->data[row * mat->width + col]; // Return pointer to element
}

// Matrix utility functions for min/max value searches and row comparisons go here
