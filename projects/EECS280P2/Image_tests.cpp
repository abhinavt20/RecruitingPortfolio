
// Image_tests.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

// This file contains the unit tests for the Image ADT.
// The tests validate that the Image functions (such as Image_init, Image_get_pixel, and Image_set_pixel) work correctly.

#include "Image.h"
#include <cassert>
#include <iostream>

using namespace std;

// Test for Image initialization
void test_image_init() {
    cout << "Running test_image_init" << endl;
    Image img;
    Image_init(&img, 4, 4); // Initialize a 4x4 image
    assert(Image_width(&img) == 4); // Validate width
    assert(Image_height(&img) == 4); // Validate height
    cout << "PASS!" << endl;
}

// Test for setting and getting pixel values
void test_image_set_pixel() {
    cout << "Running test_image_set_pixel" << endl;
    Image img;
    Image_init(&img, 3, 3); // Initialize a 3x3 image
    Pixel p = {255, 0, 0};  // Red pixel
    Image_set_pixel(&img, 1, 1, p); // Set middle pixel to red
    Pixel result = Image_get_pixel(&img, 1, 1);
    assert(result.r == 255 && result.g == 0 && result.b == 0); // Check pixel value
    cout << "PASS!" << endl;
}

// Run all Image tests
int main() {
    test_image_init();
    test_image_set_pixel();
    return 0;
}
