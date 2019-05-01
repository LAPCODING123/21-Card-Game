class Player
{
private:
  string name;
  Card *hand;
  int size;
  string status; //winner lose or draw
public:
  Player(string s);
  void setName(string s) { name = s; }
  string getName() { return name; }
  void getCard(Card c)
  {
    hand[size] = c;
    size++;
  }
  int getSize() { return size; }
  void showHand()
  {
    for (int i = 0; i < size; i++)
      hand[i].display();
  }
  Card getCardInHand(int stepsBack) {return hand[size-(stepsBack)];} //TODO test this
  void changeCardValue(int stepsBack, int value) {hand[size-(stepsBack)].setValue(value);}
  int hasThisManyXCards(string, string, int);
  int hasThisManyXCards(string, int);
  int hasThisManyXCards( string);
  int hasThisManyXCards( int);

  int hasThisManyXCards(Card);
  int getTotal()
  {
    int total = 0;
    for (int i = 0; i < size; i++)
      total += hand[i].getValue();
    return total;
  }

  void setStatus(string s) {status = s;} //modifier
  string getStatus() {return status;} //accessor

};


Player::Player(string s)
{
  name = s;
  hand = new Card[52];
  size = 0;
  status = "draw";
}

int Player::hasThisManyXCards(string face, string suit, int value)
{
  int hasThisManyOfXCard = 0;
  for(int i = 0; i <= getSize(); i++) //getSize returns actual value
  {
    if (getCardInHand(i).getFace() == face)
      if (getCardInHand(i).getSuit() == suit)
        if (getCardInHand(i).getValue() == value)
          hasThisManyOfXCard++;
  }
  return hasThisManyOfXCard;
}


Player::hasThisManyXCards(string faceOrSuit, int value)
{
  int hasThisManyOfXCard = 0;
  for(int i = 0; i <= getSize(); i++)
  {
    if (getCardInHand(i).getFace() == faceOrSuit || getCardInHand(i).getSuit() == faceOrSuit)
      if (getCardInHand(i).getValue() == value)
        hasThisManyOfXCard++;
  }
  return hasThisManyOfXCard;
}

Player::hasThisManyXCards(string faceOrSuit)
{
  int hasThisManyOfXCard = 0;
  for(int i = 0; i <= getSize(); i++)
  {
    if (getCardInHand(i).getFace() == faceOrSuit || getCardInHand(i).getSuit() == faceOrSuit)
        hasThisManyOfXCard++;
  }
  return hasThisManyOfXCard;
}

Player::hasThisManyXCards(int value)
{
  int hasThisManyOfXCard = 0;
  for(int i = 0; i <= getSize(); i++)
  {
    if (getCardInHand(i).getValue() == value)
      hasThisManyOfXCard++;
  }
  return hasThisManyOfXCard;
}
