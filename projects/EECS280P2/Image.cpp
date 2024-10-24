
// Image.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

// This file contains the implementation of the Image ADT.
// Each Image is made up of three Matrix objects, representing the red, green, and blue color channels.

#include "Image.h"
#include <cassert>

using namespace std;

// Initialize an Image with given width and height
void Image_init(Image* img, int width, int height) {
    assert(width > 0 && height > 0); // Ensure valid dimensions
    Matrix_init(&img->red_channel, width, height);
    Matrix_init(&img->green_channel, width, height);
    Matrix_init(&img->blue_channel, width, height);
    img->width = width;
    img->height = height;
}

// Get the width of the image
int Image_width(const Image* img) {
    return img->width;
}

// Get the height of the image
int Image_height(const Image* img) {
    return img->height;
}

// Set the pixel color in an image at row, col
void Image_set_pixel(Image* img, int row, int col, Pixel p) {
    *Matrix_at(&img->red_channel, row, col) = p.r;
    *Matrix_at(&img->green_channel, row, col) = p.g;
    *Matrix_at(&img->blue_channel, row, col) = p.b;
}

// Image utility functions for reading and writing from PPM files go here
