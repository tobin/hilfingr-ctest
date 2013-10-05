#include <unordered_map>
#include <tuple>
#include <string>
#include <iostream>
  
using namespace std;

string decks[4];  

#define D if (0)

int card_value(char card) {
  if (('2' <= card) && (card <= '9'))
    return card - '0';
  switch (card) {
  case 'A': return 1;
  case 'T': return 10;
  case 'J': return 11;
  case 'Q': return 12;
  case 'K': return 13;
  }
  cerr << "Unrecognzied card '" << card << "'!" << endl;
  return 0;
}

int memo[13][13][13][13][2];

void max_score(int taken[4], int player, int *me, int *him) {

  if (memo[taken[0]][taken[1]][taken[2]][taken[3]][0] != -1) {
    *me = memo[taken[0]][taken[1]][taken[2]][taken[3]][player];
    *him = memo[taken[0]][taken[1]][taken[2]][taken[3]][!player];
    return;
  }

  // player is 0 or 1
  // returns my_score, his_score

  int my_best = 0;
  int his_best = 0;
  
  for (int d=0; d<4; d++) {                            // Try taking the top card from deck d

    if (taken[d] == decks[d].length()) continue;       // no cards left in this deck

    char top_card = decks[d].at(decks[d].length()-1-taken[d]);     // evaluate value of this card
    taken[d] ++;

    int his_score, my_score;
    max_score(taken, !player, &his_score, &my_score);
    my_score += card_value(top_card);

    if (my_score > my_best) {
      my_best = my_score;
      his_best = his_score;
    }

    taken[d] --; 	       
  }
  
  *me = my_best;
  *him = his_best;
  
  memo[taken[0]][taken[1]][taken[2]][taken[3]][player] = *me;
  memo[taken[0]][taken[1]][taken[2]][taken[3]][!player] = *him;
  return;
}

int main(int argc, char **argv) {
  int n = 0;
  while (cin >> decks[0] >> decks[1] >> decks[2] >> decks[3]) {
    cout << "Deal " << ++n << ":";
    D cout << endl;

    for (int a=0; a<13; a++) 
      for (int b=0; b<13; b++) 
	for (int c=0; c<13; c++) 
	  for (int d=0; d<13; d++) {
	    memo[a][b][c][d][0] = -1;
	    memo[a][b][c][d][1] = -1;
	  }

    D for (int i=0; i<4; i++) 
      cout << " Deck #" << i << ": " << decks[i] << endl;

    int total_value = 0;
    for (int d=0; d<4; d++) {
      for (int i=0; i<decks[d].length(); i++)
	total_value += card_value(decks[d].at(i));
    }

    int taken[4] = {0,0,0,0};
    int my_best = 0;
    int his_best = 0;
    max_score(taken, 0, &my_best, &his_best);
    cout << " First player wins " << my_best << " out of " << total_value << endl;
  }
  return 0; 
}
