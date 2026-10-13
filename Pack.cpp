#include "Card.hpp"
#include "Pack.hpp"
#include <array>
#include <string>

Pack::Pack()
{

    Pack pack[24];

    for (int s = SPADES; s <= DIAMONDS; ++s)
    {
        Suit suit = static_cast<Suit>(s);
        for (int r = NINE; r <= ACE; ++r)
        {
            Rank rank = static_cast<Rank>(r);
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream &pack_input);

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one();

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset();

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle();

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const;