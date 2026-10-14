#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_card_ctor)
{
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_get_suit)
{
    Card c(ACE, HEARTS);
    Suit trump = SPADES;
    ASSERT_EQUAL(HEARTS, c.get_suit(trump));

    Card left_bower(JACK, CLUBS);
    ASSERT_EQUAL(trump, left_bower.get_suit(trump));

    Card trump_suit(TWO, SPADES);
    ASSERT_EQUAL(trump, trump_suit.get_suit(trump));
}

TEST(test_is_face_or_ace)
{
    Card jack(JACK, SPADES);
    ASSERT_EQUAL(true, jack.is_face_or_ace());

    Card queen(QUEEN, HEARTS);
    ASSERT_EQUAL(true, queen.is_face_or_ace());

    Card king(KING, CLUBS);
    ASSERT_EQUAL(true, king.is_face_or_ace());

    Card ace(ACE, DIAMONDS);
    ASSERT_EQUAL(true, ace.is_face_or_ace());

    Card non_face(NINE, SPADES);
    ASSERT_EQUAL(false, non_face.is_face_or_ace());
}

TEST(test_bowers)
{
    Suit trump = SPADES;
    Card left_bower(JACK, CLUBS);
    ASSERT_EQUAL(true, left_bower.is_left_bower(trump));

    Card right_bower(JACK, SPADES);
    ASSERT_EQUAL(true, right_bower.is_right_bower(trump));

    Card random(ACE, DIAMONDS);
    ASSERT_EQUAL(false, random.is_left_bower(trump));
    ASSERT_EQUAL(false, random.is_right_bower(trump));
}

TEST(test_suit_next)
{
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
}

TEST(test_card_less_with_led)
{
    // one card is right bower
    Suit trump = SPADES;
    Card led_card(ACE, DIAMONDS);
    Card a(JACK, SPADES);
    Card b(NINE, HEARTS);
    ASSERT_EQUAL(false, Card_less(a, b, led_card, trump)); // first is right
    ASSERT_EQUAL(true, Card_less(b, a, led_card, trump));  // second is right

    trump = CLUBS;
    ASSERT_EQUAL(false, Card_less(a, b, led_card, trump)); // first is left
    ASSERT_EQUAL(true, Card_less(b, a, led_card, trump));  // second is left

    Card c(QUEEN, DIAMONDS);
    trump = HEARTS;
    ASSERT_EQUAL(true, Card_less(c, b, led_card, trump));  // second is trump (ISSUE HERE)
    ASSERT_EQUAL(false, Card_less(b, c, led_card, trump)); // first is trump (ISSUE HERE)

    Card d(QUEEN, HEARTS);
    ASSERT_EQUAL(false, Card_less(d, b, led_card, trump)); // first is higher trump, non led
    ASSERT_EQUAL(true, Card_less(b, d, led_card, trump));  // second is higher trump, non led

    Card f(KING, CLUBS);
    ASSERT_EQUAL(false, Card_less(f, a, led_card, trump)); // first is higher non trump
    ASSERT_EQUAL(true, Card_less(a, f, led_card, trump));  // second is higher non trump

    ASSERT_EQUAL(false, Card_less(c, a, led_card, trump)); // first is led
    ASSERT_EQUAL(true, Card_less(a, c, led_card, trump));  // second is led

    Card e(TEN, DIAMONDS);
    ASSERT_EQUAL(false, Card_less(led_card, e, led_card, trump)); // first is higher led
    ASSERT_EQUAL(true, Card_less(e, led_card, led_card, trump));  // second is higher led
}

TEST_MAIN()
