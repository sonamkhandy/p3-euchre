#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

class Game
{
public:
  Game(istream &pack_file, bool shuffle_input, int points_input, vector<Player *> &players_input)
  {
    pack = Pack(pack_file);
    shuffle_mode = shuffle_input;
    points_to_win = points_input;
    players = players_input;
    team_0_pts = 0;
    team_1_pts = 0;
    dealer = 0;
    trump_suit = SPADES;
  }

  void play();

private:
  vector<Player *> players;
  Pack pack;
  Suit trump_suit;
  bool shuffle_mode;
  int points_to_win;
  int team_0_pts;
  int team_1_pts;
  int dealer;
  int order_up_team;

  // this just shuffles the deck
  void shuffle()
  {
    pack.shuffle();
  }

  // this would be the code to set up the start of the game - like all the cards the players have + the upcard
  void deal(Card &upcard)
  {
    int left_player = (dealer + 1) % 4;

    vector<int> deal_sizes = {3, 2, 3, 2, 2, 3, 2, 3};

    for (int i = 0; i < 8; ++i)
    {
      int num_of_cards = deal_sizes[i];

      for (int j = 0; j < num_of_cards; j++)
      {
        players[left_player]->add_card(pack.deal_one());
      }

      left_player = (left_player + 1) % 4;
    }

    upcard = pack.deal_one();
  }

  // handles make trump for the game including dealer and such around the table - use make trump from player classes
  void make_trump(Card &upcard)
  {
    int left_player = (dealer + 1) % 4;

    for (int i = 0; i < 4; ++i)
    {
      bool is_dealer = (left_player == dealer);

      if (players[left_player]->make_trump(upcard, is_dealer, 1, trump_suit))
      {
        cout << players[left_player]->get_name() << " orders up " << trump_suit << endl;
        players[dealer]->add_and_discard(upcard);
        order_up_team = left_player % 2;
        return;
      }

      else
      {
        cout << players[left_player]->get_name() << " passes" << endl;
        left_player = (left_player + 1) % 4;
      }
    }

    for (int i = 0; i < 4; ++i)
    {
      bool is_dealer = (left_player == dealer);

      if (players[left_player]->make_trump(upcard, is_dealer, 2, trump_suit))
      {
        cout << players[left_player]->get_name() << " orders up " << trump_suit << endl;
        order_up_team = left_player % 2;
        return;
      }
      else
      {
        cout << players[left_player]->get_name() << " passes" << endl;
        left_player = (left_player + 1) % 4;
      }
    }
  }

  // code for the 5 tricks + score tallying
  void play_hand();
};

int main(int argc, char *argv[])
{

  if (argc != 12)
  {
    std::cout << "Usage: " << argv[0]
              << " PACK_FILENAME [shuffle|noshuffle] "
              << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 "
              << "NAME3 TYPE3 NAME4 TYPE4\n";
    return 1;
  }
}