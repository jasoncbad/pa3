/* --------------------------------

  BigIntegerTest.c | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Test client for BigInteger ADT for pa3.

-----------------------------------
*/
#include <stdio.h>
#include "BigInteger.h"

// main
int main(int argc, char* argv[]) {

  // create a big integer list
  BigInteger A;

  char myString[] = "-000010209390";

  A = stringToBigInteger(myString);

  // free memory associated with the big integer
  freeBigInteger(&A);

  return 0;
}
