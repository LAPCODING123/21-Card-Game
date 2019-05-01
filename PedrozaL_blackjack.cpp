//042518@LorenzoPedroza
//21 Card Game aka Blackjack
//Resource: https://www.bicyclecards.com/how-to-play/blackjack/
/*Blackjack. How to win or lose or push:
-Total>21 Bust
-Total>dealer<22 win
-total<dealer lose
-total=dealer push

*/
#include "Dealer3.h"
#include <iostream>
#include <time.h>
#include <windows.h>

void displayPlayerHand (Player& );
void makeAceElevenIfBlackjack(Player& );
void updatePlayerStatii(Player, Player, Dealer );
void convertAcetoEleven(Player& );

int main()
{
  Dealer blackJackDealer("COM Dealer", "blackjack");
  Player player1("COM Player");
  int hitOrStay = -1; //TODO if using string. Add string processing to increase program security
  int wantToPlayAgain = 0; //TODO stirngs
  string playerName;
  int oneOrEleven = 1;

  srand((unsigned)time(NULL)); //enable randomness in ceratin Player 1 decisions

  for (int i = 2; i > 0; i--) //shuffle
  {
    blackJackDealer.proShuffle();
    //blackJackDealer.shuffle();
  }

  cout << "\nWelcome to the 21 Card Game, aka BlackJack";
  cout << "\nPlayer, please enter your name: ";
  getline(cin, playerName);
  Player player2(playerName);
  cout << "\nLet's Begin!\n\n";

  cout << "Dealer deals to everyone...\n";

  for (int i = 0; i < 2; i++)
  {
    player1.getCard(blackJackDealer.deal());
    player2.getCard(blackJackDealer.deal());
    blackJackDealer.getCard(blackJackDealer.deal());
  }

  displayPlayerHand(player1);
  displayPlayerHand(player2);
  cout << "The dealer has: \n";
  cout << "his first card faced down\n";
  blackJackDealer.getCardInHand(1).display();

  //Adjust Ace for Natual Blackjacks
  makeAceElevenIfBlackjack(player1);
  makeAceElevenIfBlackjack(player2);
  makeAceElevenIfBlackjack(blackJackDealer);

  //cout << endl << "DEBUGGING-Blackjack Dealer Deck Size: " << blackJackDealer.getSize() << endl;  //DEBUG
  //cout << endl << "DEBUGGING-Blackjack Dealer upCard value: " << blackJackDealer.getCardInHand(1).getValue() << endl; //DEBUG

  //player1 A.I.
  do
  {
    if (player1.getTotal() < 17) //https://www.bicyclecards.com/how-to-play/blackjack/
    {
      if (player1.hasThisManyXCards("Ace")>0 && player1.getTotal()+10 >= 17 && player1.getTotal()+10 < 22) //benefit possibly by staying with ace
      {
        hitOrStay = rand()%2; //Up to player to take chance
        if (hitOrStay = 1)
          convertAcetoEleven(player1);//staying means it intends ace to be 11
      }

      else if (blackJackDealer.getSize() == 2 && blackJackDealer.getCardInHand(1).getValue() == 1) //Ace in Dealer upcard
        hitOrStay = rand()%2; //player must take chance

      else if(blackJackDealer.getSize() == 2 && blackJackDealer.getCardInHand(1).getValue()>=7) //First round of cards dealt. High up card
        hitOrStay = 0;

      else if(blackJackDealer.getSize() == 2 && blackJackDealer.getCardInHand(1).getValue()<7) //Dealer's upcard is poor
      {
        if (player1.getTotal()>=12) //stop drawing once hand total is 12 or higher
          hitOrStay = 1;

        else
          hitOrStay = 0;
      }

      else
        hitOrStay = 0;
    }

    else //greater than 17. Risk to take
    {
      if (player1.getTotal() == 21) //need to stay if already 21
        hitOrStay = 1;
      else
        hitOrStay = rand()%2; //player must take chance
    }

    //execute choice
    if (hitOrStay == 0)
    {
      player1.getCard(blackJackDealer.deal()); //Best to deal
      cout << endl << player1.getName() << " hits\n";
    }
    else if (hitOrStay == 1)
      cout << endl << player1.getName() << " stays\n";

    displayPlayerHand(player1);

    if(player1.getTotal()>21)
    {
      player1.setStatus("bust");
      cout << player1.getName() << " has " << player1.getStatus() << "!\n\n";
    }
  } while(player1.getStatus() != "bust" && hitOrStay == 0);

  //player 2 decison system
  do
  {
    do
    {
      cout << player2.getName() << ", will you like to hit(0) or stay(1): ";
      cin >> hitOrStay;
    } while(hitOrStay != 0 && hitOrStay != 1);

    if (hitOrStay == 0)
    {
      player2.getCard(blackJackDealer.deal());
      cout << endl << player2.getName() << " hits\n";
    }
    else if (hitOrStay == 1)
    {
      cout << endl << player2.getName() << " stays\n";
      if(player2.hasThisManyXCards("Ace")>0)
        convertAcetoEleven(player2);
    }

    displayPlayerHand(player2);

    if(player2.getTotal()>21)
    {
      player2.setStatus("bust");
      cout << player2.getName() << " has " << player2.getStatus() << "!\n\n";
    }
  } while(player2.getStatus() != "bust" && hitOrStay != 1);

  //By this point, all players have played a move, dealer can also show his hand
  displayPlayerHand(player1);
  displayPlayerHand(player2);
  if (blackJackDealer.getSize() == 2)//tell player dealer flips cards to build up suspense
  cout << blackJackDealer.getName() << " flips up down card...\n";
  displayPlayerHand(blackJackDealer);

  //Dealer's turn
  while(blackJackDealer.getTotal() < 17)
  { //dealer must deal while under 17 cards. Only make while loop, not do while as they are scenarios in which this does not even occur
    blackJackDealer.getCard(blackJackDealer.deal());
    cout << blackJackDealer.getName() << " hits\n";
    displayPlayerHand(blackJackDealer);
    if (blackJackDealer.getTotal()+11 > 17 && blackJackDealer.getTotal()+11 < 22) //if counting card as 11 brings total to 17 or more, but not over 21, must count as 11 TODO veirfy this
      convertAcetoEleven(blackJackDealer);
  }
  if(blackJackDealer.getTotal()>21)
  {
    blackJackDealer.setStatus("bust");
    cout << blackJackDealer.getName() << " has " << blackJackDealer.getStatus() << "!\n";
  }
  else
    cout << blackJackDealer.getName() << " stays\n";

  updatePlayerStatii(player1, player2, blackJackDealer);

  cin.ignore();
  cin.get();
  return 0;
}

void displayPlayerHand(Player& p) //can take player or dealer; only using base parent Player class functions //http://www.bogotobogo.com/cplusplus/upcasting_downcasting.php
{
  cout << p.getName() << " has: \n";
  p.showHand();
  cout << p.getName() << "'s Total is: ";
  if (p.hasThisManyXCards(11)>0) //Contains aces already shifted to 11
  {
    for (int i = 1; i <= p.hasThisManyXCards(11); i++) //TODO DEBUG if needed
      cout << p.getTotal()-10*i << " or ";
  }
  cout << p.getTotal();
  if(p.hasThisManyXCards("Ace")>0 && p.hasThisManyXCards(11) == 0) //has aces all at value 1
  {
    for (int i = 1; i <= p.hasThisManyXCards("Ace"); i++) //need to start at 1.Display all possible totals for multiple aces
      cout << " or " << p.getTotal()+10*i; //show value as 11 //TODO DEBUG if needed
  }
  cout << endl << endl;
}

void makeAceElevenIfBlackjack(Player& p)
{
    //Ace/Blackjack Correction for Player 1
  if(p.hasThisManyXCards("Ace")>0 && p.getTotal()+10 == 21) //already ace, so need to add 1+10 to make it 11 so player wins
    convertAcetoEleven(p);
}


void updatePlayerStatii(Player p1, Player p2, Dealer d)
{
  if (p1.getTotal() > 21)
    p1.setStatus("bust");
  if (p2.getTotal() > 21)
    p2.setStatus("bust");
  if (d.getTotal() > 21)
    d.setStatus("bust");

  if(p1.getTotal() == d.getTotal() && p1.getStatus() != "bust")
    p1.setStatus("push");
  if(p2.getTotal() == d.getTotal() && p2.getStatus() != "bust")
    p2.setStatus("push");

  if(d.getStatus() != "bust")
  {
    if(p1.getStatus() != "push") //prevent declaring push a win or loss
    {
      if(p1.getTotal() > d.getTotal() && p1.getStatus() != "bust")
        p1.setStatus("winner");
      else
        p1.setStatus("loser");
    }

    if(p2.getStatus() != "push")
    {
      if(p2.getTotal() > d.getTotal() && p2.getStatus() != "bust" && p2.getStatus() != "push")
        p2.setStatus("winner");
      else
        p2.setStatus("loser");
    }

    if(p1.getStatus() == "push" && p2.getStatus() == "push")
    {
      d.setStatus("push");
      cout << endl << p1.getName() << " and " << p2.getName() << " " << p2.getStatus() << " with " << d.getName() << "!";
      cout << "\nThe game is a draw!";
      return ; //already gave out results
    }
  }

  else if(d.getStatus() == "bust")
  {
    if (p1.getStatus() != "bust")
      p1.setStatus("winner");
    else
      p1.setStatus("loser");

    if (p2.getStatus() != "bust")
      p2.setStatus("winner");
    else
      p2.setStatus("loser");
  }
  cout << endl << p1.getName() << "'s hand is a " << p1.getStatus();
  cout << endl << p2.getName() << "'s hand is a " << p2.getStatus();
}

void convertAcetoEleven(Player& p)
{
  for (int i = 1; i <= p.getSize(); i++) //find ace, make it 11 so reflected in total. Steps bakc fx needs value of 1 or more.
    if (p.getCardInHand(i).getFace()=="Ace")
    {
      p.changeCardValue(i, 11);
      break; //ONLY change one. Or it busts
    }
}
