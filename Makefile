# --------------------------------
#
#  Makefile | PA3
#  Programmer: Jay Montoya
#  UCSC ID: jaanmont | 1742317
#
#-----------------------------------
ListTest : ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	gcc -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

BigIntegerTest.o : BigIntegerTest.c BigInteger.h
	gcc -c -std=c99 -Wall BigIntegerTest.c

BigInteger.o :	BigInteger.c BigInteger.h
	gcc -c -std=c99 -Wall BigInteger.c

clean :
	rm -f Lex ListTest ListTest.o List.o BigIntegerTest BigIntegerTest.o BigInteger.o
