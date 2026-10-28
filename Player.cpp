#include "Card.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class SimplePlayer : public Player
{
private:
    std::vector<Card> hand;
    std::string name;

public:
    SimplePlayer(const std::string &name_in)
    {
        name = name_in;
    }

    // EFFECTS returns player's name
    const std::string &get_name() const override
    {
        return name;
    }

    // REQUIRES player has less than MAX_HAND_SIZE cards
    // EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override
    {
        hand.push_back(c);
    }

    // REQUIRES round is 1 or 2
    // MODIFIES order_up_suit
    // EFFECTS If Player wishes to order up a trump suit then return true and
    //   change order_up_suit to desired suit.  If Player wishes to pass, then do
    //   not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override
    {
        Suit upsuit = upcard.get_suit();
        Suit nextsuit = Suit_next(upsuit);
        int counter = 0;

        if (round == 1)
        {
            for (int i = 0; i < hand.size(); ++i)
            {
                if (hand[i].is_left_bower(upsuit))
                {
                    ++counter;
                }
                else if (hand[i].get_suit() == upsuit && hand[i].is_face_or_ace())
                {
                    ++counter;
                }
            }
            if (counter >= 2)
            {
                order_up_suit = upsuit;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (is_dealer == true)
            {
                order_up_suit = nextsuit;
                return true;
            }
            else
            {
                for (int i = 0; i < hand.size(); ++i)
                {
                    if (hand[i].is_left_bower(nextsuit))
                    {
                        ++counter;
                    }
                    else if (hand[i].get_suit() == nextsuit && hand[i].is_face_or_ace())
                    {
                        ++counter;
                    }
                }
                if (counter >= 1)
                {
                    order_up_suit = nextsuit;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override
    {
        Suit trump_suit = upcard.get_suit();
        Card lowest_card = upcard;
        int index_of_lowest = 0;

        for (int i = 0; i < hand.size(); ++i)
        {
            if (Card_less(hand[i], lowest_card, trump_suit))
            {
                lowest_card = hand[i];
                index_of_lowest = i;
            }
        }

        if (lowest_card != upcard)
        {
            hand[index_of_lowest] = upcard;
        }
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Leads one Card from Player's hand according to their strategy
    //   "Lead" means to play the first Card in a trick.  The card
    //   is removed the player's hand.
    Card lead_card(Suit trump) override
    {
        Card lead_card = hand[0];
        int trump_counter = 0;
        int index_of_highest = 0;

        for (int k = 0; k < hand.size(); ++k)
        {
            if (hand[k].get_suit(trump) != trump)
            {
                if (lead_card.get_suit(trump) == trump)
                {
                    lead_card = hand[k];
                    index_of_highest = k;
                }
                else if (!Card_less(hand[k], lead_card, trump))
                {
                    lead_card = hand[k];
                    index_of_highest = k;
                }
            }
            else
            {
                ++trump_counter;
            }
        }

        if (trump_counter == hand.size())
        {
            for (int j = 0; j < hand.size(); ++j)
            {
                if (Card_less(lead_card, hand[j], trump))
                {
                    lead_card = hand[j];
                    index_of_highest = j;
                }
            }
        }

        hand.erase(hand.begin() + index_of_highest);
        return lead_card;
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Plays one Card from Player's hand according to their strategy.
    //   The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override
    {
        int index_of_removed = 0;
        Card removed_card = hand[0];
        Suit led_suit = led_card.get_suit(trump);

        for (int i = 0; i < hand.size(); ++i)
        {
            if (removed_card.get_suit(trump) == led_suit)
            {
                if (hand[i].get_suit(trump) == led_suit)
                {
                    if (Card_less(removed_card, hand[i], trump))
                    {
                        removed_card = hand[i];
                        index_of_removed = i;
                    }
                }
            }
            else
            {
                if (hand[i].get_suit(trump) == led_suit)
                {
                    removed_card = hand[i];
                    index_of_removed = i;
                }
                else
                {
                    if (Card_less(hand[i], removed_card, trump))
                    {
                        removed_card = hand[i];
                        index_of_removed = i;
                    }
                }
            }
        }

        hand.erase(hand.begin() + index_of_removed);
        return removed_card;
    }
};
class HumanPlayer : public Player
{
private:
    std::vector<Card> hand;
    std::string name;

public:
    HumanPlayer(const std::string &name_in)
    {
        name = name_in;
    }

    void print_hand() const
    {
        for (size_t i = 0; i < hand.size(); ++i)
        {
            cout << "Human player " << name << "'s hand: "
                 << "[" << i << "] " << hand[i] << "\n";
        }
    }

    const std::string &get_name() const override
    {
        return name;
    }

    void add_card(const Card &c) override
    {
        hand.push_back(c);
        sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override
    {
        print_hand();
        string decision;

        if (round == 1)
        {
            cout << "Human player " << name << ", please enter a pass, or \"order up\":\n";
            cin >> decision;

            if (decision != "pass")
            {
                string up;
                cin >> up;
                order_up_suit = upcard.get_suit();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
            cin >> decision;

            if (decision != "pass")
            {
                order_up_suit = string_to_suit(decision);
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override
    {
        print_hand();

        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";

        int discard_card_index;
        cin >> discard_card_index;

        if (discard_card_index != -1)
        {
            hand.erase(hand.begin() + discard_card_index);
            hand.push_back(upcard);
            sort(hand.begin(), hand.end());
        }
    }

    Card lead_card(Suit trump) override
    {
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";

        int removed_card_index;
        cin >> removed_card_index;

        Card removed_card = hand[removed_card_index];

        hand.erase(hand.begin() + removed_card_index);

        return removed_card;
    }

    Card play_card(const Card &led_card, Suit trump) override
    {
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";

        int removed_card_index;
        cin >> removed_card_index;

        Card removed_card = hand[removed_card_index];

        hand.erase(hand.begin() + removed_card_index);

        return removed_card;
    }
};

// EFFECTS: Returns a pointer to a player with the given name and strategy
// To create an object that won't go out of scope when the function returns,
// use "return new Simple(name)" or "return new Human(name)"
// Don't forget to call "delete" on each Player* after the game is over
Player *Player_factory(const std::string &name, const std::string &strategy)
{
    if (strategy == "Simple")
    {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    else if (strategy == "Human")
    {
        return new HumanPlayer(name);
    }
    // Repeat for each other type of Player
    // Invalid strategy if we get here
    assert(false);
    return nullptr;
}

// EFFECTS: Prints player's name to os
std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << p.get_name();
    return os;
}