/* --------------------------------

  List.h | PA3
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

-----------------------------------
*/
typedef struct ListObj* List;

// construction/destruction
List newList(void);
void freeList(List* pL);

// accessors
int length(List L);
int index(List L);
long front(List L);
long back(List L);
long get(List L);

// operations
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, long data);
void append(List L, long data);
void insertBefore(List L, long data);
void insertAfter(List L, long data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

void printList(FILE* out, List L);

// also included for this project
List copyList(List L);
void set(List L, long x);
int listEquals(List A, List B);
