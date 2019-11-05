/* --------------------------------

  BigInteger.c | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

-----------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"
#include "List.h"

// definition of a BigInteger object
typedef struct BigIntegerObj {
  // A BigInteger is represented by its sign (int which is -1, 1, or 0). And
  // a list of longs representing its magnitude.
  int sign;
  List magnitude;
} BigIntegerObj;

// -----------------------------------------------------------------
// construction/destruction
// -----------------------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger() {

    // create a reference to a BigInteger object
    BigInteger A;

    // allocate dynamic memory for this object
    A = malloc(sizeof(BigIntegerObj));

    // set sign to 0
    A->sign = 0;

    // create the list that represents the magnitude
    A->magnitude = newList();

    return A;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN) {
  // check for already NULL
  if (pN != NULL && *pN != NULL) {
    // nothing needs to be done about sign.
    // but all heap memory associated with magnitude must be freed.
    freeList(&(A->magnitude));

    // the pointer pN must also be freed and set to NULL
    free(*pN);
    *pN = NULL;
  }
}

// -----------------------------------------------------------------
// access functions
// -----------------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N) {

  return 0;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B) {

  return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {

  return 0;
}

// -----------------------------------------------------------------
// manipulation procedures
// -----------------------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N) {

  return;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {

  return;
}

// -----------------------------------------------------------------
// BigInteger arithmetic operations
// -----------------------------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal
// integer represented in base 10 by the string s.
// PRE: s is a non-empty string containing only base ten digits {0,1,2..,9}
//  and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s) {

  return NULL;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {

  return NULL;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting it's
// current state: S = A + B.
void add(BigInteger S, BigInteger A, BigInteger B) {

  return;
}

// sum()
// Returns a reference to a new BigInteger object representing A+B.
BigInteger sum(BigInteger A, BigInteger B) {

  return NULL;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B) {

  return;
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {

  return NULL;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B) {

  return;
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B) {

  return NULL;
}

// -----------------------------------------------------------------
// Other operations
// -----------------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N) {

  return;
}
