#ifndef CONTEST_H
#define CONTEST_H

#ifdef __cplusplus

#include <cstdlib>
#include <cstdio>
#include <climits>
#include <stdarg.h>
#include <cstring>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

extern "C" {

#else

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <strings.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#endif

/* NOTES:
 *    Row-Major Order: To represent a 2D array (or higher) in
 *    completely kosher C, one can use a one-dimensional array
 *    comprising the rows or columns concatenated.  In "row-major order",
 *    an MxN array A is stored in a one-dimensional array, A', containing
 *    M*N elements (at least), with A[0,0] in A'[0], A[0,1] in A'[1],
 *    ... A[0,N-1] in A'[N-1], A[1,0] in A'[N], etc., or in general with
 *    A[i,j] in A'[j + i * N]. 
 *   
 *    Declaring a C array
 *       double A[5][4]
 *    produces an array of 5 rows each with 4 elements, laid out in
 *    memory in row-major order (that is, passing A or &A[0][0] to a
 *    function expecting a double* will cause the function to see the
 *    elements in row-major order).  Unfortunately, standard C or C++ 
 *    don't direct provide ways of passing such an array with its
 *    bounds, nor do they even have array types (as such) whose bounds
 *    are non-constant.  So in the functions below, you must
 *    explicitly pass in the size of the array argument.
 */


/** Set X to solve AX = B.  Requires that A be NxN, laid out in
 *  row-major order, where B and X have size N.  X may contain NaNs 
 *  or infinities if A is singular.  It is legal for X to overlap any 
 *  of the input data. */
extern void linearSolve (int N, double* A, double* B, double* X);

/** Set X to minimize || AX - B ||, where A is MxN, 0<N<=M, laid out
 *  in row-major order, B has size M, and X has size N.  Assumes that 
 *  rank(A) = N.   Returns the square residual || AX - B ||**2. 
 *  Requires that X not overlap B. */
extern double leastSquares (int M, int N, double* A, double* b, double* x);

/** Given that COEFS is an MxN array laid out in row-major order,
 *  LIMITS is an M-element array, and OBJECTIVE is an N-element array, 
 *  return an (N+1)-element array, X, that maximizes
 *          _
 *         \
 *         /_      OBJECTIVE[j]*X[j]
 *       j = 0..N-1
 *
 *  subject to the constraints 
 *
 *       X[j] >= 0,  for j = 0..N-1; and 
 *          _
 *         \
 *         /_      COEFS[i][j] * X[j]  <=  LIMITS[i],  for i = 0..M-1.
 *       j = 0..N-1
 *
 *  Also sets X[N] to the optimum value of the objective function (which 
 *  may be +infinity).  Returns null if there is no feasible solution. */
extern double* optimize (int M, int N, 
			 double* coefs, double* limits, double* objective);


#ifdef __cplusplus
}

using namespace std;
#endif

#endif
