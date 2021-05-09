#include <stdio.h>
#include <assert.h>
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

  // Init the random generator
  srandom(0);

  // Example of GSet with element of type int

  // Create the GSet
  struct GSetInt* setInt = GSetIntAlloc();

  // Try to pop an empty GSet
  bool raised = false;
  Try {

    int* p = GSetIntPop(setInt);
    (void)p;

  } Catch (TryCatchExc_OutOfRange) {

    raised = true;

  } EndTry;
  assert(raised == true);

  // Load an array into the GSet
  int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  GSetIntFromArrayOfData(
    setInt,
    arr,
    10);
  assert(GSetIntGetSize(setInt) == 10);
  assert(*(GSetIntCurData(setInt)) == 0);
  GSetForEach(setInt, int, printf("%d ", *data));printf("\n");

  // Convert the GSet to an array of pointer
  int** arrPtr = GSetIntToArrayOfPtr(setInt);
  for (int i = 0; i < 10; ++i) assert(arrPtr[i] == arr + i);

  // Create a GSet from an array of pointer
  struct GSetInt setIntB = GSetIntCreate();
  GSetIntFromArrayOfPtr(
    &setIntB,
    arrPtr,
    10);
  GSetForEach(&setIntB, int, assert(*data == arr[iData]));

  // Convert the GSet to an array of pointer
  int* arrB = GSetIntToArrayOfData(&setIntB);
  for (int i = 0; i < 10; ++i) assert(arrB[i] == arr[i]);

  // Free memory
  GSetIntEmpty(&setIntB);
  free(arrB);
  free(arrPtr);

  // Pop the data
  int* ptrInt = GSetIntPop(setInt);
  assert(*ptrInt == 0);
  assert(GSetIntGetSize(setInt) == 9);
  assert(*(GSetIntCurData(setInt)) == 9);
  GSetForEach(setInt, int, printf("%d ", *data));printf("\n");

  // Push back the data
  GSetIntPush(
    setInt,
    ptrInt);
  assert(GSetIntGetSize(setInt) == 10);
  assert(*(GSetIntCurData(setInt)) == 9);
  GSetForEach(setInt, int, printf("%d ", *data));printf("\n");

  // Drop the data
  ptrInt = GSetIntDrop(setInt);
  assert(*ptrInt == 9);
  assert(GSetIntGetSize(setInt) == 9);
  assert(*(GSetIntCurData(setInt)) == 8);
  GSetForEach(setInt, int, printf("%d ", *data));printf("\n");

  // Add back the data
  GSetIntAdd(
    setInt,
    ptrInt);
  assert(GSetIntGetSize(setInt) == 10);
  assert(*(GSetIntCurData(setInt)) == 8);
  GSetForEach(setInt, int, printf("%d ", *data));printf("\n");

  // Shuffle the data
  GSetIntShuffle(setInt);
  int check[10] = {9, 0, 2, 4, 1, 6, 7, 5, 3, 8};
  GSetForEach(setInt, int, printf("%d ", *data));printf("\n");
  GSetForEach(setInt, int, assert(*data == check[iData]));
  assert(GSetIntGetSize(setInt) == 10);
  assert(*(GSetIntCurData(setInt)) == 8);

  // Sort back the data
  GSetIntSort(
    setInt,
    GSetIntCmp);
  GSetForEach(setInt, int, printf("%d ", *data));printf("\n");
  GSetForEach(setInt, int, assert(*data == iData));
  assert(GSetIntGetSize(setInt) == 10);
  assert(*(GSetIntCurData(setInt)) == 9);

  // Free the GSet
  GSetIntFree(&setInt);

  // Example of typed GSet

  // Create the GSet
  struct GSetUserData* setUserData = GSetUserDataAlloc();

  // Push a data
  struct UserData* userData = malloc(sizeof(struct UserData));
  *userData = (struct UserData){ .val = 2 };
  GSetUserDataPush(
    setUserData,
    userData);

  // Pop the data
  struct UserData* ptrUserData = GSetUserDataPop(setUserData);
  assert(ptrUserData->val == userData->val);

  // Free memory
  GSetUserDataFlush(setUserData);
  GSetUserDataFree(&setUserData);
  UserDataFree(&userData);

  // Return the sucess code
  return EXIT_SUCCESS;

}

