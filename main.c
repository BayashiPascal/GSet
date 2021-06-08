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
char* arrStr[sizeArr] = {"a", "b", "c"};

#define Test(Name, Type)                                                     \
  do {                                                                       \
    GSet ## Name* setA = GSet ## Name ## Alloc();                            \
    GSet ## Name* setB = GSet ## Name ## FromArr(arr ## Name, sizeArr);      \
    GSetFree(&setA);                                                         \
    GSetFree(&setB);                                                         \
  } while(false)

// Main function
int main() {

  Test(Char, char);
  Test(Str, char*);

  // Return the sucess code
  return EXIT_SUCCESS;

}

