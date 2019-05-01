#include "Card3.h"
#include <time.h>
#include <windows.h>

//modified to allow deck of with max value 10

class Deck
{
private:
  int numOfCards;
  Card *cards;
  string game;
public:
  Deck();
  Deck(int);
  Deck(string );
  Deck(int, string );
  void set();
  void setValues(int []);
  Card draw();
  bool allDrawn() { return numOfCards == 0; }
  void display();
  void shuffle();
  void perfectShuffle(int);
private:
  void swap(Card *, Card *);
};

Deck::Deck()
{
  srand((unsigned)time(NULL));
  numOfCards = 52;
  game = "default";
  set();
}

Deck::Deck(string setGameTo)
{
  srand((unsigned)time(NULL));
  numOfCards = 52;
  game = setGameTo;
  set();
}

Deck::Deck(int c)
{
  if (c < 1 || c > 52)
  {
    cerr << "INVALID DECK SIZE\n";
    exit(0); // https://stackoverflow.com/questions/30250934/how-to-end-c-code
  }
  srand((unsigned)time(NULL));
  numOfCards = c;
  game = "default";
  set();
}

Deck::Deck(int c, string setGameTo)
{
  if (c < 1 || c > 52)
  {
    cerr << "INVALID DECK SIZE\n";
    exit(0); // https://stackoverflow.com/questions/30250934/how-to-end-c-code
  }
  srand((unsigned)time(NULL));
  numOfCards = c;
  game = setGameTo;
  set();
}

void Deck::set()
{
  cards = new Card[numOfCards];

  string f[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
                   "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
  string s[4] = { "Spades", "Hearts", "Clubs", "Diamonds"};  //"\3", "\4", "\5", "\6" ACII symbol will not display

  int v[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
  int k = 0;

  for (int i = 0; i < 4; i++) // loop thru suits
    for (int j = 0; j < 13; j++) // loop thru faces & values
    {
      if (game == "blackjack" && v[j] > 10) //set cards for a game of Black Jack
        v[j] = 10;
      cards[k++].set(f[j], s[i], v[j]);
      if (k == numOfCards)
        return;
    }
}

void Deck::setValues(int values[])
{
  int k = 0;
  for (int i = 0; i < 4; i++) // loop thru suits
    for (int j = 0; j < 13; j++) // loop thru values
    {
      cards[k++].setValue(values[j]); //Aaron DeCastro: Another way to change kings and queens to ten: change with this. I will stick with my way for now.
      if (k == numOfCards)
        return;
    }
}

Card Deck::draw()
{
  numOfCards--;//index ready now
  return cards[numOfCards];
}

void Deck::swap(Card *firstCard, Card *secondCard)
{
	Card tempCard = *firstCard;
	*firstCard = *secondCard;
	*secondCard = tempCard;
}

void Deck::display()
{
  for (int i = 0; i < numOfCards; i++)
    cards[i].display();
}

void Deck::shuffle()
{
  int swaps = (rand() % numOfCards) + 1;
	for(int i = 0; i < swaps; i++)
		swap(&cards[rand()%numOfCards], &cards[rand()%numOfCards]);
}

void Deck::perfectShuffle(int times)
{
	if (times <= 0 || numOfCards % 2 == 1)
  {
    cerr << "INVALID SHUFFLE\n";
    return;
  }

	const int SPLIT = numOfCards / 2;
	Card *topHalf = new Card[SPLIT];
	Card *bottomHalf = new Card[SPLIT];

	do
	{
		for (int i = 0; i < numOfCards; i++)
		{
			if (i < SPLIT)
				topHalf[i] = cards[i];
			else
				bottomHalf[i-SPLIT] = cards[i];
		}

		for (int i = 0, t = 0, b = 0; i < numOfCards; i++)
		{
			if (i % 2 == 0)
				cards[i] = topHalf[t++];
			else
				cards[i] = bottomHalf[b++];
		}
	} while (--times > 0);

	delete [] topHalf;
	delete [] bottomHalf;
}
