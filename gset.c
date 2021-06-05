// ------------------ gset.c ------------------

// Include the header
#include <string.h>
#include <float.h>
#include <math.h>
#include "gset.h"

// ================== Macros =========================

// Polymorphic free
struct GSetElem;
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

  // Current element (according to iteration operations)
  struct GSetElem* elem;

  // Index of the iterator, set to 0 by GSetIterReset, incremented by
  // GSetIterNext, decremented by GSetIterPrev
  size_t idx;

  // Flag raised when the iterator reaches its end
  bool iterEnd;

  // Type of iteration
  enum GSetIteration iteration;

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
void GSetFree(
  struct GSet** const that) {

  // If the memory is already freed, nothing to do
  if (that == NULL || *that == NULL) return;

  // Empty the GSet
  //GSetEmpty(*that);

  // Free the memory
  free(*that);
  *that = NULL;

}

void GSetPush_Int(struct GSet* that, int data) {

  that->first->data.Int = data;

}

void GSetPush_UInt(struct GSet* that, unsigned int data) {

  that->first->data.UInt = data;

}

void GSetPush_Ptr(struct GSet* that, void* data) {

  that->first->data.Ptr = data;

}

int GSetPop_Int(struct GSet* that) {

  return that->first->data.Int;

}

unsigned int GSetPop_UInt(struct GSet* that) {

  return that->first->data.UInt;

}

void* GSetPop_Ptr(struct GSet* that) {

  return that->first->data.Ptr;

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
    .elem = NULL,
    .idx = 0,
    .iterEnd = false,
    .iteration = GSetIteration_forward,

  };

  // Return the GSet
  return that;

}

// ------------------ gset.c ------------------
