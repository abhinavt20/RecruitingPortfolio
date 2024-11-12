
// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79
// Implementation file for the Rescue the Countess project.
// This file contains the definitions of functions that implement the stack and queue-based path-finding
// algorithms to navigate the castle layout and rescue the Countess.
// Functions include logic for processing the map layout, managing warp pipes, and handling movement constraints.

// B99292359FFD910ED13A7E6C7F9705B8742F0D79

#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include "rescue.h"
#include "xcode_redirect.hpp"


using namespace std;

rescueTheCountess::rescueTheCountess(){
}

rescueTheCountess::~rescueTheCountess(){
}

void rescueTheCountess::getMode(int argc, char * argv[]) {

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    
    int choice;
    int option_index = 0;
    option long_options[] = {
        // ******check no argument vs required argument I AM UNSURE
        //**** single or double quotes
        { "stack", no_argument,         nullptr, 's'},
        { "queue", no_argument,         nullptr, 'q'},
        { "output", required_argument,         nullptr, 'o'},
        { "help", no_argument,         nullptr, 'h'},
        { nullptr, 0,                 nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "sqo:h", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            cout << "--stack, -s: If this switch is set, use the stack-based routing scheme. \n";
            cout << "--queue, -q: If this switch is set, use the queue-based routing scheme. \n";
            cout << "--output (M|L), -o (M|L): Indicates the output file format by following the flag with an M (map format) or L (coordinate list format). If the --output option is not specified, default to map output format (M), if --output is specified on the command line, the argument (either M or L) to it is required. \n";
            cout << "--help, -h: Prints this input specification. \n";
                
            exit(0);
                
        case 's':
            if (isStack || isQueue){
                cerr << "Stack or queue can only be specified once\n";
                exit(1);
            }
                
            isStack = true;
            break;
                
        case 'q':
            if (isStack || isQueue){
                cerr << "Stack or queue can only be specified once\n";
                exit(1);
            }
            
            isQueue = true;
            break;
        
        //****** if no input default to map output
        case 'o':
            if (strcmp(optarg, "L") == 0) {
                printList = true;
            }
            else {
                printMap = true;
            }
            break;
            

        // ***** check that the location of list is valid
//        case 'L':
//            printList = true;
//            break;
//

        default:
            cerr << "Unknown command line option\n";
            exit(1);
        } // switch
    } // while

    if (!isStack && !isQueue) {
        cerr << "Stack or queue must be specified\n";
        exit(1);
    } // if
    
return;
    
} // getMode()


    
int rescueTheCountess::createMap(){
    
    cin >> mapType;
    cin >> mapNumRooms;
    cin >> mapDimentions;
        
    mapVec.resize(mapNumRooms, vector<vector<mapValues> > (mapDimentions, vector<mapValues> (mapDimentions)));
        
    if (mapType == 'M'){
        unsigned int room = 0;
        unsigned int row = 0;
        unsigned int col = 0;
        
        char firstChar = '\0';
        unsigned int index = 0;
        string line;
        while (cin >> firstChar){
            if (firstChar == '/'){
                getline(cin, line);
            }
            else{
                
                if ((firstChar != '.') && (firstChar != '#') && (firstChar != '!') && (firstChar != 'C') && (firstChar != 'S') && (isdigit(firstChar) == 0)){
                    return 2;
                } //if
                
                //room = index / (mapDimentions * mapDimentions)
    
                row = index / mapDimentions;
                col = index % mapDimentions;
                
                mapVec[room][row][col].gridValue = firstChar;

                // coordinates where S starts
                if (firstChar == 'S'){
                    startLoc.roomLoc = room;
                    startLoc.xLoc = row;
                    startLoc.yLoc = col;
                            } // if

                index++;
                
                if (index == (mapDimentions * mapDimentions)) {
                    room++;
                    index = 0;
                } //if
            }
        } // while
    } //if
    
    else { //if mapType is L
        unsigned int room = 0;
        unsigned int row = 0;
        unsigned int col = 0;
        char junk = '\0';
        char junk1 = '\0';
        string junk2;
        char value = '\0';
        
        
        while(cin >> junk1){
            if (junk1 == '/'){
                getline(cin, junk2);
            } // if
            else {
                cin >> room >> junk >> row >> junk >> col >> junk >> value >> junk;
                
                if (value != '.' && value != '#' && value != '!' && value != 'C' && value != 'S' && isdigit(value) == 0){
                    cerr << "Unknown map character\n";
                    return 2;
                } //if
                if (!(room < mapNumRooms)){
                    cerr << "Invalid room number\n";
                    return 3;
                }
                if (!(row < mapDimentions)){
                    cerr << "Invalid row numberr\n";
                    return 4;
                }
                
                if (!(col < mapDimentions)){
                    cerr << "Invalid column numberr\n";
                    return 5;
                }

                mapVec[room][row][col].gridValue = value;
                if (value == 'S'){
                    startLoc.roomLoc = room;
                    startLoc.xLoc = row;
                    startLoc.yLoc = col;
                }
            } // else
        } // while
    } // else
    return 0;
}
    


void rescueTheCountess::investigate(){
    
    currentLocation = startLoc;
    
    dequeSQ.push_back(currentLocation);
    
    //set start location to discovered
    mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc].discovered = true;
    numTilesDiscovered++;
    
    while(!dequeSQ.empty() && foundCountess == false){
        if (isStack == true){
            currentLocation = dequeSQ.back();
            dequeSQ.pop_back();
            
        }//if
        else if (isQueue == true){
            currentLocation = dequeSQ.front();
            dequeSQ.pop_front();
            
        }//else if
        
//        cout << currentLocation.roomLoc << ", " << currentLocation.xLoc << ", " << currentLocation.yLoc << ", " << mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc].cameFrom << endl;

// if an invalid pipe is found do not look n, e, s, w
    if (foundCountess == false){
        char currentMapChar = mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc].gridValue;
        // if current location is a warp pipe
        if (isdigit(currentMapChar) > 0){
            // if room does exisits
            unsigned int temp = (currentMapChar - '0');
            if (temp < mapNumRooms){ // if valid room
                
                char warpChar = mapVec[temp][currentLocation.xLoc][currentLocation.yLoc].gridValue;
                bool warpDiscovered = mapVec[temp][currentLocation.xLoc][currentLocation.yLoc].discovered;
                
                //if the room location is a valid place to walk and not discovered
                if ((warpChar == '.'  || (isdigit(warpChar) > 0) || warpChar == 'C') && warpDiscovered == false) {
                    char currentRoomChar = static_cast<char>(currentLocation.roomLoc + '0');
                    mapVec[temp][currentLocation.xLoc][currentLocation.yLoc].cameFrom = currentRoomChar;

                    
                    locationToDeque.roomLoc = temp;
                    locationToDeque.xLoc = currentLocation.xLoc;
                    locationToDeque.yLoc = currentLocation.yLoc;
                    dequeSQ.push_back(locationToDeque);
                    numTilesDiscovered++;
                }
                
                if (warpChar == 'C') {
                    foundCountess = true;
                    backtrace(temp, currentLocation.xLoc, currentLocation.yLoc);
                }


                mapVec[temp][currentLocation.xLoc][currentLocation.yLoc].discovered = true;

            }
        }
        }

        char currentMapChar1 = mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc].gridValue;
        // if current location is a warp pipe
        if (isdigit(currentMapChar1)){
            continue;
        }
            
        if (foundCountess == false ){
            lookNorth(currentLocation, dequeSQ);
        }
        if (foundCountess == false){
            lookEast(currentLocation, dequeSQ);
        }
        if (foundCountess == false){
            lookSouth(currentLocation, dequeSQ);
        }
        if (foundCountess == false){
            lookWest(currentLocation, dequeSQ);
        }
        
    }//while

    if (foundCountess == false){
        solution = false;
    }

    return;
}
// do


// **** check for countess and also if the program has no solution
void rescueTheCountess::lookNorth(location currentLocation, deque<location> &dequeSQ){
    //if current location is not in row 0
    
    if (currentLocation.xLoc != 0) {
        char northChar = mapVec[currentLocation.roomLoc][currentLocation.xLoc - 1][currentLocation.yLoc].gridValue;
        bool nDiscovered = mapVec[currentLocation.roomLoc][currentLocation.xLoc - 1][currentLocation.yLoc].discovered;
        
        if ((northChar == '.' || (isdigit(northChar) > 0) || northChar == 'C') && nDiscovered == false){
            locationToDeque.roomLoc = currentLocation.roomLoc;
            locationToDeque.xLoc = currentLocation.xLoc - 1;
            locationToDeque.yLoc = currentLocation.yLoc;
            dequeSQ.push_back(locationToDeque);
            numTilesDiscovered++;
            
            mapVec[currentLocation.roomLoc][currentLocation.xLoc - 1][currentLocation.yLoc].discovered = true;
            mapVec[currentLocation.roomLoc][currentLocation.xLoc - 1][currentLocation.yLoc].cameFrom = 'n';
            
           
        } //if
        if (northChar == 'C') {
            foundCountess = true;
            backtrace(currentLocation.roomLoc, currentLocation.xLoc - 1, currentLocation.yLoc);
 
        }
    } // if
    return;
} // north

void rescueTheCountess::lookEast(location currentLocation, deque<location> &dequeSQ){
    // if current location is not in max dimestions column
    if (currentLocation.yLoc < (mapDimentions - 1)) {
        char eastChar = mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc + 1].gridValue;
        bool eDiscovered = mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc + 1].discovered;
        
        
        
        if ((eastChar == '.' || (isdigit(eastChar) > 0) || eastChar == 'C') && eDiscovered == false){
            locationToDeque.roomLoc = currentLocation.roomLoc;
            locationToDeque.xLoc = currentLocation.xLoc;
            locationToDeque.yLoc = currentLocation.yLoc + 1;
            dequeSQ.push_back(locationToDeque);
            numTilesDiscovered++;

            
            mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc + 1].discovered = true;
            mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc + 1].cameFrom = 'e';
        } //if
        
        
        if (eastChar == 'C') {
            foundCountess = true;
            backtrace(currentLocation.roomLoc, currentLocation.xLoc, currentLocation.yLoc + 1);
        }
    } // if
    return;
} //east


void rescueTheCountess::lookSouth(location currentLocation, deque<location> &dequeSQ){
    // if current location is not in max dimestions row
    if (currentLocation.xLoc < (mapDimentions - 1)) {
        char southChar = mapVec[currentLocation.roomLoc][currentLocation.xLoc + 1][currentLocation.yLoc].gridValue;
        bool sDiscovered = mapVec[currentLocation.roomLoc][currentLocation.xLoc + 1][currentLocation.yLoc].discovered;
        
        if ((southChar == '.' || (isdigit(southChar) > 0) || southChar == 'C') && sDiscovered == false){
            locationToDeque.roomLoc = currentLocation.roomLoc;
            locationToDeque.xLoc = currentLocation.xLoc + 1;
            locationToDeque.yLoc = currentLocation.yLoc;
            dequeSQ.push_back(locationToDeque);
            numTilesDiscovered++;

            
            mapVec[currentLocation.roomLoc][currentLocation.xLoc + 1][currentLocation.yLoc].discovered = true;
            mapVec[currentLocation.roomLoc][currentLocation.xLoc + 1][currentLocation.yLoc].cameFrom = 's';


        } //if
        

        if (southChar == 'C') {
            foundCountess = true;
            backtrace(currentLocation.roomLoc, currentLocation.xLoc + 1, currentLocation.yLoc);
        }
    } // if
    return;
}


void rescueTheCountess::lookWest(location currentLocation, deque<location> &dequeSQ){
    //if current location is not in colum 0
    if (currentLocation.yLoc != 0) {
        char westChar = mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc - 1].gridValue;
        bool wDiscovered = mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc - 1].discovered;
        
        if ((westChar == '.' || (isdigit(westChar) > 0) || westChar == 'C') && wDiscovered == false){
            locationToDeque.roomLoc = currentLocation.roomLoc;
            locationToDeque.xLoc = currentLocation.xLoc;
            locationToDeque.yLoc = currentLocation.yLoc - 1;
            dequeSQ.push_back(locationToDeque);
            numTilesDiscovered++;

            
            mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc - 1].discovered = true;
            mapVec[currentLocation.roomLoc][currentLocation.xLoc][currentLocation.yLoc - 1].cameFrom = 'w';
            
        } //if
        if (westChar == 'C') {
            foundCountess = true;
            backtrace(currentLocation.roomLoc, currentLocation.xLoc, currentLocation.yLoc - 1);

        }
    } // if
    return;
}



void rescueTheCountess::backtrace(unsigned int countessRoom, unsigned int countessRow, unsigned int countessCol){
    //start at countess and look where the previous location was (if it was north then go south )
    backtraceLoc.roomLoc = countessRoom;
    backtraceLoc.xLoc = countessRow;
    backtraceLoc.yLoc = countessCol;

    while(mapVec[backtraceLoc.roomLoc][backtraceLoc.xLoc][backtraceLoc.yLoc].gridValue != 'S'){
        
        char cameFromChar = mapVec[backtraceLoc.roomLoc][backtraceLoc.xLoc][backtraceLoc.yLoc].cameFrom;
        if (cameFromChar == 'n'){
            backtraceLoc.xLoc = backtraceLoc.xLoc + 1;
            backtraceLoc.directionToCountess = 'n';
            mapVec[backtraceLoc.roomLoc][backtraceLoc.xLoc][backtraceLoc.yLoc].backtrackChar = 'n';
            backtraceVec.push_back(backtraceLoc);

        }

        if (cameFromChar == 'e'){
            backtraceLoc.yLoc = backtraceLoc.yLoc - 1;
            backtraceLoc.directionToCountess = 'e';
            mapVec[backtraceLoc.roomLoc][backtraceLoc.xLoc][backtraceLoc.yLoc].backtrackChar = 'e';
            backtraceVec.push_back(backtraceLoc);
            
        }

        if (cameFromChar == 's'){
            backtraceLoc.xLoc = backtraceLoc.xLoc - 1;
            backtraceLoc.directionToCountess = 's';
            mapVec[backtraceLoc.roomLoc][backtraceLoc.xLoc][backtraceLoc.yLoc].backtrackChar = 's';
            backtraceVec.push_back(backtraceLoc);
            
        }

        if (cameFromChar == 'w'){
            backtraceLoc.yLoc = backtraceLoc.yLoc + 1;
            backtraceLoc.directionToCountess = 'w';
            mapVec[backtraceLoc.roomLoc][backtraceLoc.xLoc][backtraceLoc.yLoc].backtrackChar = 'w';

            backtraceVec.push_back(backtraceLoc);
            
        }

        if (isdigit(cameFromChar)){
            backtraceLoc.roomLoc = (cameFromChar - '0');
            backtraceLoc.directionToCountess = 'p';
            mapVec[backtraceLoc.roomLoc][backtraceLoc.xLoc][backtraceLoc.yLoc].backtrackChar = 'p';
            backtraceVec.push_back(backtraceLoc);
        }
    }
    
    return;
}

void rescueTheCountess::print(){
    if (solution == false) {
            cout << "No solution, " << numTilesDiscovered << " tiles discovered.\n";
        }

    else if (printList == true){
        cout << "Path taken: \n";
        size_t vecSize = backtraceVec.size();
        unsigned int vecSize1 = static_cast<unsigned>(vecSize);
        for (unsigned int i = vecSize1 - 1; i >= 1; i--){
            cout << "(" << backtraceVec[i].roomLoc << "," << backtraceVec[i].xLoc <<
                "," << backtraceVec[i].yLoc << "," << backtraceVec[i].directionToCountess << ")\n";
        }
        
        cout << "(" << backtraceVec[0].roomLoc << "," << backtraceVec[0].xLoc <<
                    "," << backtraceVec[0].yLoc << "," << backtraceVec[0].directionToCountess << ")\n";

    }

    else {
        cout << "Start in room " << startLoc.roomLoc << ", row " << startLoc.xLoc << ", column " << startLoc.yLoc << "\n";
        
        for (size_t i = 0; i < mapNumRooms; i++){
            cout << "//castle room " << i << "\n";
            for (size_t j = 0; j < mapDimentions; j++){
                for (size_t k = 0; k < mapDimentions; k++){
                    char charToPrint = mapVec[i][j][k].backtrackChar;

                    if (charToPrint == 'n' || charToPrint == 'e' || charToPrint == 's' || charToPrint == 'w' || charToPrint == 'p'){
                        cout << mapVec[i][j][k].backtrackChar;
                    }
                    else {
                        cout << mapVec[i][j][k].gridValue;
                    }
                }
                cout << "\n";
            }
        }
    }
    
return;
}


