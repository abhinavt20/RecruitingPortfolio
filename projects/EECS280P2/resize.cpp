
// resize.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

// This file contains the driver program for resizing images using seam carving.
// The program reads an input image, resizes it based on command-line arguments, and writes the resized image to an output file.

#include "Image.h"
#include "processing.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH HEIGHT
";
        return 1;
    }

    // Get command line arguments
    const char* fileIn = argv[1];
    const char* fileOut = argv[2];
    int width = stoi(argv[3]);
    int height = stoi(argv[4]);

    // Open input file and check for errors
    ifstream fIN;
    fIN.open(fileIn);
    if (!fIN.is_open()) {
        cout << "Error opening file: " << fileIn << endl;
        return 1;
    }

    // Initialize the image from input file
    Image img;
    Image_init(&img, width, height);
    Image_read_from_PPM(&img, fIN);

    // Resize the image using seam carving algorithm
    seam_carve(&img, width, height);

    // Write the resized image to the output file
    ofstream fOUT;
    fOUT.open(fileOut);
    if (!fOUT.is_open()) {
        cout << "Error opening file: " << fileOut << endl;
        return 1;
    }
    Image_print(&img, fOUT);
    fIN.close();
    fOUT.close();
    return 0;
}
