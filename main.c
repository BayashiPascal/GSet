#include <stdio.h>
#include <assert.h>
#include "gset.h"

// Dummy struct
struct Dummy {

  int a;

};

int GSetDummyCmp(void const* a, void const* b) {

  struct Dummy* sa = *(struct Dummy* const*)a;
  struct Dummy* sb = *(struct Dummy* const*)b;
  return (sa->a < sb->a ? -1 : sa->a > sb->a ? 1 : 0);

}

// GSet of pointer to Dummy struct
DefineGSet(Dummy, struct Dummy*)

#define sizeArr 3

char arrChar[sizeArr] = {'a', 'b', 'c'};
char dataChar[2] = {'d', 'e'};

char* arrStr[sizeArr] = {"a", "b", "c"};
char* dataStr[2] = {"d", "e"};

struct Dummy dummyA = {.a = 0};
struct Dummy dummyB = {.a = 1};
struct Dummy dummyC = {.a = 2};
struct Dummy dummyD = {.a = 3};
struct Dummy dummyE = {.a = 4};
struct Dummy* arrDummy[sizeArr] = {&dummyA, &dummyB, &dummyC};
struct Dummy* dataDummy[2] = {&dummyD, &dummyE};

#define STRINGIFY(x) #x
#define STRINGIFY_VALUE_OF(x) STRINGIFY(x)

#define Test(Name, Type)                                                     \
  do {                                                                       \
    GSet ## Name* setA = GSet ## Name ## Alloc();                            \
    assert(GSetGetSize(setA) == 0);                                          \
    GSet ## Name* setB = GSet ## Name ## FromArr(sizeArr, arr ## Name);      \
    assert(GSetGetSize(setB) == sizeArr);                                    \
    GSetIter ## Name* iterA =                                                \
      GSetIter ## Name ## Alloc(setA);                                       \
    bool flagCatch = false;                                                  \
    Try {GSetIsFirst(iterA);}                                                \
    Catch(TryCatchExc_OutOfRange) {flagCatch = true;} EndCatch;              \
    assert(flagCatch == true);                                               \
    flagCatch = false;                                                       \
    Try {GSetIsLast(iterA);}                                                 \
    Catch(TryCatchExc_OutOfRange) {flagCatch = true;} EndCatch;              \
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
    assert(GSetIsLast(iterA) == true);                                      \
    GSetAdd(setA, data ## Name[1]);                                          \
    assert(GSetGetSize(setA) == 2);                                          \
    assert(GSetIsFirst(iterA) == true);                                      \
    assert(GSetIsLast(iterA) == false);                                      \
    GSetNext(iterA);                                                        \
    assert(GSetGet(iterA) == data ## Name[1]);                               \
    assert(GSetIsFirst(iterA) == false);                                      \
    assert(GSetIsLast(iterA) == true);                                      \
    GSetAddArr(setA, 2, ((Type[]){0,0}));                                    \
    GSetAddArr(setA, 2, data ## Name);                                       \
    Type* toArr = GSet ## Name ## ToArr(setA);                               \
    free(toArr);                                                             \
    Type popA = GSetPop(setA);                                               \
    assert (popA == data ## Name[0]);                                        \
    Type dropA = GSetDrop(setA);                                             \
    assert (dropA == data ## Name[1]);                                       \
    GSetAppend(setA, setB);                                                  \
    GSetMerge(setA, setB);                                                   \
    assert (GSetGetSize(setA) == 10);                                        \
    GSetEmpty(setA);                                                         \
    GSetShuffle(setA);                                                       \
    GSetSort(setA, GSet ## Name ## Cmp, true);                               \
    Type getA;                                                               \
    Try {getA = GSetGet(iterA);} CatchDefault {} EndCatchDefault;            \
    Try {getA = GSetPick(iterA);} CatchDefault {} EndCatchDefault;           \
    GSetReset(iterA);                                                        \
    GSetNext(iterA);                                                         \
    GSetPrev(iterA);                                                         \
    Try {GSetIsFirst(iterA);} CatchDefault {} EndCatchDefault;               \
    Try {GSetIsLast(iterA);} CatchDefault {} EndCatchDefault;                \
    GSetForEach(iterA) {                                                     \
      getA = GSetGet(iterA);                                                 \
    }                                                                        \
    (void)getA;                                                              \
    GSetIterFree(&iterA);                                                    \
    GSetIterFree(&iterB);                                                    \
    GSetIterFree(&iterC);                                                    \
    GSetFree(&setA);                                                         \
    GSetFree(&setB);                                                         \
    printf("GSet%s OK\n", STRINGIFY_VALUE_OF(Name));                         \
  } while(false)

// Main function
int main() {

GSetChar* set = GSetCharAlloc();
GSetAdd(set, 'a');
GSetAddArr(set, 2, ((char[]){0,0}));
GSetAppend(set, set);
GSetEmpty(set);
GSetFree(&set);

  printf("Commit id: %s\n", GSetGetCommitId());
  //Test(Char, char);
  //Test(Str, char*);
  //Test(Dummy, struct Dummy*);

  // Return the sucess code
  return EXIT_SUCCESS;

}

