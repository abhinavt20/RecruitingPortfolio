// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "Player.h"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

class Simple : public Player {
    public:
        
    Simple(string input) {
        name = input;
    }
    
    //EFFECTS returns player's name
    virtual const string &get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) override {
        assert(playerHand.size() < MAX_HAND_SIZE);
        playerHand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                int round, string &order_up_suit) const override {
        assert(round == 1 || round == 2);
        
        string upcardSuit = upcard.get_suit();
        int sameSuitFaceCards1 = 0;
        int sameSuitFaceCards2 = 0;
        for (size_t i = 0; i < playerHand.size(); i++) {
            if (playerHand.at(i).is_face() 
                && playerHand.at(i).get_rank() == "Jack") {
                if (playerHand.at(i).get_suit() == upcardSuit ||
                    playerHand.at(i).get_suit() == Suit_next(upcardSuit)) {
                    sameSuitFaceCards1++;
                    sameSuitFaceCards2++;
                }
            }
            else if (playerHand.at(i).is_face() 
                    && playerHand.at(i).get_rank() != "Jack") {
                if (playerHand.at(i).get_suit() == upcardSuit) {
                    sameSuitFaceCards1++;
                }
                else if (playerHand.at(i).get_suit() == Suit_next(upcardSuit)) {
                    sameSuitFaceCards2++;
                }
            }
        }

        if (round == 1 && (sameSuitFaceCards1 > 1)) {
            order_up_suit = upcardSuit;
            return true;
        }
        else if ((round == 2 && sameSuitFaceCards2 > 0) 
                || (round == 2 && is_dealer)){
            order_up_suit = Suit_next(upcardSuit);
            return true;
        }
        else {
            return false;
        }
    }



    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) override {
        assert(playerHand.size() > 0);

        playerHand.push_back(upcard);
        int lowIndex = 0;
        Card highCard = playerHand.at(0);
        for (size_t i = 0; i < playerHand.size(); i++) {
            if (Card_less(playerHand.at(i), highCard, upcard.get_suit())) {
                highCard = playerHand.at(i);
                lowIndex = static_cast<int>(i);
            }
        }
        playerHand.erase(playerHand.begin() + lowIndex);
    }
    

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(const string &trump) override {
        assert(playerHand.size() > 0);
        assert(trump == "Diamonds" || trump == "Spades" 
                || trump == "Clubs" || trump == "Hearts");
        
        int amountOfTrumps = 0;
        int maxPos = 0;
        Card highest;
        int sizeOfHand = playerHand.size();


        if (trump == "Spades") {
            Card temp(Card::RANK_TWO, Card::SUIT_DIAMONDS);
            highest = temp;
        }

        for (size_t i = 0; i < playerHand.size(); i++) {
            if (playerHand.at(i).is_trump(trump)) {
                amountOfTrumps++;
            }
        }

        //if all trumps 
        if (amountOfTrumps == sizeOfHand) {
            for (size_t i = 0; i < playerHand.size(); i++) {
                if (Card_less(highest, playerHand.at(i), trump)) {
                    highest = playerHand.at(i);
                    maxPos = i;
                }
            }

        playerHand.erase(playerHand.begin() + maxPos);
        return highest;
        }
        //if not all trumps 
        else {
            for (size_t i = 0; i < playerHand.size(); i++) {
                if (!playerHand.at(i).is_trump(trump) 
                    && Card_less(highest, playerHand.at(i), trump)) {
                    highest = playerHand.at(i);
                    maxPos = i;
                }
            }

            playerHand.erase(playerHand.begin() + maxPos);
            return highest;
        }
    
    
    }
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, const string &trump) override {
        assert(playerHand.size() >= 1);
        assert(trump == "Diamonds" || trump == "Spades" 
                || trump == "Clubs" || trump == "Hearts");
    
        Card highestCard;
        int minPos = 0;
        int maxPos = 0;
        int ledSuitsInHand = 0;
        
        //highest possible card
        Card lowestCard(Card::RANK_JACK, trump);

        if (trump == "Spades") {
            Card temp(Card::RANK_TWO, Card::SUIT_DIAMONDS);
            highestCard = temp;
        }

        //checks if any cards in the players hand follow suit of led card
        for (size_t i = 0; i < playerHand.size(); i++) {
            if (playerHand.at(i).get_suit(trump) == led_card.get_suit(trump)) {
                ledSuitsInHand++;
            }
        }

        //if any cards follow led suit
        if (ledSuitsInHand > 0) {
            for (size_t i = 0; i < playerHand.size(); i++) {
                if ((playerHand.at(i).get_suit(trump) 
                        == led_card.get_suit(trump)) &&
                        Card_less(highestCard, playerHand.at(i), 
                                led_card, trump)) {
                    highestCard = playerHand.at(i);
                    maxPos = i;
                }
            }

            playerHand.erase(playerHand.begin() + maxPos);
            return highestCard;
        }
        
        //if no cards in hand are led suit 
        else {
            for (size_t i = 0; i < playerHand.size(); i++) {
                if (Card_less(playerHand.at(i), lowestCard, trump)) {
                    lowestCard = playerHand.at(i);
                    minPos = i;
                }
            }

            playerHand.erase(playerHand.begin() + minPos);
            return lowestCard;
        }
    }
    
    private:
        string name;
        vector<Card> playerHand;
        
};

class Human : public Player {
public:
    
    Human(string input) {
        name = input;
    }

     //EFFECTS returns player's name
    virtual const string &get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) override {
        assert(playerHand.size() < MAX_HAND_SIZE);
        
        playerHand.push_back(c);
    }


    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                int round, string &order_up_suit) const override {
        assert(round == 1 || round == 2);

        vector<Card> playerHandCopy = playerHand;

        sort(playerHandCopy.begin(), playerHandCopy.end());
        for (size_t t = 0; t < playerHandCopy.size(); t++) {
            cout << "Human player " << name 
            << "'s hand: [" << t << "] " 
            << playerHandCopy.at(t) << endl;
        }

        string passOrSuit;
        cout << "Human player " << name 
            << ", please enter a suit, or \"pass\":" << endl;
        cin >> passOrSuit;
        if (passOrSuit == "pass") {
            return false;
        }
        else {
            order_up_suit = passOrSuit;
            return true;
        }
    }


    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) override {
        assert(playerHand.size() > 0);

        sort(playerHand.begin(), playerHand.end());
        for (size_t t = 0; t < playerHand.size(); t++) {
            cout << "Human player " << name 
                << "'s hand: [" << t << "] " << playerHand.at(t) << endl;
        }
        playerHand.push_back(upcard);
        int discardChoice;

        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name 
            << ", please select a card to discard:" << endl;

        cin >> discardChoice;
        int discardIndex = 0;
        if (discardChoice == -1) {
            discardIndex = static_cast<int>(playerHand.size()) - 1;
        }
        else {
            discardIndex = discardChoice;
        }
        
        playerHand.erase(playerHand.begin() + discardIndex);
    }


    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(const string &trump) override {
        assert(playerHand.size() > 0);
        assert(trump == "Diamonds" || trump == "Spades" 
                || trump == "Clubs" || trump == "Hearts");

        sort(playerHand.begin(), playerHand.end());
        for (size_t t = 0; t < playerHand.size(); t++) {
            cout << "Human player " << name 
                << "'s hand: [" << t << "] " << playerHand.at(t) << endl;
        }
        int cardSelection;
        cout << "Human player " << name << ", please select a card:" << endl;
        cin >> cardSelection;
        Card selectedCard = playerHand.at(cardSelection);
        playerHand.erase(playerHand.begin() + cardSelection);
        return selectedCard;
        
    }


    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, const string &trump) override {
        return lead_card(trump);
    }

        
    private:
        string name;
        vector<Card> playerHand;
    
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
// Factory function to create Player objects dynamically based on strategy
Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new Simple(name);
    }
    else if (strategy == "Human") {
        return new Human(name);
    }
    else {
        return nullptr;
    }
}

//EFFECTS: Prints player's name to os
// Overload for << operator to print Player details
std::ostream & operator<<(std::ostream &os, const Player &p) {
    return os << p.get_name();
}

