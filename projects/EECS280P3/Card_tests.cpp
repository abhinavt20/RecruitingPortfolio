// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <ostream>

using namespace std;


// Test case for verifying function correctness
TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Test case for verifying function correctness
TEST(test_constructor) {
    Card c1;
    ASSERT_EQUAL(Card::RANK_TWO, c1.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c1.get_suit());
}

// Test case for verifying function correctness
TEST(test_get_suit_trump) {
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(trump, c2.get_suit(trump));
}

// Test case for verifying function correctness
TEST(test_is_face) {
    Card c3(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_THREE, Card::SUIT_HEARTS);
    assert(c3.is_face());
    assert(c4.is_face() == false);
}

// Test case for verifying function correctness
TEST(test_is_right_bower) {
    Card c5(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    assert(c5.is_right_bower(trump));
    
    Card c6(Card::RANK_JACK, Card::SUIT_CLUBS);
    trump = Card::SUIT_SPADES;
    assert(c6.is_right_bower(trump) == false);
    
}

// Test case for verifying function correctness
TEST(test_is_left_bower) {
    Card c7(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_CLUBS;
    assert(c7.is_left_bower(trump));
    
    Card c8(Card::RANK_JACK, Card::SUIT_HEARTS);
    trump = Card::SUIT_CLUBS;
    assert(c8.is_left_bower(trump) == false);
}

// Test case for verifying function correctness
TEST(test_is_trump) {
    Card c9(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_CLUBS;
    assert(c9.is_trump(trump));
    
    Card c10(Card::RANK_NINE, Card::SUIT_SPADES);
    trump = Card::SUIT_CLUBS;
    assert(c10.is_trump(trump) == false);
    
    Card c11(Card::RANK_KING, Card::SUIT_SPADES);
    trump = Card::SUIT_SPADES;
    assert(c11.is_trump(trump));
}

// Test case for verifying function correctness
TEST(test_operators) {
    Card c12(Card::RANK_SEVEN, Card::SUIT_HEARTS);
    Card c13(Card::RANK_NINE, Card::SUIT_HEARTS);
    assert(c12 < c13);
    
    Card c14(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c15(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    assert(c14 < c15);
    
    Card c16(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c17(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    assert(c16 > c17);
    
    Card c18(Card::RANK_KING, Card::SUIT_SPADES);
    Card c19(Card::RANK_KING, Card::SUIT_SPADES);
    assert(c18 == c19);
    assert((c18 > c18) == false);
    assert(c18 >= c18);
    assert((c18 < c18) == false);
    assert(c18 <= c18);
    assert((c18 != c18) == false);
    assert(c18 == c18);

}

// Test case for verifying function correctness
TEST(test_suit_next) {
    string suit1 = Card::SUIT_DIAMONDS;
    assert(Suit_next(suit1) == Card::SUIT_HEARTS);
    
    string suit2 = Card::SUIT_SPADES;
    assert(Suit_next(suit2) == Card::SUIT_CLUBS);
}

// Test case for verifying function correctness
TEST(test_print) {
    ostringstream os;
    ostringstream osExpected;
    Card c20(Card::RANK_KING, Card::SUIT_SPADES);
    osExpected << "King of Spades";
    os << c20;
    ASSERT_EQUAL(os.str(), osExpected.str());
}

// Test case for verifying function correctness
TEST(test_card_less_1) {
    string trump = Card::SUIT_DIAMONDS;
    
    Card c21(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c22(Card::RANK_NINE, Card::SUIT_CLUBS);
    assert(Card_less(c21, c22, trump) == false);
    
    Card c23(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c24(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    assert(Card_less(c23, c24, trump) == false);
    
    Card c25(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c26(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    assert(Card_less(c25, c26, trump));
    
    Card c27(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c28(Card::RANK_NINE, Card::SUIT_SPADES);
    assert(Card_less(c27, c28, trump) == false);
    
}

// Test case for verifying function correctness
TEST(test_card_less_with_led) {
    string trump = Card::SUIT_DIAMONDS;
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
    string ledCardSuit = led_card.get_suit();
    
    Card c29(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c30(Card::RANK_NINE, Card::SUIT_SPADES);
    assert(Card_less(c29, c30, led_card, trump) == false);
    
    Card c31(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card c32(Card::RANK_SIX, Card::SUIT_SPADES);
    assert(Card_less(c31, c32, led_card, trump) == false);
    
    Card c33(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c34(Card::RANK_NINE, Card::SUIT_HEARTS);
    assert(Card_less(c33, c34, led_card, trump) == false);
    
    Card c35(Card::RANK_TWO, Card::SUIT_CLUBS);
    Card c36(Card::RANK_THREE, Card::SUIT_HEARTS);
    assert(Card_less(c35, c36, led_card, trump));
}


TEST_MAIN()

