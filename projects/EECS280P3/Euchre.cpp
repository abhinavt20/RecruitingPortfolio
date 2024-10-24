// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

class GamePlay {
    
public:

    GamePlay(vector <Player*> vectorPlayers, string shuffle, 
            int pointsToWin, ifstream &packInput) {
        //initilize pack here. Use istream???
        Pack pack(packInput);
        
        playerToPlay = 1;

        doDontShuffle = shuffle;
       
        players = vectorPlayers;
       
        dealerNumber = 0;
        handCount = 0;

        targetScore = pointsToWin;
        t1score = 0;
        t2score = 0;
        t1trickWins = 0;
        t2trickWins = 0;
    }

    
    void shuffle(){
        if (doDontShuffle == "shuffle"){
            pack.shuffle();
            pack.reset();
        }
        else {
            pack.reset();
        }
    }

    void deal() {

        int const batchSize = 8;

        shuffle();
        
        int toTheLeft = 1;

        for(size_t batch = 0; batch < batchSize; batch++){
                //first half of batch
            if(batch < batchSize/2 && (batch % 2 == 0)){
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
            }
            else if(batch < batchSize/2 && (batch % 2 == 1)){
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
            }
            
            //second half of batch
            else if(batch >= batchSize/2 && (batch % 2 == 0)){
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
            }
            else if(batch >= batchSize/2 && (batch % 2 == 1)){
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
                players.at((dealerNumber + toTheLeft) % 4)->add_card(pack.deal_one());
            }

            toTheLeft++;
        }

    }

    // returns upcard
    void startHand(int handCount, Card upcard) {
        cout << "Hand " << handCount << endl;
        cout << *players.at(dealerNumber) << " deals" << endl;
        cout << upcard << " turned up" << endl;
    }
    

    // set value for trump (suit), orderUp (bool)
    void makeTrump(Card upcard) {
        int round = 1;

        int playerIndex;
        if (dealerNumber == 3){
            playerIndex = 0;
        }
        else {
            playerIndex = dealerNumber + 1;
        }


        string orderUpSuit = upcard.get_suit();
        for (size_t i = 0; i < 8; i++) {
            if (i >= 4) {
                round = 2;
            }

            bool isDealer = false;

            if (playerIndex == dealerNumber){
                isDealer = true;
            }
            else {
                isDealer = false;
            }

            bool makesTrump = players.at(playerIndex)->
                            make_trump(upcard, isDealer, round, orderUpSuit);

            if (makesTrump && round == 1){
                cout << *players.at(playerIndex) 
                    << " orders up " << orderUpSuit << endl;
                cout << endl; 
                trump = orderUpSuit;
                orderUpPlayerIndex = playerIndex;

                players.at(dealerNumber)->add_and_discard(upcard);

                return;
            }
            else if(makesTrump && round == 2) {
                cout << *players.at(playerIndex) 
                    << " orders up " << orderUpSuit << endl;
                cout << endl; 

                trump = orderUpSuit;
                orderUpPlayerIndex = playerIndex;
                    
                return;
                }
            else{
                cout << *players.at(playerIndex) << " passes" << endl;
            }

            nextPlayer(playerIndex);

        }
    }


    
    void trickTaking() {
        Card cardsInTrick[4];
        int playerTricks[4] = {0,0,0,0};

        int leaderIndex;
            if (dealerNumber == 3){
                leaderIndex = 0;
            }
            else {
                leaderIndex = dealerNumber + 1;
            }

        for (size_t i = 0; i < 5; i++) {
            ledCard = players.at(leaderIndex)->lead_card(trump);
            
            cardsInTrick[0] = ledCard;
            cout << ledCard << " led by " << *players.at(leaderIndex) << endl;
            int playerToPlay = leaderIndex;
            nextPlayer(playerToPlay);
            
           
            cardsInTrick[1] = players.at(playerToPlay)->play_card(ledCard, trump);
            cout << cardsInTrick[1] << " played by " 
                << *players.at(playerToPlay) << endl;
            nextPlayer(playerToPlay);
           
            
            cardsInTrick[2] = players.at(playerToPlay)->play_card(ledCard, trump);
            cout << cardsInTrick[2] << " played by " 
                << *players.at(playerToPlay) << endl;
            nextPlayer(playerToPlay);
            
            cardsInTrick[3] = players.at(playerToPlay)->play_card(ledCard, trump);
            cout << cardsInTrick[3] << " played by " 
                << *players.at(playerToPlay) << endl;
            nextPlayer(playerToPlay);
        
            int winningCardIndex = compareFourCards(cardsInTrick[0], 
                                cardsInTrick[1], cardsInTrick[2], cardsInTrick[3]);
            leaderIndex = (leaderIndex + winningCardIndex) % 4;
            
            //adds one point to the index of the winning player
            playerTricks[leaderIndex]++;
            
            cout << *players.at(leaderIndex) << " takes the trick" << endl;
            cout << endl;
        }
        calculateScoring(playerTricks);
    }
    
    void calculateScoring(int tricks[]) {
        //int tricks[4] = playerTricks;
        t1trickWins = tricks[0] + tricks[2];
        t2trickWins = tricks[1] + tricks[3];
        
        if (t1trickWins > t2trickWins && 
            !(orderUpPlayerIndex == 0 || orderUpPlayerIndex == 2)) {
            t1score += 2;
            cout << *players.at(0) << " and " 
                << *players.at(2) << " win the hand" << endl;
            cout << "euchred!" << endl;
        }
        else if (t1trickWins > t2trickWins && (orderUpPlayerIndex == 0 
                || orderUpPlayerIndex == 2)) {
            if (t1trickWins == 5) {
                t1score += 2;
                cout << *players.at(0) << " and " 
                    << *players.at(2) << " win the hand" << endl;
                cout << "march!" << endl;
            }
            else {
                t1score += 1;
                cout << *players.at(0) << " and " 
                    << *players.at(2) << " win the hand" << endl;
            }
        }
        else if (t1trickWins < t2trickWins && !(orderUpPlayerIndex == 1 
                || orderUpPlayerIndex == 3)) {
            t2score += 2;
            cout << *players.at(1) << " and " 
                << *players.at(3) << " win the hand" << endl;
            cout << "euchred!" << endl;
        }
        else {
            if (t2trickWins == 5) {
                t2score += 2;
                cout << *players.at(1) << " and " 
                    << *players.at(3) << " win the hand" << endl;
                cout << "march!" << endl;
            }
            else {
                t2score += 1;
                cout << *players.at(1) << " and " 
                    << *players.at(3) << " win the hand" << endl;
            }
        }

        handCount++;
        dealerNumber++;
        if (dealerNumber == 4) {
            dealerNumber = 0;
        }

        cout << *players.at(0) << " and " << *players.at(2) 
            << " have " << t1score << " points" << endl;
        cout << *players.at(1) << " and " << *players.at(3) 
            << " have " << t2score << " points" << endl;
        cout << endl;
        
    }


    void nextPlayer(int &input) {
        if (input == 3) {
            input = 0;
        }
        else {
            input++;
        }
    }
    

    int compareFourCards(Card ledCard, Card card2, Card card3, Card card4) {
        Card bestCard;
        int bestIndex;

        if (Card_less(ledCard, card2, ledCard, trump)) {
            bestCard = card2;
            bestIndex = 1;
        }
        else {
            bestCard = ledCard;
            bestIndex = 0;
        }
        if (Card_less(bestCard, card3, ledCard, trump)) {
            bestCard = card3;
            bestIndex = 2;
        }
        if (Card_less(bestCard, card4, ledCard, trump)) {
            bestCard = card4;
            bestIndex = 3;
        }
        return bestIndex;
    }
    
    int getT1Points() {
        return t1score;
    }
    
    int getT2Points() {
        return t2score;
    }
    
    int getTargetScore() {
        return targetScore;
    }

    void playGame(){

        deal(); 

        Card upcard = pack.deal_one();

        startHand(handCount, upcard);

        makeTrump(upcard);

        trickTaking();
    }

    

private:
    Card upcard;
    string trump;
    //bool orderUp;
    int playerToPlay;
    Card ledCard;
    vector <Player*> players;
    string doDontShuffle;
    int dealerNumber;
    Pack pack;
    int t1trickWins;
    int t2trickWins;
    int targetScore;
    int handCount;
    int orderUpPlayerIndex;
    int t1score;
    int t2score;
    
    //int tricks[4];
};

// Main function to drive the Euchre game simulation
int main(int argc, char* argv[]) {

    string shuffleDecision = argv[2];

    if (argc != 12 || (atoi(argv[3]) < 1 || atoi(argv[3]) > 100)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }
    if (shuffleDecision != "shuffle" && shuffleDecision != "noshuffle") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }

    for (int i = 5; i < argc; i = i + 2) {
        string playerType = argv[i];
        if (playerType != "Simple" && playerType != "Human") {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
                 << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
                 << "NAME4 TYPE4" << endl;
        }
    }
    
    string fileInput = argv[1];
    ifstream ins(fileInput);

    ins.open(fileInput);
    if (!ins.is_open()) {
        cout << "Error opening" << fileInput << endl;
        return 0;
    }
    
    vector <Player*> players;
    players.push_back(Player_factory(argv[4], argv[5]));
    players.push_back(Player_factory(argv[6], argv[7]));
    players.push_back(Player_factory(argv[8], argv[9]));
    players.push_back(Player_factory(argv[10], argv[11]));
    
    int pointsToWinGame = atoi(argv[3]);
    
    GamePlay * game = new GamePlay(players, shuffleDecision, pointsToWinGame, ins);
    
    for (int i = 0; i < argc; i++) {
	    cout << argv[i] << " ";
	}
	cout << endl;


    
    while (game->getT1Points() < game->getTargetScore() 
        && game->getT2Points() < game->getTargetScore()) {
        game->playGame();
    }


    if (game->getT1Points() >= pointsToWinGame){
        cout << *players.at(0) << " and " << *players.at(2) << " win!" << endl;
    }
    else {
        cout << *players.at(1) << " and " << *players.at(3) << " win!" << endl;
    }



	for (size_t i = 0; i < players.size(); i++) {
		delete players.at(i);
	}

	delete game;
        
   
}


    



    

