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
  char myString9[] = "+2276072577093344144759489101587794740543956923406513235017249485312182256620379054691648041393022029";
  char myString8[] = "+9521651023449965519405564118547355094880066777565423238991085675906554459642294029683201863865856036";

  // create the big integer
  A = stringToBigInteger(myString9);
  B = stringToBigInteger(myString8);

  printBigInteger(stdout, A);
  printBigInteger(stdout, B);

  //negate(A);    // test negate

  // testing sum
  printf("\nTESTING DIFF: A + B\n");
  C = diff(A, B);
  printf("\n");
  printBigInteger(stdout, C);

  //printBigInteger(stdout, A);

  // testing add
  /*printf("\nTESTING ADD: C = A + B");

  add(C, A, B);
  printf("\n");
  printBigInteger(stdout, C);*/


  // test makeZero
  printf("\nTESTING makeZero(): \n");
  makeZero(A);  // test makeZero
  printBigInteger(stdout, A);
  printf("\n");

  // free memory associated with the big integer
  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);

  return 0;
}
