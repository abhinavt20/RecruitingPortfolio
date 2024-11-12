// 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7
//  amongUs.cpp
//  p4
//
//  Created by Abhinav Tadikonda on 11/29/22.
//

#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <utility>
#include <map>
#include <unordered_map>
#include "xcode_redirect.hpp"
#include <limits>
#include <iomanip>
#include <cmath>


using namespace std;

struct Coordinate {
    int x = 0;
    int y = 0;
    char location;
};

struct Prim {
    double minEdgeWeight = numeric_limits<double>::infinity();
    size_t precedingVertex = 0;
    bool known = false;
};

class amongUs {
public:
    
    bool MSTStatus = false;
    bool FASTTSPStatus = false;
    bool OPTTSPStatus = false;
    
    void getMode(int argc, char * argv[]);
    void readIn();

    void MST();
    double MSTForC(size_t permLength);

    void FASTTSP();
    double FASTTSPForC();

    void OPTTSP();
    double distance(Coordinate &one, Coordinate &two);

    
    vector<Coordinate> coordinateVector;
    vector<Prim> primVector;
    vector<vector<double>> TwoDVecdistance;
    
    vector<size_t> indecies;

    size_t numVerticies = 0;
    
    void genPerms(size_t permLength);
    bool promising(size_t permLength);


    double currentRunningTotal = 0;
    
    double bestDistance = 0;
    vector<size_t> bestPath;
    
    double MSTForC2(vector<size_t> primVectorC);

    


private:

};


//____________________________________________________________________________________

void amongUs::getMode(int argc, char * argv[]) {
    opterr = false; // Let us handle all error output for command line options
    
    int choice;
    int option_index = 0;
    option long_options[] = {
        // ******check no argument vs required argument I AM UNSURE
        //**** single or double quotes
        { "mode", required_argument,         nullptr, 'm'},
        { "help", no_argument,         nullptr, 'h'},
        { nullptr, 0,                 nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            cout << "-m, –mode {MST|FASTTSP|OPTTSP}: \n" << "MST: Find the minimum spanning tree (MST) of the map \n" << "FASTTSP: Find a fast, but not necessarily optimal, solution to the TSP \n" << "OPTTSP: Find the optimal solution to the TSP \n";
            
            exit(0);

        case 'm':
            switch(optarg[0]){
                case 'M':
                    MSTStatus = true;
                    break;
                    
                case 'F':
                    FASTTSPStatus = true;
                    break;
                    
                case 'O':
                    OPTTSPStatus = true;
                    break;
                default:
                    cerr << "Invalid mode\n";
                    exit(1);
            }
            break;

        default:
            cerr << "Invalid command line option\n";
            exit(1);
        } // switch
        
        if (MSTStatus == false && FASTTSPStatus == false && OPTTSPStatus == false){
            cerr << "No mode specified\n";
            exit(1);
        }
        
    } // while
    
return;
    
} // getMode()

void amongUs::readIn() {
    int xCoor = 0;
    int yCoor = 0;
    
    cin >> numVerticies;
    
    coordinateVector.resize(numVerticies);
    for (size_t i = 0; i < numVerticies; i++){
        cin >> xCoor >> yCoor;
        coordinateVector[i].x = xCoor;
        coordinateVector[i].y = yCoor;
        
        if (xCoor < 0 && yCoor < 0){
            coordinateVector[i].location = 'L';
        }
        else if ((xCoor == 0 && yCoor <= 0) || (xCoor <= 0 && yCoor == 0)){
            coordinateVector[i].location = 'D';
        }
        else {
            coordinateVector[i].location = 'O';
        }
        
    }
}


void amongUs::MST() {
    if (MSTStatus == true){
        double distanceBetweenVertices = 0;
        primVector.resize(numVerticies);
        primVector[0].minEdgeWeight = 0;
//        double minEdgeWeight = 0;
        double totalMSTDistance = 0;
        size_t minEdgeWeightIndex = 0;
        bool areThereLabs = false;
        bool areThereOuter = false;
        bool areThereDecontamination = false;

        
        for (size_t i = 0; i < numVerticies; i++){
            double minEdgeWeight1 = numeric_limits<double>::infinity();
            
            if (coordinateVector[i].location == 'L'){
                areThereLabs = true;
            }
            if (coordinateVector[i].location == 'O'){
                areThereOuter = true;
            }
            if (coordinateVector[i].location == 'D'){
                areThereDecontamination = true;
            }
            
            for (size_t j = 0; j < numVerticies; j++){
                if ((primVector[j].known == false) && (primVector[j].minEdgeWeight < minEdgeWeight1)){
                    minEdgeWeight1 = primVector[j].minEdgeWeight;
                    minEdgeWeightIndex = j;
                }
            }
            
            primVector[minEdgeWeightIndex].known = true;
            totalMSTDistance += minEdgeWeight1;
                        
            for (size_t k = 0; k < numVerticies; k++){
                if (primVector[k].known == false){
                    //find distance to all other verticies
                    distanceBetweenVertices = sqrt(distance(coordinateVector[minEdgeWeightIndex], coordinateVector[k]));
                    if (distanceBetweenVertices < primVector[k].minEdgeWeight){
                        primVector[k].minEdgeWeight = distanceBetweenVertices;
                        primVector[k].precedingVertex = minEdgeWeightIndex;
                    }
                }
            }
        } // for
        
        if (areThereLabs == true && areThereOuter == true && areThereDecontamination == false){
            cerr << "Cannot construct MST \n";
            exit(1);
        }
        
        cout << totalMSTDistance << "\n";
        for (size_t m = 1; m < numVerticies; m++){
            cout << min(m, primVector[m].precedingVertex) << " " << max(m, primVector[m].precedingVertex) << "\n";
        }
    }
}


double amongUs::MSTForC(size_t permLength) {
    vector<Prim> primVectorC;
    double distanceBetweenVerticesC = 0;
    double totalMSTDistanceC = 0;
    size_t minEdgeWeightIndexC = 0;
    primVectorC.resize(numVerticies);
    primVectorC[permLength].minEdgeWeight = 0;

    for (size_t i = permLength; i < numVerticies; i++){
        double minEdgeWeightC = numeric_limits<double>::infinity();
        
        for (size_t j = permLength; j < numVerticies; j++){
            if (primVectorC[j].known == false && primVectorC[j].minEdgeWeight < minEdgeWeightC){
                minEdgeWeightC = primVectorC[j].minEdgeWeight;
                minEdgeWeightIndexC = j;
            }
        }

        primVectorC[minEdgeWeightIndexC].known = true;
        totalMSTDistanceC += minEdgeWeightC;

        for (size_t k = permLength; k < numVerticies; k++){
            if (primVectorC[k].known == false){
                //find distance to all other verticies
                distanceBetweenVerticesC = TwoDVecdistance[indecies[minEdgeWeightIndexC]][indecies[k]];
                if (distanceBetweenVerticesC < primVectorC[k].minEdgeWeight){
                    primVectorC[k].minEdgeWeight = distanceBetweenVerticesC;
                    primVectorC[k].precedingVertex = minEdgeWeightIndexC;
                }
            }
        }
    } // for
    
    return totalMSTDistanceC;
}
    
double amongUs::distance(Coordinate &one, Coordinate &two) {
    if (MSTStatus == true){
        if ((one.location == 'O' && two.location == 'L') || (one.location == 'L' && two.location == 'O')){
            return numeric_limits<double>::infinity();
        }
    }
    
    double xDiff = static_cast<double>(one.x - two.x);
    double yDiff = static_cast<double>(one.y - two.y);
    double xyDistance = (xDiff * xDiff) + (yDiff * yDiff);
    return xyDistance;
}


void amongUs::FASTTSP() {
    if (FASTTSPStatus == true){
        int numEdges = 2;
        double formulaTotal = 0;
        double distanceIK = 0;
        double distanceKJ = 0;
        double distanceIJ = 0;
        int minEdgeWeightIndex = -1;

        //min of two vertices for FASTTSP
        indecies.push_back(0);
        indecies.push_back(1);
        indecies.push_back(0);
        double totalDist = 0;

        totalDist = 2 * sqrt(distance(coordinateVector[0], coordinateVector[1]));

        size_t currentVerticy = 2;
        while (currentVerticy < numVerticies){
            double minEdgeWeight = numeric_limits<double>::infinity();

            for (int i = 0; i < numEdges; i++){
                distanceIK = distance(coordinateVector[indecies[i]], coordinateVector[currentVerticy]);
                distanceKJ = distance(coordinateVector[currentVerticy], coordinateVector[indecies[i + 1]]);
                distanceIJ = distance(coordinateVector[indecies[i]], coordinateVector[indecies[i + 1]]);

                formulaTotal = sqrt(distanceIK) + sqrt(distanceKJ) - sqrt(distanceIJ);

                if (formulaTotal < minEdgeWeight){
                    minEdgeWeight = formulaTotal;
                    minEdgeWeightIndex = i;
                }
            }

            indecies.insert(indecies.begin() + minEdgeWeightIndex + 1, currentVerticy);

            currentVerticy++;
            numEdges++;
            totalDist += minEdgeWeight;
        }

        cout << totalDist << "\n";
        for (size_t i = 0; i < numVerticies; i++){
            cout << indecies[i] << " ";
        }
    }
}

double amongUs::FASTTSPForC() {
    int numEdges = 2;
    double formulaTotal = 0;
    double distanceIK = 0;
    double distanceKJ = 0;
    double distanceIJ = 0;
    int minEdgeWeightIndex = -1;

    //min of two vertices for FASTTSP
    indecies.push_back(0);
    indecies.push_back(1);
    indecies.push_back(0);
    double totalDist = 0;

    totalDist = 2 * sqrt(distance(coordinateVector[0], coordinateVector[1]));

    size_t currentVerticy = 2;
    while (currentVerticy < numVerticies){
        double minEdgeWeight = numeric_limits<double>::infinity();

        for (int i = 0; i < numEdges; i++){
            distanceIK = distance(coordinateVector[indecies[i]], coordinateVector[currentVerticy]);
            distanceKJ = distance(coordinateVector[currentVerticy], coordinateVector[indecies[i + 1]]);
            distanceIJ = distance(coordinateVector[indecies[i]], coordinateVector[indecies[i + 1]]);

            formulaTotal = sqrt(distanceIK) + sqrt(distanceKJ) - sqrt(distanceIJ);

            if (formulaTotal < minEdgeWeight){
                minEdgeWeight = formulaTotal;
                minEdgeWeightIndex = i;
            }
        }

        indecies.insert(indecies.begin() + minEdgeWeightIndex + 1, currentVerticy);

        currentVerticy++;
        numEdges++;
        totalDist += minEdgeWeight;
    }
    return totalDist;
}


void amongUs::OPTTSP() {
    if (OPTTSPStatus == true){
//        cout << "hello from opt" << endl;

        TwoDVecdistance.resize(numVerticies, vector<double>(numVerticies));
        //Start by constructing a distance matrix so that distance lookups are efficient.
        for (size_t i = 0; i < numVerticies; i++){
            for (size_t j = 0; j < numVerticies; j++){
                double distBetween = distance(coordinateVector[i], coordinateVector[j]);
                TwoDVecdistance[i][j] = sqrt(distBetween);
            }
        }
        
        //        Run part B to get an upper bound of the distance, and store it in some sort of bestDistance variable, and store the path in a bestPath variable.
        bestDistance = FASTTSPForC();
        bestPath = indecies;
        
        // Call genPerms(1).
        genPerms(1);
        
//        Print bestDistance and bestPath.

        cout << bestDistance << "\n";
//        for (auto i : bestPath){
//            cout << i << " ";
//        }
        for (size_t i = 0; i < numVerticies; i++){
            cout << bestPath[i] << " ";
        }
    }
}

void amongUs::genPerms(size_t permLength) {
//    cout << "hello from gen" << endl;

//  If permLength == path.size(), if it's less than bestDistance (taking into account the final edge), update bestDistance and bestPath.
    if (permLength == numVerticies) {
    // Do something with the path
        double tempDist = currentRunningTotal + TwoDVecdistance[indecies[0]][indecies[permLength -1]];
        if (tempDist < bestDistance) {
            bestDistance = tempDist;
            // double check this step
            bestPath = indecies;
        }
      return;
    }  // if ..complete path
//    cout << "Im here 2" << endl;

//    Call promising().
    if (!promising(permLength)) {
      return;
    }  // if ..not promising
//    cout << "Im here 1" << endl;

//    Iterate over the remaining rooms not part of the subtour, adding to the running total.
    for (size_t i = permLength; i < numVerticies; ++i) {
//        Iterate over the remaining rooms not part of the subtour, adding to the running total.
        swap(indecies[permLength], indecies[i]);
        currentRunningTotal += TwoDVecdistance[indecies[permLength]][indecies[permLength-1]];
//        Recursively call genPerms(permLength + 1).
//        cout << "Im here" << endl;
        genPerms(permLength + 1);
//        Swap the rooms in the path vector back, subtracting from the running total.
        currentRunningTotal -= TwoDVecdistance[indecies[permLength]][indecies[permLength-1]];
        swap(indecies[permLength], indecies[i]);
    }  // for ..unpermuted elements
}  // genPerms()

bool amongUs::promising(size_t permLength) {
//    cout << "hello from promise" << endl;
    size_t unvisitedNum = numVerticies - permLength;
    if (unvisitedNum < 5){
        return true;
    }
    
//    if (primVectorC.empty() == false){
//        primVectorC.clear();
//    }
////    primVectorC.resize(numVerticies);
////    primVectorC[0].minEdgeWeight = 0;
//////
//    primVectorC.resize(numVerticies);
//    primVectorC[permLength].minEdgeWeight = 0;
//
//    for (size_t i = 0; i < permLength; i++){
//        primVectorC[i].known = true;
//    }
    
//    vector<size_t> tempVec(indecies.begin() + permLength, indecies.end());
    
    // call part A
    double totalForMSTC = MSTForC(permLength);
//    cout << "hello";

    double startToMST = numeric_limits<double>::infinity();
    double endToMST = numeric_limits<double>::infinity();
    
//    startToMST = TwoDVecdistance[indecies[0]][indecies[permLength]];
//    endToMST = TwoDVecdistance[indecies[permLength - 1]][indecies[permLength]];
    
    // look through entire matrix to find closest vertex
    // ignore values already added to TSP
    size_t endIndex = permLength - 1;
    for (size_t i = 0; i < numVerticies; i++){
        if (i < permLength){
            continue;
        }
        if (TwoDVecdistance[indecies[0]][indecies[i]] < startToMST){
            startToMST = TwoDVecdistance[indecies[0]][indecies[i]];
        }
        if (TwoDVecdistance[indecies[endIndex]][indecies[i]] < endToMST){
            endToMST = TwoDVecdistance[indecies[endIndex]][indecies[i]];
        }
    }
    
    double overallTotalApprox = totalForMSTC + currentRunningTotal + startToMST + endToMST;

    if (bestDistance > overallTotalApprox){
        return true;
    }
    return false;
}



//___________________________________________________________________________________

int main(int argc, char *argv[]){
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    cout << std::setprecision(2); //Always show 2 decimal places
    cout << std::fixed; //Disable scientific notation for large numbers

    amongUs amongUsObj;

    amongUsObj.getMode(argc, argv);
    amongUsObj.readIn();
    amongUsObj.MST();
    amongUsObj.FASTTSP();
    amongUsObj.OPTTSP();
    
    return 0;
    
}


