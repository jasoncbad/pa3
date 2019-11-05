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

  char myString1[] = "-000010209390";
  char myString2[] = "+00001020939000";
  char myString3[] = "-010209390";
  char myString4[] = "-4324879";
  char myString5[] = "93280";
  char myString6[] = "11";
  char myString7[] = "0";
  char myString8[] = "+22";
  char myString9[] = "-0";
  char myString10[] = "-11";

  A = stringToBigInteger(myString9);

  // free memory associated with the big integer
  freeBigInteger(&A);

  return 0;
}
