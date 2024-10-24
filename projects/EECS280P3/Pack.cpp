// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "Pack.h"
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
// Default constructor for Pack that initializes cards in order
Pack::Pack() {
    int count = 0;
    next = 0;
    for (size_t i = 0; i < NUM_SUITS; i++) {
        for (size_t j = 7; j < NUM_RANKS; j++) {
            cards[count] = Card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
            count++;
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(istream& pack_input) {
    string tempRank;
    string tempSuit;
    string junk;
    next = 0;
    for (size_t i = 0; i < PACK_SIZE; i++) {
        pack_input >> tempRank >> junk >> tempSuit;
        cards[i] = Card(tempRank, tempSuit);
    }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    int tempIndex = next;
    next++;
    return cards[tempIndex];
}

// EFFECTS: Resets next index to first card in the Pack
// Resets the pack to the initial state for a new game
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    array<Card, PACK_SIZE> tempArray;
    array<Card, PACK_SIZE> tempArray1;

    int counter = 12;
    int counter2 = 0;

    for (size_t i = 0; i < PACK_SIZE ; i = i + 2) {
            tempArray[i] = cards[counter];
            tempArray[i + 1] = cards[counter2];
            tempArray1[i] = cards[counter];
            tempArray1[i + 1] = cards[counter2];
            counter++;
            counter2++;
        }

    counter = 12;
    counter2 = 0;

    for (size_t j = 0; j < 6; j++) {
        for (size_t i = 0; i < PACK_SIZE ; i = i + 2) {
            tempArray[i] = tempArray1[counter];
            tempArray[i + 1] = tempArray1[counter2];
            counter++;
            counter2++;
        }
        for (size_t n = 0; n < PACK_SIZE; n++) {
            tempArray1[n] = tempArray[n];
        }
        counter = 12;
        counter2 = 0;
    }
    for (size_t n = 0; n < PACK_SIZE; n++) {
        cards[n] = tempArray[n];
    }
        
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next == 24) {
        return true;
    }
    else {
        return false;
    }
}

