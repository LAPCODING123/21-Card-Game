#include <iostream>
using namespace std;

class Card
{
private:
  string face;
  string suit;
  int value;
public:
  void set(string, string, int);
  void setValue(int v) { value = v; }
  string getFace() { return face; }
  string getSuit() { return suit; }
  int getValue() { return value; }
  void display() { cout << getFace() << " of " << getSuit() << " = " << getValue() << endl; }
};

void Card::set(string f, string s, int v)
{
  face = f;
  suit = s;
  value = v;
}
