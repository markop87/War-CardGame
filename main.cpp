/*
War - simple card game simulator.

The objective of the game is to win all of the cards.

The deck is divided evenly among the players, giving each a down stack.
In unison, each player reveals the top card of their deck-this is a "battle"
and the player with the higher card takes both of the cards played
and moves them to their stack. Aces are high, and suits are ignored.

If the two cards played are of equal value, then there is a "war".
Both players place the next card from their pile face down
and then another card face-up.
The owner of the higher face-up card wins the war and
adds all the cards on the table to the bottom of their deck.
If the face-up cards are again equal then the battle repeats with another set of face-down/up cards.
This repeats until one player's face-up card is higher than their opponent's.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include <conio.h>

// ESC key assignment
#define QUIT 27

// function to clear screen
void Clear()
{
    #if defined _WIN32
        system("cls"); // windows
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear"); // linux
    #elif defined (__APPLE__)
        system("clear"); // apple
    #endif
}

// struct for deck of cards
struct Deck
{
    std::string card; // card value expressed in string
    int value; // card point value
};

int main()
{
    // vector of objects for deck of cards
    // \x05 - clubs
    // \x06 - spades
    // \x04 - hearts
    // \x03 - diamonds
    std::vector <Deck> cards
    {
        { " 2\x05", 2 },
        { " 3\x05", 3 },
        { " 4\x05", 4 },
        { " 5\x05", 5 },
        { " 6\x05", 6 },
        { " 7\x05", 7 },
        { " 8\x05", 8 },
        { " 9\x05", 9 },
        { "10\x05", 10 },
        { " J\x05", 11 },
        { " Q\x05", 12 },
        { " K\x05", 13 },
        { " A\x05", 14 },
        { " 2\x06", 2 },
        { " 3\x06", 3 },
        { " 4\x06", 4 },
        { " 5\x06", 5 },
        { " 6\x06", 6 },
        { " 7\x06", 7 },
        { " 8\x06", 8 },
        { " 9\x06", 9 },
        { "10\x06", 10 },
        { " J\x06", 11 },
        { " Q\x06", 12 },
        { " K\x06", 13 },
        { " A\x06", 14 },
        { " 2\x03", 2 },
        { " 3\x03", 3 },
        { " 4\x03", 4 },
        { " 5\x03", 5 },
        { " 6\x03", 6 },
        { " 7\x03", 7 },
        { " 8\x03", 8 },
        { " 9\x03", 9 },
        { "10\x03", 10 },
        { " J\x03", 11 },
        { " Q\x03", 12 },
        { " K\x03", 13 },
        { " A\x03", 14 },
        { " 2\x04", 2 },
        { " 3\x04", 3 },
        { " 4\x04", 4 },
        { " 5\x04", 5 },
        { " 6\x04", 6 },
        { " 7\x04", 7 },
        { " 8\x04", 8 },
        { " 9\x04", 9 },
        { "10\x04", 10 },
        { " J\x04", 11 },
        { " Q\x04", 12 },
        { " K\x04", 13 },
        { " A\x04", 14 }
    };

    //shuffle vector of objects "cards"
    std::random_device rd;
    std::shuffle(cards.begin(), cards.end(), rd);

    std::queue <int> p1_cards; //queue for player 1's cards
    std::queue <int> p2_cards; //queue for player 2's cards

    // adding each even card to the first player's queue
    for(int i = 0; i < 52; i+=2)
    {
        p1_cards.push(i);
    }

    // adding every odd card to the second player's turn
    for(int i = 1; i < 53; i+=2)
    {
        p2_cards.push(i);
    }

    int round = 1; // round counter

    //game loop, that will be repeated until one player's queue is empty, that means he will lose all his cards
    while(!p1_cards.empty() && !p2_cards.empty())
    {
        // displaying how many cards players have left
        std::cout << "\nP1 cards left: " << p1_cards.size();
        std::cout << "\nP2 cards left: " << p2_cards.size();

        int key = 0; // Variable for storing the pressed key

        // displaying instructions for the player
        std::cout << "\n\nPress any key to continue or ESC to quit.\n";

        // when you press the ESC key, the game closes
        // if any other key is pressed, the game continues
        switch(key = getch())
        {
            case QUIT:
                return 0;
                break;

            default:
                Clear(); // screen cleaning
                break;
        }

        // displaying the current round
        std::cout << "Round " << round;

        // displaying the card played that is the first in players' queues
        std::cout << "\n\n" << cards[p1_cards.front()].card << " vs " << cards[p2_cards.front()].card;

        // when player 1's card has a higher value than player 2's card
        if(cards[p1_cards.front()].value > cards[p2_cards.front()].value)
        {
            std::cout << "\n\nPlayer 1 won!\n";

            // adding both cards to the end of the first player's queue
            p1_cards.push(p1_cards.front());
            p1_cards.push(p2_cards.front());

            // removing played cards from the queue
            p1_cards.pop();
            p2_cards.pop();
        }
        // when player 2's card has a higher value than player 1's card
        else if(cards[p1_cards.front()].value < cards[p2_cards.front()].value)
        {
            std::cout << "\n\nPlayer 2 won!\n";

            // adding both cards to the end of the second player's queue
            p2_cards.push(p2_cards.front());
            p2_cards.push(p1_cards.front());

            // removing played cards from the queue
            p1_cards.pop();
            p2_cards.pop();
        }
        // when there is a tie
        else if (cards[p1_cards.front()].value == cards[p2_cards.front()].value && p1_cards.size() > 3 && p2_cards.size() > 3)
        {
            std::cout << " - War!\n"; // note for a draw

            std::queue <int> war; // new queue for storing played cards

            // adding played cards to a war queue
            war.push(p1_cards.front());
            war.push(p2_cards.front());

            // loop for playing the war
            // this repeats until one player's face-up card is higher than their opponent's
            while(cards[p1_cards.front()].value == cards[p2_cards.front()].value)
            {
                // removing previously played cards from the players queue
                p1_cards.pop();
                p2_cards.pop();

                // cards over which the war will be fought
                std::cout << cards[p1_cards.front()].card << " vs " << cards[p2_cards.front()].card << "\n";

                // adding those card to a war queue
                war.push(p1_cards.front());
                war.push(p2_cards.front());

                // removing cards from the players queue
                p1_cards.pop();
                p2_cards.pop();

                // cards that decide the fate of the war
                std::cout << cards[p1_cards.front()].card << " vs " << cards[p2_cards.front()].card << "\n";

                // adding those card to a war queue
                war.push(p1_cards.front());
                war.push(p2_cards.front());

                // if player 1's card is higher, the cards from the war queue will be transferred to his turn
                if(cards[p1_cards.front()].value > cards[p2_cards.front()].value)
                {
                    std::cout << "\nPlayer 1 won!\n";

                    while(!war.empty())
                    {
                        p1_cards.push(war.front());
                        war.pop();
                    }
                }
                // if player 2's card is higher, the cards from the war queue will be transferred to his turn
                if(cards[p1_cards.front()].value < cards[p2_cards.front()].value)
                {
                    std::cout << "\nPlayer 2 won!\n";

                    while(!war.empty())
                    {
                        p2_cards.push(war.front());
                        war.pop();
                    }
                }

            }

            // removing previously played cards from the players queue
            p1_cards.pop();
            p2_cards.pop();
        }
        // when there is a tie but player 1 has too few cards for war
        else if(cards[p1_cards.front()].value == cards[p2_cards.front()].value && p1_cards.size() < 3)
        {
            std::cout << "Player 1 doesn't have enough cards!\nPlayer 2 won the war!\n";
            return 0;
        }
        // when there is a tie but player 2 has too few cards for war
        else if(cards[p1_cards.front()].value == cards[p2_cards.front()].value && p2_cards.size() < 3)
        {
            std::cout << "Player 2 doesn't have enough cards!\nPlayer 1 won the war!\n";
            return 0;
        }

        round++; // increasing the round counter
    }

    return 0;
}
