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
    amani->add_card(Card(TEN, DIAMONDS));
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

//add and discard tests


TEST(add_and_discard_normal)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand
    amani->add_card(Card(NINE, DIAMONDS));
    amani->add_card(Card(TEN, DIAMONDS));
    amani->add_card(Card(QUEEN, DIAMONDS));
    amani->add_card(Card(KING, DIAMONDS));
    amani->add_card(Card(ACE, DIAMONDS));

    Card upcard = Card(TEN, HEARTS);

    amani->add_and_discard(upcard);

    //these would be the non trump cards that would leave in order from highest to lowest first
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(ACE, DIAMONDS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(KING, DIAMONDS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(QUEEN, DIAMONDS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(TEN, DIAMONDS));

    //the upcard shouldve been kept and then the nine of diamonds should have been discarded and thus not present bc this is trump
    ASSERT_EQUAL(amani->lead_card(HEARTS), upcard);

    delete amani;
}

TEST(add_and_discard_discard_upcard)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand
    amani->add_card(Card(JACK, HEARTS));
    amani->add_card(Card(TEN, HEARTS));
    amani->add_card(Card(QUEEN, HEARTS));
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, HEARTS));

    Card upcard = Card(NINE, HEARTS);

    amani->add_and_discard(upcard);

    //these would be the  trump cards that would leave in order from highest to lowest first - the nine of hearts should never enter
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(JACK, HEARTS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(ACE, HEARTS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(KING, HEARTS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(QUEEN, HEARTS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(TEN,HEARTS));

    delete amani;
}

TEST(add_and_discard_keep_left_bower)
{
    Player *amani = Player_factory("Amani", "Simple");

    //hand

    //left bower
    amani->add_card(Card(JACK, DIAMONDS));
    amani->add_card(Card(JACK, HEARTS));
    amani->add_card(Card(QUEEN, HEARTS));
    amani->add_card(Card(KING, HEARTS));
    amani->add_card(Card(ACE, HEARTS));

    Card upcard = Card(TEN, HEARTS);

    //upcard wont be picked up because its the smallest - just want to make sure that left bower ranks where it should
    amani->add_and_discard(upcard);

    //these would be the trump cards that would leave in order from highest to lowest first - including rank of left bower
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(JACK, HEARTS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(JACK, DIAMONDS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(ACE, HEARTS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(KING, HEARTS));
    ASSERT_EQUAL(amani->lead_card(HEARTS), Card(QUEEN, HEARTS));

    delete amani;
}

//lead_card tests

TEST(test_lead_card_all_trump) {

  Player *amani = Player_factory("Amani", "Simple");
  
  //hand
  amani->add_card(Card(NINE, HEARTS));
  amani->add_card(Card(TEN, HEARTS));
  amani->add_card(Card(JACK, HEARTS));
  amani->add_card(Card(QUEEN, HEARTS));
  amani->add_card(Card(KING, HEARTS)); 

  Card card_led = amani->lead_card(HEARTS);

  // highest trump should lead
  ASSERT_EQUAL(card_led, Card(JACK, HEARTS));

  delete amani;
}

TEST(test_lead_card_all_trump_left_bower) {

  Player *amani = Player_factory("Amani", "Simple");

  //hand
  amani->add_card(Card(NINE, HEARTS));
  amani->add_card(Card(TEN, HEARTS));
  //left bower, the one to be removed
  amani->add_card(Card(JACK, DIAMONDS));
  amani->add_card(Card(QUEEN, HEARTS));
  amani->add_card(Card(KING, HEARTS)); 

  Card card_led = amani->lead_card(HEARTS);

  // highest trump should lead
  ASSERT_EQUAL(card_led, Card(JACK, DIAMONDS));

  delete amani;
}

TEST(test_lead_card_all_non_trump_except_left_bower) {

  Player *amani = Player_factory("Amani", "Simple");
  amani->add_card(Card(NINE, SPADES));
  amani->add_card(Card(TEN, SPADES));
  //left bower, should not be removed
  amani->add_card(Card(JACK, SPADES));
  amani->add_card(Card(QUEEN, SPADES));
  amani->add_card(Card(KING, SPADES)); 

  Card card_led = amani->lead_card(CLUBS);

  // highest non-trump should lead
  ASSERT_EQUAL(card_led, Card(KING, SPADES));

  delete amani;
}

TEST(test_lead_card_mix_of_trump_and_non_trump) {

  Player *amani = Player_factory("Amani", "Simple");
  
  //hand
  amani->add_card(Card(NINE, SPADES));
  amani->add_card(Card(TEN, HEARTS));
  amani->add_card(Card(JACK, CLUBS));
  amani->add_card(Card(QUEEN, CLUBS));
  //should be removed
  amani->add_card(Card(KING, SPADES)); 

  Card card_led = amani->lead_card(CLUBS);

  // highest non-trump should lead
  ASSERT_EQUAL(card_led, Card(KING, SPADES));

  delete amani;
}

TEST(test_lead_card_all_non_trump) {

  Player *amani = Player_factory("Amani", "Simple");

  //hand
  amani->add_card(Card(NINE, CLUBS));
  amani->add_card(Card(TEN, CLUBS));
  amani->add_card(Card(JACK, CLUBS));
  amani->add_card(Card(QUEEN, CLUBS));
  //should be removed
  amani->add_card(Card(KING, CLUBS)); 

  Card card_led = amani->lead_card(HEARTS);

  // highest non-trump should lead
  ASSERT_EQUAL(card_led, Card(KING, CLUBS));

  delete amani;
}

//play_card tests

TEST(test_play_card_follow_suit) 
{
  Player *amani = Player_factory("Amani", "Simple");

  //hand
  amani->add_card(Card(NINE, SPADES));
  amani->add_card(Card(TEN, SPADES));
  amani->add_card(Card(QUEEN, SPADES));
  amani->add_card(Card(NINE, CLUBS));
  amani->add_card(Card(TEN, CLUBS));

  Card led_card(KING, SPADES);
  Card card_played = amani->play_card(led_card, HEARTS);

  ASSERT_EQUAL(card_played, Card(QUEEN, SPADES));
  delete amani;
}

TEST(test_play_card_lowest_in_hand_standard) 
{
  Player *amani = Player_factory("Amani", "Simple");

  //hand
  amani->add_card(Card(NINE, SPADES));
  amani->add_card(Card(TEN, SPADES));
  amani->add_card(Card(QUEEN, SPADES));
  amani->add_card(Card(JACK, CLUBS));
  amani->add_card(Card(TEN, CLUBS));

  Card led_card(KING, HEARTS);
  Card card_played = amani->play_card(led_card, DIAMONDS);

  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete amani;
}

TEST(test_play_card_follow_suit_left_bower) 
{
  Player *amani = Player_factory("Amani", "Simple");

  //hand
  amani->add_card(Card(NINE, SPADES));
  amani->add_card(Card(TEN, SPADES));
  amani->add_card(Card(QUEEN, SPADES));
  amani->add_card(Card(ACE, SPADES));
  amani->add_card(Card(JACK, CLUBS));

  Card led_card(KING, SPADES);
  Card card_played = amani->play_card(led_card, SPADES);

  ASSERT_EQUAL(card_played, Card(JACK, CLUBS));
  delete amani;
}

TEST(test_play_card_lowest_card_left_bower) 
{
  Player *amani = Player_factory("Amani", "Simple");

  //hand
  amani->add_card(Card(ACE, SPADES));
  amani->add_card(Card(KING, SPADES));
  amani->add_card(Card(QUEEN, SPADES));
  //left bower, highest value
  amani->add_card(Card(JACK, DIAMONDS));
  amani->add_card(Card(KING, DIAMONDS));

  Card led_card(KING, CLUBS);
  Card card_played = amani->play_card(led_card, HEARTS);

  ASSERT_EQUAL(card_played, Card(QUEEN, SPADES));
  delete amani;
}

TEST_MAIN()
