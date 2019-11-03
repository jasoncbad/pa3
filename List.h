//
// Jay Montoya
// 1742317 - jaanmont
// pa2
//
typedef struct ListObj* List;

List newList(void);
void freeList(List* pL);

int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* data);
void append(List L, void* data);
void insertBefore(List L, void* data);
void insertAfter(List L, void* data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

void printList(FILE* out, List L);

List concatList(List A, List B);
