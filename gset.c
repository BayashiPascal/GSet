// ------------------ gset.c ------------------

// Include the header
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include "gset.h"

// ================== Macros =========================

// Malloc raising exception if it fails
#define SafeMalloc(T, S)  \
  do { \
    T = malloc(S); \
    if (T == NULL) Raise(TryCatchExc_MallocFailed); \
  } while(false)

// Loop from 0 to (N - 1)
#define ForZeroTo(I, N) for (size_t I = 0; I < N; ++I)

// Get a random number in [0.0, 1.0]
#define rnd() (float)(rand())/(float)(RAND_MAX)

// ================== Private type definitions =========================

// Union to memorise the data in a GSet element independently of its type
union GSetElemData {
  char Char;
  unsigned char UChar;
  int Int;
  unsigned int UInt;
  long Long;
  unsigned long ULong;
  float Float;
  double Double;
  void* Ptr;
};

// Structure of a GSet element
struct GSetElem {

  // Data in the element
 union GSetElemData data;

  // Previous element in the set
  struct GSetElem* prev;

  // Next element in the set
  struct GSetElem* next;

};
typedef struct GSetElem GSetElem;

// Structure of a GSet
struct GSet {

  // Size of the GSet (i.e. number of GSetElem currently in it)
  size_t size;

  // First element of the set
  GSetElem* first;

  // Last element of the set
  GSetElem* last;

};

// Structure of an iterator on a GSet
struct GSetIter {

  // Current element
  GSetElem* elem;

  // Type of iteration
  enum GSetIterType type;

};

// ================== Private functions declaration =========================

// Create a new GSetElem
// Output:
//   Return the new GSetElem.
static GSetElem GSetElemCreate(
  void);

// Allocate memory for a new GSetElem
// Output:
//   Return the new GSetElem.
static GSetElem* GSetElemAlloc(
  void);

// Free the memory used by a GSetElem, do not free the memory used by the data
// it contains.
// Input:
//   that: the GSetElem to be freed
static void GSetElemFree(
  GSetElem** const that);

// Create a new GSet
// Output:
//   Return the new GSet.
static GSet GSetCreate(
  void);

// Push an element at the head of the set
// Inputs:
//   that: the set
//   elem: the element
static void GSetPushElem(
      GSet* const that,
  GSetElem* const elem);

// Add an element at the tail of the set
// Inputs:
//   that: the set
//   elem: the element
static void GSetAddElem(
      GSet* const that,
  GSetElem* const elem);

// Pop an element from the head of the set
// Input:
//   that: the set
// Output:
//   Return the element
static GSetElem* GSetPopElem(
  GSet* const that);

// Drop an element from the tail of the set
// Input:
//   that: the set
// Output:
//   Return the element
static GSetElem* GSetDropElem(
  GSet* const that);

// Create a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
GSetIter GSetIterCreate(
  enum GSetIterType const type);

// ================== Public functions definition =========================

// Function to get the commit id of the library
// Output:
//   Return a string containing the result of `git rev-parse HEAD` at
//   compilation time
char const* GSetGetCommitId(
  void) {

  // Return the commit id
  #define STRINGIFY(x) #x
  #define STRINGIFY_VALUE_OF(x) STRINGIFY(x)
  return STRINGIFY_VALUE_OF(COMMIT);

}

// Allocate memory for a new GSet
// Output:
//   Return the new GSet.
GSet* GSetAlloc(
  void) {

  // Allocate memory for the GSet
  GSet* that = NULL;
  SafeMalloc(
    that,
    sizeof(GSet));

  // Create the GSet
  *that = GSetCreate();

  // Return the GSet
  return that;

}

// Empty the GSet with GSetEmpty() and free the memory it used.
// Input:
//   that: the GSet to be freed
void GSetFree_(
  GSet** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Empty the GSet
  GSetEmpty_(*that);

  // Free the memory
  free(*that);
  *that = NULL;

}

// Push data at the head of the set
// Inputs:
//   that: the set
//   data: the data
#define GSetPush__(N, T)                                                     \
void GSetPush_ ## N(                                                         \
  GSet* const that,                                                   \
             T const data) {                                                 \
  GSetElem* elem = GSetElemAlloc();                                   \
  elem->data.N = data;                                                       \
  GSetPushElem(that, elem);                                                  \
}
GSetPush__(Char, char)
GSetPush__(UChar, unsigned char)
GSetPush__(Int, int)
GSetPush__(UInt, unsigned int)
GSetPush__(Long, long)
GSetPush__(ULong, unsigned long)
GSetPush__(Float, float)
GSetPush__(Double, double)
GSetPush__(Ptr, void*)

// Add data at the tail of the set
// Inputs:
//   that: the set
//   data: the data
#define GSetAdd__(N, T)                                                      \
void GSetAdd_ ## N(                                                          \
  GSet* const that,                                                   \
             T const data) {                                                 \
  GSetElem* elem = GSetElemAlloc();                                   \
  elem->data.N = data;                                                       \
  GSetAddElem(that, elem);                                                   \
}
GSetAdd__(Char, char)
GSetAdd__(UChar, unsigned char)
GSetAdd__(Int, int)
GSetAdd__(UInt, unsigned int)
GSetAdd__(Long, long)
GSetAdd__(ULong, unsigned long)
GSetAdd__(Float, float)
GSetAdd__(Double, double)
GSetAdd__(Ptr, void*)

// Add an array of data at the tail of the set
// Inputs:
//   that: the set
//   arr: the array of data
#define GSetAddArr__(N, T)     \
void GSetAddArr_ ## N(        \
  GSet* const that,  \
             size_t const size, \
             T const* const arr) {                                        \
  ForZeroTo(i, size) { \
    GSetElem* elem = GSetElemAlloc();                                   \
    elem->data.N = arr[i];                                                   \
    GSetAddElem(that, elem);                                              \
  } \
}
#define GSetAddArrPtr__(N, T)     \
void GSetAddArr_ ## N(        \
  GSet* const that,  \
             size_t const size, \
             T const* const arr) {                                        \
  ForZeroTo(i, size) { \
    GSetElem* elem = GSetElemAlloc();                                   \
    elem->data.N = ((void**)arr)[i];                                                   \
    GSetAddElem(that, elem);                                              \
  } \
}
GSetAddArr__(Char, char)
GSetAddArr__(UChar, unsigned char)
GSetAddArr__(Int, int)
GSetAddArr__(UInt, unsigned int)
GSetAddArr__(Long, long)
GSetAddArr__(ULong, unsigned long)
GSetAddArr__(Float, float)
GSetAddArr__(Double, double)
GSetAddArrPtr__(Ptr, void)

// Pop data from the head of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the head of the set and return it
#define GSetPop__(N, T)                                                      \
T GSetPop_ ## N(                                                             \
  GSet* const that) {                                                 \
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);                        \
  GSetElem* elem = GSetPopElem(that);                                 \
  T data = elem->data.N;                                                     \
  GSetElemFree(&elem);                                                       \
  return data;                                                               \
}
GSetPop__(Char, char)
GSetPop__(UChar, unsigned char)
GSetPop__(Int, int)
GSetPop__(UInt, unsigned int)
GSetPop__(Long, long)
GSetPop__(ULong, unsigned long)
GSetPop__(Float, float)
GSetPop__(Double, double)
GSetPop__(Ptr, void*)

// Drop data from the tail of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the tail of the set and return it
#define GSetDrop__(N, T)                                                     \
T GSetDrop_ ## N(                                                            \
  GSet* const that) {                                                 \
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);                        \
  GSetElem* elem = GSetDropElem(that);                                \
  T data = elem->data.N;                                                     \
  GSetElemFree(&elem);                                                       \
  return data;                                                               \
}
GSetDrop__(Char, char)
GSetDrop__(UChar, unsigned char)
GSetDrop__(Int, int)
GSetDrop__(UInt, unsigned int)
GSetDrop__(Long, long)
GSetDrop__(ULong, unsigned long)
GSetDrop__(Float, float)
GSetDrop__(Double, double)
GSetDrop__(Ptr, void*)

// Append data from a set to the end of another
// Input:
//   that: the set where data are added
//   tho: the set containing data to add
void GSetAppend_(
        GSet* const that,
  GSet const* const tho) {

  // Appending a set to itself will create infinite loop
  if (that == tho) Raise(TryCatchExc_InfiniteLoop);

  // If the set source is empty, nothing to do
  if (tho->size == 0) return;

  // Iterator on the data to copy
  GSetIter* iter = NULL;

  // Variable to memorise the raised exception, if any
  int raisedExc = 0;

  Try {

    // Loop on the element of the set source
    iter = GSetIterAlloc(GSetIterForward);
    GSetIterReset_(iter, tho);
    do {

      // Add the data from the source to the destination
      GSetElem* elem = GSetElemAlloc();
      elem->data = iter->elem->data;
      GSetAddElem(that, elem);

    } while (GSetIterNext_(iter));

  } CatchDefault {

    // Memorise the raised exception
    raisedExc = TryCatchGetLastExc();

  } EndCatchDefault;

  // Free memory
  GSetIterFree_(&iter);

  // If there has been a raised exception, it
  if (raisedExc != 0) Raise(raisedExc);

}

// Merge a set into another. The merged set is empty after this operation
// Input:
//   that: the extended set
//   tho: the merged set
void GSetMerge_(
  GSet* const that,
  GSet* const tho) {

  // Merging a set to itself will create infinite loop
  if (that == tho) Raise(TryCatchExc_InfiniteLoop);

  // If the merged set is empty, nothing to do
  if (tho->size == 0) return;

  // If that is empty
  if (that->size == 0) {

    // Simply copy tho in that
    *that = *tho;

  // Else, that is not empty
  } else {

    // Check for overflow
    if (that->size > SIZE_MAX - tho->size) Raise(TryCatchExc_IntOverflow);

    // Connect the tail of that to the head of tho
    that->last->next = tho->first;
    tho->first->prev = that->last;

    // Update the last element of that
    that->last = tho->last;

    // Update the size of that
    that->size += tho->size;

  }

  // Empty tho
  tho->first = NULL;
  tho->last = NULL;
  tho->size = 0;

}

// Return the number of element in the set
// Input:
//   that: the set
// Output:
//   Return the number of element.
size_t GSetGetSize_(
  GSet const* const that) {

  return that->size;

}

// Empty the set. Memory used by data in it is not freed.
// To empty the set and free data, use GSet<N>Flush() instead.
// Input:
//   that: the set
void GSetEmpty_(
  GSet* const that) {

  // Loop until the set is empty
  while (GSetGetSize_(that) > 0) {

    // Pop the element
    GSetElem* elem = GSetPopElem(that);

    // Free the element, in memory of L3-37
    GSetElemFree(&elem);

  }

}

// Shuffle the set
// Input:
//   that: the set
void GSetShuffle_(
  GSet* const that) {

  // If the array has less than 2 elements, nothing to do
  if (that->size < 2) return;

  // Convert the GSet into an array of pointers to data
  union GSetElemData* arr = NULL;
  SafeMalloc(
    arr,
    sizeof(union GSetElemData) * that->size);
  GSetElem* ptr = that->first;
  size_t i = 0;
  while (ptr != NULL) {

    arr[i] = ptr->data;
    ptr = ptr->next;
    ++i;

  }

  // Shuffle the array
  // (Fischer-Yates-Durstenfeld-Knuth algorithm)
  for (size_t i = that->size - 1; i > 0; --i) {

     size_t j = (size_t)round(rnd() * (double)i);
     if (i != j) {

       union GSetElemData ptr = arr[j];
       arr[j] = arr[i];
       arr[i] = ptr;

     }

  }

  // Copy the shuffled data back in the elements
  ptr = that->first;
  i = 0;
  while (ptr != NULL) {

    ptr->data = arr[i];
    ptr = ptr->next;
    ++i;

  }

  // Free memory used by the temporary array
  free(arr);

}

// Sort the elements of a GSet
// Inputs:
//   that: the set to sort
//   cmp: the comparison function used to sort
// It uses qsort, see man page for details. Elements are sorted in ascending
// order, relative to the comparison function cmp(a,b) which much returns
// a negative value if a<b, a positive value if a>b, and 0 if a=b
#define GSetSort__(N, T) \
void GSetSort_ ## N(    \
  GSet* const that,   \
          int (*cmp)(void const*, void const*), \
         bool inc) { \
  if (that->size < 2) return; \
  T* arr = NULL;  \
  SafeMalloc(arr, sizeof(T) * that->size); \
  GSetElem* ptr = that->first; \
  size_t i = 0; \
  while (ptr != NULL) { \
    arr[i] = ptr->data.N; \
    ptr = ptr->next; \
    ++i; \
  } \
  Try { \
    qsort(arr, that->size, sizeof(T), cmp); \
    ptr = that->first; \
    i = 0; \
    while (ptr != NULL) { \
      if (inc == true) \
        ptr->data.N = arr[i]; \
      else \
        ptr->data.N = arr[that->size - 1 - i]; \
      ptr = ptr->next; \
      ++i; \
    } \
    free(arr); \
  } CatchDefault { \
    free(arr); Raise(TryCatchGetLastExc()); \
  } EndCatchDefault; \
}
GSetSort__(Char, char)
GSetSort__(UChar, unsigned char)
GSetSort__(Int, int)
GSetSort__(UInt, unsigned int)
GSetSort__(Long, long)
GSetSort__(ULong, unsigned long)
GSetSort__(Float, float)
GSetSort__(Double, double)
GSetSort__(Ptr, void*)

// Allocate memory for a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
GSetIter* GSetIterAlloc(
  enum GSetIterType const type) {

  // Allocate memory for the GSet
  GSetIter* that = NULL;
  SafeMalloc(
    that,
    sizeof(GSetIter));

  // Create the GSet
  *that = GSetIterCreate(type);

  // Return the GSet
  return that;

}

// Free the memory used by a GSetIter.
// Input:
//   that: the GSetIter to be freed
void GSetIterFree_(
  GSetIter** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Free the memory
  free(*that);
  *that = NULL;

}

// Get the current data from a set
// Input:
//   that: the iterator
// Output:
//   Return the current data
#define GSetIterGet__(N, T)                                                  \
T GSetIterGet_ ## N(                                                         \
  GSetIter const* const that) {                                       \
  if (that->elem == NULL) Raise(TryCatchExc_OutOfRange);                     \
  T data = that->elem->data.N;                                               \
  return data;                                                               \
}
GSetIterGet__(Char, char)
GSetIterGet__(UChar, unsigned char)
GSetIterGet__(Int, int)
GSetIterGet__(UInt, unsigned int)
GSetIterGet__(Long, long)
GSetIterGet__(ULong, unsigned long)
GSetIterGet__(Float, float)
GSetIterGet__(Double, double)
GSetIterGet__(Ptr, void*)

// Pick the current data from a set
// Input:
//   that: the iterator
//   set: the associated set
// Output:
//   Remove the current data from the set and return it
#define GSetIterPick__(N, T)                                                 \
T GSetIterPick_ ## N(                                                        \
  GSetIter* const that,                                               \
  GSet* const set) {                                                  \
  if (that->elem == NULL) Raise(TryCatchExc_OutOfRange);                     \
  T data = that->elem->data.N;                                               \
  if (set->first == that->elem) set->first = set->first->next;               \
  if (set->last == that->elem) set->last = set->last->prev;                  \
  if (that->elem->next != NULL) that->elem->next->prev = that->elem->prev;   \
  if (that->elem->prev != NULL) that->elem->prev->next = that->elem->next;   \
  GSetElem* elem = that->elem;                                        \
  if (GSetIterNext_(that) == false)                                          \
    if (GSetIterPrev_(that) == false)                                        \
      that->elem = NULL;                                                     \
  GSetElemFree(&elem);                                                       \
  --(set->size);                                                             \
  return data;                                                               \
}
GSetIterPick__(Char, char)
GSetIterPick__(UChar, unsigned char)
GSetIterPick__(Int, int)
GSetIterPick__(UInt, unsigned int)
GSetIterPick__(Long, long)
GSetIterPick__(ULong, unsigned long)
GSetIterPick__(Float, float)
GSetIterPick__(Double, double)
GSetIterPick__(Ptr, void*)

// Reset the iterator to its first element
// Input:
//   that: the iterator
//    set: the associated set
void GSetIterReset_(
    GSetIter* const that,
  GSet const* const set) {

  // Switch according to the type of iterator
  switch (that->type) {

    case GSetIterForward:
      that->elem = set->first;
      break;

    case GSetIterBackward:
      that->elem = set->last;
      break;

    default:
      Raise(TryCatchExc_NotYetImplemented);

  }

}

// Move the iterator to the next element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator could move to the next element, else false
bool GSetIterNext_(
  GSetIter* const that) {

  if (that->elem == NULL) return false;

  // Variable to memorise the returned flag
  bool flag = false;

  // Switch according to the type of iterator
  switch (that->type) {

    case GSetIterForward:
      if (that->elem->next != NULL) {

        that->elem = that->elem->next;
        flag = true;

      }

      break;

    case GSetIterBackward:
      if (that->elem->prev != NULL) {

        that->elem = that->elem->prev;
        flag = true;

      }

      break;

    default:
      Raise(TryCatchExc_NotYetImplemented);

  }

  // Return the flag
  return flag;

}

// Move the iterator to the previous element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator could move to the previous element, else false
bool GSetIterPrev_(
  GSetIter* const that) {

  if (that->elem == NULL) return false;

  // Variable to memorise the returned flag
  bool flag = false;

  // Switch according to the type of iterator
  switch (that->type) {

    case GSetIterForward:
      if (that->elem->prev != NULL) {

        that->elem = that->elem->prev;
        flag = true;

      }

      break;

    case GSetIterBackward:
      if (that->elem->next != NULL) {

        that->elem = that->elem->next;
        flag = true;

      }

      break;

    default:
      Raise(TryCatchExc_NotYetImplemented);

  }

  // Return the flag
  return flag;

}

// Check if an iterator is on its first element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator is on its first element, else false
bool GSetIterIsFirst_(
  GSetIter* const that) {

  if (that->elem == NULL) Raise(TryCatchExc_OutOfRange);

  // Variable to memorise the returned flag
  bool flag = true;

  // Switch according to the type of iterator
  switch (that->type) {

    case GSetIterForward:
      if (that->elem->prev != NULL) flag = false;
      break;

    case GSetIterBackward:
      if (that->elem->next != NULL) flag = false;
      break;

    default:
      Raise(TryCatchExc_NotYetImplemented);

  }

  // Return the flag
  return flag;

}

// Check if an iterator is on its last element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator is on its last element, else false
bool GSetIterIsLast_(
  GSetIter* const that) {

  if (that->elem == NULL) Raise(TryCatchExc_OutOfRange);

  // Variable to memorise the returned flag
  bool flag = true;

  // Switch according to the type of iterator
  switch (that->type) {

    case GSetIterForward:
      if (that->elem->next != NULL) flag = false;
      break;

    case GSetIterBackward:
      if (that->elem->prev != NULL) flag = false;
      break;

    default:
      Raise(TryCatchExc_NotYetImplemented);

  }

  // Return the flag
  return flag;

}

// Clone an iterator
// Input:
//   that: the iterator
// Output:
//   Return a clone of the iterator
GSetIter* GSetIterClone_(
  GSetIter* const that) {

  // Allocate memory for the clone
  GSetIter* clone = GSetIterAlloc(that->type);

  // Copy the iterator
  *clone = *that;

  // Return the clone
  return clone;

}

// Set the type of an iterator
// Input:
//   that: the iterator
//   type: the type
void GSetIterSetType_(
  GSetIter* const that,
  GSetIterType const type) {

  // Set the type
  that->type = type;

}

// Get the type of an iterator
// Input:
//   that: the iterator
// Return the type of the iterator
GSetIterType GSetIterGetType_(
  GSetIter const* const that) {

  // Return the type
  return that->type;

}

// Deallocation functions for GSet<N>Flush on default typed GSet

#define Free_(N, T)                                                          \
void N ## Free(T* const that) {                                              \
  if (that == NULL || *that == NULL) return;                                 \
  free(*that); *that = NULL;                                                 \
}
Free_(CharPtr, char*)
Free_(UCharPtr, unsigned char*)
Free_(IntPtr, int*)
Free_(UIntPtr, unsigned int*)
Free_(LongPtr, long*)
Free_(ULongPtr, unsigned long*)
Free_(FloatPtr, float*)
Free_(DoublePtr, double*)
Free_(Str, char*)

// Comparison functions for GSet<N>Sort on default typed GSet

int GSetCharCmp(void const* a, void const* b) {

  return (*(char const*)a < *(char const*)b ? -1 :
          *(char const*)a > *(char const*)b ? 1 : 0);

}

int GSetUCharCmp(void const* a, void const* b) {

  return (*(unsigned char const*)a < *(unsigned char const*)b ? -1 :
          *(unsigned char const*)a > *(unsigned char const*)b ? 1 : 0);

}

int GSetIntCmp(void const* a, void const* b) {

  return (*(int const*)a < *(int const*)b ? -1 :
          *(int const*)a > *(int const*)b ? 1 : 0);

}

int GSetUIntCmp(void const* a, void const* b) {

  return (*(unsigned int const*)a < *(unsigned int const*)b ? -1 :
          *(unsigned int const*)a > *(unsigned int const*)b ? 1 : 0);

}

int GSetLongCmp(void const* a, void const* b) {

  return (*(long const*)a < *(long const*)b ? -1 :
          *(long const*)a > *(long const*)b ? 1 : 0);

}

int GSetULongCmp(void const* a, void const* b) {

  return (*(unsigned long const*)a < *(unsigned long const*)b ? -1 :
          *(unsigned long const*)a > *(unsigned long const*)b ? 1 : 0);

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

int GSetCharPtrCmp(void const* a, void const* b) {

  char* sa = *(char* const*)a;
  char* sb = *(char* const*)b;
  if (sa == NULL && sb == NULL) return 0;
  if (sa == NULL && sb != NULL) return -1;
  if (sa != NULL && sb == NULL) return 1;
  return strcmp(sa, sb);

}

// ================== Private functions definition =========================

// Create a new GSetElem
// Output:
//   Return the new GSetElem.
static GSetElem GSetElemCreate(
  void) {

  // Create the GSetElem
  GSetElem that = (GSetElem){

    .prev = NULL,
    .next = NULL,

  };

  // Return the GSetElem
  return that;
}

// Allocate memory for a new GSetElem
// Output:
//   Return the new GSetElem.
static GSetElem* GSetElemAlloc(
  void) {

  // Allocate memory for the element
  GSetElem* that = NULL;
  SafeMalloc(
    that,
    sizeof(GSetElem));

  // Create the element
  *that = GSetElemCreate();

  // Return the new GSetElem
  return that;

}

// Free the memory used by a GSetElem, do not free the memory used by the data
// it contains.
// Input:
//   that: the GSetElem to be freed
static void GSetElemFree(
  GSetElem** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Free the memory
  free(*that);
  *that = NULL;

}

// Create a new GSet
// Output:
//   Return the new GSet.
static GSet GSetCreate(
  void) {

  // Create the GSet
  GSet that = (GSet){

    .size = 0,
    .first = NULL,
    .last = NULL,

  };

  // Return the GSet
  return that;

}

// Push an element at the head of the set
// Inputs:
//   that: the set
//   elem: the element
static void GSetPushElem(
      GSet* const that,
  GSetElem* const elem) {

  // Check for overflow
  if (that->size > SIZE_MAX - 1) Raise(TryCatchExc_IntOverflow);

  // Add the element to the head of the set
  elem->next = that->first;
  if (that->first != NULL) that->first->prev = elem;
  that->first = elem;
  if (that->size == 0) that->last = elem;

  // Update the size of the set
  ++(that->size);

}

// Add an element at the tail of the set
// Inputs:
//   that: the set
//   elem: the element
static void GSetAddElem(
      GSet* const that,
  GSetElem* const elem) {

  // Check for overflow
  if (that->size > SIZE_MAX - 1) Raise(TryCatchExc_IntOverflow);

  // Add the element to the tail of the set
  elem->prev = that->last;
  if (that->last != NULL) that->last->next = elem;
  that->last = elem;
  if (that->size == 0) that->first = elem;

  // Update the size of the set
  ++(that->size);

}

// Pop an element from the head of the set
// Input:
//   that: the set
// Output:
//   Return the element
static GSetElem* GSetPopElem(
  GSet* const that) {

  // Remove the first element
  GSetElem* elem = that->first;
  if (that->last == that->first) that->last = NULL;
  that->first = elem->next;
  if (that->first != NULL) that->first->prev = NULL;

  // Update the size of the set
  --(that->size);

  // Return the element
  return elem;

}

// Drop an element from the tail of the set
// Input:
//   that: the set
// Output:
//   Return the element
static GSetElem* GSetDropElem(
  GSet* const that) {

  // Remove the last element
  GSetElem* elem = that->last;
  if (that->last == that->first) that->first = NULL;
  that->last = elem->prev;
  if (that->last != NULL) that->last->next = NULL;

  // Update the size of the set
  --(that->size);

  // Return the element
  return elem;

}

// Create a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
GSetIter GSetIterCreate(
  enum GSetIterType const type) {

  // Create the GSet
  GSetIter that = (GSetIter){

    .elem = NULL,
    .type = type,

  };

  // Return the GSet
  return that;

}

// ------------------ gset.c ------------------
