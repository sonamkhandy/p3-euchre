#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name)
{
    Player *alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_add_card_normal)
{
    Player *amani = Player_factory("Amani", "Simple");

    Card added = Card(ACE, SPADES);
    amani->add_card(added);

    //lead card has to be the first card cause there is only one card so it should be equal no matter what
    Card play_card = amani->lead_card(HEARTS);

    ASSERT_EQUAL(added, play_card);

    delete amani;

}

// make trump test cases


//round 1 logic
TEST(test_make_trump_r1_trump_made_left_bower)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //left_bower
    amani->add_card(Card(JACK, DIAMONDS));
    amani->add_card(Card(TEN, DIAMONDS));
    //other face card
    amani->add_card(Card(QUEEN, HEARTS));
    amani->add_card(Card(KING, SPADES));
    amani->add_card(Card(ACE, SPADES));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //first round, dealer/no dealer doesn't matter
    bool order_up = amani->make_trump(upcard, false, 1, order_up_suit);

    ASSERT_EQUAL(true, order_up);
    ASSERT_EQUAL(HEARTS, order_up_suit);

    delete amani;
}

TEST(test_make_trump_r1_trump_made_normal)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //face card 1
    amani->add_card(Card(JACK, HEARTS));
    amani->add_card(Card(TEN, DIAMONDS));
    //face card 2
    amani->add_card(Card(QUEEN, HEARTS));
    //face card 3
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, SPADES));

    //
    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //first round, dealer/no dealer doesn't matter
    bool order_up = amani->make_trump(upcard, false, 1, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(true, order_up);
    //if order_up was changed correctly
    ASSERT_EQUAL(HEARTS, order_up_suit)

    delete amani;
}

TEST(test_make_trump_r1_2_cards_exact)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //face card 1
    amani->add_card(Card(JACK, HEARTS));
    amani->add_card(Card(TEN, DIAMONDS));
    //face card 2
    amani->add_card(Card(QUEEN, HEARTS));
    amani->add_card(Card(KING, SPADES));
    amani->add_card(Card(ACE, SPADES));

    //
    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //first round, dealer/no dealer doesn't matter
    bool order_up = amani->make_trump(upcard, false, 1, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(true, order_up);
    //if order_up was changed correctly
    ASSERT_EQUAL(HEARTS, order_up_suit)

    delete amani;
}

//makes sure the dealer being true instead of false doesnt change anything if its round 1
TEST(test_make_trump_r1_normal_dealer_true)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //face card 1
    amani->add_card(Card(JACK, HEARTS));
    amani->add_card(Card(TEN, DIAMONDS));
    //face card 2
    amani->add_card(Card(QUEEN, HEARTS));
    //face card 3
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, SPADES));

    //
    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //first round, dealer/no dealer doesn't matter
    bool order_up = amani->make_trump(upcard, true, 1, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(true, order_up);
    //if order_up was changed correctly
    ASSERT_EQUAL(HEARTS, order_up_suit)

    delete amani;
}

TEST(test_make_trump_r1_trump_not_made_normal)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    amani->add_card(Card(JACK, HEARTS));
    amani->add_card(Card(TEN, DIAMONDS));
    amani->add_card(Card(QUEEN, DIAMONDS));
    amani->add_card(Card(KING, SPADES));
    amani->add_card(Card(ACE, SPADES));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //first round, dealer/no dealer doesn't matter
    bool order_up = amani->make_trump(upcard, false, 1, order_up_suit);

    ASSERT_EQUAL(false, order_up);

    ASSERT_EQUAL(SPADES, order_up_suit);

    delete amani;
}

TEST(test_make_trump_r1_number_card_of_upsuit)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //nine of upcard suit
    amani->add_card(Card(NINE, HEARTS));
    //ten of upcard suit
    amani->add_card(Card(TEN, HEARTS));
    amani->add_card(Card(QUEEN, SPADES));
    amani->add_card(Card(KING, SPADES));
    amani->add_card(Card(ACE, SPADES));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //first round, dealer/no dealer doesn't matter
    bool order_up = amani->make_trump(upcard, false, 1, order_up_suit);

    ASSERT_EQUAL(false, order_up);

    ASSERT_EQUAL(SPADES, order_up_suit);

    delete amani;
}

// round 2 logic
// dealer true 
TEST(test_make_trump_r2_dealer_true)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //all not face cards of upcard to ensure that specific logic is working
    amani->add_card(Card(JACK, SPADES));
    amani->add_card(Card(TEN, SPADES));
    amani->add_card(Card(QUEEN, SPADES));
    amani->add_card(Card(KING, SPADES));
    amani->add_card(Card(ACE, SPADES));

    //
    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //second round, dealer matters
    bool order_up = amani->make_trump(upcard, true, 2, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(true, order_up);
    //if order_up was changed correctly - needs to be the suit with the same color as the upcard, not the same suit as the upcard
    ASSERT_EQUAL(DIAMONDS, order_up_suit)

    delete amani;
}


//rest of these is dealer = false bc then its just simple player logic
TEST(test_make_trump_r2_trump_made_normal)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //face card one
    amani->add_card(Card(JACK, DIAMONDS));
    amani->add_card(Card(TEN, SPADES));
    //face card two
    amani->add_card(Card(QUEEN, DIAMONDS));
    //face card three
    amani->add_card(Card(KING, DIAMONDS));
    amani->add_card(Card(ACE, SPADES));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //second round, dealer matters but make false to check other logic
    bool order_up = amani->make_trump(upcard, false, 2, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(true, order_up);
    //if order_up was changed correctly - needs to be the suit with the same color as the upcard, not the same suit as the upcard
    ASSERT_EQUAL(DIAMONDS, order_up_suit)

    delete amani;
}

TEST(test_make_trump_r2_trump_made_exact_one)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //face card one
    amani->add_card(Card(JACK, DIAMONDS));
    amani->add_card(Card(TEN, SPADES));
    amani->add_card(Card(QUEEN, SPADES));
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, SPADES));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //second round, dealer matters but make false to check other logic
    bool order_up = amani->make_trump(upcard, false, 2, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(true, order_up);
    //if order_up was changed correctly - needs to be the suit with the same color as the upcard, not the same suit as the upcard
    ASSERT_EQUAL(DIAMONDS, order_up_suit)

    delete amani;
}

TEST(test_make_trump_r2_trump_made_left_bower)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //left bower
    amani->add_card(Card(JACK, HEARTS));
    amani->add_card(Card(TEN, SPADES));
    amani->add_card(Card(QUEEN, SPADES));
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, SPADES));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //second round, dealer matters but make false to check other logic
    bool order_up = amani->make_trump(upcard, false, 2, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(true, order_up);
    //if order_up was changed correctly - needs to be the suit with the same color as the upcard, not the same suit as the upcard
    ASSERT_EQUAL(DIAMONDS, order_up_suit)

    delete amani;
}

TEST(test_make_trump_r2_non_face_cards_of_trump)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //left bower
    amani->add_card(Card(NINE, DIAMONDS));
    amani->add_card(Card(TEN, DIAMONDS));
    amani->add_card(Card(QUEEN, SPADES));
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, SPADES));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //second round, dealer matters but make false to check other logic
    bool order_up = amani->make_trump(upcard, false, 2, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(false, order_up);
    //if order_up was changed correctly - needs to be the suit with the same color as the upcard, not the same suit as the upcard
    ASSERT_EQUAL(SPADES, order_up_suit)

    delete amani;
}

//tests that the code isn't accidentally checking for the suit of the upcard instead of the next suit
TEST(test_make_trump_r2_trump_not_made_suit_of_upcard_instead_of_next_suit)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand
    amani->add_card(Card(NINE, HEARTS));
    amani->add_card(Card(TEN, HEARTS));
    amani->add_card(Card(QUEEN, HEARTS));
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, HEARTS));

    Card upcard = Card(TEN, HEARTS);
    
    //status-quo
    Suit order_up_suit = SPADES;

    //second round, dealer matters but make false to check other logic
    bool order_up = amani->make_trump(upcard, false, 2, order_up_suit);

    //if trump was made
    ASSERT_EQUAL(false, order_up);
    //if order_up was changed correctly - needs to be the suit with the same color as the upcard, not the same suit as the upcard
    ASSERT_EQUAL(SPADES, order_up_suit)

    delete amani;
}




TEST_MAIN()
