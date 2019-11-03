# --------------------------------
#
#  Makefile | PA3
#  Programmer: Jay Montoya
#  UCSC ID: jaanmont | 1742317
#
#-----------------------------------
ListClient : ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

MatrixTest : MatrixTest.o Matrix.o List.o
	gcc -o MatrixTest MatrixTest.o Matrix.o List.o

MatrixClient : MatrixClient.o Matrix.o List.o
	gcc -o MatrixClient MatrixClient.o Matrix.o List.o

Sparse : Sparse.o Matrix.o List.o
	gcc -o Sparse Sparse.o Matrix.o List.o

MatrixTest.o : MatrixTest.c Matrix.h
	gcc -c -std=c99 -Wall MatrixTest.c

Sparse.o : Sparse.c Matrix.h
	gcc -c -std=c99 -Wall Sparse.c

Matrix.o :	Matrix.c Matrix.h
	gcc -c -std=c99 -Wall Matrix.c

clean :
	rm -f Lex ListClient ListClient.o List.o MatrixTest MatrixTest.o Matrix.o Sparse Sparse.o
