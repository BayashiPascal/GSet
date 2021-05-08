#include <stdio.h>
#include "gset.h"

// Dummy structure to test typed GSet
struct UserData {

  int val;

};

// Create typed GSet for UserData
DefineGSet(UserData, struct UserData)

// Main function
int main() {

  // Example of GSet with element of type int
  struct GSetInt* setInt = GSetIntAlloc();
  int val = 1;
  GSetIntPush(
    setInt,
    &val);
  int* ptrInt = GSetIntPop(setInt);
  printf("%d\n", *ptrInt);
  Try {

    ptrInt = GSetIntPop(setInt);

  } Catch (GSetExc_EmptySet) {

    printf("The set is empty\n");

  } EndTry;
  GSetIntFree(&setInt);

  // Example of typed GSet
  struct GSetUserData* setUserData = GSetUserDataAlloc();
  struct UserData userData = { .val = 2 };
  GSetUserDataPush(
    setUserData,
    &userData);
  struct UserData* ptrUserData = GSetUserDataPop(setUserData);
  printf("%d\n", ptrUserData->val);
  GSetUserDataFree(&setUserData);

  // Return the sucess code
  return EXIT_SUCCESS;

}

