

Programming Assignment 3 | BigInteger


Programmer: Jay Montoya
UCSC ID: jaanmont | 1742317

  This project creates a BigInteger ADT capable of performing arithmetic
operations on arbitrarily large signed integers. The underlying datastructure
for the BigInteger is a List of longs which represents the magnitude.

The BigInteger data type contains the abovementioned list of longs, and an
int representing the sign (-1, +1, 0). Along with the following operations:

  BigInteger stringToBigInteger(char* s);
  BigInteger copy(BigInteger N);
  void add(BigInteger S, BigInteger A, BigInteger B);
  BigInteger sum(BigInteger A, BigInteger B);
  void subtract(BigInteger D, BigInteger A, BigInteger B);
  BigInteger diff(BigInteger A, BigInteger B);
  void multiply(BigInteger P, BigInteger A, BigInteger B);
  BigInteger prod(BigInteger A, BigInteger B);
  void printBigInteger(FILE* out, BigInteger N);
  void normalize(BigInteger N);

  For submission purposes, BASE has been set to 1000000000 and POWER has been
set to 9 in the file BigInteger.c.

  This project passes the test script completely and free of memory leaks as of
11/16/2019.
