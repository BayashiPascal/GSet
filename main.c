#include <stdio.h>
#include <assert.h>
#include "gset.h"

// Dummy struct
struct Dummy {

  int a;

};

DefineGSet(Dummy, struct Dummy*)

// Main function
int main() {

  // Init the random generator
  srand(0);

  // Example of GSet with element of type int

  // Create the GSet
  struct GSetInt* setInt = GSetIntAlloc();
  struct GSetUInt* setUInt = GSetUIntAlloc();
  struct GSetStr* setStr = GSetStrAlloc();
  struct GSetDummy* setDummy = GSetDummyAlloc();

  // Push data
  int aInt = 0;
  GSetPush(setInt, aInt);
  int aUInt = 0;
  GSetPush(setUInt, aUInt);
  char* aStr = NULL;
  GSetPush(setStr, aStr);
  struct Dummy* aDummy = NULL;
  GSetPush(setDummy, aDummy);

  // Pop data
  aInt = GSetPop(setInt);
  aUInt = GSetPop(setUInt);
  aStr = GSetPop(setStr);
  aDummy = GSetPop(setDummy);

  // Should not compile without warning
  // ok GSetPush(setStr, aDummy);
  // ok aStr = GSetPop(setDummy);

  // Free memory
  GSetFree(&setInt);
  GSetFree(&setUInt);
  GSetFree(&setStr);
  GSetFree(&setDummy);

  // Return the sucess code
  return EXIT_SUCCESS;

}

