#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>

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
        // displaying the current round
        std::cout << "Round " << round << "\n";

        // displaying how many cards players have left
        std::cout << "\nP1 cards left: " << p1_cards.size();
        std::cout << "\nP2 cards left: " << p2_cards.size();

        // displaying the card played that is the first in players' queues
        std::cout << "\n\n" << cards[p1_cards.front()].card << " vs " << cards[p2_cards.front()].card;

        round++; // increasing the round counter
    }

    return 0;
}
