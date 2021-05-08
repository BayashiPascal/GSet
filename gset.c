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

// Number of exceptions in GSetException
#define NbExceptions GSetExc_LastID - GSetExc_EmptySet

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
  if (that->size == 0) {

    that->last = elem;
    that->curElem = elem;

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
  that->last = elem;
  if (that->size == 0) {

    that->first = elem;
    that->curElem = elem;

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
  if (that->curElem == that->first) {

    // Try to move to the next element
    bool flag = GSetIterNext(that);

    // If we couldn't move to the next, try to move to the previous
    if(flag == false) flag = GSetIterNext(that);

    // If we still couldn't move, reset the current element
    if(flag == false) that->curElem = NULL;

  }

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
  if (that->curElem == that->last) {

    // Try to move to the next element
    bool flag = GSetIterNext(that);

    // If we couldn't move to the next, try to move to the previous
    if(flag == false) flag = GSetIterNext(that);

    // If we still couldn't move, reset the current element
    if(flag == false) that->curElem = NULL;

  }

  // Remove the last element
  struct GSetElem* elem = that->last;
  that->last = elem->prev;
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
  if(flag == false) that->curElem = NULL;

  // Remove the current element
  if (that->first == that->curElem) {

    that->first = elem->next;
    elem->next->prev = NULL;

  } else if (that->last == that->curElem) {

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
        that->curElem = that->first;
        break;

      case GSetIteration_backward:

        // Move to the tail of the GSet
        that->curElem = that->last;
        break;

      default:
        break;

    }

  // Else there is no element in the dataset
  } else that->curElem = NULL;

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
        if (that->curElem->next != NULL)
          that->curElem = that->curElem->next;
        // Else, there is no next element, update the flag
        else flag = false;
        break;

      case GSetIteration_backward:

        // If there is a previous element, move to it
        if (that->curElem->prev != NULL)
          that->curElem = that->curElem->prev;
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
        if (that->curElem->prev != NULL)
          that->curElem = that->curElem->prev;
        // Else, there is no next element, update the flag
        else flag = false;
        break;

      case GSetIteration_backward:

        // If there is a next element, move to it
        if (that->curElem->next != NULL)
          that->curElem = that->curElem->next;
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
