#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool debug = false;
#define D if (debug)

string names[4] = {"West", "North", "East", "South"};


char suit(string card) {
  return card[card.length()-1];
}

int value(string card) {
  card.erase(card.length()-1,1);
  if (card.length()==2) {
    if (card == "10")
      return 10;
    else
      return -1;
  }
  switch (card[0]) {
    case '2'...'9': 
      return card[0]-'0';
  case 'J': 
    return 11;
  case 'Q':
    return 12;
  case 'K':
    return 13;
  case 'A':
    return 14;
  default:
    return -1;    
  }
}

int suitnum(char suit) {
  switch (suit) {
  case 'C': return 0;
  case 'D': return 1;
  case 'H': return 2;
  case 'S': return 3;
  default: cout << "ERROR!" << endl;
  }
  return -1;
}


vector<string> cards_played;

bool already_played(string card) {
  for (int i=0; i<cards_played.size(); i++)
    if (card == cards_played[i])
      return true;
  cards_played.push_back(card);
  return false;
}

int main(int argc, char **argv) {

  string trump;

  if (argc>1) debug = true;

  while (cin >> trump) {

    static int hand = 0;

    bool legal=true;
    int player = 0;  // West starts
    int tricks[4] = {0, 0, 0, 0};
    bool out_of[4][4];  // [player][card]

    //reset
    for (int player=0; player<4; player++)
      for (int suit=0; suit<4; suit++) 
	out_of[player][suit] = false;
    cards_played.clear();

    cout << "Hand " << ++hand <<": ";
    D cout << endl;

    D cout << trump << " is trump." << endl;
    for (int trick=0; trick<13; trick ++) {
      string card;

      // The leader
      cin >> card;
      char the_suit = suit(card);

      int best_value = value(card);
      int best_player = player;
      bool best_had_trump = (suit(card) == suit(trump));

      D cout << names[player] << "\t " << card;


      // check for a proper deck
      if (already_played(card)) {
	legal = false;
	D cout << "This card has already been played!" << endl;	
      }

	// if this was THE trump card, make sure the dealer (South?) played it
	if ((card == trump) && (player !=3))  {
	  D cout << "Trump card was played by someone other then the dealer" << endl;
	  legal = false;
	}
	
      // Get the other three cards
      for (int i=1; i<4; i++) {
	// a player's card
	cin >> card;
	player = (player + 1)%4;
	D cout << " " << card;

	// check for a proper deck
	if (already_played(card)) {
	  legal = false;
	  D cout << "This card has already been played!" << endl;	
	}

	// check whether they played a suit they allegedly ran out of
	if (out_of[player][suitnum(suit(card))]) {
	  D cout << "*Illegal*";
	  legal = false;
	}

	// check whether they followed suit
	if (suit(card) != the_suit) {
	  out_of[player][suitnum(the_suit)] = true;	
	  D cout << "(" << names[player] << " out of " << the_suit << ")";
	}

       
	// this player is the first to put down a trump card in this trick
	if (!best_had_trump && (suit(card) == suit(trump))) {
	  best_value = value(card);
	  best_player = player;
	  best_had_trump = true;
	}

	// this player has a better trump card than someone else in this trick
	if (best_had_trump && (suit(card) == suit(trump)) && (value(card) > best_value)) {
	  best_value = value(card);
	  best_player = player;
	}

	// still no trump cards in play
	if (!best_had_trump && (suit(card) == the_suit) && (value(card) > best_value)) {
	  best_value = value(card);
	  best_player = player;
	}

	// if this was THE trump card, make sure the dealer (South?) played it
	if ((card == trump) && (player !=3))  {
	  D cout << "Trump card was played by someone other then the dealer" << endl;
	  legal = false;
	}

      }

      tricks[best_player] ++;
      player = best_player;
      D cout << "\t " << names[best_player] << endl;      
    }

    if (legal) {
      int EW = tricks[0] + tricks[2];
      int NS = tricks[1] + tricks[3];
      if (EW > NS) 
	cout << "East-West win " << (EW - 6) << " points" << endl;
      else
	cout << "North-South win " << (NS - 6) << " points" << endl;
    }
    else
      cout << "Illegal play" << endl;

  }
}

