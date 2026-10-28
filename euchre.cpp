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
    team_02_pts = 0;
    team_13_pts = 0;
    dealer = 0;
    trump_suit = SPADES;
    order_up_team = 0;
    hand_number = 0;
  }

  // code that you actually call in main to run euchre
  void play()
  {
    while (team_02_pts < points_to_win && team_13_pts < points_to_win)
    {
      play_hand();
      dealer = (dealer + 1) % 4;
      ++hand_number;
    }
    if (team_02_pts >= points_to_win)
    {
      cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!\n";
    }
    else if (team_13_pts >= points_to_win)
    {
      cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!\n";
    }

    for (size_t i = 0; i < players.size(); ++i)
    {
      delete players[i];
    }
  }

private:
  vector<Player *> players;
  Pack pack;
  Suit trump_suit;
  bool shuffle_mode;
  int points_to_win;
  int team_02_pts;
  int team_13_pts;
  int dealer;
  int order_up_team;
  int hand_number;

  // this just shuffles the deck
  void shuffle()
  {
    if (shuffle_mode)
    {
      pack.shuffle();
    }
    else
      pack.reset();
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
        cout << players[left_player]->get_name() << " orders up " << trump_suit << "\n\n";
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
        cout << players[left_player]->get_name() << " orders up " << trump_suit << "\n\n";
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

  // code to evaluate the individual tricks + who wins each trick + tallies the points
  void play_tricks(int &trick_02_pts, int &trick_13_pts)
  {
    int leader = (dealer + 1) % 4;

    for (int i = 0; i < 5; ++i)
    {
      Card lead_card = players[leader]->lead_card(trump_suit);
      Card greatest_card = lead_card;
      int trick_winner = leader;

      cout << lead_card << " led by " << players[leader]->get_name() << "\n";

      for (int j = 1; j < 4; ++j)
      {
        Card comparative = players[(leader + j) % 4]->play_card(lead_card, trump_suit);
        cout << comparative << " played by " << players[(leader + j) % 4]->get_name() << "\n";

        if (Card_less(greatest_card, comparative, lead_card, trump_suit))
        {
          greatest_card = comparative;
          trick_winner = (leader + j) % 4;
        }
      }

      cout << players[trick_winner]->get_name() << " takes the trick" << "\n\n";

      if (trick_winner % 2 == 0)
      {
        ++trick_02_pts;
      }
      else
      {
        ++trick_13_pts;
      }

      leader = trick_winner;
    }
  }

  void score_tally(int &trick_02_pts, int &trick_13_pts)
  {
    if (trick_02_pts >= 3)
    {
      cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand\n";

      if (order_up_team % 2 == 0)
      {

        if (trick_02_pts == 5)
        {
          team_02_pts += 2;
          cout << "march!\n";
        }
        else
        {
          ++team_02_pts;
        }
      }
      else
      {
        team_02_pts += 2;
        cout << "euchred!\n";
      }
    }
    else
    {
      cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand\n";

      if (order_up_team % 2 == 1)
      {

        if (trick_13_pts == 5)
        {
          team_13_pts += 2;
          cout << "march!\n";
        }
        else
        {
          ++team_13_pts;
        }
      }
      else
      {
        team_13_pts += 2;
        cout << "euchred!\n";
      }
    }
  }

  // code for all the events for one hand - dealing, trump decision, tricks, and final point tallying (if someone euchred, marched, etc.)
  void play_hand()
  {
    cout << "Hand " << hand_number << "\n";
    cout << players[dealer]->get_name() << " deals\n";

    Card upcard;

    shuffle();

    deal(upcard);

    cout << upcard << " turned up\n";

    make_trump(upcard);

    int trick_02_pts = 0;
    int trick_13_pts = 0;

    play_tricks(trick_02_pts, trick_13_pts);

    score_tally(trick_02_pts, trick_13_pts);

    cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << team_02_pts << " points\n";
    cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << team_13_pts << " points\n";
  }
};

int main(int argc, char *argv[])
{
  if (argc != 12)
  {
    cout << "Usage: " << argv[0]
         << " PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 "
         << "NAME3 TYPE3 NAME4 TYPE4\n";
    return 1;
  }

  for (int i = 0; i < argc; ++i)
  {
    cout << argv[i] << " ";
  }
  cout << "\n";

  // I HATE STREAMS THEY MAKE NO SENSE (but this opens the pack file)
  ifstream pack_file(argv[1]);
  if (!pack_file.is_open())
  {
    cout << "Can't open pack file\n";
    return 1;
  }

  bool shuffle_input; // for the shuffle input
  string shuffle_yesno = argv[2];
  if (shuffle_yesno == "shuffle")
  {
    shuffle_input = true;
  }
  else if (shuffle_yesno == "noshuffle")
  {
    shuffle_input = false;
  }
  else
  {
    cout << "Shuffle command incorrect \n";
    return 1;
  }

  int points_input = stoi(argv[3]);
  if (points_input < 1 || points_input > 100)
  {
    cout << "Points are not positive\n";
    return 1;
  }

  vector<Player *> players_input; // create the players based on the input
  for (int i = 0; i < 4; ++i)
  {
    string player_name = argv[4 + (2 * i)]; // i think this logic makes sense like mathmatically...
    string player_type = argv[5 + (2 * i)];

    if (player_type != "Simple" && player_type != "Human")
    {
      cout << "Type of player invalid \n";
      return 1;
    }
    else
    {
      players_input.push_back(Player_factory(player_name, player_type));
    }
  }

  Game game(pack_file, shuffle_input, points_input, players_input);
  game.play();

  return 0;
}