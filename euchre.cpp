#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;


class Game {
  public:
  
    Game();

    void play();

  private:
    vector<Player*> players;
    Pack pack;
  

    void shuffle();

    void deal();

    void make_trump();

    void play_hand();

};


int main(int argc, char *argv[]) {

  if (argc != 12) {
    std::cout << "Usage: " << argv[0] 
              << " PACK_FILENAME [shuffle|noshuffle] "
              << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 "
              << "NAME3 TYPE3 NAME4 TYPE4\n";
    return 1;
  }




  
}