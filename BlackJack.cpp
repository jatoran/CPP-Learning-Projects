#include <iostream>
#include <array>
#include <random> // for std::mt19937
#include <ctime> // for std::time
#include <algorithm> //for shuffle
#include <numeric> // for accumulate
#include <vector>

using namespace std;

enum class CardSuit{
  suitClubs,
  suitSpades,
  suitHearts,
  suitDiamonds,
  maxSuits
};
 
enum class CardRank{
  rank2,
  rank3,
  rank4,
  rank5,
  rank6,
  rank7,
  rank8,
  rank9,
  rank10,
  rankJack,
  rankQueen,
  rankKing,
  rankAce,
  maxRanks
};


typedef struct Card{
  CardRank rank{};
  CardSuit suit{};
} Card;

void printCard(Card card){
  switch(card.rank){
    case CardRank::rank2:
      cout << '2';
      break;
    case CardRank::rank3:
      cout << '3';
      break;
    case CardRank::rank4:
      cout << '4';
      break;
    case CardRank::rank5:
      cout << '5';
      break;
    case CardRank::rank6:
      cout << '6';
      break;
    case CardRank::rank7:
      cout << '7';
      break;
    case CardRank::rank8:
      cout << '8';
      break;
    case CardRank::rank9:
      cout << '9';
      break;
    case CardRank::rank10:
      cout << 'T';
      break;
    case CardRank::rankJack:
      cout << 'J';
      break;
    case CardRank::rankQueen:
      cout << 'Q';
      break;
    case CardRank::rankKing:
      cout << 'K';
      break;
    case CardRank::rankAce:
      cout << 'A';
      break;
    default:
      cout << "stfu";
  }
  switch(card.suit){
    case CardSuit::suitSpades:
      cout << 'S';
      break;
    case CardSuit::suitHearts:
      cout << 'H';
      break;
    case CardSuit::suitDiamonds:
      cout << 'D';
      break;
    case CardSuit::suitClubs:
      cout << 'C';
      break;
    default:
      cout << "stfu";
  }
}

using deckArrayType = array <Card,52>;
using index_type = deckArrayType::size_type;

int getCardValue(Card& card){
  if (card.rank <= CardRank::rank10) return static_cast<int>(card.rank) + 2;
  else if (card.rank <= CardRank::rankKing) return 10;
  else if (card.rank == CardRank::rankAce) return 11;
  else return 0;
}

void printDeck(deckArrayType& deck){
  for (Card& card : deck){
    printCard(card);
    cout << ' ';
  }
  cout << '\n';
}

deckArrayType createDeck(){
  deckArrayType deck;
  index_type card = 0;
  int maxSuits = static_cast<index_type>(CardSuit::maxSuits);
  int maxRanks = static_cast<index_type>(CardRank::maxRanks);
  for (index_type suit = 0; suit < maxSuits; suit++) {
    for (index_type rank = 0; rank < maxRanks; rank++) {
      deck[card].suit = static_cast<CardSuit>(suit);
      deck[card].rank = static_cast<CardRank>(rank);
      card++;
    }
  }
  return deck;
}

void shuffleDeck(deckArrayType& deck){
  static mt19937 mt{ static_cast<mt19937::result_type>(time(nullptr)) };
  shuffle(deck.begin(), deck.end(), mt); //std algorithm
}

Card dealCard(deckArrayType deck, int& cardsDealt){
  Card card = deck[cardsDealt];
  cardsDealt++;
  return card;
}

bool playerDecision(){
  char playerDecision;
  cout << "(h)it or (s)tand? ";
  cin >> playerDecision;
  if (playerDecision == 's') return false;
  else return true;
}

void dealCard(string str, vector<Card>& hand, deckArrayType deck, int& targetCardsDealt, int& handScore, int& totalCardsDealt){
  cout<< '-' << str << " card dealt" << '-' << endl;
  Card card = deck[totalCardsDealt];
  hand[targetCardsDealt] = card;
  targetCardsDealt++;
  totalCardsDealt++;
  handScore += getCardValue(card);
}

void printHand(string str, vector<Card> hand, int cardsDealt, int score){
  cout<< str << " Hand: ";
  for (int i = 0; i < cardsDealt; i++){
      printCard(hand[i]);
      cout << ' ';
    }
    cout << "Value: " << score << endl;
}

bool playBlackJack(deckArrayType deck){
  int cardsDealt = 0;
  int playerCardsDealt = 0;
  int dealerCardsDealt = 0;
  int playerHandScore = 0;
  int dealerHandScore = 0;
  vector<Card> playerHand(7);
  vector<Card> dealerHand(7);
  
  cout << endl << "---------------" << endl << "NEW BLACKJACK GAME INITIATED" << endl << "---------------" << endl;

  dealCard("Dealer", dealerHand, deck, dealerCardsDealt, dealerHandScore, cardsDealt);

  dealCard("Player", playerHand, deck, playerCardsDealt, playerHandScore, cardsDealt);
  
  bool playerTurn = true;
  while(playerTurn){
    dealCard("Player", playerHand, deck, playerCardsDealt, playerHandScore, cardsDealt);
    
    printHand("Player", playerHand, playerCardsDealt, playerHandScore);
    printHand("Dealer", dealerHand, dealerCardsDealt, dealerHandScore);

    if (playerHandScore > 21) {
      cout << "--LOSS. YOU BUST--" << endl;
      return false;
    }
    else if (playerHandScore == 21) {
      cout << "21. Dealer Turn" << endl;
      playerTurn = false;
    }
    else playerTurn = playerDecision();

  }
  
  bool dealerTurn = true;
  while(dealerTurn){
    dealCard("Dealer", dealerHand, deck, dealerCardsDealt, dealerHandScore, cardsDealt);

    printHand("Player", playerHand, playerCardsDealt, playerHandScore);
    printHand("Dealer", dealerHand, dealerCardsDealt, dealerHandScore);

    if (dealerHandScore > 21){
      cout << "--WIN. DEALER BUST--" << endl;
      dealerTurn = false;
    }
    else if (dealerHandScore >= playerHandScore){
      cout << "--LOSS. DEALER HIGHER OR EQUAL --" << endl;; 
      return false;
    }
  }
 return true;
}

int main(){
  deckArrayType deck = createDeck();
  while(1){
    shuffleDeck(deck);
    playBlackJack(deck);
  }
  
  return 0;
}