// *************** GSET.H ***************
#ifndef GSET_H
#define GSET_H

// ================= Include ==================
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// ================= Define ==================

// ================= Generic functions ==================

void GSetIterUnsupported(void*t, ...); 
#define GSetIterFree(I) _Generic((I), \
  GSetIterForward**: GSetIterForwardFree, \
  GSetIterBackward**: GSetIterBackwardFree, \
  default: GSetIterUnsupported)(I)
#define GSetIterClone(I) _Generic((I), \
  GSetIterForward*: GSetIterForwardClone, \
  GSetIterBackward*: GSetIterBackwardClone, \
  default: GSetIterUnsupported)(I)
#define GSetIterReset(I) _Generic((I), \
  GSetIterForward*: GSetIterForwardReset, \
  GSetIterBackward*: GSetIterBackwardReset, \
  default: GSetIterUnsupported)(I)
#define GSetIterStep(I) _Generic((I), \
  GSetIterForward*: GSetIterForwardStep, \
  GSetIterBackward*: GSetIterBackwardStep, \
  default: GSetIterUnsupported)(I)
#define GSetIterApply(I, F, P) _Generic((I), \
  GSetIterForward*: GSetIterForwardApply, \
  GSetIterBackward*: GSetIterBackwardApply, \
  default: GSetIterUnsupported)(I, F, P)
#define GSetIterIsFirst(I) _Generic((I), \
  GSetIterForward*: GSetIterForwardIsFirst, \
  GSetIterBackward*: GSetIterBackwardIsFirst, \
  default: GSetIterUnsupported)(I)
#define GSetIterIsLast(I) _Generic((I), \
  GSetIterForward*: GSetIterForwardIsLast, \
  GSetIterBackward*: GSetIterBackwardIsLast, \
  default: GSetIterUnsupported)(I)
#define GSetIterSetGSet(I, S) _Generic((I), \
  GSetIterForward*: GSetIterForwardSetGSet, \
  GSetIterBackward*: GSetIterBackwardSetGSet, \
  default: GSetIterUnsupported)(I, S)
#define GSetIterGet(I) _Generic((I), \
  GSetIterForward*: GSetIterForwardGet, \
  GSetIterBackward*: GSetIterBackwardGet, \
  default: GSetIterUnsupported)(I)
#define GSetIterGetElem(I) _Generic((I), \
  GSetIterForward*: GSetIterForwardGetElem, \
  GSetIterBackward*: GSetIterBackwardGetElem, \
  default: GSetIterUnsupported)(I)

// ================= Data structures ===================

// Structure of one element of the GSet
struct GSetElem;
typedef struct GSetElem {
  // Pointer toward the data
  void* _data;
  // Pointer toward the next element in the GSet
  struct GSetElem *_next;
  // Pointer toward the previous element in the GSet
  struct GSetElem *_prev;
  // Value to sort element in the GSet, 0.0 by default
  double _sortVal;
} GSetElem;

// Structure of the GSet
typedef struct GSet {
  // Pointer toward the element at the head of the GSet
  GSetElem *_head;
  // Pointer toward the last element of the GSet
  GSetElem *_tail;
  // Number of element in the GSet
  int _nbElem;
} GSet;

// Structures of the GSet iterators
typedef struct GSetIterForward {
  GSet *_set;
  GSetElem *_curElem;
} GSetIterForward;

typedef struct GSetIterBackward {
  GSet *_set;
  GSetElem *_curElem;
} GSetIterBackward;

// ================ Functions declaration ====================

// Function to create a new GSet,
// Return a pointer toward the new GSet, or null if it couldn't
// create the GSet
GSet* GSetCreate(void);

// Function to clone a GSet,
// Return a pointer toward the new GSet, or null if it couldn't
// clone the GSet
GSet* GSetClone(GSet *s);

// Function to free the memory used by the GSet
void GSetFree(GSet **s);

// Function to empty the GSet
void GSetFlush(GSet *s);

// Function to print a GSet
// Use the function 'printData' to print the data pointed to by 
// the elements, and print 'sep' between each element
// If printData is null, print the pointer value instead
// Do nothing if arguments are invalid
void GSetPrint(GSet *s, FILE* stream, 
  void(*printData)(void *data, FILE *stream), char *sep);

// Function to insert an element pointing toward 'data' at the 
// head of the GSet
// Do nothing if arguments are invalid
void GSetPush(GSet *s, void* data);

// Function to insert an element pointing toward 'data' at the 
// position defined by 'v' sorting the set in decreasing order
// Do nothing if arguments are invalid
void GSetAddSort(GSet *s, void* data, double v);

// Function to insert an element pointing toward 'data' at the 
// 'iElem'-th position 
// If 'iElem' is greater than or equal to the number of element
// in the GSet, elements pointing toward null data are added
// Do nothing if arguments are invalid
void GSetInsert(GSet *s, void* data, int iElem);

// Function to insert an element pointing toward 'data' at the 
// tail of the GSet
// Do nothing if arguments are invalid
void GSetAppend(GSet *s, void* data);

// Function to remove the element at the head of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
// Return null if arguments are invalid
void* GSetPop(GSet *s);

// Function to remove the element at the tail of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
// Return null if arguments are invalid
void* GSetDrop(GSet *s);

// Function to remove the element at the 'iElem'-th position of the GSet
// Return the data pointed to by the removed element
// Return null if arguments are invalid
void* GSetRemove(GSet *s, int iElem);

// Function to remove the element 'elem' of the GSet
// Return the data pointed to by the removed element
// The GSetElem is freed and *elem == NULL after calling this function
// Return null if arguments are invalid
void* GSetRemoveElem(GSet *s, GSetElem **elem);

// Function to remove the first element of the GSet pointing to 'data'
// Do nothing if arguments are invalid
void GSetRemoveFirst(GSet *s, void *data);

// Function to remove the last element of the GSet pointing to 'data'
// Do nothing if arguments are invalid
void GSetRemoveLast(GSet *s, void *data);

// Function to remove all the selement of the GSet pointing to 'data'
// Do nothing if arguments are invalid
void GSetRemoveAll(GSet *s, void *data);

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
// Return the data pointed to by the element
// Return null if arguments are invalid
void* GSetGet(GSet *s, int iElem);

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
// Return the GSetElem
// Return null if arguments are invalid
GSetElem* GSetGetElem(GSet *s, int iElem);

// Function to get the index of the first element of the GSet
// which point to 'data'
// Return -1 if arguments are invalid or 'data' is not in the GSet
int GSetGetIndexFirst(GSet *s, void *data);

// Function to get the index of the last element of the GSet
// which point to 'data'
// Return -1 if arguments are invalid or 'data' is not in the GSet
int GSetGetIndexLast(GSet *s, void *data);

// Function to sort the element of the gset in increasing order of 
// _sortVal
// Do nothing if arguments are invalid or the sort failed
void GSetSort(GSet *s);

// Merge the GSet '*r' at the end of the GSet '*s'
// '*r' and '*s' can be empty
// After calling this function (*r == null) and *r is freed
// Do nothing if arguments are invalid
void GSetMerge(GSet **s, GSet **r);

// Split the GSet 's' at the GSetElem 'e'
// 'e' must be and element of 's'
// Return a new GSet starting with 'e', ot NULL if memory allocation 
// failed or arguments are invalid
GSet* GSetSplit(GSet *s, GSetElem *e);

// Switch the 'iElem'-th and 'jElem'-th element of the set
// Do nothing if arguments are invalid
void GSetSwitch(GSet *s, int iElem, int jElem);

// Create a new GSetIterForward for the GSet 'set'
// The iterator is reset upon creation
// Return NULL if memory couldn't be allocated
GSetIterForward* GSetIterForwardCreate(GSet *set);

// Create a new GSetIterBackward for the GSet 'set'
// The iterator is reset upon creation
// Return NULL if memory couldn't be allocated
GSetIterBackward* GSetIterBackwardCreate(GSet *set);

// Free the memory used by a GSetIterForward (not by its atached GSet)
// Do nothing if arguments are invalid
void GSetIterForwardFree(GSetIterForward **that);

// Free the memory used by a GSetIterBackward (not by its atached GSet)
// Do nothing if arguments are invalid
void GSetIterBackwardFree(GSetIterBackward **that);

// Clone a GSetIterForward
// Return NULL if arguments are invalid or memory allocation failed
GSetIterForward* GSetIterForwardClone(GSetIterForward *that);

// Clone a GSetIterBackward
// Return NULL if arguments are invalid or memory allocation failed
GSetIterBackward* GSetIterBackwardClone(GSetIterBackward *that);

// Reset the GSetIterForward to its starting position
// Do nothing if arguments are invalid
void GSetIterForwardReset(GSetIterForward *that);

// Reset the GSetIterBackward to its starting position
// Do nothing if arguments are invalid
void GSetIterBackwardReset(GSetIterBackward *that);

// Step the GSetIterForward
// Return false if arguments are invalid or we couldn't step
// Return true else
bool GSetIterForwardStep(GSetIterForward *that);

// Step the GSetIterBackward
// Return false if arguments are invalid or we couldn't step
// Return true else
bool GSetIterBackwardStep(GSetIterBackward *that);

// Apply a function to all elements of the GSet of the GSetIterForward
// The iterator is first reset, then the function is apply sequencially
// using the Step funciton of the iterator
// Do nothing if arguments are invalid
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
void GSetIterForwardApply(GSetIterForward *that, 
  void(*fun)(void *data, void *param), void *param);

// Apply a function to all elements of the GSet of the GSetIterBackward
// The iterator is first reset, then the function is apply sequencially
// using the Step funciton of the iterator
// Do nothing if arguments are invalid
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
void GSetIterBackwardApply(GSetIterBackward *that, 
  void(*fun)(void *data, void *param), void *param);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false if arguments are invalid
// Return false else
bool GSetIterForwardIsFirst(GSetIterForward *that);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false if arguments are invalid
// Return false else
bool GSetIterBackwardIsFirst(GSetIterBackward *that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false if arguments are invalid
// Return false else
bool GSetIterForwardIsLast(GSetIterForward *that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false if arguments are invalid
// Return false else
bool GSetIterBackwardIsLast(GSetIterBackward *that);

// Change the attached set of the iterator, and reset it
// Do nothing if argument is invalid
void GSetIterForwardSetGSet(GSetIterForward *that, GSet *set);

// Change the attached set of the iterator, and reset it
// Do nothing if argument is invalid
void GSetIterBackwardSetGSet(GSetIterBackward *that, GSet *set);

// Return the data currently pointed to by the iterator
// Return null if arguments are invalid
void* GSetIterForwardGet(GSetIterForward *that);

// Return the data currently pointed to by the iterator
// Return null if arguments are invalid
void* GSetIterBackwardGet(GSetIterBackward *that);

// Return the element currently pointed to by the iterator
// Return null if arguments are invalid
GSetElem* GSetIterForwardGetElem(GSetIterForward *that);

// Return the element currently pointed to by the iterator
// Return null if arguments are invalid
GSetElem* GSetIterBackwardGetElem(GSetIterBackward *that);


#endif
