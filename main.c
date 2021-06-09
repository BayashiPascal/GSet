#include <stdio.h>
#include <assert.h>
#include "gset.h"

// Dummy struct
struct Dummy {

  int a;

};

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

#define Test(Name, Type)                                                     \
  do {                                                                       \
    GSet ## Name* setA = GSet ## Name ## Alloc();                            \
    GSet ## Name* setB = GSet ## Name ## FromArr(sizeArr, arr ## Name);      \
    GSetIter ## Name* iterA =                                                \
      GSetIter ## Name ## Alloc(setA, GSetIterForward);                      \
    GSetIter ## Name* iterB =                                                \
      GSetIter ## Name ## Alloc(setA, GSetIterBackward);                     \
    GSetIter ## Name* iterC = GSetIter ## Name ## Clone(iterA);              \
    GSetPush(setA, data ## Name[0]);                                         \
    GSetAdd(setA, data ## Name[1]);                                          \
    GSetAddArr(setA, 2, ((Type[]){0,0}));                                    \
    GSetAddArr(setA, 2, data ## Name);                                       \
    Type* toArr = GSet ## Name ## ToArr(setA);                               \
    free(toArr);                                                             \
    Type popA = GSetPop(setA);                                               \
    assert (popA == data ## Name[0]);                                        \
    Type dropA = GSetDrop(setA);                                             \
    assert (dropA == data ## Name[1]);                                       \
    GSetAppend(setA, setB);                                                  \
    GSetIterFree(&iterA);                                                    \
    GSetIterFree(&iterB);                                                    \
    GSetIterFree(&iterC);                                                    \
    GSetFree(&setA);                                                         \
    GSetFree(&setB);                                                         \
  } while(false)

// Main function
int main() {

  Test(Char, char);
  Test(Str, char*);
  Test(Dummy, struct Dummy*);

  // Return the sucess code
  return EXIT_SUCCESS;

}

