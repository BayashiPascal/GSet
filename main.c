#include <stdio.h>
#include "gset.h"

// Dummy structure to test typed GSet
struct UserData {

  int val;

};

// Function to free the dummy structure, required to create a GSet of type
// UserData
void UserDataFree(struct UserData** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Free the memory
  free(*that);
  *that = NULL;

}

// Create a typed GSet for UserData
DefineGSet(UserData, struct UserData)

// Main function
int main() {

  // Example of GSet with element of type int

  // Create the GSet
  struct GSetInt* setInt = GSetIntAlloc();

  // Push a data
  int val = 1;
  GSetIntPush(
    setInt,
    &val);

  // Pop the data
  int* ptrInt = GSetIntPop(setInt);
  printf("%d\n", *ptrInt);

  // Try to pop an empty GSet
  Try {

    ptrInt = GSetIntPop(setInt);

  } Catch (TryCatchExc_OutOfRange) {

    printf("The set is empty\n");

  } EndTry;

  // Free the GSet
  GSetIntFree(&setInt);

  // Example of typed GSet

  // Create the GSet
  struct GSetUserData* setUserData = GSetUserDataAlloc();

  // Push a data
  struct UserData userData = { .val = 2 };
  GSetUserDataPush(
    setUserData,
    &userData);

  // Pop the data
  struct UserData* ptrUserData = GSetUserDataPop(setUserData);
  printf("%d\n", ptrUserData->val);

  // Free the GSet
  GSetUserDataFree(&setUserData);

  // Return the sucess code
  return EXIT_SUCCESS;

}

