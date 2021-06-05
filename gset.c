// ------------------ gset.c ------------------

// Include the header
#include <string.h>
#include <float.h>
#include <math.h>
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

// Structure of a GSet element
struct GSetElem {

  // Data in the element
  union {
    char Char;
    unsigned char UChar;
    int Int;
    unsigned int UInt;
    long Long;
    unsigned long ULong;
    float Float;
    double Double;
    void* Ptr;
  } data;

  // Previous element in the set
  struct GSetElem* prev;

  // Next element in the set
  struct GSetElem* next;

};

// Structure of a GSet
struct GSet {

  // Size of the GSet (i.e. number of GSetElem currently in it)
  size_t size;

  // First element of the set
  struct GSetElem* first;

  // Last element of the set
  struct GSetElem* last;

};

// ================== Private functions declaration =========================

// Create a new GSetElem
// Output:
//   Return the new GSetElem.
static struct GSetElem GSetElemCreate(
  void);

// Allocate memory for a new GSetElem
// Output:
//   Return the new GSetElem.
static struct GSetElem* GSetElemAlloc(
  void);

// Free the memory used by a GSetElem, do not free the memory used by the data
// it contains.
// Input:
//   that: the GSetElem to be freed
static void GSetElemFree(
  struct GSetElem** const that);

// Create a new GSet
// Output:
//   Return the new GSet.
static struct GSet GSetCreate(
  void);

// Push an element at the head of the set
// Inputs:
//   that: the set
//   elem: the element
static void GSetPushElem(
      struct GSet* const that,
  struct GSetElem* const elem);

// Add an element at the tail of the set
// Inputs:
//   that: the set
//   elem: the element
static void GSetAddElem(
      struct GSet* const that,
  struct GSetElem* const elem);

// Pop an element from the head of the set
// Input:
//   that: the set
// Output:
//   Return the element
static struct GSetElem* GSetPopElem(
  struct GSet* const that);

// Drop an element from the tail of the set
// Input:
//   that: the set
// Output:
//   Return the element
static struct GSetElem* GSetDropElem(
  struct GSet* const that);

// ================== Public functions definition =========================

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

// Empty the GSet with GSetEmpty() and free the memory it used.
// Input:
//   that: the GSet to be freed
void GSetFree_(
  struct GSet** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Empty the GSet
  //GSetEmpty(*that);

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
  struct GSet* const that,                                                   \
             T const data) {                                                 \
  struct GSetElem* elem = GSetElemAlloc();                                   \
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
  struct GSet* const that,                                                   \
             T const data) {                                                 \
  struct GSetElem* elem = GSetElemAlloc();                                   \
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

// Pop data from the head of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the head of the set and return it
#define GSetPop__(N, T)                                                      \
T GSetPop_ ## N(                                                             \
  struct GSet* const that) {                                                 \
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);                        \
  struct GSetElem* elem = GSetPopElem(that);                                 \
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
  struct GSet* const that) {                                                 \
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);                        \
  struct GSetElem* elem = GSetDropElem(that);                                \
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

// ================== Private functions definition =========================

// Create a new GSetElem
// Output:
//   Return the new GSetElem.
static struct GSetElem GSetElemCreate(
  void) {

  // Create the GSetElem
  struct GSetElem that = (struct GSetElem){

    .prev = NULL,
    .next = NULL,

  };

  // Return the GSetElem
  return that;
}

// Allocate memory for a new GSetElem
// Output:
//   Return the new GSetElem.
static struct GSetElem* GSetElemAlloc(
  void) {

  // Allocate memory for the element
  struct GSetElem* that = NULL;
  SafeMalloc(
    that,
    sizeof(struct GSetElem));

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
  struct GSetElem** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Free the memory
  free(*that);
  *that = NULL;

}

// Create a new GSet
// Output:
//   Return the new GSet.
static struct GSet GSetCreate(
  void) {

  // Create the GSet
  struct GSet that = (struct GSet){

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
      struct GSet* const that,
  struct GSetElem* const elem) {

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
      struct GSet* const that,
  struct GSetElem* const elem) {

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
static struct GSetElem* GSetPopElem(
  struct GSet* const that) {

  // Remove the first element
  struct GSetElem* elem = that->first;
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
static struct GSetElem* GSetDropElem(
  struct GSet* const that) {

  // Remove the last element
  struct GSetElem* elem = that->last;
  that->last = elem->prev;
  if (that->last != NULL) that->last->next = NULL;

  // Update the size of the set
  --(that->size);

  // Return the element
  return elem;

}

// ------------------ gset.c ------------------
