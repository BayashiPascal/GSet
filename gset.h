// *************** GSET.H ***************
#ifndef GSET_H
#define GSET_H

// ================= Include ==================
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pberr.h"

// ================= Define ==================

// ================= Generic functions ==================

#define GSetIterFree(IterRef) _Generic(IterRef, \
  GSetIterForward**: GSetIterForwardFree, \
  GSetIterBackward**: GSetIterBackwardFree, \
  default: PBErrInvalidPolymorphism)(IterRef)

#define GSetIterClone(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardClone, \
  GSetIterBackward*: GSetIterBackwardClone, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterReset(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardReset, \
  GSetIterBackward*: GSetIterBackwardReset, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterStep(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardStep, \
  GSetIterBackward*: GSetIterBackwardStep, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterApply(Iter, Fun, Param) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardApply, \
  GSetIterBackward*: GSetIterBackwardApply, \
  default: PBErrInvalidPolymorphism)(Iter, Fun, Param)

#define GSetIterIsFirst(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardIsFirst, \
  GSetIterBackward*: GSetIterBackwardIsFirst, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterIsLast(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardIsLast, \
  GSetIterBackward*: GSetIterBackwardIsLast, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterSetGSet(Iter, Set) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardSetGSet, \
  GSetIterBackward*: GSetIterBackwardSetGSet, \
  default: PBErrInvalidPolymorphism)(Iter, Set)

#define GSetIterGet(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardGet, \
  GSetIterBackward*: GSetIterBackwardGet, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterGetElem(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardGetElem, \
  GSetIterBackward*: GSetIterBackwardGetElem, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterRemoveElem(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardRemoveElem, \
  GSetIterBackward*: GSetIterBackwardRemoveElem, \
  default: PBErrInvalidPolymorphism)(Iter)

// ================= Data structures ===================

// Structure of one element of the GSet
struct GSetElem;
typedef struct GSetElem {
  // Pointer toward the data
  void* _data;
  // Pointer toward the next element in the GSet
  struct GSetElem* _next;
  // Pointer toward the previous element in the GSet
  struct GSetElem* _prev;
  // Value to sort element in the GSet, 0.0 by default
  float _sortVal;
} GSetElem;

// Structure of the GSet
typedef struct GSet {
  // Pointer toward the element at the head of the GSet
  GSetElem* _head;
  // Pointer toward the last element of the GSet
  GSetElem* _tail;
  // Number of element in the GSet
  int _nbElem;
} GSet;

// Structures of the GSet iterators
typedef struct GSetIterForward {
  // GSet attached to the iterator
  GSet* _set;
  // Current element
  GSetElem* _curElem;
} GSetIterForward;

typedef struct GSetIterBackward {
  // GSet attached to the iterator
  GSet* _set;
  // Current element
  GSetElem* _curElem;
} GSetIterBackward;

// ================ Functions declaration ====================

// Function to create a new GSet,
// Return a pointer toward the new GSet
GSet* GSetCreate(void);

// Static constructors for GSet
#if BUILDMODE != 0
inline
#endif 
GSet GSetCreateStatic(void);

// Function to clone a GSet,
// Return a pointer toward the new GSet
GSet* GSetClone(GSet* that);

// Function to free the memory used by the GSet
void GSetFree(GSet** s);

// Function to empty the GSet
#if BUILDMODE != 0
inline
#endif 
void GSetFlush(GSet* that);

// Return the number of element in the set
#if BUILDMODE != 0
inline
#endif 
int GSetNbElem(GSet* that);

// Function to print a GSet
// Use the function 'printData' to print the data pointed to by 
// the elements, and print 'sep' between each element
// If printData is null, print the pointer value instead
void GSetPrint(GSet* that, FILE* stream, 
  void(*printData)(void* data, FILE* stream), char* sep);

// Function to insert an element pointing toward 'data' at the 
// head of the GSet
#if BUILDMODE != 0
inline
#endif 
void GSetPush(GSet* that, void* data);

// Function to insert an element pointing toward 'data' at the 
// position defined by 'v' sorting the set in increasing order
void GSetAddSort(GSet* that, void* data, double v);

// Function to insert an element pointing toward 'data' at the 
// 'iElem'-th position 
// If 'iElem' is greater than or equal to the number of element
// in the GSet, elements pointing toward null data are added
// If the data is inserted inside the set, the current elements from
// the iElem-th elem are pushed 
void GSetInsert(GSet* that, void* data, int iElem);

// Function to insert an element pointing toward 'data' at the 
// tail of the GSet
#if BUILDMODE != 0
inline
#endif 
void GSetAppend(GSet* that, void* data);

// Function to remove the element at the head of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* GSetPop(GSet* that);

// Function to remove the element at the tail of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* GSetDrop(GSet* that);

// Function to remove the element at the 'iElem'-th position of the GSet
// Return the data pointed to by the removed element
#if BUILDMODE != 0
inline
#endif 
void* GSetRemove(GSet* that, int iElem);

// Function to remove the element 'elem' of the GSet
// Return the data pointed to by the removed element
// The GSetElem is freed and *elem == NULL after calling this function
#if BUILDMODE != 0
inline
#endif 
void* GSetRemoveElem(GSet* that, GSetElem** elem);

// Function to remove the first element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void GSetRemoveFirst(GSet* that, void* data);

// Function to remove the last element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void GSetRemoveLast(GSet* that, void* data);

// Function to remove all the selement of the GSet pointing to 'data'
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void GSetRemoveAll(GSet* that, void* data);

// Function to get the data at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* GSetGet(GSet* that, int iElem);

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetGetElem(GSet* that, int iElem);

// Function to get the index of the first element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
int GSetGetIndexFirst(GSet* that, void* data);

// Function to get the index of the last element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
int GSetGetIndexLast(GSet* that, void* data);

// Function to get the first element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetGetFirstElem(GSet* that, void* data);

// Function to get the last element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetGetLastElem(GSet* that, void* data);

// Function to sort the element of the gset in increasing order of 
// _sortVal
void GSetSort(GSet* that);

// Merge the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
// After calling this function 'set' is empty 
#if BUILDMODE != 0
inline
#endif 
void GSetMerge(GSet* that, GSet* set);

// Split the GSet at the GSetElem 'e'
// 'e' must be and element of the set
// the set new end is the element before 'e', the set becomes empty if 
// 'e' was the first element
// Return a new GSet starting with 'e', or NULL if 'e' is not 
// an element of the set
#if BUILDMODE != 0
inline
#endif 
GSet* GSetSplit(GSet* that, GSetElem* e);

// Append the element of the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void GSetAppendSet(GSet* that, GSet* set);

// Append the element of the GSet 'that' at the end of the GSet 'set'
// Elements are kept sorted
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void GSetAppendSortedSet(GSet* that, GSet* set);

// Switch the 'iElem'-th and 'jElem'-th element of the set
#if BUILDMODE != 0
inline
#endif 
void GSetSwitch(GSet* that, int iElem, int jElem);

// Set the sort value of the GSetElem 'that' to 'v'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetSortVal(GSetElem* that, float v);

// Create a new GSetIterForward for the GSet 'set'
// The iterator is reset upon creation
GSetIterForward* GSetIterForwardCreate(GSet* set);
#if BUILDMODE != 0
inline
#endif 
GSetIterForward GSetIterForwardCreateStatic(GSet* set);

// Create a new GSetIterBackward for the GSet 'set'
// The iterator is reset upon creation
GSetIterBackward* GSetIterBackwardCreate(GSet* set);
#if BUILDMODE != 0
inline
#endif 
GSetIterBackward GSetIterBackwardCreateStatic(GSet* set);

// Free the memory used by a GSetIterForward (not by its attached GSet)
// Do nothing if arguments are invalid
void GSetIterForwardFree(GSetIterForward** that);

// Free the memory used by a GSetIterBackward (not by its attached GSet)
// Do nothing if arguments are invalid
void GSetIterBackwardFree(GSetIterBackward** that);

// Clone a GSetIterForward
GSetIterForward* GSetIterForwardClone(GSetIterForward* that);

// Clone a GSetIterBackward
GSetIterBackward* GSetIterBackwardClone(GSetIterBackward* that);

// Reset the GSetIterForward to its starting position
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardReset(GSetIterForward* that);

// Reset the GSetIterBackward to its starting position
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardReset(GSetIterBackward* that);

// Step the GSetIterForward
// Return false if we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardStep(GSetIterForward* that);

// Step the GSetIterBackward
// Return false if we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardStep(GSetIterBackward* that);

// Apply a function to all elements of the GSet of the GSetIterForward
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardApply(GSetIterForward* that, 
  void(*fun)(void* data, void* param), void* param);

// Apply a function to all elements of the GSet of the GSetIterBackward
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardApply(GSetIterBackward* that, 
  void(*fun)(void* data, void* param), void* param);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardIsFirst(GSetIterForward* that);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardIsFirst(GSetIterBackward* that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardIsLast(GSetIterForward* that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardIsLast(GSetIterBackward* that);

// Change the attached set of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardSetGSet(GSetIterForward* that, GSet* set);

// Change the attached set of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardSetGSet(GSetIterBackward* that, GSet* set);

// Return the data currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* GSetIterForwardGet(GSetIterForward* that);

// Return the data currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* GSetIterBackwardGet(GSetIterBackward* that);

// Return the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetIterForwardGetElem(GSetIterForward* that);

// Return the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetIterBackwardGetElem(GSetIterBackward* that);

// Remove the element currently pointed to by the iterator
// The iterator is moved forward to the next element
// Return false if we couldn't move
// Return true else
// It's the responsibility of the user to delete the content of the 
// element prior to calling this function
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardRemoveElem(GSetIterForward* that);

// Remove the element currently pointed to by the iterator
// The iterator is moved backward to the next element
// Return false if we couldn't move
// Return true else
// It's the responsibility of the user to delete the content of the 
// element prior to calling this function
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardRemoveElem(GSetIterBackward* that);

// Move the 'iElem'-th element to the 'pos' index in the GSet
void GSetMoveElem(GSet* that, int iElem, int pos);

// ================ Inliner ====================

#if BUILDMODE != 0
#include "gset-inline.c"
#endif

#endif
