#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"
#include "string.h"
#define MAX_BUFFER 50

int main(int argc, char** argv) {
  // 1) Check that there are two command line arguments (other than the program
  // name). Quit with a usage message to stderr if more than or less than
  // two strings are given on the command line.
  printf("You entered %d arguments...\n" , argc);

  for (int i = 0; i < argc; ++i)
    printf("%s ", argv[i]);

  if (argc != 3) {
    fprintf(stderr, "%s", "STDERR: bad argument structure\n");
    exit(1);
  }

  // declare files
  FILE* inFile;
  FILE* outFile;

  // open streams to files
  inFile = fopen(argv[1], "r");
  outFile = fopen(argv[2],"w");

  // read the entire line
  /*while(fgets(str, MAX_BUFFER, inFile) != NULL) {
    strcpy(inputArray[j], str);
  }*/

  char* string1;
  char* string2;

  // scan the top of the file to get the length of the number on line 2
  int n;
  fscanf(inFile, "%d\n", &n);
  string1 = calloc(n+2, sizeof(char));
  fscanf(inFile, "%s\n", string1);

  int m;
  fscanf(inFile, "%d\n", &m);
  string2 = calloc(n+2, sizeof(char));
  fscanf(inFile, "%s\n", string2);

  // create the big integers...
  BigInteger A, B, C, D, E;
  A = stringToBigInteger(string1);
  B = stringToBigInteger(string2);

  printBigInteger(outFile, A);
  fprintf(outFile, "\n\n");
  printBigInteger(outFile, B);
  fprintf(outFile, "\n\n");

  // calc sum and diff
  C = sum(A, B);
  D = diff(A, B);

  printBigInteger(outFile, C);
  fprintf(outFile, "\n\n");
  printBigInteger(outFile, D);
  fprintf(outFile, "\n\n");

  // calc A - A
  freeBigInteger(&C);
  C = diff(A, A);
  printBigInteger(outFile, C);
  fprintf(outFile, "\n\n");

  // calc 3A - 2B
  freeBigInteger(&C);
  C = sum(A, A);
  add(C, C, A);

  freeBigInteger(&D);
  D = sum(B, B);

  E = diff(C, D);

  printBigInteger(outFile, E);
  fprintf(outFile, "\n\n");




  // AB

  // A^2

  // B^2

  // 9A^4 + 16B^5


  // houskeeping
  fclose(inFile);
  fclose(outFile);

  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);
  A = NULL;
  B = NULL;
  C = NULL;
  D = NULL;

  free(string1);
  free(string2);
  string1 = NULL;
  string2 = NULL;

  return 0;
}
