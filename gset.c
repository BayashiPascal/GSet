// ------------------ gset.c ------------------

// Include the header
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
  that->first = elem;
  ++(that->size);

}

// Remove and return the data at the head of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data
void* GSetPop(
  struct GSet* const that) {

  // If there is no data to pop, raise an exception
  // TODO if (that->size == 0) Raise();

  // Remove the first element
  struct GSetElem* elem = that->first;
  that->first = elem->next;
  --(that->size);

  // Memorise the data and free the element
  void* data = elem->data;
  GSetElemFree(&elem);

  // Return the element's data
  return data;

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
