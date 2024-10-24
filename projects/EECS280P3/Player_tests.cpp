// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

// Test case for verifying function correctness
TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Test case for verifying function correctness
TEST(test_add_card_simple) {
    Player * jack = Player_factory("Jack", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    jack->add_card(c1);
    Card c2(Card::RANK_TEN, Card::SUIT_SPADES);
    jack->add_card(c2);
    Card c3(Card::RANK_KING, Card::SUIT_HEARTS);
    jack->add_card(c3);
    Card c4(Card::RANK_QUEEN, Card::SUIT_SPADES);
    jack->add_card(c4);
    
    Card ledCard(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cardPlayed = jack->play_card(ledCard, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(cardPlayed, c4);

    delete jack;
    
    Player * tom = Player_factory("Tom", "Simple");
    Card c5(Card::RANK_QUEEN, Card::SUIT_SPADES);
    tom->add_card(c5);
    Card c6(Card::RANK_NINE, Card::SUIT_SPADES);
    tom->add_card(c6);
    Card c7(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    tom->add_card(c7);
    Card c8(Card::RANK_TEN, Card::SUIT_SPADES);
    tom->add_card(c8);
    
    Card ledCard1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cardPlayed1 = tom->play_card(ledCard1, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(cardPlayed1, c5);

    delete tom;
    
}

// Test case for verifying function correctness
TEST(test_make_trump) {
    Player * sam = Player_factory("Sam", "Simple");
    Card c1(Card::RANK_ACE, Card::SUIT_CLUBS);
    sam->add_card(c1);
    Card c2(Card::RANK_KING, Card::SUIT_CLUBS);
    sam->add_card(c2);
    Card c3(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    sam->add_card(c3);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    sam->add_card(c4);
    
    Card upcard(Card::RANK_JACK, Card::SUIT_CLUBS);
    string orderUpSuit;
    
    bool samOrder = sam->make_trump(upcard, false, 1, orderUpSuit);
    assert(samOrder);
    ASSERT_EQUAL(orderUpSuit, Card::SUIT_CLUBS);
    
    delete sam;
    
    Player * abby = Player_factory("Abby", "Simple");
    Card c11(Card::RANK_ACE, Card::SUIT_CLUBS);
    abby->add_card(c11);
    Card c21(Card::RANK_KING, Card::SUIT_HEARTS);
    abby->add_card(c21);
    Card c31(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    abby->add_card(c31);
    Card c41(Card::RANK_TEN, Card::SUIT_SPADES);
    abby->add_card(c41);
    
    Card upcard2(Card::RANK_KING, Card::SUIT_DIAMONDS);
    string orderUpSuit2;
    
    bool abbyOrder = abby->make_trump(upcard2, false, 1, orderUpSuit2);
    assert(abbyOrder == false);
    
    delete abby;
    
    Player * ted = Player_factory("Ted", "Simple");
    Card c12(Card::RANK_JACK, Card::SUIT_HEARTS);
    ted->add_card(c12);
    Card c22(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ted->add_card(c22);
    Card c32(Card::RANK_NINE, Card::SUIT_SPADES);
    ted->add_card(c32);
    Card c42(Card::RANK_TEN, Card::SUIT_SPADES);
    ted->add_card(c42);
    
    Card upcard3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    string orderUpSuit3;
    
    bool tedOrder = ted->make_trump(upcard3, false, 1, orderUpSuit3);
    assert(tedOrder);
    ASSERT_EQUAL(orderUpSuit3, Card::SUIT_DIAMONDS);
                 
     delete ted;

     Player * larry = Player_factory("Larry", "Simple");
     Card c13(Card::RANK_KING, Card::SUIT_HEARTS);
     larry->add_card(c13);
     Card c23(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
     larry->add_card(c23);
     Card c43(Card::RANK_QUEEN, Card::SUIT_SPADES);
     larry->add_card(c43);
     Card c53(Card::RANK_NINE, Card::SUIT_HEARTS);
     larry->add_card(c53);
     
     Card upcard4(Card::RANK_JACK, Card::SUIT_DIAMONDS);
     string orderUpSuit4;
     
     bool larryOrder = larry->make_trump(upcard4, false, 2, orderUpSuit4);
     assert(larryOrder);
     ASSERT_EQUAL(orderUpSuit4, Card::SUIT_HEARTS);
     
     delete larry;
                 
     Player * mary = Player_factory("Mary", "Simple");
     Card c14(Card::RANK_KING, Card::SUIT_CLUBS);
     mary->add_card(c14);
     Card c24(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
     mary->add_card(c24);
     Card c34(Card::RANK_KING, Card::SUIT_DIAMONDS);
     mary->add_card(c34);
     Card c44(Card::RANK_QUEEN, Card::SUIT_SPADES);
     mary->add_card(c44);
     
     Card upcard5(Card::RANK_JACK, Card::SUIT_DIAMONDS);
     string orderUpSuit5;
     
     bool maryOrder = mary->make_trump(upcard5, true, 2, orderUpSuit5);
     assert(maryOrder);
     ASSERT_EQUAL(orderUpSuit5, Card::SUIT_HEARTS);
                 
     delete mary;
    
}
                 
// Test case for verifying function correctness
TEST(add_and_discard) {
    Player * cam = Player_factory("Cam", "Simple");
    Card c1(Card::RANK_ACE, Card::SUIT_SPADES);
    cam->add_card(c1);
    Card c2(Card::RANK_KING, Card::SUIT_SPADES);
    cam->add_card(c2);
    Card c3(Card::RANK_QUEEN, Card::SUIT_SPADES);
    cam->add_card(c3);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    cam->add_card(c4);
        
    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    cam->add_and_discard(upcard);
    
    Card cardPlayed = cam->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(cardPlayed, c4);
        
    delete cam;
        
    Player * joy = Player_factory("Joy", "Simple");
    Card c11(Card::RANK_KING, Card::SUIT_CLUBS);
    joy->add_card(c11);
    Card c21(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    joy->add_card(c21);
    Card c31(Card::RANK_NINE, Card::SUIT_CLUBS);
    joy->add_card(c31);
    Card c41(Card::RANK_JACK, Card::SUIT_CLUBS);
    joy->add_card(c41);
        
    Card upcard1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    joy->add_and_discard(upcard1);
    
    Card cardPlayed1 = joy->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed1, c41);
        
    delete joy;
    
    Player * jimmy = Player_factory("Jimmy", "Simple");
    Card c12(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    jimmy->add_card(c12);
    Card c22(Card::RANK_TEN, Card::SUIT_SPADES);
    jimmy->add_card(c22);
    Card c32(Card::RANK_NINE, Card::SUIT_CLUBS);
    jimmy->add_card(c32);
    Card c42(Card::RANK_JACK, Card::SUIT_CLUBS);
    jimmy->add_card(c42);
        
    Card upcard2(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    jimmy->add_and_discard(upcard2);
    
    Card cardPlayed2 = jimmy->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed2, c22);
        
    delete jimmy;
    
    Player * john = Player_factory("John", "Simple");
    Card c6(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    john->add_card(c6);
    Card c7(Card::RANK_TEN, Card::SUIT_SPADES);
    john->add_card(c7);
    Card c8(Card::RANK_NINE, Card::SUIT_CLUBS);
    john->add_card(c8);
    Card c9(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    john->add_card(c9);
        
    Card upcard3(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    john->add_and_discard(upcard3);
    
    Card cardPlayed3 = john->lead_card(Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(cardPlayed3, upcard3);
        
    delete john;
}

// Test case for verifying function correctness
TEST(test_lead_card) {
    // only trump. plays most valuable
    Player * ian = Player_factory("Ian", "Simple");
    Card c1(Card::RANK_KING, Card::SUIT_CLUBS);
    ian->add_card(c1);
    Card c2(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ian->add_card(c2);
    Card c3(Card::RANK_NINE, Card::SUIT_CLUBS);
    ian->add_card(c3);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    ian->add_card(c4);

    Card cardPlayed1 = ian->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed1, c4);
        
    delete ian;
    
    // some trump, some not. plays highest non-trump
    Player * dan = Player_factory("Dan", "Simple");
    Card c11(Card::RANK_KING, Card::SUIT_CLUBS);
    dan->add_card(c11);
    Card c21(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    dan->add_card(c21);
    Card c41(Card::RANK_KING, Card::SUIT_SPADES);
    dan->add_card(c41);
    Card c51(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    dan->add_card(c51);

    Card cardPlayed2 = dan->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed2, c41);
        
    delete dan;
    
    // two cards
    Player * ben = Player_factory("Ben", "Simple");
    Card c12(Card::RANK_NINE, Card::SUIT_HEARTS);
    ben->add_card(c11);
    Card c22(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ben->add_card(c21);
    
    Card cardPlayed3 = ben->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed3, c11);
        
    delete ben;
    
    // one card
    Player * ty = Player_factory("Ty", "Simple");
    Card c7(Card::RANK_TEN, Card::SUIT_SPADES);
    ty->add_card(c7);
    
    
    Card cardPlayed4 = ty->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed4, c7);
        
    delete ty;
    
    Player * stevie = Player_factory("Stevie", "Simple");
    Card c100(Card::RANK_KING, Card::SUIT_CLUBS);
    stevie->add_card(c100);
    Card c101(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    stevie->add_card(c101);
    Card c102(Card::RANK_KING, Card::SUIT_SPADES);
    stevie->add_card(c102);
    Card c103(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    stevie->add_card(c103);

    Card cardPlayed100 = stevie->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed100, c102);
        
    Card cardPlayed101 = stevie->play_card(cardPlayed100, Card::SUIT_CLUBS);
    ASSERT_EQUAL(cardPlayed101, c103)
    
    delete stevie;
    
}

// Test case for verifying function correctness
TEST(test_play_card) {
    Player * jay = Player_factory("Jay", "Simple");
    Card c51(Card::RANK_KING, Card::SUIT_DIAMONDS);
    jay->add_card(c51);
    Card c61(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    jay->add_card(c61);
    Card c71(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    jay->add_card(c71);
    Card c81(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    jay->add_card(c81);
    
    Card ledCard5(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cardPlayed5 = jay->play_card(ledCard5, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(cardPlayed5, c61);
    
    delete jay;
}

TEST_MAIN()
