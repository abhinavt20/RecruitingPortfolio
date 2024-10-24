
// processing.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

// This file contains the implementation of the seam carving algorithm
// and image processing functions for resizing images.

#include "processing.h"
#include <cassert>

using namespace std;

// Rotate the image 90 degrees to the left
void rotate_left(Image* img) {
    int width = Image_width(img);
    int height = Image_height(img);

    Image aux;
    Image_init(&aux, height, width); // Switch width and height

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
        }
    }

    *img = aux;
}

// Additional seam carving and energy matrix functions would be implemented here
