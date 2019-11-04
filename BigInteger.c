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
  List* magnitude;
} BigIntegerObj;

// -----------------------------------------------------------------
// construction/destruction
// -----------------------------------------------------------------

BigInteger newBigInteger() {

  return NULL;
}

void freeBigInteger(BigInteger* pN) {

  return;
}

// -----------------------------------------------------------------
// access functions
// -----------------------------------------------------------------

int sign(BigInteger N) {

  return 0;
}

int compare(BigInteger A, BigInteger B) {

  return 0;
}

int equals(BigInteger A, BigInteger B) {

  return 0;
}

// -----------------------------------------------------------------
// manipulation procedures
// -----------------------------------------------------------------

void makeZero(BigInteger N) {

  return;
}

void negate(BigInteger N) {

  return;
}

// -----------------------------------------------------------------
// BigInteger arithmetic operations
// -----------------------------------------------------------------

BigInteger stringToBigInteger(char* s) {

  return NULL;
}

BigInteger copy(BigInteger N) {

  return NULL;
}

void add(BigInteger S, BigInteger A, BigInteger B) {

  return;
}

BigInteger sum(BigInteger A, BigInteger B) {

  return NULL;
}

void subtract(BigInteger D, BigInteger A, BigInteger B) {

  return;
}

BigInteger diff(BigInteger A, BigInteger B) {

  return NULL;
}

void multiply(BigInteger P, BigInteger A, BigInteger B) {

  return;
}

BigInteger prod(BigInteger A, BigInteger B) {

  return NULL;
}

// -----------------------------------------------------------------
// Other operations
// -----------------------------------------------------------------

void printBigInteger(FILE* out, BigInteger N) {

  return;
}
