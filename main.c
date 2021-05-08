#include <stdio.h>
#include "gset.h"

// Dummy structure to test typed GSet
struct UserData {

  int val;

};

// Function to free the dummy structure, required to create GSetUserData
void UserDataFree(struct UserData** const that) {

  if (that == NULL || *that == NULL) return;
  free(*that);
  *that = NULL;

}

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

  } Catch (TryCatchExc_OutOfRange) {

    printf("The set is empty\n");

  } EndTry;
  GSetIntPush(
    setInt,
    malloc(sizeof(int)));
  GSetIntFlush(setInt);
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

