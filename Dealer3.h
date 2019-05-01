#include "Deck4.h"
#include "Player4.h"

class Dealer : public Player
{
private:
  Deck *deck;
public:
  //using Player::Player;
  //Dealer: Player

  Dealer(string name):Player(name) { deck = new Deck();/*using Player::Player;*/}

  Dealer(string name, int numOfCards): Player(name) //game specific constructors
  {
    //using Player::Player;
    deck = new Deck(numOfCards);
  }

  Dealer(string name, string game): Player(name) //game specific constructors
  {
    //using Player::Player;
    deck = new Deck(game);
  }

  Dealer(string name, int numOfCards, string game): Player(name) //game specific constructors
  {
    //using Player::Player;
    deck = new Deck(numOfCards, game);
  }

  using Player::Player;

  //Dealer(): player (int numOfcards) {Deck deck(numOfcards);/*using Player::Player;*/}
  //Dealer(string game) {Deck deck(game); /*using Player::Player;*/}

  Card deal() { return deck->draw(); }
  void simpleShuffle() { deck->shuffle(); }
  void proShuffle()
  {
    deck->shuffle(); //http://www.cplusplus.com/forum/beginner/139181/
    deck->perfectShuffle(3);
    deck->shuffle();
  }
  void amazingShuffle()
  {
    deck->shuffle();
    deck->shuffle();
    deck->shuffle();
    deck->shuffle();
  }
};
