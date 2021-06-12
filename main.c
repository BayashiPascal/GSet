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
    assert(GSETGETSIZE(setA) == 0);                                          \
    GSet ## Name* setB = GSet ## Name ## FromArr(SIZE_ARR, arr ## Name);      \
    assert(GSETGETSIZE(setB) == SIZE_ARR);                                    \
    GSetIter ## Name* iterA =                                                \
      GSetIter ## Name ## Alloc(setA);                                       \
    bool flagCatch = false;                                                  \
    Try {GSETISFIRST(iterA);}                                                \
      Catch(TryCatchExc_OutOfRange) {flagCatch = true;} EndCatch;            \
    assert(flagCatch == true);                                               \
    flagCatch = false;                                                       \
    Try {GSETISLAST(iterA);}                                                 \
      Catch(TryCatchExc_OutOfRange) {flagCatch = true;} EndCatch;            \
    assert(flagCatch == true);                                               \
    assert(GSETITERGETTYPE(iterA) == GSetIterForward);                       \
    GSetIter ## Name* iterB =                                                \
      GSetIter ## Name ## Alloc(setB);                                       \
    assert(GSETISFIRST(iterB) == true);                                      \
    assert(GSETISLAST(iterB) == false);                                      \
    assert(GSETITERGETTYPE(iterB) == GSetIterForward);                       \
    GSETITERSETTYPE(iterB, GSetIterBackward);                                \
    assert(GSETITERGETTYPE(iterB) == GSetIterBackward);                      \
    assert(GSETISFIRST(iterB) == false);                                     \
    assert(GSETISLAST(iterB) == true);                                       \
    GSetIter ## Name* iterC = GSetIter ## Name ## Clone(iterB);              \
    assert(GSETITERGETTYPE(iterC) == GSETITERGETTYPE(iterB));                \
    assert(GSETISFIRST(iterC) == false);                                     \
    assert(GSETISLAST(iterC) == true);                                       \
    GSETPUSH(setA, data ## Name[0]);                                         \
    assert(GSETGETSIZE(setA) == 1);                                          \
    GSETRESET(iterA);                                                        \
    assert(GSETGET(iterA) == data ## Name[0]);                               \
    assert(GSETISFIRST(iterA) == true);                                      \
    assert(GSETISLAST(iterA) == true);                                       \
    GSETADD(setA, data ## Name[1]);                                          \
    assert(GSETGETSIZE(setA) == 2);                                          \
    assert(GSETISFIRST(iterA) == true);                                      \
    assert(GSETISLAST(iterA) == false);                                      \
    GSETNEXT(iterA);                                                         \
    assert(GSETGET(iterA) == data ## Name[1]);                               \
    assert(GSETISFIRST(iterA) == false);                                     \
    assert(GSETISLAST(iterA) == true);                                       \
    GSETADDARR(setA, 2, ((Type[]) {0, 0}));                                  \
    assert(GSETGETSIZE(setA) == 4);                                          \
    assert(GSETISFIRST(iterA) == false);                                     \
    assert(GSETISLAST(iterA) == false);                                      \
    GSETNEXT(iterA);                                                         \
    assert(GSETGET(iterA) == 0);                                             \
    assert(GSETISFIRST(iterA) == false);                                     \
    assert(GSETISLAST(iterA) == false);                                      \
    GSETNEXT(iterA);                                                         \
    assert(GSETGET(iterA) == 0);                                             \
    assert(GSETISFIRST(iterA) == false);                                     \
    assert(GSETISLAST(iterA) == true);                                       \
    GSETADDARR(setA, 2, data ## Name);                                       \
    assert(GSETGETSIZE(setA) == 6);                                          \
    assert(GSETISFIRST(iterA) == false);                                     \
    assert(GSETISLAST(iterA) == false);                                      \
    GSETNEXT(iterA);                                                         \
    assert(GSETGET(iterA) == data ## Name[0]);                               \
    assert(GSETISFIRST(iterA) == false);                                     \
    assert(GSETISLAST(iterA) == false);                                      \
    GSETNEXT(iterA);                                                         \
    assert(GSETGET(iterA) == data ## Name[1]);                               \
    assert(GSETISFIRST(iterA) == false);                                     \
    assert(GSETISLAST(iterA) == true);                                       \
    Type* toArr = GSet ## Name ## ToArr(setA);                               \
    GSETRESET(iterA);                                                        \
    GSETENUM(iterA, idx) assert(toArr[idx] == GSETGET(iterA));          \
    printf("%zu elements: ", GSETGETSIZE(setA));                             \
    GSETFOR(iterA) printf("%zu ", (size_t)GSETGET(iterA));               \
    printf("\n");                                                            \
    free(toArr);                                                             \
    Type popA = GSETPOP(setA);                                               \
    assert(popA == data ## Name[0]);                                         \
    assert(GSETGETSIZE(setA) == 5);                                          \
    Type dropA = GSETDROP(setA);                                             \
    assert(dropA == data ## Name[1]);                                        \
    assert(GSETGETSIZE(setA) == 4);                                          \
    flagCatch = false;                                                       \
    Try {GSETAPPEND(setA, setA);}                                            \
      Catch(TryCatchExc_InfiniteLoop) {flagCatch = true;} EndCatch;          \
    assert(flagCatch == true);                                               \
    flagCatch = false;                                                       \
    Try {GSETMERGE(setA, setA);}                                             \
      Catch(TryCatchExc_InfiniteLoop) {flagCatch = true;} EndCatch;          \
    assert(flagCatch == true);                                               \
    GSETRESET(iterA);                                                        \
    FOR(i, 4) GSETNEXT(iterA);                                               \
    GSETAPPEND(setA, setB);                                                  \
    assert(GSETGETSIZE(setA) == 4 + SIZE_ARR);                                \
    assert(GSETGETSIZE(setB) == SIZE_ARR);                                    \
    GSETITERSETTYPE(iterB, GSetIterForward);                                 \
    GSETNEXT(iterA);                                                         \
    GSETFOR(iterB) {                                                     \
      assert(GSETGET(iterB) == GSETGET(iterA));GSETNEXT(iterA);              \
    }                                                                        \
    printf("%zu elements: ", GSETGETSIZE(setA));                             \
    GSETFOR(iterA) printf("%zu ", (size_t)GSETGET(iterA));               \
    printf("\n");                                                            \
    GSETMERGE(setA, setB);                                                   \
    assert(GSETGETSIZE(setA) == 4 + 2 * SIZE_ARR);                            \
    assert(GSETGETSIZE(setB) == 0);                                          \
    GSETSHUFFLE(setA);                                                       \
    printf("shuffled %zu elements: ", GSETGETSIZE(setA));                    \
    GSETFOR(iterA) printf("%zu ", (size_t)GSETGET(iterA));               \
    printf("\n");                                                            \
    GSETSORT(setA, GSet ## Name ## Cmp, true);                               \
    printf("sorted %zu elements: ", GSETGETSIZE(setA));                      \
    GSETFOR(iterA) printf("%zu ", (size_t)GSETGET(iterA));               \
    printf("\n");                                                            \
    GSETITERRESET(iterA);                                                    \
    Type prev = GSETGET(iterA);                                              \
    GSETNEXT(iterA);                                                         \
    GSETFOR(iterA) {                                                     \
      Type cur = GSETGET(iterA);                                             \
      assert(GSet ## Name ## Cmp(&prev, &cur) < 1);                          \
      prev = cur;                                                            \
    }                                                                        \
    GSETRESET(iterA);                                                        \
    Type picked = GSETPICK(iterA);                                           \
    assert(GSETGETSIZE(setA) == 9);                                          \
    GSETNEXT(iterA);                                                         \
    picked = GSETPICK(iterA);                                                \
    assert(GSETGETSIZE(setA) == 8);                                          \
    while (GSETNEXT(iterA));                                                 \
    picked = GSETPICK(iterA);                                                \
    (void)picked;                                                            \
    assert(GSETGETSIZE(setA) == 7);                                          \
    printf("remaining %zu elements: ", GSETGETSIZE(setA));                   \
    GSETFOR(iterA) printf("%zu ", (size_t)GSETGET(iterA));               \
    printf("\n");                                                            \
    GSETEMPTY(setA);                                                         \
    assert(GSETGETSIZE(setA) == 0);                                          \
    GSETSHUFFLE(setA);                                                       \
    GSETSORT(setA, GSet ## Name ## Cmp, true);                               \
    GSETADDARR(setA, 2, ((Type[]) {0, 0}));                                  \
    GSETITERFREE(&iterA);                                                    \
    assert(iterA == NULL);                                                   \
    GSETITERFREE(&iterB);                                                    \
    assert(iterB == NULL);                                                   \
    GSETITERFREE(&iterC);                                                    \
    assert(iterC == NULL);                                                   \
    GSETFREE(&setA);                                                         \
    assert(setA == NULL);                                                    \
    GSETFREE(&setB);                                                         \
    assert(setB == NULL);                                                    \
    printf("Test GSet" #Name " OK\n");                                       \
  } while(false)

#define TESTPTR(Name, Type)                                                  \
  TEST(Name, Type*);                                                         \
  do {                                                                       \
    GSet ## Name* setA = GSet ## Name ## Alloc();                            \
    Type* data = malloc(sizeof(Type));                                       \
    GSETPUSH(setA, data);                                                    \
    GSet ## Name ## Flush(setA);                                             \
    GSETFREE(&setA);                                                         \
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
