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
  BigInteger A, B, C, D, E;

  // string to test on
  char myString9[] = "9163574346363325007361058";
  char myString8[] = "+4597814412658653960738664";

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

  printf("\nTESTING ADD: E = A + B\n");
  E = newBigInteger();
  add(E, A, B);
  printf("\n");
  printBigInteger(stdout, E);
  freeBigInteger(&E);

  printf("\nTESTING ADD: E = A + A\n");
  E = newBigInteger();
  add(E, A, A);
  printf("\n");
  printBigInteger(stdout, E);
  freeBigInteger(&E);

  printf("\nTESTING ADD: A = A + A\n\t(a has been changed!)\n");
  add(A, A, A);
  printf("\n");
  printBigInteger(stdout, A);

  printf("\nTESTING DIFF: A - B\n");
  D = diff(A, B);
  printf("\n");
  printBigInteger(stdout, D);


  printf("\nTESTING SUBTRACT: E = A - B\n");
  E = newBigInteger();
  subtract(E, A, B);
  printf("\n");
  printBigInteger(stdout, E);
  freeBigInteger(&E);

  printf("\nTESTING SUBTRACT: E = A - A\n");
  E = newBigInteger();
  subtract(E, A, A);
  printf("\n");
  printBigInteger(stdout, E);

  printf("\nTESTING SUBTRACT: A = A - A\n");
  subtract(A, A, A);
  printf("\n");
  printBigInteger(stdout, A);

  printf("\nTESTING PROD: A - B\n");
  freeBigInteger(&A);
  A = stringToBigInteger(myString9);
  BigInteger F = prod(A, B);
  printBigInteger(stdout, F);



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
  freeBigInteger(&D);
  freeBigInteger(&E);
  freeBigInteger(&F);

  return 0;
}
