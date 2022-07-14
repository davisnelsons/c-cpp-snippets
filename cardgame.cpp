#include <iostream>
#include <array>
#include <iterator>  // std::begin(), std::end(); required for C-arrays
#include <random>    // std::mt19937; needed to feed std::shuffle()
#include <algorithm>
#include <fstream>
#include <numeric>

enum class CardSuit
{
    club,
    diamond,
    heart,
    spade,

    max_suits
};

enum class CardRank
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace,

    max_ranks
};

struct Card
{
  CardRank rank{};
  CardSuit suit{};
};

void printCard(const Card card) {
    switch (card.rank)
    {
    case CardRank::rank_2:      std::cout << '2';   break;
    case CardRank::rank_3:      std::cout << '3';   break;
    case CardRank::rank_4:      std::cout << '4';   break;
    case CardRank::rank_5:      std::cout << '5';   break;
    case CardRank::rank_6:      std::cout << '6';   break;
    case CardRank::rank_7:      std::cout << '7';   break;
    case CardRank::rank_8:      std::cout << '8';   break;
    case CardRank::rank_9:      std::cout << '9';   break;
    case CardRank::rank_10:     std::cout << 'T';   break;
    case CardRank::rank_jack:   std::cout << 'J';   break;
    case CardRank::rank_queen:  std::cout << 'Q';   break;
    case CardRank::rank_king:   std::cout << 'K';   break;
    case CardRank::rank_ace:    std::cout << 'A';   break;
    default:
        std::cout << '?';
        break;
    }

    switch (card.suit)
    {
    case CardSuit::club:       std::cout << 'C';   break;
    case CardSuit::diamond:    std::cout << 'D';   break;
    case CardSuit::heart:      std::cout << 'H';   break;
    case CardSuit::spade:      std::cout << 'S';   break;
    default:
        std::cout << '?';
        break;
    }

    std::cout << "\t";
}

std::array<Card, 52> createDeck() {
    std::array<Card, 52> deck;

    // for(int suit_index = 0; suit_index < static_cast<int>(CardSuit::max_suits); suit_index++){
    //     for(int rank_index = 0; rank_index < static_cast<int>(CardRank::max_ranks); rank_index++){
            
    //     }
    // }

    for(int i = 0; i < 52; i++) {
        int suit = i / 13;
        int rank = i % 13;
        deck[i] = Card {static_cast<CardRank>(rank), static_cast<CardSuit>(suit)};
    }
    return deck;
}

void printDeck(const std::array<Card, 52>& deck) {
    for (Card card : deck) {
        printCard(card);
    }
}

void printCards(const std::vector<Card>& cards) {
    std::cout << "your cards: ";
    for(Card card : cards) {
        printCard(card);
    }
    std::cout << "\n";
}

bool askHitOrStand()
{
    std::cout << "Hit or stand? (type 1/0) ";
    int ans;
    std::cin >> ans;
    return static_cast<bool>(ans);
}

int cardVal(Card card) {
    int val{};
    switch(card.rank) {
        case CardRank::rank_2:      val = 2;   break;
        case CardRank::rank_3:      val = 3;   break;
        case CardRank::rank_4:      val = 4;   break;
        case CardRank::rank_5:      val = 5;   break;
        case CardRank::rank_6:      val = 6;   break;
        case CardRank::rank_7:      val = 7;   break;
        case CardRank::rank_8:      val = 8;   break;
        case CardRank::rank_9:      val = 9;   break;
        case CardRank::rank_10:     val = 10;   break;
        case CardRank::rank_jack:   val = 10;   break;
        case CardRank::rank_queen:  val = 10;   break;
        case CardRank::rank_king:   val = 10;   break;
        case CardRank::rank_ace:    val = 11;   break;
        default:
            val = -1;
            break;
    }
    return val;
}

void printScore(int playerScore, int dealerScore) {
    std::cout << "Your score: " << playerScore << " dealer score: " << dealerScore << "\n";
}

bool playBlackjack(const std::array<Card, 52>& deck) {
    int dealerScore = cardVal(deck.at(0));
    int playerScore = cardVal(deck.at(1)) + cardVal(deck.at(2));
    
    printScore(playerScore, dealerScore);
    
    if(playerScore == 21) return true;
    if(dealerScore == 21 && playerScore != 21) return false;

    int cardIndex = 3;
    
    while(1) {
        if(askHitOrStand())
        {
            playerScore += cardVal(deck.at(cardIndex++));
            if(playerScore >= 22) {
                printScore(playerScore, dealerScore);
                return false;
            } 
            if(dealerScore < 17) {
                dealerScore += cardVal(deck.at(cardIndex++));
            }
            printScore(playerScore, dealerScore);
            if(dealerScore >= 22) return true;

        } else {
            while(dealerScore < 17) {
                dealerScore += cardVal(deck.at(cardIndex++));
            }
            printScore(playerScore, dealerScore);
            if (dealerScore > 21) return true;
            if (dealerScore > playerScore) return false;
            return true;
        }
    }
}

int main()
{
    std::array<Card, 52> deck = createDeck();
    std::shuffle(std::begin(deck), std::end(deck), std::mt19937{std::random_device{}()});
    if(playBlackjack(deck)) {
        std::cout << "You won!";
    } else {
        std::cout << "You lost..";
    }

    return 0;
}



