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
  GSetInt* setInt = GSetIntAlloc();
  GSetUInt* setUInt = GSetUIntAlloc();
  GSetStr* setStr = GSetStrAlloc();
  GSetDummy* setDummy = GSetDummyAlloc();

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

  // Iterator
  GSetIterInt* iterInt =
    GSetIterIntAlloc(
      setInt,
      GSetIterForward);
  GSetIterReset(iterInt);
  //aInt = GSetIterGet(iterInt);
  GSetIterDummy* iterDummy =
    GSetIterDummyAlloc(
      setDummy,
      GSetIterBackward);
  GSetIterReset(iterDummy);
  //aDummy = GSetIterGet(iterDummy);

  // Free memory
  GSetFree(&setInt);
  GSetFree(&setUInt);
  GSetFree(&setStr);
  GSetFree(&setDummy);

  GSetIterFree(&iterInt);
  GSetIterFree(&iterDummy);

  // Return the sucess code
  return EXIT_SUCCESS;

}

