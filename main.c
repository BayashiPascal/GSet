#include <stdio.h>
#include <assert.h>
#include "gset.h"

// Loop from 0 to (N - 1)
#define FOR(I, N) for (size_t I = 0; I < N; ++I)

// Dummy struct
struct Dummy {

  int a;

};

int GSetDummyCmp(
  void const* a,
  void const* b) {

  struct Dummy* sa = *(struct Dummy* const*)a;
  struct Dummy* sb = *(struct Dummy* const*)b;
  if (sa == NULL && sb == NULL) return 0;
  if (sa == NULL && sb != NULL) return -1;
  if (sa != NULL && sb == NULL) return 1;
  return (sa->a < sb->a ? -1 : sa->a > sb->a ? 1 : 0);

}

void DummyFree(struct Dummy** const that) {

  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;

}

// GSet of pointer to Dummy struct
GSETDEF(Dummy, struct Dummy*)

#define SIZE_ARR 3

char arrChar[SIZE_ARR] = {'a', 'b', 'c'};
char dataChar[2] = {'d', 'e'};

int arrInt[SIZE_ARR] = {-1, -2, -3};
int dataInt[2] = {-4, -5};

unsigned int arrUInt[SIZE_ARR] = {1, 2, 3};
unsigned int dataUInt[2] = {4, 5};

long arrLong[SIZE_ARR] = {-1, -2, -3};
long dataLong[2] = {-4, -5};

unsigned long arrULong[SIZE_ARR] = {1, 2, 3};
unsigned long dataULong[2] = {4, 5};

float arrFloat[SIZE_ARR] = {1., 2., 3.};
float dataFloat[2] = {4., 5.};

double arrDouble[SIZE_ARR] = {1., 2., 3.};
double dataDouble[2] = {4., 5.};

char* arrStr[SIZE_ARR] = {"a", "b", "c"};
char* dataStr[2] = {"d", "e"};

struct Dummy dummyA = { .a = 0 };
struct Dummy dummyB = { .a = 1 };
struct Dummy dummyC = { .a = 2 };
struct Dummy dummyD = { .a = 3 };
struct Dummy dummyE = { .a = 4 };
struct Dummy* arrDummy[SIZE_ARR] = {&dummyA, &dummyB, &dummyC};
struct Dummy* dataDummy[2] = {&dummyD, &dummyE};

void CharFree(char* that) {(void)that;}

#define TEST(Name, Type)                                                     \
  printf("Test GSet" #Name "\n");                                            \
  do {                                                                       \
    GSet ## Name* setA = GSet ## Name ## Alloc();                            \
    assert(GSetGetSize(setA) == 0);                                          \
    GSet ## Name* setB = GSet ## Name ## FromArr(SIZE_ARR, arr ## Name);     \
    assert(GSetGetSize(setB) == SIZE_ARR);                                   \
    GSetIter ## Name* iterA =                                                \
      GSetIter ## Name ## Alloc(setA);                                       \
    bool flagCatch = false;                                                  \
    Try {GSetIsFirst(iterA);}                                                \
      Catch(TryCatchExc_OutOfRange) {flagCatch = true;} EndCatch;            \
    assert(flagCatch == true);                                               \
    flagCatch = false;                                                       \
    Try {GSetIsLast(iterA);}                                                 \
      Catch(TryCatchExc_OutOfRange) {flagCatch = true;} EndCatch;            \
    assert(flagCatch == true);                                               \
    assert(GSetIterGetType(iterA) == GSetIterForward);                       \
    GSetIter ## Name* iterB =                                                \
      GSetIter ## Name ## Alloc(setB);                                       \
    assert(GSetIsFirst(iterB) == true);                                      \
    assert(GSetIsLast(iterB) == false);                                      \
    assert(GSetIterGetType(iterB) == GSetIterForward);                       \
    GSetIterSetType(iterB, GSetIterBackward);                                \
    assert(GSetIterGetType(iterB) == GSetIterBackward);                      \
    assert(GSetIsFirst(iterB) == false);                                     \
    assert(GSetIsLast(iterB) == true);                                       \
    GSetIter ## Name* iterC = GSetIter ## Name ## Clone(iterB);              \
    assert(GSetIterGetType(iterC) == GSetIterGetType(iterB));                \
    assert(GSetIsFirst(iterC) == false);                                     \
    assert(GSetIsLast(iterC) == true);                                       \
    GSetPush(setA, data ## Name[0]);                                         \
    assert(GSetGetSize(setA) == 1);                                          \
    GSetReset(iterA);                                                        \
    assert(GSetGet(iterA) == data ## Name[0]);                               \
    assert(GSetIsFirst(iterA) == true);                                      \
    assert(GSetIsLast(iterA) == true);                                       \
    GSetAdd(setA, data ## Name[1]);                                          \
    assert(GSetGetSize(setA) == 2);                                          \
    assert(GSetIsFirst(iterA) == true);                                      \
    assert(GSetIsLast(iterA) == false);                                      \
    GSetNext(iterA);                                                         \
    assert(GSetGet(iterA) == data ## Name[1]);                               \
    assert(GSetIsFirst(iterA) == false);                                     \
    assert(GSetIsLast(iterA) == true);                                       \
    GSetAddArr(setA, 2, ((Type[]) {0, 0}));                                  \
    assert(GSetGetSize(setA) == 4);                                          \
    assert(GSetIsFirst(iterA) == false);                                     \
    assert(GSetIsLast(iterA) == false);                                      \
    GSetNext(iterA);                                                         \
    assert(GSetGet(iterA) == 0);                                             \
    assert(GSetIsFirst(iterA) == false);                                     \
    assert(GSetIsLast(iterA) == false);                                      \
    GSetNext(iterA);                                                         \
    assert(GSetGet(iterA) == 0);                                             \
    assert(GSetIsFirst(iterA) == false);                                     \
    assert(GSetIsLast(iterA) == true);                                       \
    GSetAddArr(setA, 2, data ## Name);                                       \
    assert(GSetGetSize(setA) == 6);                                          \
    assert(GSetIsFirst(iterA) == false);                                     \
    assert(GSetIsLast(iterA) == false);                                      \
    GSetNext(iterA);                                                         \
    assert(GSetGet(iterA) == data ## Name[0]);                               \
    assert(GSetIsFirst(iterA) == false);                                     \
    assert(GSetIsLast(iterA) == false);                                      \
    GSetNext(iterA);                                                         \
    assert(GSetGet(iterA) == data ## Name[1]);                               \
    assert(GSetIsFirst(iterA) == false);                                     \
    assert(GSetIsLast(iterA) == true);                                       \
    Type* toArr = GSet ## Name ## ToArr(setA);                               \
    GSetReset(iterA);                                                        \
    GSETENUM(iterA, idx) assert(toArr[idx] == GSetGet(iterA));               \
    printf("%zu elements: ", GSetGetSize(setA));                             \
    GSETFOR(iterA) printf("%zu ", (size_t)GSetGet(iterA));                   \
    printf("\n");                                                            \
    free(toArr);                                                             \
    Type popA = GSetPop(setA);                                               \
    assert(popA == data ## Name[0]);                                         \
    assert(GSetGetSize(setA) == 5);                                          \
    Type dropA = GSetDrop(setA);                                             \
    assert(dropA == data ## Name[1]);                                        \
    assert(GSetGetSize(setA) == 4);                                          \
    flagCatch = false;                                                       \
    Try {GSetAppend(setA, setA);}                                            \
      Catch(TryCatchExc_InfiniteLoop) {flagCatch = true;} EndCatch;          \
    assert(flagCatch == true);                                               \
    flagCatch = false;                                                       \
    Try {GSetMerge(setA, setA);}                                             \
      Catch(TryCatchExc_InfiniteLoop) {flagCatch = true;} EndCatch;          \
    assert(flagCatch == true);                                               \
    GSetReset(iterA);                                                        \
    FOR(i, 4) GSetNext(iterA);                                               \
    GSetAppend(setA, setB);                                                  \
    assert(GSetGetSize(setA) == 4 + SIZE_ARR);                               \
    assert(GSetGetSize(setB) == SIZE_ARR);                                   \
    GSetIterSetType(iterB, GSetIterForward);                                 \
    GSetNext(iterA);                                                         \
    GSETFOR(iterB) {                                                         \
      assert(GSetGet(iterB) == GSetGet(iterA));GSetNext(iterA);              \
    }                                                                        \
    printf("%zu elements: ", GSetGetSize(setA));                             \
    GSETFOR(iterA) printf("%zu ", (size_t)GSetGet(iterA));                   \
    printf("\n");                                                            \
    GSetMerge(setA, setB);                                                   \
    assert(GSetGetSize(setA) == 4 + 2 * SIZE_ARR);                           \
    assert(GSetGetSize(setB) == 0);                                          \
    GSetShuffle(setA);                                                       \
    printf("shuffled %zu elements: ", GSetGetSize(setA));                    \
    GSETFOR(iterA) printf("%zu ", (size_t)GSetGet(iterA));                   \
    printf("\n");                                                            \
    GSetSort(setA, GSet ## Name ## Cmp, true);                               \
    printf("sorted %zu elements: ", GSetGetSize(setA));                      \
    GSETFOR(iterA) printf("%zu ", (size_t)GSetGet(iterA));                   \
    printf("\n");                                                            \
    GSetIterReset(iterA);                                                    \
    Type prev = GSetGet(iterA);                                              \
    GSetNext(iterA);                                                         \
    GSETFOR(iterA) {                                                         \
      Type cur = GSetGet(iterA);                                             \
      assert(GSet ## Name ## Cmp(&prev, &cur) < 1);                          \
      prev = cur;                                                            \
    }                                                                        \
    GSetReset(iterA);                                                        \
    Type picked = GSetPick(iterA);                                           \
    assert(GSetGetSize(setA) == 9);                                          \
    GSetNext(iterA);                                                         \
    picked = GSetPick(iterA);                                                \
    assert(GSetGetSize(setA) == 8);                                          \
    while (GSetNext(iterA));                                                 \
    picked = GSetPick(iterA);                                                \
    (void)picked;                                                            \
    assert(GSetGetSize(setA) == 7);                                          \
    printf("remaining %zu elements: ", GSetGetSize(setA));                   \
    GSETFOR(iterA) printf("%zu ", (size_t)GSetGet(iterA));                   \
    printf("\n");                                                            \
    GSetEmpty(setA);                                                         \
    assert(GSetGetSize(setA) == 0);                                          \
    GSetShuffle(setA);                                                       \
    GSetSort(setA, GSet ## Name ## Cmp, true);                               \
    GSetAddArr(setA, 2, ((Type[]) {0, 0}));                                  \
    GSetIterFree(&iterA);                                                    \
    assert(iterA == NULL);                                                   \
    GSetIterFree(&iterB);                                                    \
    assert(iterB == NULL);                                                   \
    GSetIterFree(&iterC);                                                    \
    assert(iterC == NULL);                                                   \
    GSetFree(&setA);                                                         \
    assert(setA == NULL);                                                    \
    GSetFree(&setB);                                                         \
    assert(setB == NULL);                                                    \
    printf("Test GSet" #Name " OK\n");                                       \
  } while(false)

#define TESTPTR(Name, Type)                                                  \
  TEST(Name, Type*);                                                         \
  do {                                                                       \
    GSet ## Name* setA = GSet ## Name ## Alloc();                            \
    Type* data = malloc(sizeof(Type));                                       \
    GSetPush(setA, data);                                                    \
    GSet ## Name ## Flush(setA);                                             \
    GSetFree(&setA);                                                         \
  } while(false)

// Main function
int main() {

  printf(
    "Commit id: %s\n",
    GSetGetCommitId());
  TEST(Char, char);
  TEST(Int, int);
  TEST(UInt, unsigned int);
  TEST(Long, long);
  TEST(ULong, unsigned long);
  TEST(Float, float);
  TEST(Double, double);
  TESTPTR(Str, char);
  TESTPTR(Dummy, struct Dummy);
  printf("All unit tests OK\n");

  // Return the sucess code
  return EXIT_SUCCESS;

}
