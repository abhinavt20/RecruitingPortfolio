
// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79
// Main execution file for the Rescue the Countess project.
// This file initializes the program, handles command-line arguments, and coordinates the execution
// of routing schemes based on user input. It also manages input/output modes and error handling.

// #B99292359FFD910ED13A7E6C7F9705B8742F0D79

#include <stdio.h>

#include "rescue.h"


int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);


    rescueTheCountess rescueMain;

    rescueMain.getMode(argc, argv);
    int temp = rescueMain.createMap();
    if (temp == 2){
        cerr << "Unknown map character\n";
        return 1;
    }
    if (temp == 3){
        cerr << "Invalid room number\n";
        return 1;
    }
    if (temp == 4){
        cerr << "Invalid row number\n";
        return 1;
    }
    if (temp == 5){
        cerr << "Invalid column number\n";
        return 1;
    }
    rescueMain.investigate();
    rescueMain.print();

    return 0;
}


