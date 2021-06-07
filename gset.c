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

// Structure of an iterator on a GSet
struct GSetIter {

  // Current element
  struct GSetElem* elem;

  // Type of iteration
  enum GSetIterType type;

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

// Create a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
struct GSetIter GSetIterCreate(
  enum GSetIterType const type);

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

// Append data from a set to the end of another
// Input:
//   that: the set where data are added
//   tho: the set containing data to add
void GSetAppend_(
        struct GSet* const that,
  struct GSet const* const tho) {

  // If the set source is empty, nothing to do
  if (tho->size == 0) return;
  // TODO: try catch
  // Loop on the element of the set source
  struct GSetIter* iter = GSetIterAlloc(GSetIterForward);
  do {

    // Add the data from the source to the destination
    struct GSetElem* elem = GSetElemAlloc();
    elem->data = iter->elem->data;
    GSetAddElem(that, elem);

  } while (GSetIterNext_(iter));

  // Free memory
  GSetIterFree_(&iter);

}

// Return the number of element in the set
// Input:
//   that: the set
// Output:
//   Return the number of element.
size_t GSetGetSize_(
  struct GSet const* const that) {

  return that->size;

}

// Empty the set. Memory used by data in it is not freed.
// To empty the set and free data, use GSet<N>Flush() instead.
// Input:
//   that: the set
void GSetEmpty_(
  struct GSet* const that) {

  // Loop until the set is empty
  while (GSetGetSize_(that) > 0) {

    // Pop the element
    struct GSetElem* elem = GSetPopElem(that);

    // Free the element, in memory of L3-37
    GSetElemFree(&elem);

  }

}

// Allocate memory for a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
struct GSetIter* GSetIterAlloc(
  enum GSetIterType const type) {

  // Allocate memory for the GSet
  struct GSetIter* that = NULL;
  SafeMalloc(
    that,
    sizeof(struct GSetIter));

  // Create the GSet
  *that = GSetIterCreate(type);

  // Return the GSet
  return that;

}

// Free the memory used by a GSetIter.
// Input:
//   that: the GSetIter to be freed
void GSetIterFree_(
  struct GSetIter** const that) {

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
  struct GSetIter const* const that) {                                       \
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
  struct GSetIter* const that,                                               \
  struct GSet* const set) {                                                  \
  if (that->elem == NULL) Raise(TryCatchExc_OutOfRange);                     \
  T data = that->elem->data.N;                                               \
  if (set->first == that->elem) set->first = set->first->next;               \
  if (set->last == that->elem) set->last = set->last->prev;                  \
  if (that->elem->next != NULL) that->elem->next->prev = that->elem->prev;   \
  if (that->elem->prev != NULL) that->elem->prev->next = that->elem->next;   \
  struct GSetElem* elem = that->elem;                                        \
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
    struct GSetIter* const that,
  struct GSet const* const set) {

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
  struct GSetIter* const that) {

  if (that->elem == NULL) Raise(TryCatchExc_OutOfRange);

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
  struct GSetIter* const that) {

  if (that->elem == NULL) Raise(TryCatchExc_OutOfRange);

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
  struct GSetIter* const that) {

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
  struct GSetIter* const that) {

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
struct GSetIter* GSetIterClone_(
  struct GSetIter* const that) {

  // Allocate memory for the clone
  struct GSetIter* clone = GSetIterAlloc(that->type);

  // Copy the iterator
  *clone = *that;

  // Return the clone
  return clone;

}

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

// Create a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
struct GSetIter GSetIterCreate(
  enum GSetIterType const type) {

  // Create the GSet
  struct GSetIter that = (struct GSetIter){

    .elem = NULL,
    .type = type,

  };

  // Return the GSet
  return that;

}

// ============= Deallocation functions for default typed GSet =============
#define Free(N, T)                                                           \
void N ## Free(T* const that) {                                             \
  if (that == NULL || *that == NULL) return;                                 \
  free(*that); *that = NULL;                                                 \
}
Free(CharPtr, char*)
Free(UCharPtr, unsigned char*)
Free(IntPtr, int*)
Free(UIntPtr, unsigned int*)
Free(LongPtr, long*)
Free(ULongPtr, unsigned long*)
Free(FloatPtr, float*)
Free(DoublePtr, double*)
Free(Str, char*)

// ------------------ gset.c ------------------
