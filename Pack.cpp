#include "Card.hpp"
#include "Pack.hpp"
#include <array>
#include <string>

Pack::Pack()
{
    int i = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s)
    {
        Suit suit = static_cast<Suit>(s);
        for (int r = NINE; r <= ACE; ++r)
        {
            Rank rank = static_cast<Rank>(r);
            cards[i] = Card(rank, suit);
            ++i;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream &pack_input)
{
    for (int i = 0; i < 24; ++i)
    {
        Card tempcard;
        operator>>(pack_input, tempcard);
        cards[i] = tempcard;
    }
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one()
{
    ++next;
    Card tempcard = cards[next - 1];
    int index = 24 - next;
    std::array<Card, index> temparray;
    for (int i = 1;)
        return tempcard;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset()
{
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle()
{
    for (int rheasucks = 0; rheasucks < 7; ++rheasucks)
    {
        std::array<Card, 12> half1;
        std::array<Card, 12> half2;
        for (int i = 0; i < 12; ++i)
        {
            half1[i] = cards[i];
        }
        for (int i = 12; i < 24; ++i)
        {
            half2[i] = cards[i];
        }
        for (int i = 0; i < 24; ++i)
        {
            if (i % 2 == 0)
            {
                cards[i] = half2[i / 2];
            }
            else
            {
                cards[i] = half1[(i + 1) / 2];
            }
        }
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const
{
}