// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

//EFFECTS Initializes Card to the Two of Spades
// Constructor for the Card class that initializes card object
Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const string &rank_in, const string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

//EFFECTS Returns the rank
string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card::get_suit(const string &trump) const{
    assert(trump == SUIT_DIAMONDS || trump == SUIT_CLUBS ||
           trump == SUIT_SPADES || trump == SUIT_HEARTS);

    if (trump == SUIT_DIAMONDS && (rank == RANK_JACK && suit == SUIT_HEARTS)) {
        return SUIT_DIAMONDS;
    }
    else if (trump == SUIT_HEARTS && (rank == RANK_JACK && suit == SUIT_DIAMONDS)) {
        return SUIT_HEARTS;
    }
    else if (trump == SUIT_CLUBS && (rank == RANK_JACK && suit == SUIT_SPADES)) {
        return SUIT_CLUBS;
    }
    
    else if (trump == SUIT_SPADES && (rank == RANK_JACK && suit == SUIT_CLUBS)) {
        return SUIT_SPADES;
    }
    else {
        return suit;
    }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    if (rank == RANK_ACE || rank == RANK_KING ||
        rank == RANK_QUEEN || rank == RANK_JACK) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const string &trump) const {
    assert(trump == SUIT_DIAMONDS || trump == SUIT_CLUBS ||
           trump == SUIT_SPADES || trump == SUIT_HEARTS);

    if (rank == RANK_JACK && suit == trump) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const string &trump) const {
    assert(trump == SUIT_DIAMONDS || trump == SUIT_CLUBS ||
           trump == SUIT_SPADES || trump == SUIT_HEARTS);

    if (trump == SUIT_DIAMONDS && rank == RANK_JACK && suit == SUIT_HEARTS) {
        return true;
    }
    else if (trump == SUIT_HEARTS && rank == RANK_JACK && suit == SUIT_DIAMONDS) {
        return true;
    }
    else if (trump == SUIT_SPADES && rank == RANK_JACK && suit == SUIT_CLUBS) {
        return true;
    }
    else if (trump == SUIT_CLUBS && rank == RANK_JACK && suit == SUIT_SPADES) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const string &trump) const {
    assert(trump == "Diamonds" || trump == "Spades" 
                || trump == "Clubs" || trump == "Hearts");

    if (suit == trump || is_left_bower(trump)) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
// Overloading the < operator to compare two Card objects
bool operator<(const Card &lhs, const Card &rhs) {
    int lhsTempRank = 0;
    int rhsTempRank = 0;
    int lhsTempSuit = 0;
    int rhsTempSuit = 0;
    
    for (size_t n = 0; n < NUM_SUITS; n++) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[n]) {
            lhsTempSuit = n;
        }
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[n]) {
            rhsTempSuit = n;
        }
    }
    for (size_t i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            lhsTempRank = i;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rhsTempRank = i;
        }
    }
    
    if (lhsTempRank < rhsTempRank) {
        return true;
    }
    else if (lhsTempRank == rhsTempRank) {
        if (lhsTempSuit < rhsTempSuit) {
            return true;
        }
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    return lhs == rhs || lhs < rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    return !(lhs <= rhs);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    return !(lhs < rhs);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    return (lhs.get_rank() == rhs.get_rank()) && (lhs.get_suit() == rhs.get_suit());
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
string Suit_next(const string &suit) {
    if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else {
        return "";
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream & operator<<(ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const string &trump) {
    assert(trump == "Diamonds" || trump == "Clubs" ||
           trump == "Spades" || trump == "Hearts");

    if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else if (!a.is_trump(trump) && !b.is_trump(trump)) {
        return a < b;
    }
    else if (a.is_trump(trump) && b.is_trump(trump)) {
        if (a.is_right_bower(trump)) {
            return false;
        }
        else if (b.is_right_bower(trump)) {
            return true;
        }
        else if (b.is_left_bower(trump)) {
            return true;
        }
        else if (a.is_left_bower(trump)) {
            return false;
        }
        else {
            return a < b;
        }
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const string &trump) {
    assert(trump == "Diamonds" || trump == "Spades" 
                || trump == "Clubs" || trump == "Hearts");

    if (a.is_trump(trump) || b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }
    else if (a.get_suit() == led_card.get_suit() && b.get_suit() != led_card.get_suit()) {
        return false;
    }
    else if (a.get_suit() != led_card.get_suit() && b.get_suit() == led_card.get_suit()) {
        return true;
    }
    else {
        return a < b;
    }
}




// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
