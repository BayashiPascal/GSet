// ------------------ gset.c ------------------

// Include the header
#include <string.h>
#include <float.h>
#include <math.h>
#include "gset.h"

// ================== Macros =========================

// Polymorphic free
static void GSetElemFree(struct GSetElem**);
#define PolyFree(P) _Generic(P, \
  struct GSet**: GSetFree, \
  struct GSetElem**: GSetElemFree)(P)

// Malloc freeing the assigned variable and raising exception if it fails
#define SafeMalloc(T, S)  \
  do { \
    PolyFree(&(T)); \
    T = malloc(S); \
    if (T == NULL) Raise(TryCatchExc_MallocFailed); \
  } while(false)

// Loop from 0 to (n - 1)
#define ForZeroTo(I, N) for (int I = 0; I < N; ++I)

// Get a random number in [0.0, 1.0]
#define rnd() (float)(rand())/(float)(RAND_MAX)

// ================== Private type definitions =========================

// Structure of a GSet element
struct GSetElem {

  // Data in the element
  void* data;

  // Previous element in the set
  struct GSetElem* prev;

  // Next element in the set
  struct GSetElem* next;

};

// ================== Private functions declaration =========================

// Create a new GSetElem
// Input:
//   data: the data contained by the element
// Output:
//   Return the new GSetElem.
static struct GSetElem GSetElemCreate(
  void* const data);

// Allocate memory for a new GSetElem
// Input:
//   data: the data contained by the element
// Output:
//   Return the new GSetElem.
static struct GSetElem* GSetElemAlloc(
  void* const data);

// Free the memory used by a GSetElem, do not free the memory used by the data
// it contains.
// Input:
//   that: the GSetElem to be freed
static void GSetElemFree(
  struct GSetElem** const that);

// ================== Public functions definition =========================

// Deallocation functions for default typed GSet
void IntFree(int** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;
}
void LongFree(long** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;
}
void FloatFree(float** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;
}
void DoubleFree(double** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;
}
void UIntFree(unsigned int** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;
}
void ULongFree(unsigned long** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;
}
void StrFree(char*** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that); *that = NULL;
}

// Comparison functions for the default typed GSets
int GSetIntCmp(void const* a, void const* b) {

  return (*(int const*)a < *(int const*)b ? -1 :
          *(int const*)a > *(int const*)b ? 1 : 0);

}

int GSetLongCmp(void const* a, void const* b) {

  return (*(long const*)a < *(long const*)b ? -1 :
          *(long const*)a > *(long const*)b ? 1 : 0);

}

int GSetFloatCmp(void const* a, void const* b) {

  float x = *(float*)a;
  float y = *(float*)b;
  if ((x - y) > DBL_EPSILON) return 1;
  else if ((x - y) < -DBL_EPSILON) return -1;
  else return 0;

}

int GSetDoubleCmp(void const* a, void const* b) {

  double x = *(double*)a;
  double y = *(double*)b;
  if ((x - y) > DBL_EPSILON) return 1;
  else if ((x - y) < -DBL_EPSILON) return -1;
  else return 0;

}

int GSetUIntCmp(void const* a, void const* b) {

  return (*(unsigned int const*)a < *(unsigned int const*)b ? -1 :
          *(unsigned int const*)a > *(unsigned int const*)b ? 1 : 0);

}

int GSetULongCmp(void const* a, void const* b) {

  return (*(unsigned long const*)a < *(unsigned long const*)b ? -1 :
          *(unsigned long const*)a > *(unsigned long const*)b ? 1 : 0);

}

int GSetStrCmp(void const* a, void const* b) {

  char* sa = *(char* const*)a;
  char* sb = *(char* const*)b;
  return strcmp(sa, sb);

}

// Create a new GSet
// Output:
//   Return the new GSet.
struct GSet GSetCreate(
  void) {

  // Create the GSet
  struct GSet that = (struct GSet){

    .size = 0,
    .first = NULL,
    .last = NULL,
    .elem = NULL,
    .iteration = GSetIteration_forward,

  };

  // Return the GSet
  return that;

}

// Allocate memory for a new GSet
// Output:
//   Return the new GSet.
struct GSet* GSetAlloc(
  void) {

  // Allocate memory for the GSet
  struct GSet* that = NULL;
  SafeMalloc(
    that,
    sizeof(struct GSet));

  // Create the GSet
  *that = GSetCreate();

  // Return the GSet
  return that;

}

// Copy a GSet into another GSet
// Inputs:
//   that: the GSet
//    tho: the other GSet
// Output:
//   tho is first emptied and then filled with elements whose data is the
//   the data of the elements of that, in same order
void GSetCopy( 
        struct GSet* const that,
  struct GSet const* const tho) {

  // Empty the GSet
  GSetEmpty(that);

  // Loop on the element of the GSet
  struct GSetElem* elem = tho->first;
  while (elem != NULL) {

    // Copy the element
    GSetAdd(
      that,
      elem->data);

    // Move to the next elem
    elem = elem->next;

  }

}

// Empty the GSet with GSetEmpty() and free the memory it used.
// Input:
//   that: the GSet to be freed
void GSetFree(
  struct GSet** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Empty the GSet
  GSetEmpty(*that);

  // Free the memory
  free(*that);
  *that = NULL;

}

// Empty the GSet. Memory used by data in it is not freed.
// To empty the GSet and free data the data in it, use GSet<N>Flush() instead.
// Input:
//   that: the GSet
void GSetEmpty(
  struct GSet* const that) {

  // Loop until there is no more element in the GSet
  while (that->size > 0) {

    // Pop the element and free it
    struct GSetElem* elem = that->first;
    that->first = elem->next;
    GSetElemFree(&elem);
    --(that->size);

  }

  // Update the current element
  that->elem = NULL;

  // Update the size of the set
  that->size = 0;

}

// Add data at the head of the GSet
// Inputs:
//   that: the GSet
//   data: the data to add
void GSetPush(
  struct GSet* const that,
         void* const data) {

  // Create a new element with the data
  struct GSetElem* elem = GSetElemAlloc(data);

  // Add the element to the head of the set
  elem->next = that->first;
  if (that->first != NULL) that->first->prev = elem;
  that->first = elem;
  if (that->size == 0) {

    that->last = elem;
    that->elem = elem;

  }

  ++(that->size);

}

// Add data at the tail of the GSet
// Inputs:
//   that: the GSet
//   data: the data to add
void GSetAdd(
  struct GSet* const that,
         void* const data) {

  // Create a new element with the data
  struct GSetElem* elem = GSetElemAlloc(data);

  // Add the element to the tail of the set
  elem->prev = that->last;
  if (that->last != NULL) that->last->next = elem;
  that->last = elem;
  if (that->size == 0) {

    that->first = elem;
    that->elem = elem;

  }

  ++(that->size);

}

// Remove and return the data at the head of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetPop(
  struct GSet* const that) {

  // If there is no data to pop, raise an exception
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);

  // If the removed element is the current element
  if (that->elem == that->first) {

    // Try to move to the next element
    bool flag = GSetIterNext(that);

    // If we couldn't move to the next, try to move to the previous
    if(flag == false) flag = GSetIterNext(that);

    // If we still couldn't move, reset the current element
    if(flag == false) that->elem = NULL;

  }

  // Remove the first element
  struct GSetElem* elem = that->first;
  that->first = elem->next;
  if (that->first != NULL) that->first->prev = NULL;
  --(that->size);

  // Memorise the data and free the element
  void* data = elem->data;
  GSetElemFree(&elem);

  // Return the element's data
  return data;

}

// Remove and return the data at the tail of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetDrop(
  struct GSet* const that) {

  // If there is no data to drop, raise an exception
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);

  // If the removed element is the current element
  if (that->elem == that->last) {

    // Try to move to the next element
    bool flag = GSetIterNext(that);

    // If we couldn't move to the next, try to move to the previous
    if(flag == false) flag = GSetIterPrev(that);

    // If we still couldn't move, reset the current element
    if(flag == false) that->elem = NULL;

  }

  // Remove the last element
  struct GSetElem* elem = that->last;
  that->last = elem->prev;
  if (that->last != NULL) that->last->next = NULL;
  --(that->size);

  // Memorise the data and free the element
  void* data = elem->data;
  GSetElemFree(&elem);

  // Return the element's data
  return data;

}

// Remove and return the data of the current element of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetPick(
  struct GSet* const that) {


  // If there is no data to pick, raise an exception
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);

  // Try to move to the next element
  bool flag = GSetIterNext(that);

  // Memorise the current element
  struct GSetElem* elem = that->first;

  // If we couldn't move to the next, try to move to the previous
  if(flag == false) flag = GSetIterNext(that);

  // If we still couldn't move, reset the current element
  if(flag == false) that->elem = NULL;

  // Remove the current element
  if (that->first == that->elem) {

    that->first = elem->next;
    elem->next->prev = NULL;

  } else if (that->last == that->elem) {

    that->last = elem->prev;
    elem->prev->next = NULL;

  } else {

    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;

  }

  --(that->size);

  // Memorise the data and free the element
  void* data = elem->data;
  GSetElemFree(&elem);

  // Return the element's data
  return data;

}

// Sort the elements of a GSet
// Inputs:
//   that: the GSet to sort
//   cmp: the comparison function used to sort
// It uses qsort, see man page for details. Elements are sorted in ascending
// order, relative to the comparison function cmp(a,b) which much returns
// a negative value if a<b, a positive value if a>b, and 0 if a=b
void GSetSort(
  struct GSet* const that,
                 int (*cmp)(void const*, void const*)) {

  // If there is less than 2 elements there is no need to sort
  if (that->size < 2) return;
  
  // Convert the GSet into an array of pointers to data
  void** arr = GSetToArrayOfPtr(that);

  // Sort the array
  qsort(
    arr,
    that->size,
    sizeof(void*),
    cmp);

  // Copy the sorted data back in the elements
  struct GSetElem* ptr = that->first;
  int i = 0;
  while (ptr != NULL) {

    ptr->data = arr[i];
    ptr = ptr->next;
    ++i;

  }

  // Free memory used by the temporary array
  free(arr);

}

// Shuffle the elements of a GSet
// Input:
//   that: the GSet to shuffle
void GSetShuffle(
  struct GSet* const that) {

  // Convert the GSet into an array of pointers to data
  void** arr = GSetToArrayOfPtr(that);

  // Shuffle the array
  // (Fischer-Yates algorithm)
  for (int i = that->size - 1; i > 0; --i) {

     int j = (int)round(rnd() * (int)i);
     if (i != j) {

       void* ptr = arr[j];
       arr[j] = arr[i];
       arr[i] = ptr;

     }

  }

  // Copy the shuffled data back in the elements
  struct GSetElem* ptr = that->first;
  int i = 0;
  while (ptr != NULL) {

    ptr->data = arr[i];
    ptr = ptr->next;
    ++i;

  }

  // Free memory used by the temporary array
  free(arr);

}

// Convert the GSet to an array of pointers to its data
// Input:
//   that: the GSet to convert
// Output:
//   Return an array of pointers to data in the same order as the current
//   element order
void** GSetToArrayOfPtr(
  struct GSet* const that) {

  // Create the array of pointers
  void** arr = malloc(sizeof(void*) * that->size);
  if (arr == NULL) Raise(TryCatchExc_MallocFailed);

  // Copy the pointers in the array
  struct GSetElem* ptr = that->first;
  int i = 0;
  while (ptr != NULL) {

    arr[i] = ptr->data;
    ptr = ptr->next;
    ++i;

  }

  // Return the array
  return arr;

}

// Convert an array of pointers to a GSet
// Inputs:
//   that: the GSet
//    arr: the array to convert
//   size: the size of the array
// Output:
//   The GSet is first emptied and then filled with elements whose data is the
//   pointers in the array in the order of the array
void GSetFromArrayOfPtr(
  struct GSet* const that,
        void** const arr,
           int const size) {

  // Empty the GSet
  GSetEmpty(that);

  // Loop on the element of the array, and add the pointer to the GSet
  ForZeroTo(iVal, size) GSetAdd(that, arr[iVal]);

}

// Append a GSet at the end of another GSet
// Inputs:
//   that: the GSet
//    tho: the other GSet
// Output:
//   tho is appended at the end of that and becomes empty after this operation
void GSetAppend(
  struct GSet* const that,
  struct GSet* const tho) {

  // If the other set is empty, nothing to do
  if (tho->first == NULL) return;

  // If the set is empty, it simply becames the other set
  if (that->first == NULL) *that = *tho;
  // Else, both set contain elements
  else {

    // Append tho at the end of that
    that->last->next = tho->first;
    tho->first->prev = that->last;
    that->last = tho->last;
    that->size += tho->size;
    if (that->elem == NULL) that->elem = that->first;

    // Disconnect tho from its elements, else there is an inconsistency in
    // the fact that tho->first->prev is not null
    *tho = GSetCreate();

  }

}

// Get the data of the current element in the GSet
// Input:
//   that: the GSet
// Output:
//   Return the pointer to the data of the current element
void* GSetCurData(
  struct GSet const* const that) {

  // If there is no data to get, raise an exception
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);

  // Return the data of the current element
  return that->elem->data;

}

// Get the size of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the size of the data set
int GSetGetSize(
  struct GSet const* const that) {

  // Return the data of the current element
  return that->size;

}

// Reset the current element of the iterator according to the direction
// of the iteration.
// Input:
//   that: the GSet
void GSetIterReset(
  struct GSet* const that) {

  // If there are elements in the set
  if (that->size > 0) {

    // Switch on the type of iteration
    switch (that->iteration) {

      case GSetIteration_forward:

        // Move to the head of the GSet
        that->elem = that->first;
        break;

      case GSetIteration_backward:

        // Move to the tail of the GSet
        that->elem = that->last;
        break;

      default:
        break;

    }

  // Else there is no element in the dataset
  } else that->elem = NULL;

}

// Move the current element in the GSet one step in the direction of the
// iteration.
// Input:
//   that: the GSet
// Output:
//   If there is no element, do nothing and return false. If there are
//   elements and the iterator can move in the requested direction,
//   udpate the current element and return true. If there are elements
//   and the iterator can't move in the requested direction, do nothing
//   and return false.
bool GSetIterNext(
  struct GSet* const that) {

  // Variable to memorise the returned flag
  bool flag = true;

  // If there are elements in the set
  if (that->size > 0) {

    // Switch on the type of iteration
    switch (that->iteration) {

      case GSetIteration_forward:

        // If there is a next element, move to it
        if (that->elem->next != NULL)
          that->elem = that->elem->next;
        // Else, there is no next element, update the flag
        else flag = false;
        break;

      case GSetIteration_backward:

        // If there is a previous element, move to it
        if (that->elem->prev != NULL)
          that->elem = that->elem->prev;
        // Else, there is no next element, update the flag
        else flag = false;
        break;

      default:
        break;

    }

  // Else, there is no element in the set, update the flag
  } else flag = false;

  // Return the flag
  return flag;

}

// Move the current element in the GSet one step in the opposite
// direction of the iteration.
// Input:
//   that: the GSet
// Output:
//   If there is no element, do nothing and return false. If there are
//   elements and the iterator can move in the requested direction,
//   udpate the current element and return true. If there are elements
//   and the iterator can't move in the requested direction, do nothing
//   and return false.
bool GSetIterPrev(
  struct GSet* const that) {
  // Variable to memorise the returned flag
  bool flag = true;

  // If there are elements in the set
  if (that->size > 0) {

    // Switch on the type of iteration
    switch (that->iteration) {

      case GSetIteration_forward:

        // If there is a previous element, move to it
        if (that->elem->prev != NULL)
          that->elem = that->elem->prev;
        // Else, there is no next element, update the flag
        else flag = false;
        break;

      case GSetIteration_backward:

        // If there is a next element, move to it
        if (that->elem->next != NULL)
          that->elem = that->elem->next;
        // Else, there is no next element, update the flag
        else flag = false;
        break;

      default:
        break;

    }

  // Else, there is no element in the set, update the flag
  } else flag = false;

  // Return the flag
  return flag;

}

// ================== Private functions definition =========================

// Create a new GSetElem
// Input:
//   data: the data contained by the element
// Output:
//   Return the new GSetElem.
static struct GSetElem GSetElemCreate(
  void* const data) {

  // Create the GSetElem
  struct GSetElem that = (struct GSetElem){

    .prev = NULL,
    .next = NULL,
    .data = data,

  };

  // Return the GSetElem
  return that;
}

// Allocate memory for a new GSetElem
// Input:
//   data: the data contained by the element
// Output:
//   Return the new GSetElem.
static struct GSetElem* GSetElemAlloc(
  void* const data) {

  // Allocate memory for the element
  struct GSetElem* that = NULL;
  SafeMalloc(
    that,
    sizeof(struct GSetElem));

  // Create the element
  *that = GSetElemCreate(data);

  // Return the new GSetElem
  return that;

}

// Free the memory used by a GSetElem, do not free the memory used by the data
// it contains.
// Input:
//   that: the GSetElem to be freed
static void GSetElemFree(
  struct GSetElem** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Free the memory
  free(*that);
  *that = NULL;

}

// ------------------ gset.c ------------------
