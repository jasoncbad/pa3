/* --------------------------------

  BigInteger.c | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

-----------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"
#include "List.h"

// --------------------------------------------
// define statements of base and power
// these macros will satisfy BASE = 10^POWER
// --------------------------------------------
#define BASE 1000

// power must be 0 <= POWER <= 9
#define POWER 3

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
    freeList(&((*pN)->magnitude));

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
  return N->sign;
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
  N->sign = 0;
  clear(N->magnitude);
  return;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
  if (N->sign == -1) {
    N->sign = 1;
  } else if (N->sign == 1) {
    N->sign = -1;
  }
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
  printf("\tstringToBigInteger() started...\n");

  // create a BigInteger object to return
  BigInteger A = newBigInteger();

  // First determine the sign by observing the first character in the string
  char* cursorChar = s;
  printf("\t\tFirst char in the given string is: %c\n", *cursorChar);

  if (*cursorChar == '-') {
    A->sign = -1;
  } else if (*cursorChar == '+') {
    A->sign = 1;
  } else {
    // assume positive because according to the precondition, the only other
    // possible thing this char could be is an integer...
    A->sign = 1;
  }

  // After the first character has been observed, shave off any leading zeroes.
  // To do this,first make sure we get to the first non-"-"/"+" char.
  if (*cursorChar == '-' || *cursorChar == '+') {
    cursorChar = cursorChar + 1;
  }

  // move the cursor char pointer to point to the first actual number.
  while (*cursorChar == '0') {
    cursorChar = cursorChar + 1;
  }

  printf("\t\tFirst actual number in the given string is: %c\n", *cursorChar);



  // Run through all meaningful characters and count how many there are
  int length = 0;
  while(*cursorChar != '\0') {
    length++;
    cursorChar = cursorChar + 1;
  }

  printf("\t\tNumber of meaningful digits in the string is: %d\n", length);


  if (length == 0) {
    printf("\tcould not build bigInt.. no meaningful digits in string!\n");
    return A;
  }

  // Determine the highest power of the list by ceiling[(length-1) / POWER]
  // the most significat place is now the 10^new_power's place.
  // add +1 to this new_power to get how many entries our list should have.
  int new_power = (length - 1) / POWER;
  int num_entries;

  num_entries = new_power + 1;

  printf("\t\tThe most significant place for this BigInteger in base %d is the 10^%d's place...\n", BASE, new_power);
  printf("\t\tThe number of nodes our list is then: %d\n", num_entries);

  // count from 1 to (num_entries) in a for loop and perform the following
  // 1. The first iteration is special, because the most significant 'digit'
  //      may have less than POWER digits. Take the first (length(s) % POWER)
  //      characters off the front of the string and create the first entry.
  // 2. The remaining characters in the string should be able to be picked off
  //      in groupings of POWER to be appended to the list.
  //
  // NOTES:
  //    - Case where the grouping starts with zero or zeroes. Should be handled
  //      by the typecasting mechanism.
  //    - Case where the first grouping starts with zero/zeroes. Already
  //      handled by the beginning of this function.

  // make sure the cursor is at the first meaningful digit
  // SO: set cursor to the beginning
  cursorChar = s;
  // THEN: skip -+ if any
  if (*cursorChar == '-' || *cursorChar == '+') {
    cursorChar = cursorChar + 1;
  }
  // THEN: move the cursor char pointer to point to the first actual number.
  while (*cursorChar == '0') {
    cursorChar = cursorChar + 1;
  }

  // start building!
  for (int i = 1 ; i <= num_entries; i++) {
    char str[9] = { '\0' }; // dummy holder for our values

    // special first case - when i = 1 and there is not a consistent grouping
    // in the highest power.
    if (i == 1 && (length % POWER != 0)) {
      int numDigits = length % POWER; // number of digits we need to place in
                                      // the most significant entry
      // take these first characters off the front
      for (int j = 1; j <= numDigits; j++) {
        sprintf(str + strlen(str), "%d", (*cursorChar) - 48 ); // use sprintf to load up the str
        cursorChar++;
      }
      long result = strtol(str, NULL, 10); // this result stores the long we need

      // create the first entry
      append(A->magnitude, result);
      continue;
    }

    // OTHERWISE: pick off normal groupings!
    strncpy(str, "", sizeof(str));
    for (int j = 1; j <= POWER; j++) {
      sprintf(str + strlen(str), "%d", (*cursorChar) - 48 ); // use sprintf to load up the str
      cursorChar++;
    }
    long result = strtol(str, NULL, 10);

    // create the entry
    append(A->magnitude, result);

  } // end of for loop

  printf("\tLIST CREATED: "); printList(stdout, A->magnitude);

  printf("\tstringToBigInteger() ended...\n");
  return A;
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
