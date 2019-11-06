/* --------------------------------

  BigIntegerTest.c | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Test client for BigInteger ADT for pa3.

-----------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

// main
int main(int argc, char* argv[]) {

  // create a big integer list
  BigInteger A;

  // string to test on
  char myString9[] = "6523485630758234007488392857982374523487612398700554";

  // create the big integer
  A = stringToBigInteger(myString9);

  printBigInteger(stdout, A);

  negate(A);    // test negate

  printBigInteger(stdout, A);

  makeZero(A);  // test makeZero

  printBigInteger(stdout, A);

  // free memory associated with the big integer
  freeBigInteger(&A);

  return 0;
}
