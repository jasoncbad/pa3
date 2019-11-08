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
  BigInteger A, B, C;

  // string to test on
  char myString9[] = "11112278";
  char myString8[] = "9830";

  // create the big integer
  A = stringToBigInteger(myString9);
  B = stringToBigInteger(myString8);

  printBigInteger(stdout, A);
  printBigInteger(stdout, B);

  //negate(A);    // test negate

  // testing sum
  printf("\nTESTING SUM: A + B\n");
  C = sum(A, B);
  printf("\n");
  printBigInteger(stdout, C);

  //printBigInteger(stdout, A);


  // test makeZero
  printf("\nTESTING makeZero(): \n");
  makeZero(A);  // test makeZero
  printBigInteger(stdout, A);

  // free memory associated with the big integer
  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);

  return 0;
}
