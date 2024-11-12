
// Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// This file implements the gameplay for Project 2a - The Walking Deadline.
// It includes the main logic for handling rounds, managing the player's quiver and attacks, 
// and processing zombie movement and statistics.
// Detailed comments are added for each function to enhance readability and explain the game logic.

// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include "P2random.h"
#include "xcode_redirect.hpp"


using namespace std;


struct Zombie {
    string name = "";
    unsigned int distance = 0;
    unsigned int speed = 0;
    unsigned int health = 0;
    unsigned int roundsActive = 1;
};


struct zombieCompare {
    
    bool operator() (const Zombie *zombieOne, const Zombie *zombieTwo){
        unsigned int etaOne = zombieOne->distance/zombieOne->speed;
        unsigned int etaTwo = zombieTwo->distance/zombieTwo->speed;
        
        if (etaOne < etaTwo){
            return false;
        }
        else if (etaOne > etaTwo){
            return true;
        }
        else{
            if (zombieOne->health < zombieTwo->health){
                return false;
            }
            else if (zombieOne->health > zombieTwo->health){
                return true;
            }
            else {
                if (zombieOne->name < zombieTwo->name){
                    return false;
                }
                else {
                    return true;
                }
            }
        }
    }
};

struct zombieMostActive {
    
    bool operator() (const Zombie *zombieOne, const Zombie *zombieTwo){
        if (zombieOne->roundsActive < zombieTwo->roundsActive){
            return true;
        }
        else if (zombieOne->roundsActive > zombieTwo->roundsActive){
            return false;
        }
        else{
            if (zombieOne->name > zombieTwo->name){
                return true;
            }
            else{
                return false;
            }
        }
    }
};


struct zombieLeastActive {
    
    bool operator() (const Zombie *zombieOne, const Zombie *zombieTwo){
        if (zombieOne->roundsActive < zombieTwo->roundsActive){
            return false;
        }
        else if (zombieOne->roundsActive > zombieTwo->roundsActive){
            return true;
        }
        else{
            if (zombieOne->name > zombieTwo->name){
                return true;
            }
            else{
                return false;
            }
        }
    }
};


struct medianLarger {
    
    bool operator() (const Zombie *zombieOne, const Zombie *zombieTwo){
        if (zombieOne->roundsActive > zombieTwo->roundsActive){
            return true;
        }
        else {
            return false;
        }
        
    }
};

struct medianSmaller {
    
    bool operator() (const Zombie *zombieOne, const Zombie *zombieTwo){
        if (zombieOne->roundsActive < zombieTwo->roundsActive){
            return true;
        }
        else {
            return false;
        }
    }
};


class Gameplay {
public:
    
    Zombie *namedZombieToVec;
    
    deque<Zombie*> masterList;
    
    priority_queue<Zombie*, deque<Zombie*>, zombieCompare> priorityQueueCompare;

    
    deque<Zombie*> orderKilled;

    bool verbose = false;
    bool statistic = false;
    bool median = false;
    
    unsigned int statisticNum = 0;
    
    unsigned int quiverCapacity = 0;
    unsigned int randomSeed = 0;
    unsigned int maxRandDistance = 0;
    unsigned int maxRandSpeed = 0;
    unsigned int maxRandHealth = 0;
    
    unsigned int whatRoundShouldBe = 1;

    unsigned int readInCurrentRound = 1;
    unsigned int numOfRandomZombies = 0;
    unsigned int numOfNamedZombies = 0;
    
    bool deathStatus = false;
    bool victory = false;
    string eatenBy = "";
    
    unsigned int numRefillArrows = 0;
    string lastZombie;
    
    void getMode(int argc, char * argv[]);
    void readInHeader();
    void readInSingleRound();
    void createRandomZombie(unsigned int numZombies);
    void createNamedZombie();
    void roundBreakdown();
    void shootZombies();
    void advanceZombies();
    void statisticOutput();
    int calculateMedian();
    
    bool fileFinished = false;
    int medianValue = 0;
    bool atLeastOneDeath = false;



private:

    
};


void Gameplay::getMode(int argc, char * argv[]) {
    opterr = false; // Let us handle all error output for command line options
    
    int choice;
    int option_index = 0;
    option long_options[] = {
        // ******check no argument vs required argument I AM UNSURE
        //**** single or double quotes
        { "verbose", no_argument,         nullptr, 'v'},
        { "statistics", required_argument,         nullptr, 's'},
        { "median", no_argument,         nullptr, 'm'},
        { "help", no_argument,         nullptr, 'h'},
        { nullptr, 0,                 nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "vs:mh", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            cout << "-v, --verbose: The -v flag is optional. If provided, indicates that you should print out extra messages during the operation of the program about zombies being created, moved, or destroyed. See Verbose Output. \n";
            cout << "-s <num>, --statistics <num>: The -s flag is optional. If it is provided, then <num> is a required uint32_t. If provided, you should print out statistics at the end of the program. You’ll print out <num> entries for each type of statistic. The -s flag will always be followed by a positive number. See Statistics Output. \n";
            cout << "-m, --median: The -m flag is optional. If provided, indicates that you should print out extra messages during the program indicating the median time that zombies have been active before being destroyed. \n";
            
            exit(0);
            break;

        case 'v':
            verbose = true;
            break;
                
        case 's':
            statisticNum = unsigned(atoi(optarg));
            statistic = true;
            break;
                
        case 'm':
            median = true;
            break;
        
        default:
            cerr << "Unknown command line option\n";
            exit(1);
        } // switch
    } // while

    
return;
    
} // getMode()



void Gameplay::readInHeader(){
    string junk;
    string junk1;

    // first line of code which is not needed
    getline(cin, junk);
    cin >> junk1 >> quiverCapacity >> junk1 >> randomSeed >> junk1
        >> maxRandDistance >> junk1 >> maxRandSpeed >> junk1 >> maxRandHealth >> junk1 >> junk1 >> readInCurrentRound;
    
    P2random::initialize(randomSeed, maxRandDistance, maxRandSpeed, maxRandHealth);
}

    

void Gameplay::readInSingleRound(){
    //TODO: we need to keep updating whatRoundShouldBe later on when we finish a round
    string junk2;
    if (whatRoundShouldBe == readInCurrentRound){
        cin >> junk2 >> numOfRandomZombies >> junk2 >> numOfNamedZombies;
        
        if (numOfRandomZombies > 0){
            createRandomZombie(numOfRandomZombies);
        }
        
        createNamedZombie();
    }
}

   

void Gameplay::createRandomZombie(unsigned int numZombies){
    
    for (size_t i = 0; i < numZombies; i++){
        std::string name1  = P2random::getNextZombieName();
        uint32_t distance1 = P2random::getNextZombieDistance();
        uint32_t speed1    = P2random::getNextZombieSpeed();
        uint32_t health1   = P2random::getNextZombieHealth();
        
        // create new pointer like a constructor
        //namedZombieToVec = new Zombie;
        
        Zombie *namedZombieToVec = new Zombie;
        
        //TODO: do these need to be . or ->
        namedZombieToVec->name = name1;
        namedZombieToVec->distance = distance1;
        namedZombieToVec->speed = speed1;
        namedZombieToVec->health = health1;
        
        //TODO: Unsure ab how to update the number of active rounds
//        namedZombieToVec.round = round;
        

        if (verbose){
            cout << "Created: " << namedZombieToVec->name << " (distance: " << namedZombieToVec->distance << ", speed: " << namedZombieToVec->speed << ", health: " << namedZombieToVec->health << ")\n";
        }
        
        // use new operator to create new zombie pointers
        // use the delete later on to delete them
        
        masterList.push_back(namedZombieToVec);
        //TODO: push into my priority queue but im unsure how to
        priorityQueueCompare.push(namedZombieToVec);
        
    }

}



void Gameplay::createNamedZombie(){
    string firstString;
    string junk3;
    unsigned int zombieDistance;
    unsigned int zombieSpeed;
    unsigned int zombieHealth;
    
    while(cin >> firstString){
        if (firstString != "---"){
            cin >> junk3 >> zombieDistance >> junk3 >> zombieSpeed >> junk3 >> zombieHealth;
            
            Zombie *namedZombieToVec = new Zombie;
            
            namedZombieToVec->name = firstString;
            namedZombieToVec->distance = zombieDistance;
            namedZombieToVec->speed = zombieSpeed;
            namedZombieToVec->health = zombieHealth;
            
            //TODO: Unsure ab how to update the number of active rounds
//            namedZombieToVec.round = whatRoundShouldBe;
            
            if (verbose){
                cout << "Created: " << firstString << " (distance: " << zombieDistance
                << ", speed: " << zombieSpeed << ", health: " << zombieHealth << ")\n";
            }
            masterList.push_back(namedZombieToVec);
            //TODO: push into my priority queue but im unsure how to
            priorityQueueCompare.push(namedZombieToVec);

        } // if
        else{
            break;
        }
    } // while
    
    //reads in the next round's value ahead of time
    cin >> junk3 >> readInCurrentRound;
    
    if (cin.fail()){
        fileFinished = true;
    }
    
}


void Gameplay::roundBreakdown(){
    while(deathStatus == false){
        // step 1: If the --verbose flag is enabled, print Round: followed by the round number.
        if (verbose == true){
            cout << "Round: " << whatRoundShouldBe << "\n";
        }
        
        // step 2: You refill your quiver. Set the number of arrows you have equal to your quiver capacity.
        numRefillArrows = quiverCapacity;
        
        // step 3: All active zombies advance toward you, updated in the order that they were created.
        if (masterList.size() != 0) {
            advanceZombies();
        }
        
//        step 4: At this point, if the Player was killed in Step 3, the battle ends.
//                Print any required messages and statistics.
        if (deathStatus == true){
            
            cout << "DEFEAT IN ROUND " << whatRoundShouldBe << "! " << eatenBy << " ate your brains! \n";
            break;
        }
        
//        step 5: New zombies appear:
        //        Random zombies are created.
        //        Named zombies are created.
        //        If the --verbose flag is enabled, print new active zombie name, speed, distance, and health information in the order they were created, along with “Created.” This is true for both random and named zombies. For example: Created: paoletti0 (distance: 25, speed: 20, health: 1)
        
        readInSingleRound();
    
        // step 6: Player shoots zombies.
//        Shoot the zombie with the lowest ETA (tie breaking described above) until your quiver         is empty.
//        If you destroy a zombie AND the --verbose flag is enabled, display a message; for             example: Destroyed: paoletti0 (distance: 4, speed: 1, health: 0)
        if (priorityQueueCompare.size() != 0){
            shootZombies();
        }
        
        if (median && atLeastOneDeath){
            medianValue = calculateMedian();
            cout << "At the end of round " << whatRoundShouldBe << ", the median zombie lifetime is " << medianValue << "\n";
        }
        
        if (priorityQueueCompare.size() == 0 && fileFinished){
//            victory = true;
            cout << "VICTORY IN ROUND " << whatRoundShouldBe << "! " << lastZombie << " was the last zombie. \n";
            break;
        }
        
        
//        if (victory == true){
//            break;
//        }
        
        
        whatRoundShouldBe++;
        
//        }

    }

}

void Gameplay::shootZombies(){
    
    while(numRefillArrows != 0 && priorityQueueCompare.size() != 0){
//        if(priorityQueueCompare.size() == 0){
//            break;
//        }
        
        Zombie *tempZombie = priorityQueueCompare.top();
        //TODO: Step 7: add to median
        
        if(tempZombie->health <= numRefillArrows){
            numRefillArrows = numRefillArrows - tempZombie->health;
            tempZombie->health = 0;
        }
        else {
            tempZombie->health = tempZombie->health - numRefillArrows;
            numRefillArrows = 0;
        }
        
//        tempZombie->health = tempZombie->health - 1;
//        numRefillArrows = numRefillArrows - 1;

        if(tempZombie->health == 0){
            if(priorityQueueCompare.size() == 1){
                lastZombie = tempZombie->name;
            }
            atLeastOneDeath = true;
            
            orderKilled.push_back(tempZombie);
            // add all median stuff
//            medianLargerPQ.push(tempZombie);
//            medianSmallerPQ.push(tempZombie);

//            if(median == true){
//                calculateMedian();
//            }
            
            if(verbose){
                cout << "Destroyed: " << tempZombie->name << " (distance: " << tempZombie->distance
                << ", speed: " << tempZombie->speed << ", health: " << tempZombie->health << ")\n";
            }
            priorityQueueCompare.pop();
        }
    }//while
    
    //  Step 8:
    //  If there are no more zombies and none will be generated in a future round, then you have won the battle.
    //  Print any required messages and statistics. The battle ends.
        
}


void Gameplay::advanceZombies(){
    
//    1. Update the zombie and move it closer to you.
//    2. If the --verbose flag is enabled, print the zombie name, speed, distance, and health, along with Moved: For example: Moved: paoletti0 (distance: 0, speed: 20, health: 1)
//    3. If at this point the zombie has reached you (has distance == 0), then it attacks you and you die.
//    4. If you die, the first zombie that reached you is the one that has “eaten” you (see Survival or Demise Message). You still need to update the other zombies, so don’t exit the loop yet!
    
    for (Zombie *i : masterList){
        unsigned int updatedDistance = 0;
        if (i->health != 0){
            i->roundsActive = i->roundsActive + 1;
            
            updatedDistance = (i->distance - i->speed);
            if (i->speed >= i->distance){
                i->distance = 0;
                if (deathStatus == false){
                    eatenBy = i->name;
                }
                deathStatus = true;
            }
            else{
                i->distance = updatedDistance;
            }
            
            if (verbose == true){
                cout << "Moved: " << i->name << " (distance: " << i->distance << ", speed: " << i->speed << ", health: " << i->health << ")\n";
            }

            //i->roundsActive++;

        }
    }
    
}

void Gameplay::statisticOutput(){
    if (statistic == true){
        cout << "Zombies still active: " << priorityQueueCompare.size() << "\n";
        
        cout << "First zombies killed: \n";
        if (orderKilled.size() < statisticNum){
            for (size_t i = 0; i < orderKilled.size(); i++){
                cout << orderKilled[i]->name << " " << (i + 1) << "\n";
            }
        }
        else{
            for (size_t i = 0; i < statisticNum; i++){
                cout << orderKilled[i]->name << " " << (i + 1) << "\n";
            }
        }
        
        cout << "Last zombies killed: \n";
        if (orderKilled.size() < statisticNum){
            for (size_t i = orderKilled.size(); i > 0; i--){
                cout << orderKilled[i - 1]->name << " " << (i) << "\n";
            }
        }
        else{
            int tempNum = statisticNum;
            for (size_t i = orderKilled.size(); i > (orderKilled.size()-statisticNum); i--){
                cout << orderKilled[i - 1]->name << " " << tempNum << "\n";
                tempNum--;
            }
        }

//        for (Zombie *i : masterList){
//            priorityQueueMostActive.push(i);
//            priorityQueueLeastActive.push(i);
//        }
        priority_queue<Zombie*, deque<Zombie*>, zombieMostActive> priorityQueueMostActive(masterList.begin(), masterList.end());
        priority_queue<Zombie*, deque<Zombie*>, zombieLeastActive> priorityQueueLeastActive(masterList.begin(), masterList.end());
        
        cout << "Most active zombies: \n";
        if (priorityQueueMostActive.size() < statisticNum){
            size_t tempSize = priorityQueueMostActive.size();
            for (size_t i = 0; i < tempSize; i++){
                cout << priorityQueueMostActive.top()->name << " " << priorityQueueMostActive.top()->roundsActive << "\n";
                priorityQueueMostActive.pop();
            }
        }
        else {
            for (size_t i = 0; i < statisticNum; i++){
                cout << priorityQueueMostActive.top()->name << " " << priorityQueueMostActive.top()->roundsActive << "\n";
                priorityQueueMostActive.pop();
            }
        }
        
        
        cout << "Least active zombies: \n";
        if (priorityQueueLeastActive.size() < statisticNum){
            size_t tempSize = priorityQueueLeastActive.size();
            for (size_t i = 0; i < tempSize; i++){
                cout << priorityQueueLeastActive.top()->name << " " << priorityQueueLeastActive.top()->roundsActive << "\n";
                priorityQueueLeastActive.pop();
            }
        }
        else {
            for (size_t i = 0; i < statisticNum; i++){
                cout << priorityQueueLeastActive.top()->name << " " << priorityQueueLeastActive.top()->roundsActive << "\n";
                priorityQueueLeastActive.pop();
            }
        }
    }
    
    
    for (Zombie *i : masterList){
        delete i;
    }

}


int Gameplay::calculateMedian(){
    priority_queue<Zombie*, deque<Zombie*>, medianLarger> medianLargerPQ;
    priority_queue<Zombie*, deque<Zombie*>, medianSmaller> medianSmallerPQ;
    
    Zombie *tempZombie2;
    int med = 0;
    
//    for(size_t it = 0; ;it++){
//        if (masterList[it]->health == 0){
//            tempZombie2 = masterList[it];
//            break;
//        }
//    }
    tempZombie2 = orderKilled[0];
    
    med = tempZombie2->roundsActive;
    medianSmallerPQ.push(tempZombie2);
    
    int iterator = 0;
    for (Zombie *i : orderKilled){
        if(i->health == 0){
            if (iterator == 0){
                iterator++;
                continue;
            }
            int currValueRA = i->roundsActive;
            
            if (medianSmallerPQ.size() > medianLargerPQ.size()) {
                if (currValueRA < med) {
                    medianLargerPQ.push(medianSmallerPQ.top());
                    medianSmallerPQ.pop();
                    medianSmallerPQ.push(i);
                }
                else {
                    medianLargerPQ.push(i);
                }
                
                med = (medianSmallerPQ.top()->roundsActive + medianLargerPQ.top()->roundsActive)/2;
            }
            
            else if (medianSmallerPQ.size() == medianLargerPQ.size()) {
                if (currValueRA < med) {
                    medianSmallerPQ.push(i);
                    med = medianSmallerPQ.top()->roundsActive;
                }
                else {
                    medianLargerPQ.push(i);
                    med = medianLargerPQ.top()->roundsActive;
                }
            }
            
            else {
                if (currValueRA > med) {
                    medianSmallerPQ.push(medianLargerPQ.top());
                    medianLargerPQ.pop();
                    medianLargerPQ.push(i);
                }
                else{
                    medianSmallerPQ.push(i);
                }
                med = (medianSmallerPQ.top()->roundsActive + medianLargerPQ.top()->roundsActive)/2;
            }
        }
    }
    
    return med;
}


//___________________________________________________________________________________

int main(int argc, char *argv[]){
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    Gameplay gameplayMain;
    
    gameplayMain.getMode(argc, argv);
    gameplayMain.readInHeader();
    gameplayMain.roundBreakdown();
    gameplayMain.statisticOutput();
    

    return 0;
    
}
