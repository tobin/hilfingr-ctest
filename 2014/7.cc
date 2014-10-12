#include <iostream>
#include <assert.h>

/*  NB: Non-working solution.

    This grid-game is a lot like "quinto" from the 2000 contest,
    except that it's played modulo five instead of modulo 2, and here
    the borders "wrap around".

    I tried a basic backtracking search solution, but it is too slow.
    The "MOD" variable sets the modulus of the game (5 for the contest
    problem, but you can set it to 2 for testing).

    Not sure how to improve.  One possible approach: the problem
    itself can be written (I think) as a set of linear equations in
    GF(5) and solved directly via Gaussian elimination.

    Tobin Fricke 
    October 2014
 */

const int MOD = 5;

using namespace std;
#define D if (1)

typedef struct problem {
  bool bound[5][5];
  int vals[5][5];
  int pushes[5][5];
} problem_t;

bool solved(const problem_t problem) {
  for (int i=0; i<5; i++)
    for (int j=0; j<5; j++)
      if (problem.vals[i][j] != 0)
	return false;
  return true;
}

bool read_problem(problem_t &problem) {
  for (int i=0; i<5; i++)  // row
    for (int j=0; j<5; j++)  { // col
      if (!(cin >> problem.vals[i][j]))
	return false;
      problem.bound[i][j] = false;
      problem.pushes[i][j] = 0;
    }
  return true; // success
}

void print_vals(const problem_t problem) {
  for (int i=0; i<5; i++)  { // row
    for (int j=0; j<5; j++)  { // col
      cout << problem.vals[i][j];
      if (j<4) 
	cout << " ";
    }
    cout << endl;
  }
}

void print_solution(const problem_t problem) {
  for (int i=0; i<5; i++)  { // row
    for (int j=0; j<5; j++)  { // col
      cout << problem.pushes[i][j];
      if (j<4) 
	cout << " ";
    }
    cout << endl;
  }
}

bool feasible(const problem_t problem) {
  for (int i=0; i<5; i++)  
    for (int j=0; j<5; j++)  
      if (problem.vals[i][j] != 0) { // this cell not solved
	bool all_bound = true;
	for (int dx=-1; dx<=1; dx++)  
	  for (int dy=-1; dy<=1; dy++)  
	    if (!problem.bound[(i+dx)%5][(j+dy)%5]) {
	      all_bound = false;
	      goto not_all_bound;
	    }
      not_all_bound:
	if (all_bound) 
	  return false; // not feasible
      }
  return true;
}

void push_at(problem_t &problem, int i, int j) {
  problem.pushes[i][j] ++;
  for (int dx=-1; dx<=1; dx++)  
    for (int dy=-1; dy<=1; dy++)  {
      int ii = (i+dx)%5;
      int jj = (j+dy)%5;
      problem.vals[ii][jj] = (problem.vals[ii][jj] + 1) % MOD;
    }
}

bool solve_problem(problem_t &problem) {
  // Check if problem still feasible
  if (!feasible(problem)) {
    D cout << "Not feasible --> backtracking" << endl;
    return false;
  }

  // find first unbound value
  int i,j;
  for (i=0; i<5; i++)  
    for (j=0; j<5; j++)  
      if (!problem.bound[i][j])
	goto found_unbound;
  D cout << "All elements are bound!" << endl;
  return true; 

 found_unbound:
  D cout << "Solving at " << i << ", " << j << endl;

  problem_t new_problem = problem;
  new_problem.bound[i][j] = true;
 
  for (int pushes=0; pushes<=MOD; pushes++) {
   
    if (solve_problem(new_problem)) {
      problem = new_problem;
      return true;
    }

    D cout << "Pushing at "<< i << ", " << j << endl;
    push_at(new_problem, i, j);
    D print_vals(new_problem);

  }

  return false;
}


int main(int argc, char **argv) {
  int set = 0;
  problem_t problem;
  while (read_problem(problem)) {
    D print_vals(problem);
    bool solved = solve_problem(problem);
    cout << "Case " << set << ":" << endl;
    print_solution(problem);
  }
  return 0;
}
