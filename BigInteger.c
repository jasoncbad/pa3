/* --------------------------------

  BigInteger.c | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Contains definitions for the BigInteger data type.
  A BigIntegerObj has two components:
    - an int (1, -1, 0) specifying the sign.
    - a normalized List of longs specifying the magnitude.

  For a complete list of operations see the BigInteger.h file.

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
#define BASE 1000000000

// power must be 0 <= POWER <= 9
#define POWER 9

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
  int returnThis = 0;
  // compare the signs and try to find an exit case between them
  if (sign(A) < sign(B)) {
    returnThis = -1;
  } else if (sign(B) < sign(A)) {
    returnThis = 1;
  } else {
    // compare the number of digits and also try to find an exit case
    if (length(A->magnitude) > length(B->magnitude)) {
      returnThis = 1;
    } else if (length(B->magnitude) > length(A->magnitude)) {
      returnThis = -1;
    } else {
      // the lists have the same length.. we must compare each digit
      // we need to use the cursors for this. So I will save the state of
      // each cursor
      int a_cursor_state, b_cursor_state;
      a_cursor_state = index(A->magnitude);
      b_cursor_state = index(B->magnitude);

      // move cursors to the front
      moveFront(A->magnitude); moveFront(B->magnitude);

      // while cursors are defined
      while ((index(A->magnitude) != -1) && (index(B->magnitude) != -1)) {
        // compare the elements directly
        long elementA = get(A->magnitude);
        long elementB = get(B->magnitude);

        if (elementA < elementB) {
          // A < B if both positive.. but A > B if both negative
          if(sign(A) == 1) {
            returnThis = -1; break;
          } else if (sign(A) == -1) {
            returnThis = 1; break;
          }
        } else if (elementB < elementA) {
          // B < A if both positive.. but B > A if both negative
          if (sign(A) == 1) {
            returnThis = 1; break;
          } else if (sign(A) == -1) {
            returnThis = -1; break;
          }
        } else {
          // do nothing
        }
        // move the cursors next
        moveNext(A->magnitude); moveNext(B->magnitude);
      }

      // weve gone through all digits and did not find any differences

      // restore cursor of A to its original state
      if (a_cursor_state != -1) {
        moveFront(A->magnitude);
        for (int i = 0; i < a_cursor_state; i++) {
          moveNext(A->magnitude);
        }
      }

      // do the same thing to B
      if (b_cursor_state != -1) {
        moveFront(B->magnitude);
        for (int i = 0; i < b_cursor_state; i++) {
          moveNext(B->magnitude);
        }
      }

      return returnThis;
    }
  }
  return returnThis; // dummy return that is never actually reached
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {
  if (A->sign != B->sign) return 0;

  return listEquals(A->magnitude, B->magnitude);
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
  //printf("\tstringToBigInteger() started...\n");

  // create a BigInteger object to return
  BigInteger A = newBigInteger();

  // First determine the sign by observing the first character in the string
  char* cursorChar = s;
  //printf("\t\tFirst char in the given string is: %c\n", *cursorChar);

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

  //printf("\t\tFirst actual number in the given string is: %c\n", *cursorChar);
  // Run through all meaningful characters and count how many there are
  int length = 0;
  while(*cursorChar != '\0') {
    length++;
    cursorChar = cursorChar + 1;
  }
  //printf("\t\tNumber of meaningful digits in the string is: %d\n", length);
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

  printf("\tLIST CREATED: "); //printList(stdout, A->magnitude);

  printf("\tstringToBigInteger() ended...\n");
  return A;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {

  // create a new BigInteger which we will return
  BigInteger A = newBigInteger();

  // copy over the sign of list N
  A->sign = N->sign;

  // copy over the list of N into a new list representing the magnitude of A.
  freeList(&(A->magnitude));
  A->magnitude = copyList(N->magnitude);


  // return the deep copy
  // we have allocated HEAP data for a new BigInteger, and also for a new List.
  return A;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting it's
// current state: S = A + B.
void add(BigInteger S, BigInteger A, BigInteger B) {
  BigInteger T = sum(A, B);

  // we've now obtained T.. match magnitudes and swap list pointers
  S->sign = sign(T);

  List delete_this = S->magnitude; // save for deletion
  S->magnitude = T->magnitude; // point to T's magnitude instead

  // free the list assoscated with  S previously..
  freeList(&delete_this);

  // but when we free T.. the list will also be freed.. so set the list to null.
  T->magnitude = NULL;
  freeBigInteger(&T);
  T = NULL;
}

// sum()
// Returns a reference to a new BigInteger object representing A+B.
BigInteger sum(BigInteger A, BigInteger B) {
  // We must create S to return.
  BigInteger S;
  S = newBigInteger();
  S->sign = +1;

  // move the cursors of each list to the back and prepare to iterate forward
  // in a while loop.
  moveBack(A->magnitude); moveBack(B->magnitude);

  // sick of using '->'...
  List AList = A->magnitude;
  List BList = B->magnitude;
  List SList = S->magnitude;

  //printf("\t\tCursor A before while loop: %d", index(AList) );
  //printf("\t\tCursor B before while loop: %d", index(BList) );

  // while both cursors are defined..
  while ((index(AList) != -1) && (index(BList) != -1)) {
      // add the two list elements and insert them into the
      // new entry that is to be prepended to the list in S.
      prepend(SList, (sign(A) * get(AList)) + (sign(B) * get(BList)) );

      movePrev(AList);
      if (AList != BList) { // to avoid duplicate movement on the same list
        movePrev(BList);
      }
  }
  // A list still has stuff in it!
  if (index(AList) != -1) {
    // prepend the rest of A list
    while (index(AList) != -1) {
      prepend(SList, sign(A) * get(AList));
      movePrev(AList);
    }
  }
  // B list still has stuff in it!
  if (index(BList) != -1) {
    // prepend the rest of B list
    while (index(BList) != -1) {
      prepend(SList, sign(B) * get(BList));
      movePrev(BList);
    }
  }
  normalize(S);
  return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B) {
  BigInteger T = diff(A, B);

  // we've now obtained T.. match magnitudes and swap list pointers
  D->sign = sign(T);

  List delete_this = D->magnitude; // save for deletion
  D->magnitude = T->magnitude; // point to T's magnitude instead

  // free the list assoscated with  S previously..
  freeList(&delete_this);

  // but when we free T.. the list will also be freed.. so set the list to null.
  T->magnitude = NULL;
  freeBigInteger(&T);
  T = NULL;
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {
  // create the new BigInt
  BigInteger S = newBigInteger();
  S->sign = +1;

  moveBack(A->magnitude); moveBack(B->magnitude);

  List AList = A->magnitude;
  List BList = B->magnitude;
  List SList = S->magnitude;

  while((index(AList) != -1) && (index(BList) != -1)) {

    // straight computation
    prepend(SList, (sign(A) * get(AList)) - (sign(B) * get(BList)));
    moveFront(SList);

    //printf("\tdiff() -- just prepended value of %ld\n", get(SList));

    movePrev(AList);
    if (AList != BList) {
      movePrev(BList);
    }
  }

  // A list extras
  if (index(AList) != -1) {
    while (index(AList) != -1) {
      prepend(SList, sign(A) * get(AList));
      movePrev(AList);
    }
  }

  // B list extras (SPECIAL!.. 0 - B);
  if (index(BList) != -1) {
     while (index(BList) != -1) {
       prepend(SList, -1 * get(BList));
       movePrev(BList);
     }
  }

  normalize(S);
  return S;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B) {
  BigInteger T = prod(A, B);

  // we've now obtained T.. match magnitudes and swap list pointers
  P->sign = sign(T);

  List delete_this = P->magnitude; // save for deletion
  P->magnitude = T->magnitude; // point to T's magnitude instead

  // free the list assoscated with  S previously..
  freeList(&delete_this);

  // but when we free T.. the list will also be freed.. so set the list to null.
  T->magnitude = NULL;
  freeBigInteger(&T);
  T = NULL;
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B) {
  //printf("\t\tproduct() entered...\n");
  BigInteger TempBigInt = newBigInteger();
  TempBigInt->sign = +1;
  int duplicate = 0;

  if (A == B) {
    duplicate = 1;
    B = copy(B);
  }

  BigInteger P = newBigInteger();
  P->sign = +1; // pretend all is positive for now.


  moveBack(A->magnitude); moveBack(B->magnitude);

  int counter = 0;
  while(index(B->magnitude) != -1) {

    clear(TempBigInt->magnitude);

    //printf("\t\t\tzeros before... = %d...\n", counter);

    // if we need zeros at the beginning..
    for (int i = 0; i < counter; i++) {
      append(TempBigInt->magnitude, 0);
    }

    //printf("\t\t\t\tTempBigInt: ");
    //printBigInteger(stdout, TempBigInt);
    //printf("\n");

    // tempList is ready to go
    moveBack(A->magnitude);
    while (index(A->magnitude) != -1) {
      // multiple the current element at B to A..
      prepend(TempBigInt->magnitude, get(B->magnitude) * get(A->magnitude) );
      movePrev(A->magnitude);

      //printf("\t\t\tTempBigInt: ");
      //printBigInteger(stdout, TempBigInt);
      //printf("\n");
    }

    // at this point.. templist is built. we need to normalize
    // and add to P.
    normalize(TempBigInt);
    add(P, TempBigInt, P);
    normalize(P);
    movePrev(B->magnitude);
    counter++;
  }

  // after everything is normalized... and added. P should be built correctly
  if (sign(A) == sign(B)) {
    P->sign = +1;
  } else {
    P->sign = -1;
  }

  freeBigInteger(&TempBigInt);
  TempBigInt = NULL;

  if (duplicate == 1) {
    freeBigInteger(&B);
    B = A;
  }

  return P;
}

// -----------------------------------------------------------------
// Other operations
// -----------------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N) {
  // check for the 0 state
  if (sign(N) == 0) {
    fprintf(out, "%d", 0);
    return;
  } else if (sign(N) == -1) {
    fprintf(out, "-");
  }

  printList(out, N->magnitude);

  return;
}

// normalize()
// takes a bigInteger and normalizes it according to the current base.
void normalize(BigInteger N) {
  // hold the magnitude list.
  List NList = N->magnitude;
  // determine the sign
  if (front(NList) < 0) {
    N->sign = -1;

    // we need to flip every value
    moveFront(NList);
    while(index(NList) != -1) {
      set(NList, get(NList) * -1);
      moveNext(NList);
    }
  }
  // else the sign is positive and its time to start from the back
  // and move forward determining the amount of carries and borrows needed.
  moveBack(NList);
  long carry = 0;
  while(index(NList) != -1) {
      // apply a carry
      if (carry != 0) {
        //printf("\t\tadding %ld to %ld..\n", carry, get(NList));
        set(NList, get(NList) + carry);
        carry = 0;
      }

      // if the index is out of bounds.. determine by how much
      if (get(NList) < 0) {
        // determine how many borrows were needed..
        if ((get(NList) / BASE) == 0) {
          carry = -1;
        } else {
          carry = (get(NList) / BASE) - 1; // will product a negative carry in this case
        }
        set(NList, get(NList) + abs(BASE * carry));
      } else if (get(NList) >= BASE) {
        //printf("\ncarry applicable!\n");
        carry = (get(NList) / BASE); // will produce a positive carry
        //printf("\tcarry set to %ld!\n", carry);
        //printf("\tneed to subract %ld from the current base!\n", carry);
        set(NList, get(NList) - (BASE * carry));
      } else {
        // digit is within range and no carry is needed..
      }
      movePrev(NList);
  }

  // if a carry still exists.. prepend the amount
  if (carry > 0) {
    prepend(NList, carry);
  }

  // remove any leading entries that are zero.
  moveFront(NList);
  while(index(NList) != -1) {
    if (get(NList) == 0) {
      deleteFront(NList);
      moveFront(NList);
    } else {
      break;
    }
  }

  if (length(NList) == 0) {
    prepend(NList, 0);
    N->sign = 0;
  }
}
