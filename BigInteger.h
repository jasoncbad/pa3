/* --------------------------------

  BigInteger.h | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

-----------------------------------
*/
typedef struct BigIntegerObj* BigInteger;

// Constructor/Destructor
BigInteger newBigInteger();
void freeBigInteger(BigInteger* pN);

// access functions
int sign(BigInteger N);
int compare(BigInteger A, BigInteger B);
int equals(BigInteger A, BigInteger B);

// manipulation procedures
void makeZero(BigInteger N);
void negate(BigInteger N);

// BigInteger arithmetic operations
BigInteger stringToBigInteger(char* s);
BigInteger copy(BigInteger N);
void add(BigInteger S, BigInteger A, BigInteger B);
BigInteger sum(BigInteger A, BigInteger B);
void subtract(BigInteger D, BigInteger A, BigInteger B);
BigInteger diff(BigInteger A, BigInteger B);
void multiply(BigInteger P, BigInteger A, BigInteger B);
BigInteger prod(BigInteger A, BigInteger B);

// other operations
void printBigInteger(FILE* out, BigInteger N);
void normalize(BigInteger N);
