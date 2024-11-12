
// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79
// Header file for the Rescue the Countess project.
// Contains declarations of functions and classes that are used to implement
// the path-finding algorithms and data structures required to help Marco navigate the castle.

// B99292359FFD910ED13A7E6C7F9705B8742F0D79

#ifndef rescue_h
#define rescue_h

#include <vector>
#include <string>
#include <deque>
#include "xcode_redirect.hpp"

using namespace std;

struct mapValues {
    char gridValue = '.';
    bool discovered = false; 
    
    char cameFrom = 'y';
    char backtrackChar = '@';
};

struct location {
    unsigned int roomLoc = 0;
    unsigned int xLoc = 0;
    unsigned int yLoc = 0;

    char directionToCountess = 'x';
};


class rescueTheCountess {
    
    
private:
    
public:
    
    ~rescueTheCountess();

    
    deque<location> dequeSQ;
    vector<location> backtraceVec;
    
    int numTilesDiscovered = 0;

    vector<vector<vector<mapValues> > > mapVec;

    bool isQueue = false;
    bool isStack = false;
    bool printMap = false;
    bool printList = false;
    
    bool solution = true;



    char mapType = 'M';
    unsigned int mapNumRooms = 0;
    unsigned int mapDimentions = 0;
    
    unsigned int roomLocationS = 0;
    unsigned int xLocationS = 0;
    unsigned int yLocationS = 0;
    
    location startLoc;
    location locationToDeque;
    location currentLocation;
    location backtraceLoc;
    
    bool foundCountess = false;
    
    void getMode(int argc, char * argv[]);
    int createMap();
    void lookNorth(location currentLocation, deque<location> &dequeSQ);
    void lookEast(location currentLocation, deque<location> &dequeSQ);
    void lookSouth(location currentLocation, deque<location> &dequeSQ);
    void lookWest(location currentLocation, deque<location> &dequeSQ);
    void investigate();
    void backtrace(unsigned int countessRoom,
                   unsigned int countessRow, unsigned int countessCol);
    void print();
    rescueTheCountess();
};

#endif

