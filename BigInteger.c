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
          returnThis = -1; break;
        } else if (elementB < elementA) {
          returnThis = 1; break;
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
  return 0; // dummy return that is never actually reached
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
  A->magnitude = copyList(N->magnitude);

  // return the deep copy
  // we have allocated HEAP data for a new BigInteger, and also for a new List.
  return A;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting it's
// current state: S = A + B.
void add(BigInteger S, BigInteger A, BigInteger B) {
  // CASE: S = A + B
  // we can perform the normal algorithm since none of the mechanisms will
  // collide
  int carry = 0;
  if (S != A && S != B) {
    makeZero(S); // we will be overwriting S...

    // if both are negative
    if ((A->sign == -1) && (B->sign == -1)) {
      // follow the normal algorithm. Ensure result S is negative.
      S->sign = -1;
    } else if (A->sign == -1 && B->sign == 1) {
      // we must perform B - A
      subtract(S, B, A);
      return;
    } else if (A->sign == 1 && B->sign == -1) {
      // we must perform A - B
      subtract(S, A, B);
      return;
    } else {
      S->sign = 1;
    }

    // we need to save the state of the cursors in A and B because we want to
    // restore this state after the operation.
    int a_cursor_state = index(A->magnitude);
    int b_cursor_state = index(B->magnitude);

    // move the cursors of each list to the back and prepare to iterate forward
    // in a while loop.
    moveBack(A->magnitude); moveBack(B->magnitude);

    // create a flag called carry which will let us know if a carry is needed.

    // sick of using '->'...
    List AList = A->magnitude;
    List BList = B->magnitude;
    List SList = S->magnitude;

    printf("\n\t\tCursor A before while loop: %d", index(AList) );
    printf("\n\t\tCursor B before while loop: %d\n", index(BList) );

    // while both cursors are defined..
    while ((index(AList) != -1) && (index(BList) != -1)) {

        printf("\n\t\tSList: ");
        printList(stdout, SList);

        // add the two list elements and insert them into the
        // new entry that is to be prepended to the list in S.
        prepend(SList, get(AList) + get(BList));

        // move the cursor in S to the front because that is where we are operating
        moveFront(SList);

        // if theres a carry.. account for it
        if (carry == 1) {
          set(SList, get(SList) + 1);
          carry = 0;
        }

        if (get(SList) >= BASE) {
          carry = 1;
        }

        movePrev(AList);
        movePrev(BList);
    }

    // A list still has stuff in it!
    if (index(AList) != -1) {
      // prepend the rest of A list
      while (index(AList) != -1) {
        if (carry == 1) {
          prepend(SList, get(AList) + 1);
          carry = 0;
        } else {
          prepend(SList, get(AList));
        }
        movePrev(AList);
      }
    }

    //printList(stdout, SList);

    // B list still has stuff in it!
    if (index(BList) != -1) {
      // prepend the rest of B list
      while (index(BList) != -1) {
        if (carry == 1) {
          prepend(SList, get(BList) + 1);
          carry = 0;
        } else {
          prepend(SList, get(BList));
        }
        movePrev(BList);
      }
    }

    //printList(stdout, SList);

    // what if we still have a carry?
    // prepend a new entry
    if (carry == 1) {
      prepend(SList, 1);
      carry = 0;
    }

    //printList(stdout, SList);

    // Normalize!
    normalize(S);

    //printList(stdout, SList);

    // RESTORE CURSOR STATES!
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
    return; // return because we've finished
  }

  // CASE: S = S + A;
  // one of the operands is S, so building solution S will require performing
  // the algorithm by adding values of A to S.
  // CASE: S = A + S;
  else if ((S == A && S != B) || (S == B && S != A)) {

    // determine BigInteger K which is not equal to S...
    BigInteger K;
    if (S == A && S != B) K = B;
    else if (S == B && S != A) K = A;

    // if both are negative
    if ((K->sign == -1) && (S->sign == -1)) {
      // follow the normal algorithm. Ensure result S is negative.
      S->sign = -1;
    } else if (K->sign == -1 && S->sign == 1) {
      // we must perform S - K
      subtract(S, S, K);
      return;
    } else if (K->sign == 1 && S->sign == -1) {
      // we must perform K - S
      subtract(S, K, S);
      return;
    }

    // else perform the addition because both are positive

    List KList = K->magnitude;
    List SList = S->magnitude;
    int k_cursor_state = index(KList);
    int s_cursor_state = index(SList);

    // use K from now on.. now just add values of K to S, following the carry
    // convention, and then normalize.. restore cursor K.

    moveBack(KList);
    moveBack(SList);

    // while K cursor is still active
    int carry = 0;
    while( index(KList) != -1 ) {
      // add the element K to S.
      set(SList, get(SList) + get(KList)); // S + K
      // account for carry
      if (carry == 1) {
        set(SList, get(SList) + 1);
        carry = 0;
      }
      if (get(SList) >= BASE) {
        carry = 1;
      }
      // iterate
      movePrev(SList);
      movePrev(KList);
    }
    // if K went undefined.. We don't need to work on S anymore.. but we do
    // need to worry about the carry.
    if (index(KList) == -1 && index(SList) != -1) {
      // cursor is already where we need it.
      // account for carry
      if (carry == 1) {
        set(SList, get(SList) + 1);
        carry = 0;
      }
    } else if (index(SList) == -1 && index(KList) != -1) {
      // if S went undefined.. then we need to prepend the remaining entries of K
      // to S.. all while considering the carry
      // so S is now undefined.. K is defined
      while ( index(KList) != -1) {
        // prepend directly
        prepend(SList, get(KList));
        // account for carry
        if (carry == 1) {
          set(SList, get(SList) + 1);
          carry = 0;
        }
        if (get(SList) >= BASE) {
          carry = 1;
        }
        movePrev(KList);
      }
    }

    // both cursors went undefined at the same time.
    normalize(S);

    // restore cursor states
    if (s_cursor_state != -1) {
      moveFront(S->magnitude);
      for (int i = 0; i < s_cursor_state; i++) {
        moveNext(S->magnitude);
      }
    }
    if (k_cursor_state != -1) {
      moveFront(K->magnitude);
      for (int i = 0; i < k_cursor_state; i++) {
        moveNext(K->magnitude);
      }
    }
    return;
  }

  // CASE S = S + S = 2S
  // this case requires multiplying by 2.
  else if (S == A && S == B) {
    if (S->sign == -1) {
      S->sign = 1; // negative times negative is positive
    }

    List SList = S->magnitude;
    carry = 0;
    moveBack(SList);
    while (index(SList) != -1) {
      // perform the operation
      set(SList,  2 * get(SList));

      // account for carry
      if (carry == 1) {
        set(SList, get(SList) + 1);
        carry = 0;
      }
      if (get(SList) >= BASE) carry = 1;
      movePrev(SList);
    }

    // we are all done. Check for the carry one last time
    if (carry == 1) {
      prepend(SList, 1);
      carry = 0;
    }
    normalize(S); // normalize
    return;
  } else return;
}

// sum()
// Returns a reference to a new BigInteger object representing A+B.
BigInteger sum(BigInteger A, BigInteger B) {
  // We must create S to return.
  BigInteger S;

  // we need to determine the sign of the result
  if (A->sign == -1 && B->sign == -1) {
    // apply the algorithm to the lists normally and set sign of S to -.
    S = newBigInteger();
    S->sign = -1;
  } else if (A->sign == -1 && B->sign == 1) {
    // not applicable.. we need B - A
    // so call B - A!!
    S = diff(B, A);
    return S; // and return the result.
  } else if (A->sign == 1 && B->sign == -1) {
    // not applicable.. we need A - B
    // so call A - B!
    S = diff(A, B);
    return S;
  } else {

  // we dont care about both being positive because thats why this method exists
  // in the first place.

  // only allocate heap memory if we need to create it in SUM.. becayse in the
  // previous lines it will be created in difference.
  S = newBigInteger();

  }

  // we need to save the state of the cursors in A and B because we want to
  // restore this state after the operation.
  int a_cursor_state = index(A->magnitude);
  int b_cursor_state = index(B->magnitude);

  // move the cursors of each list to the back and prepare to iterate forward
  // in a while loop.
  moveBack(A->magnitude); moveBack(B->magnitude);

  // create a flag called carry which will let us know if a carry is needed.
  int carry = 0;

  // sick of using '->'...
  List AList = A->magnitude;
  List BList = B->magnitude;
  List SList = S->magnitude;

  printf("\t\tCursor A before while loop: %d", index(AList) );
  printf("\t\tCursor B before while loop: %d", index(BList) );

  // while both cursors are defined..
  while ((index(AList) != -1) && (index(BList) != -1)) {

      //printf("\t\tSList: ");
      //printList(stdout, SList);

      // add the two list elements and insert them into the
      // new entry that is to be prepended to the list in S.
      prepend(SList, get(AList) + get(BList));

      // move the cursor in S to the front because that is where we are operating
      moveFront(SList);

      // if theres a carry.. account for it
      if (carry == 1) {
        set(SList, get(SList) + 1);
        carry = 0;
      }

      if (get(SList) >= BASE) {
        carry = 1;
      }

      movePrev(AList);
      movePrev(BList);
  }

  //printList(stdout, SList);

  // A list still has stuff in it!
  if (index(AList) != -1) {

    // prepend the rest of A list
    while (index(AList) != -1) {
      if (carry == 1) {
        prepend(SList, get(AList) + 1);
        carry = 0;
      } else {
        prepend(SList, get(AList));
      }
      movePrev(AList);
    }
  }

  //printList(stdout, SList);

  // B list still has stuff in it!
  if (index(BList) != -1) {
    // prepend the rest of B list
    while (index(BList) != -1) {
      if (carry == 1) {
        prepend(SList, get(BList) + 1);
        carry = 0;
      } else {
        prepend(SList, get(BList));
      }
      movePrev(BList);
    }
  }

  //printList(stdout, SList);

  // what if we still have a carry?
  // prepend a new entry
  if (carry == 1) {
    prepend(SList, 1);
    carry = 0;
  }

  //printList(stdout, SList);

  // Normalize!
  normalize(S);

  //printList(stdout, SList);

  // RESTORE CURSOR STATES!
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

  printList(stdout, SList);

  return S;
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


  // create the new BigInt
   BigInteger S = newBigInteger();

   int comparison = compare(A,B);
   if (comparison < 0) {
     BigInteger Temp = A;
     A = B;
     B = Temp;
     S->sign = -1;
   } else if (comparison > 0) {
     if (sign(B) == -1) {
       printf("\nB is negative and less than S..")
       free(S);
       negate(B);
       S = sum(A,B);
       S->sign = 1;
       negate(B);
       return S;
    } else {
       S->sign = 1;
    }
   }



  // the sign of the result will now be handled in normalize because its \
  // way too complicated now

  int a_cursor_state = index(A->magnitude);
  int b_cursor_state = index(B->magnitude);
  moveBack(A->magnitude); moveBack(B->magnitude);

  int carry = 0;
  List AList = A->magnitude;
  List BList = B->magnitude;
  List SList = S->magnitude;

  while((index(AList) != -1) && (index(BList) != -1)) {

    // straight computation
    prepend(SList, (sign(A) * get(AList)) - (sign(B) * get(BList)));
    moveFront(SList);

    // subtract the carry if it exists
    if (carry != 0) {
      set(SList, get(SList)-1); // if we had a negative carry.. accounts for it
      carry = 0;
    }

    if (get(SList) < 0) {
      // set the carry to -1 for the next cycle
      carry = 1;
    }

    movePrev(AList);
    movePrev(BList);
  }

  // A list extras
  if (index(AList) != -1) {
    // prepend the rest of A list
    if (carry == 1) {
      prepend(SList, get(AList) - 1);
      carry = 0;
    } else {
      prepend(SList, get(AList));
    }
    movePrev(AList);
  }

  // B list extras (SPECIAL!.. 0 - B);
  if (index(BList) != -1) {
     while (index(BList) != -1) {
       if (carry == 1) {
         prepend(SList, (-1 * (get(BList)) - 1));
         carry = 0;
       } else {
         prepend(SList, -1 * get(BList));
       }
       movePrev(BList);
     }
  }

  // still have a carry?
  if (carry == 1) {
    prepend(SList, 1); // PREVIOUS METHOD
    //moveFront(SList);
    //set(SList, get(SList) + 1);
    carry = 0;
  } else if (carry == -1) {
    prepend(SList, -1);
  }

  normalize(S);
  return S;
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
  // defined a value to represent the list.
  List M = N->magnitude;

  // we need to go through the entire list and subtract the base if necessary.
  moveFront(M);

  // if the first entry is negative
  if (get(M) < 0) {
    // we know the sign now
    N->sign = -1;
    // flip everything
    while(index(M) != -1) {
      set(M, -1 * get(M));
      moveNext(M);
    }
  } else if (get(M) > 0) {
    // perform the normailzation for a positive answer
    //
  } else {
    // the front value of M equals 0..
    // we need to
  }

  moveFront(M);
  while (index(M) != -1) {
    if (get(M) >= BASE) {
      set(M, get(M) - BASE);
    } else if (get(M) < 0) {
      set(M, get(M) + BASE);
    }
    moveNext(M);
  }
}
