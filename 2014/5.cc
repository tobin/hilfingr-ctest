#include <iostream>
#include <assert.h>
#include <string>
#include <list>

#define D if (0) 
using namespace std;

int penalty_value(string c) {
  assert(c[0] == 'H' || c[0] == 'S' || c[0] == 'C' || c[0] == 'D');
  assert(c.length() == 2);
  switch(c[1]) {
  case 'J': return 1;
  case 'Q': return 2;
  case 'K': return 3;
  case 'A': return 4;
  default: return 0;
  }
}

void print_hand( list<string> &hand) {
  for (list<string>::iterator i=hand.begin(); i != hand.end(); i++)
    cout << *i << " ";
  cout << endl;
}


int main(int argc, char **argv) {

  while(1) {
    D cout << "================================================== NEW GAME " << endl;

    list<string> hand[2];
   
    // read the hands
    for (int p=0; p<2; p++) {
      for (int i=0; i<26; i++) {
	string card;
	if (!(cin >> card))
	  return 0;
	hand[p].push_back(card);
      }
    }

    // Begin the game
    list<string> pile;
    int p=0;  // current player
    
    while (1) {
      assert(hand[0].size() + hand[1].size() + pile.size() == 52);

      D {
	cout << endl;
	cout << "Player 0's hand: ";
	print_hand(hand[0]);
	cout << "Player 1's hand: ";
	print_hand(hand[1]);
	cout << "The pile:        ";
	print_hand(pile);
      }
      
      // Get the player's top card
      if (hand[p].empty()) {
	D cout << "Player " << p << " has no cards left." << endl;
	goto end_of_game;   
      }    
      string c = hand[p].front();
      hand[p].pop_front();
      D cout << "Player " << p << " plays the " << c << endl;

      // Put it on the pile
      pile.push_back(c);

      p = !p;   // Next player
      int penalty = penalty_value(c);
      if (penalty == 0) {
	continue; // Continue normal play
      }

      D cout << "Entering penalty mode" << endl;
      while (penalty > 0) {

	assert(hand[0].size() + hand[1].size() + pile.size() == 52);

	// Get the player's top card
	if (hand[p].empty()) {
	  D cout << "Player " << p << " has no cards left." << endl;
	  goto end_of_game;
	}
	string c = hand[p].front();
	hand[p].pop_front();
	pile.push_back(c);              // Put it on the pile
	penalty --;
	D cout << "Player " << p << " plays the " << c << " in penalty mode" << endl;

	if (penalty_value(c) > 0) {
	  penalty = penalty_value(c);   // New penalty
	  p = !p;                       // Next player
	  D cout << "New penalty of " << penalty << endl;	  
	}
      }

      D cout << "Penalty is complete " << endl;

      int q = !p;
      D cout << "Player " << q << " takes the pile " << endl;
      // penalty complete, take the pile
      hand[q].splice(hand[q].end(), pile);
      assert(pile.empty());

      // The next round begins with the winner of previous round
      // (i.e., the player who took the pile) playing the ﬁrst card.
      p = q;
    }
  end_of_game:
    cout << (52 - pile.size()) << endl;
  }
  return 0;
}
