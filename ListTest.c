/* --------------------------------

  ListTest.c | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Test client for List ADT for pa3.

-----------------------------------
*/
#include <stdio.h>
#include "List.h"

// main
int main(int argc, char* argv[]) {
  printf("Test client started...\n");

  // create a couple List ADT's
  List A = newList();
  List B = newList();

  // add some values
  printf("\tList A/B created.. adding values...");
  append(A, 1337);
  append(A, 123456789);
  append(A, 987654321);
  append(A, 27272);
  append(B, 783978);
  append(B, 3);
  append(B, 89384);
  append(B, 28373);

  // print the lists to console
  printf("\tLIST A: "); printList(A);
  printf("\t\tlength = %d", length(A));
  printf("\tLIST B: "); printList(B);
  printf("\t\tlength = %d", length(B));

  // retrieve some values
  moveFront(A); moveFront(B);
  printf("\tFront value at A is: %d\n", get(A));
  printf("\tFront value at B is: %d\n", get(B));
  moveBack(A); moveBack(B);
  printf("\tBack value at A is: %d\n", get(A));
  printf("\tBack value at B is: %d\n", get(B));

  // insert before and insert after
  printf("\t\tInserting the value 420 before A's cursor... \n");
  insertBefore(A, 420);
  printf("\t\tInserting the value 420 after B's cursor... \n");
  insertAfter(B, 420);

  // print the lists to console
  printf("\tLIST A: "); printList(A);
  printf("\t\tlength = %d", length(A));
  printf("\tLIST B: "); printList(B);
  printf("\t\tlength = %d", length(B));


  // TODO: write tests for clear() movePrev() moveNext()
  //    prepend(), deleteFront(), deleteBack(), delete()
  //    concatList(), copyList(), set()

  // Test all that shit and valgrind that shit

  // START ON BIGINTEGER RIGHT AWAY YOU PIECE OF SHIT






  // clean up our mess
  freeList(&A);
  freeList(&B);

  printf("Test client ended...\n\n");
  return 0;
}
