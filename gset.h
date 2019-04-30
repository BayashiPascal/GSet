// *************** GSET.H ***************
#ifndef GSET_H
#define GSET_H

// ================= Include ==================
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "pberr.h"
#include "pbcextension.h"

// ================= Define ==================

// Precision used when sorting a GSet
#define GSET_EPSILON 0.00001

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
  // Sorting in increasing value of _sortVal
  float _sortVal;
} GSetElem;

// Structure of the GSet
typedef struct GSet {
  // Pointer toward the element at the head of the GSet
  GSetElem* _head;
  // Pointer toward the last element of the GSet
  GSetElem* _tail;
  // Number of element in the GSet
  long _nbElem;
  // Index of the last got element
  long _indexLastGot;
  // Pointer to the last got element
  GSetElem* _lastGot;
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
GSet* GSetClone(const GSet* const that);

// Function to free the memory used by the GSet
void _GSetFree(GSet** s);

// Function to empty the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetFlush(GSet* const that);

// Return the number of element in the set
#if BUILDMODE != 0
inline
#endif 
long _GSetNbElem(const GSet* const that);

// Function to print a GSet
// Use the function 'printData' to print the data pointed to by 
// the elements, and print 'sep' between each element
// If printData is null, print the pointer value instead
void _GSetPrint(GSet* const that, FILE* const stream, 
  void(*printData)(const void* const data, FILE* const stream), 
  const char* const sep);

// Function to insert an element pointing toward 'data' at the 
// head of the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetPush(GSet* const that, void* const data);

// Function to insert an element pointing toward 'data' at the 
// position defined by 'v' sorting the set in increasing order
void _GSetAddSort(GSet* const that, void* const data, 
  const double v);

// Function to insert an element pointing toward 'data' at the 
// 'iElem'-th position 
// If 'iElem' is greater than or equal to the number of element
// in the GSet, elements pointing toward null data are added
// If the data is inserted inside the set, the current elements from
// the iElem-th elem are pushed 
void _GSetInsert(GSet* const that, void* const data, 
  const long iElem);

// Function to insert an element pointing toward 'data' at the 
// tail of the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetAppend(GSet* const that, void* const data);

// Function to remove the element at the head of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* _GSetPop(GSet* const that);

// Function to remove the element at the tail of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* _GSetDrop(GSet* const that);

// Function to remove the element at the 'iElem'-th position of the GSet
// Return the data pointed to by the removed element
#if BUILDMODE != 0
inline
#endif 
void* _GSetRemove(GSet* const that, const long iElem);

// Function to remove the element 'elem' of the GSet
// Return the data pointed to by the removed element
// The GSetElem is freed and *elem == NULL after calling this function
#if BUILDMODE != 0
inline
#endif 
void* _GSetRemoveElem(GSet* const that, GSetElem** elem);

// Function to remove the first element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveFirst(GSet* const that, const void* const data);

// Function to remove the last element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveLast(GSet* const that, const void* const data);

// Function to remove all the selement of the GSet pointing to 'data'
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveAll(GSet* const that, const void* const data);

// Function to get the data at the GSetElem
#if BUILDMODE != 0
inline
#endif 
void* GSetElemData(const GSetElem* const that);

// Function to get the data at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetGet(const GSet* const that, const long iElem);

// Function to get the data at the 'iElem'-th position of the GSet
// without removing it
// Fast version, move in the set from the last got element. The set must
// not have been modified since we've last got an element.
#if BUILDMODE != 0
inline
#endif 
void* _GSetGetJump(const GSet* const that, const long iElem);

// Function to get the data at first position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetHead(const GSet* const that);

// Function to get the data at last position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetTail(const GSet* const that);

// Function to get the GSetElem at first position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetHeadElem(const GSet* const that);

// Function to get the GSetElem at last position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetTailElem(const GSet* const that);

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetElement(const GSet* const that, const long iElem);

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
// Fast version, move in the set from the last got element. The set must
// not have been modified since we've last got an element.
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetElementJump(const GSet* const that, 
  const long iElem);
  
// Function to get the index of the first element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
long _GSetGetIndexFirst(const GSet* const that, const void* const data);

// Function to get the index of the last element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
long _GSetGetIndexLast(const GSet* const that, const void* const data);

// Function to get the first element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetFirstElem(const GSet* const that, 
  const void* const data);

// Function to get the last element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetLastElem(const GSet* const that, 
  const void* const data);

// Function to sort the element of the gset in increasing order of 
// _sortVal
void _GSetSort(GSet* const that);

// Merge the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
// After calling this function 'set' is empty 
#if BUILDMODE != 0
inline
#endif 
void _GSetMerge(GSet* const that, GSet* const set);

// Split the GSet at the GSetElem 'e'
// 'e' must be and element of the set
// the set new end is the element before 'e', the set becomes empty if 
// 'e' was the first element
// Return a new GSet starting with 'e', or NULL if 'e' is not 
// an element of the set
#if BUILDMODE != 0
inline
#endif 
GSet* _GSetSplit(GSet* const that, GSetElem* const e);

// Append the element of the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void _GSetAppendSet(GSet* const that, const GSet* const set);

// Append the element of the GSet 'that' at the end of the GSet 'set'
// Elements are kept sorted
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void _GSetAppendSortedSet(GSet* const that, const GSet* const set);

// Switch the 'iElem'-th and 'jElem'-th element of the set
#if BUILDMODE != 0
inline
#endif 
void _GSetSwitch(GSet* const that, const long iElem, const long jElem);

// Return the number of (GSetElem._data=='data') in the GSet 'that'
long _GSetCount(const GSet* const that, const void* const data);

// Set the sort value of the GSetElem 'that' to 'v'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetSortVal(GSetElem* const that, const float v);

// Set the data of the GSetElem 'that' to 'd'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetData(GSetElem* const that, void* const d);

// Set the previous element of the GSetElem 'that' to 'e'
// Do not set the link back in 'e'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetPrev(GSetElem* const that, GSetElem* const e);

// Set the next element of the GSetElem 'that' to 'e'
// Do not set the link back in 'e'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetNext(GSetElem* const that, GSetElem* const e);

// Move the 'iElem'-th element to the 'pos' index in the GSet
void _GSetMoveElem(GSet* const that, const long iElem, const long pos);

// Create a new GSetIterForward for the GSet 'set'
// The iterator is reset upon creation
GSetIterForward* _GSetIterForwardCreate(GSet* const set);
#if BUILDMODE != 0
inline
#endif 
GSetIterForward _GSetIterForwardCreateStatic(GSet* const set);

// Create a new GSetIterBackward for the GSet 'set'
// The iterator is reset upon creation
GSetIterBackward* _GSetIterBackwardCreate(GSet* const set);
#if BUILDMODE != 0
inline
#endif 
GSetIterBackward _GSetIterBackwardCreateStatic(GSet* const set);

// Free the memory used by a GSetIterForward (not by its attached GSet)
// Do nothing if arguments are invalid
void GSetIterForwardFree(GSetIterForward** that);

// Free the memory used by a GSetIterBackward (not by its attached GSet)
// Do nothing if arguments are invalid
void GSetIterBackwardFree(GSetIterBackward** that);

// Clone a GSetIterForward
GSetIterForward* GSetIterForwardClone(
  const GSetIterForward* const that);

// Clone a GSetIterBackward
GSetIterBackward* GSetIterBackwardClone(
  const GSetIterBackward* const that);

// Reset the GSetIterForward to its starting position
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardReset(GSetIterForward* const that);

// Reset the GSetIterBackward to its starting position
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardReset(GSetIterBackward* const that);

// Step the GSetIterForward
// Return false if we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardStep(GSetIterForward* const that);

// Step the GSetIterBackward
// Return false if we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardStep(GSetIterBackward* const that);

// Step back the GSetIterForward
// Return false if we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardStepBack(GSetIterForward* const that);

// Step back the GSetIterBackward
// Return false if we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardStepBack(GSetIterBackward* const that);

// Apply a function to all elements of the GSet of the GSetIterForward
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardApply(GSetIterForward* const that, 
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
void GSetIterBackwardApply(GSetIterBackward* const that, 
  void(*fun)(void* data, void* param), void* param);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardIsFirst(const GSetIterForward* const that);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardIsFirst(const GSetIterBackward* const that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardIsLast(const GSetIterForward* const that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardIsLast(const GSetIterBackward* const that);

// Change the attached set of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardSetGSet(GSetIterForward* const that, 
  GSet* const set);

// Change the attached set of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardSetGSet(GSetIterBackward* const that, 
  GSet* const set);

// Return the data currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* GSetIterForwardGet(const GSetIterForward* const that);

// Return the data currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* GSetIterBackwardGet(const GSetIterBackward* const that);

// Return the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetIterForwardGetElem(
  const GSetIterForward* const that);

// Return the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetIterBackwardGetElem(
  const GSetIterBackward* const that);

// Return the sort value of the element currently pointed to by the 
// iterator
#if BUILDMODE != 0
inline
#endif 
float GSetIterForwardGetSortVal(const GSetIterForward* const that);

// Return the sort value of the element currently pointed to by the 
// iterator
#if BUILDMODE != 0
inline
#endif 
float GSetIterBackwardGetSortVal(const GSetIterBackward* const that);

// Set the data of the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardSetData(const GSetIterForward* const that, 
  void* data);

// Set the data of the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardSetData(const GSetIterBackward* const that,
  void* data);

// Remove the element currently pointed to by the iterator
// The iterator is moved forward to the next element
// Return false if we couldn't move
// Return true else
// It's the responsibility of the user to delete the content of the 
// element prior to calling this function
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardRemoveElem(GSetIterForward* const that);

// Remove the element currently pointed to by the iterator
// The iterator is moved backward to the next element
// Return false if we couldn't move
// Return true else
// It's the responsibility of the user to delete the content of the 
// element prior to calling this function
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardRemoveElem(GSetIterBackward* const that);

// Return the sort value of GSetElem 'that'
#if BUILDMODE != 0
inline
#endif 
float GSetElemGetSortVal(const GSetElem* const that);

// Return the next element of GSetElem 'that'
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetElemNext(const GSetElem* const that);

// Return the previous element of GSetElem 'that'
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetElemPrev(const GSetElem* const that);

// Shuffle the GSet 'that'
// The random generator must have been initialized before calling 
// this function
// This function modifies the _sortVal of each elements in 'that'
// Use different algorithm according to the number of elements for
// speed performance
void GSetShuffle(GSet* const that);
void GSetShuffleA(GSet* const that);
void GSetShuffleB(GSet* const that);
void GSetShuffleC(GSet* const that);

// ================= Typed GSet ==================

#ifndef VecFloat
  typedef struct VecFloat VecFloat;
#endif
#ifndef VecFloat2D
  typedef struct VecFloat2D VecFloat2D;
#endif
#ifndef VecFloat3D
  typedef struct VecFloat3D VecFloat3D;
#endif
typedef struct GSetVecFloat {GSet _set;} GSetVecFloat;
#define GSetVecFloatCreate() ((GSetVecFloat*)GSetCreate())
inline GSetVecFloat GSetVecFloatCreateStatic(void) 
  {GSetVecFloat ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetVecFloat* GSetVecFloatClone(GSetVecFloat* const that)
  {return (GSetVecFloat*)GSetClone((GSet* const)that);}
inline VecFloat* _GSetVecFloatGet(const GSetVecFloat* const that, 
  const long iElem)
  {return (VecFloat*)_GSetGet((GSet* const)that, iElem);}
inline VecFloat* _GSetVecFloatGetJump(const GSetVecFloat* const that, 
  const long iElem)
  {return (VecFloat*)_GSetGetJump((GSet* const)that, iElem);}
inline VecFloat* _GSetVecFloatGetHead(const GSetVecFloat* const that)
  {return (VecFloat*)_GSetHead((const GSet* const)that);}
inline VecFloat* _GSetVecFloatGetTail(const GSetVecFloat* const that)
  {return (VecFloat*)_GSetTail((const GSet* const)that);}
inline VecFloat* _GSetVecFloatPop(GSetVecFloat* const that)
  {return (VecFloat*)_GSetPop((GSet* const)that);}
inline VecFloat* _GSetVecFloatDrop(GSetVecFloat* const that)
  {return (VecFloat*)_GSetDrop((GSet* const)that);}
inline VecFloat* _GSetVecFloatRemove(GSetVecFloat* const that, 
  const long iElem)
  {return (VecFloat*)_GSetRemove((GSet* const)that, iElem);}
inline VecFloat* _GSetVecFloatRemoveElem(GSetVecFloat* const that, 
  GSetElem** elem)
  {return (VecFloat*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef VecShort
  typedef struct VecShort VecShort;
#endif
#ifndef VecShort2D
  typedef struct VecShort2D VecShort2D;
#endif
#ifndef VecShort3D
  typedef struct VecShort3D VecShort3D;
#endif
#ifndef VecShort4D
  typedef struct VecShort4D VecShort4D;
#endif
typedef struct GSetVecShort {GSet _set;} GSetVecShort;
#define GSetVecShortCreate() ((GSetVecShort*)GSetCreate())
inline GSetVecShort GSetVecShortCreateStatic(void) 
  {GSetVecShort ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetVecShort* GSetVecShortClone(const GSetVecShort* const that)
  {return (GSetVecShort*)GSetClone((const GSet* const)that);}
inline VecShort* _GSetVecShortGet(const GSetVecShort* const that, 
  const long iElem)
  {return (VecShort*)_GSetGet((const GSet* const)that, iElem);}
inline VecShort* _GSetVecShortGetJump(const GSetVecShort* const that, 
  const long iElem)
  {return (VecShort*)_GSetGetJump((const GSet* const)that, iElem);}
inline VecShort* _GSetVecShortGetHead(const GSetVecShort* const that)
  {return (VecShort*)_GSetHead((const GSet* const)that);}
inline VecShort* _GSetVecShortGetTail(const GSetVecShort* const that)
  {return (VecShort*)_GSetTail((const GSet* const)that);}
inline VecShort* _GSetVecShortPop(GSetVecShort* const that)
  {return (VecShort*)_GSetPop((GSet* const)that);}
inline VecShort* _GSetVecShortDrop(GSetVecShort* const that)
  {return (VecShort*)_GSetDrop((GSet* const)that);}
inline VecShort* _GSetVecShortRemove(GSetVecShort* const that, 
  const long iElem)
  {return (VecShort*)_GSetRemove((GSet* const)that, iElem);}
inline VecShort* _GSetVecShortRemoveElem(GSetVecShort* const that, 
  GSetElem** elem)
  {return (VecShort*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef BCurve
  typedef struct BCurve BCurve;
#endif
typedef struct GSetBCurve {GSet _set;} GSetBCurve;
#define GSetBCurveCreate() ((GSetBCurve*)GSetCreate())
inline GSetBCurve GSetBCurveCreateStatic(void) 
  {GSetBCurve ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetBCurve* GSetBCurveClone(const GSetBCurve* const that)
  {return (GSetBCurve*)GSetClone((const GSet* const)that);}
inline BCurve* _GSetBCurveGet(const GSetBCurve* const that, 
  const long iElem)
  {return (BCurve*)_GSetGet((const GSet* const)that, iElem);}
inline BCurve* _GSetBCurveGetJump(const GSetBCurve* const that, 
  const long iElem)
  {return (BCurve*)_GSetGetJump((const GSet* const)that, iElem);}
inline BCurve* _GSetBCurveGetHead(const GSetBCurve* const that)
  {return (BCurve*)_GSetHead((const GSet* const)that);}
inline BCurve* _GSetBCurveGetTail(const GSetBCurve* const that)
  {return (BCurve*)_GSetTail((const GSet* const)that);}
inline BCurve* _GSetBCurvePop(GSetBCurve* const that)
  {return (BCurve*)_GSetPop((GSet* const)that);}
inline BCurve* _GSetBCurveDrop(GSetBCurve* const that)
  {return (BCurve*)_GSetDrop((GSet* const)that);}
inline BCurve* _GSetBCurveRemove(GSetBCurve* const that, const long iElem)
  {return (BCurve*)_GSetRemove((GSet* const)that, iElem);}
inline BCurve* _GSetBCurveRemoveElem(GSetBCurve* const that, 
  GSetElem** elem)
  {return (BCurve*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef SCurve
  typedef struct SCurve SCurve;
#endif
typedef struct GSetSCurve {GSet _set;} GSetSCurve;
#define GSetSCurveCreate() ((GSetSCurve*)GSetCreate())
inline GSetSCurve GSetSCurveCreateStatic(void) 
  {GSetSCurve ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetSCurve* GSetSCurveClone(const GSetSCurve* const that)
  {return (GSetSCurve*)GSetClone((const GSet* const)that);}
inline SCurve* _GSetSCurveGet(const GSetSCurve* const that, 
  const long iElem)
  {return (SCurve*)_GSetGet((const GSet* const)that, iElem);}
inline SCurve* _GSetSCurveGetJump(const GSetSCurve* const that, 
  const long iElem)
  {return (SCurve*)_GSetGetJump((const GSet* const)that, iElem);}
inline SCurve* _GSetSCurveGetHead(const GSetSCurve* const that)
  {return (SCurve*)_GSetHead((const GSet* const)that);}
inline SCurve* _GSetSCurveGetTail(const GSetSCurve* const that)
  {return (SCurve*)_GSetTail((const GSet* const)that);}
inline SCurve* _GSetSCurvePop(GSetSCurve* const that)
  {return (SCurve*)_GSetPop((GSet* const)that);}
inline SCurve* _GSetSCurveDrop(GSetSCurve* const that)
  {return (SCurve*)_GSetDrop((GSet* const)that);}
inline SCurve* _GSetSCurveRemove(GSetSCurve* const that, 
  const long iElem)
  {return (SCurve*)_GSetRemove((GSet* const)that, iElem);}
inline SCurve* _GSetSCurveRemoveElem(GSetSCurve* const that, 
  GSetElem** elem)
  {return (SCurve*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef Shapoid
  typedef struct Shapoid Shapoid;
#endif
#ifndef Facoid
  typedef struct Facoid Facoid;
#endif
#ifndef Spheroid
  typedef struct Spheroid Spheroid;
#endif
#ifndef Pyramidoid
  typedef struct Pyramidoid Pyramidoid;
#endif
typedef struct GSetShapoid {GSet _set;} GSetShapoid;
#define GSetShapoidCreate() ((GSetShapoid*)GSetCreate())
inline GSetShapoid GSetShapoidCreateStatic(void) 
  {GSetShapoid ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetShapoid* GSetShapoidClone(const GSetShapoid* const that)
  {return (GSetShapoid*)GSetClone((const GSet* const)that);}
inline Shapoid* _GSetShapoidGet(const GSetShapoid* const that, 
  const long iElem)
  {return (Shapoid*)_GSetGet((const GSet* const)that, iElem);}
inline Shapoid* _GSetShapoidGetJump(const GSetShapoid* const that, 
  const long iElem)
  {return (Shapoid*)_GSetGetJump((const GSet* const)that, iElem);}
inline Shapoid* _GSetShapoidGetHead(const GSetShapoid* const that)
  {return (Shapoid*)_GSetHead((const GSet* const)that);}
inline Shapoid* _GSetShapoidGetTail(const GSetShapoid* const that)
  {return (Shapoid*)_GSetTail((const GSet* const)that);}
inline Shapoid* _GSetShapoidPop(GSetShapoid* const that)
  {return (Shapoid*)_GSetPop((GSet* const)that);}
inline Shapoid* _GSetShapoidDrop(GSetShapoid* const that)
  {return (Shapoid*)_GSetDrop((GSet* const)that);}
inline Shapoid* _GSetShapoidRemove(GSetShapoid* const that, 
  const long iElem)
  {return (Shapoid*)_GSetRemove((GSet* const)that, iElem);}
inline Shapoid* _GSetShapoidRemoveElem(GSetShapoid* const that, 
  GSetElem** elem)
  {return (Shapoid*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef KnapSackPod
  typedef struct KnapSackPod KnapSackPod;
#endif
typedef struct GSetKnapSackPod {GSet _set;} GSetKnapSackPod;
#define GSetKnapSackPodCreate() ((GSetKnapSackPod*)GSetCreate())
inline GSetKnapSackPod GSetKnapSackPodCreateStatic(void) 
  {GSetKnapSackPod ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetKnapSackPod* GSetKnapSackPodClone(
  const GSetKnapSackPod* const that)
  {return (GSetKnapSackPod*)GSetClone((const GSet* const)that);}
inline KnapSackPod* _GSetKnapSackPodGet(
  const GSetKnapSackPod* const that, const long iElem)
  {return (KnapSackPod*)_GSetGet((const GSet* const)that, iElem);}
inline KnapSackPod* _GSetKnapSackPodGetJump(
  const GSetKnapSackPod* const that, const long iElem)
  {return (KnapSackPod*)_GSetGetJump((const GSet* const)that, iElem);}
inline KnapSackPod* _GSetKnapSackPodGetHead(
  const GSetKnapSackPod* const that)
  {return (KnapSackPod*)_GSetHead((const GSet* const)that);}
inline KnapSackPod* _GSetKnapSackPodGetTail(
  const GSetKnapSackPod* const that)
  {return (KnapSackPod*)_GSetTail((const GSet* const)that);}
inline KnapSackPod* _GSetKnapSackPodPop(GSetKnapSackPod* const that)
  {return (KnapSackPod*)_GSetPop((GSet* const)that);}
inline KnapSackPod* _GSetKnapSackPodDrop(GSetKnapSackPod* const that)
  {return (KnapSackPod*)_GSetDrop((GSet* const)that);}
inline KnapSackPod* _GSetKnapSackPodRemove(
  GSetKnapSackPod* that, const long iElem)
  {return (KnapSackPod*)_GSetRemove((GSet* const)that, iElem);}
inline KnapSackPod* _GSetKnapSackPodRemoveElem(
  GSetKnapSackPod* const that, GSetElem** elem)
  {return (KnapSackPod*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef PBPhysParticle
  typedef struct PBPhysParticle PBPhysParticle;
#endif
typedef struct GSetPBPhysParticle {GSet _set;} GSetPBPhysParticle;
#define GSetPBPhysParticleCreate() ((GSetPBPhysParticle*)GSetCreate())
inline GSetPBPhysParticle GSetPBPhysParticleCreateStatic(void) 
  {GSetPBPhysParticle ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetPBPhysParticle* GSetPBPhysParticleClone(
  const GSetPBPhysParticle* const that)
  {return (GSetPBPhysParticle*)GSetClone((const GSet* const)that);}
inline PBPhysParticle* _GSetPBPhysParticleGet(
  const GSetPBPhysParticle* const that, const long iElem)
  {return (PBPhysParticle*)_GSetGet((const GSet* const)that, iElem);}
inline PBPhysParticle* _GSetPBPhysParticleGetJump(
  const GSetPBPhysParticle* const that, const long iElem)
  {return (PBPhysParticle*)_GSetGetJump((const GSet* const)that, iElem);}
inline PBPhysParticle* _GSetPBPhysParticleGetHead(
  const GSetPBPhysParticle* const that)
  {return (PBPhysParticle*)_GSetHead((const GSet* const)that);}
inline PBPhysParticle* _GSetPBPhysParticleGetTail(
  const GSetPBPhysParticle* const that)
  {return (PBPhysParticle*)_GSetTail((const GSet* const)that);}
inline PBPhysParticle* _GSetPBPhysParticlePop(
  GSetPBPhysParticle* const that)
  {return (PBPhysParticle*)_GSetPop((GSet* const)that);}
inline PBPhysParticle* _GSetPBPhysParticleDrop(
  GSetPBPhysParticle* const that)
  {return (PBPhysParticle*)_GSetDrop((GSet* const)that);}
inline PBPhysParticle* _GSetPBPhysParticleRemove(
  GSetPBPhysParticle* const that, const long iElem)
  {return (PBPhysParticle*)_GSetRemove((GSet* const)that, iElem);}
inline PBPhysParticle* _GSetPBPhysParticleRemoveElem(
  GSetPBPhysParticle* const that, GSetElem** elem)
  {return (PBPhysParticle*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef GenTree
  typedef struct GenTree GenTree;
#endif
typedef struct GSetGenTree {GSet _set;} GSetGenTree;
#define GSetGenTreeCreate() ((GSetGenTree*)GSetCreate())
inline GSetGenTree GSetGenTreeCreateStatic(void) 
  {GSetGenTree ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetGenTree* GSetGenTreeClone(const GSetGenTree* const that)
  {return (GSetGenTree*)GSetClone((const GSet* const)that);}
inline GenTree* _GSetGenTreeGet(const GSetGenTree* const that, const long iElem)
  {return (GenTree*)_GSetGet((const GSet* const)that, iElem);}
inline GenTree* _GSetGenTreeGetJump(const GSetGenTree* const that, const long iElem)
  {return (GenTree*)_GSetGetJump((const GSet* const)that, iElem);}
inline GenTree* _GSetGenTreeGetHead(const GSetGenTree* const that)
  {return (GenTree*)_GSetHead((const GSet* const)that);}
inline GenTree* _GSetGenTreeGetTail(const GSetGenTree* const that)
  {return (GenTree*)_GSetTail((const GSet* const)that);}
inline GenTree* _GSetGenTreePop(GSetGenTree* const that)
  {return (GenTree*)_GSetPop((GSet* const)that);}
inline GenTree* _GSetGenTreeDrop(GSetGenTree* const that)
  {return (GenTree*)_GSetDrop((GSet* const)that);}
inline GenTree* _GSetGenTreeRemove(GSetGenTree* const that, const long iElem)
  {return (GenTree*)_GSetRemove((GSet* const)that, iElem);}
inline GenTree* _GSetGenTreeRemoveElem(GSetGenTree* const that, 
  GSetElem** elem)
  {return (GenTree*)_GSetRemoveElem((GSet* const)that, elem);}

typedef struct GSetStr {GSet _set;} GSetStr;
#define GSetStrCreate() ((GSetStr*)GSetCreate())
inline GSetStr GSetStrCreateStatic(void) 
  {GSetStr ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetStr* GSetStrClone(const GSetStr* const that)
  {return (GSetStr*)GSetClone((const GSet* const)that);}
inline char* _GSetStrGet(const GSetStr* const that, const long iElem)
  {return (char*)_GSetGet((const GSet* const)that, iElem);}
inline char* _GSetStrGetJump(const GSetStr* const that, const long iElem)
  {return (char*)_GSetGetJump((const GSet* const)that, iElem);}
inline char* _GSetStrGetHead(const GSetStr* const that)
  {return (char*)_GSetHead((const GSet* const)that);}
inline char* _GSetStrGetTail(const GSetStr* const that)
  {return (char*)_GSetTail((const GSet* const)that);}
inline char* _GSetStrPop(GSetStr* const that)
  {return (char*)_GSetPop((GSet* const)that);}
inline char* _GSetStrDrop(GSetStr* const that)
  {return (char*)_GSetDrop((GSet* const)that);}
inline char* _GSetStrRemove(GSetStr* const that, const long iElem)
  {return (char*)_GSetRemove((GSet* const)that, iElem);}
inline char* _GSetStrRemoveElem(GSetStr* const that, GSetElem** elem)
  {return (char*)_GSetRemoveElem((GSet* const)that, elem);}

#ifndef GenTreeStr
  typedef struct GenTreeStr GenTreeStr;
#endif
typedef struct GSetGenTreeStr {GSet _set;} GSetGenTreeStr;
#define GSetGenTreeStrCreate() ((GSetGenTreeStr*)GSetCreate())
inline GSetGenTreeStr GSetGenTreeStrCreateStatic(void) 
  {GSetGenTreeStr ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetGenTreeStr* GSetGenTreeStrClone(const GSetGenTreeStr* const that)
  {return (GSetGenTreeStr*)GSetClone((const GSet* const)that);}
inline GenTreeStr* _GSetGenTreeStrGet(const GSetGenTreeStr* const that, 
  const long iElem)
  {return (GenTreeStr*)_GSetGet((const GSet* const)that, iElem);}
inline GenTreeStr* _GSetGenTreeStrGetJump(
  const GSetGenTreeStr* const that, const long iElem)
  {return (GenTreeStr*)_GSetGetJump((const GSet* const)that, iElem);}
inline GenTreeStr* _GSetGenTreeStrGetHead(const GSetGenTreeStr* const that)
  {return (GenTreeStr*)_GSetHead((const GSet* const)that);}
inline GenTreeStr* _GSetGenTreeStrGetTail(const GSetGenTreeStr* const that)
  {return (GenTreeStr*)_GSetTail((const GSet* const)that);}
inline GenTreeStr* _GSetGenTreeStrPop(GSetGenTreeStr* const that)
  {return (GenTreeStr*)_GSetPop((GSet* const)that);}
inline GenTreeStr* _GSetGenTreeStrDrop(GSetGenTreeStr* const that)
  {return (GenTreeStr*)_GSetDrop((GSet* const)that);}
inline GenTreeStr* _GSetGenTreeStrRemove(GSetGenTreeStr* const that, 
  const long iElem)
  {return (GenTreeStr*)_GSetRemove((GSet* const)that, iElem);}
inline GenTreeStr* _GSetGenTreeStrRemoveElem(
  GSetGenTreeStr* const that, GSetElem** elem)
  {return (GenTreeStr*)_GSetRemoveElem((GSet* const)that, elem);}

// ================= Generic functions ==================

#define GSetFree(Set) _Generic(Set, \
  GSet**: _GSetFree, \
  GSetVecFloat**: _GSetFree, \
  GSetVecShort**: _GSetFree, \
  GSetBCurve**: _GSetFree, \
  GSetSCurve**: _GSetFree, \
  GSetShapoid**: _GSetFree, \
  GSetKnapSackPod**: _GSetFree, \
  GSetPBPhysParticle**: _GSetFree, \
  GSetGenTree**: _GSetFree, \
  GSetStr**: _GSetFree, \
  GSetGenTreeStr**: _GSetFree, \
  default: PBErrInvalidPolymorphism)((GSet**)(Set))

#define GSetPush(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetPush), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetPush, \
    VecFloat2D*: _GSetPush, \
    VecFloat3D*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetPush, \
    VecShort2D*: _GSetPush, \
    VecShort3D*: _GSetPush, \
    VecShort4D*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetPush, \
    Facoid*: _GSetPush, \
    Pyramidoid*: _GSetPush, \
    Spheroid*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetPush, \
    const KnapSackPod*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetPush, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetAddSort(Set, Data, Value) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetAddSort), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetAddSort, \
    VecFloat2D*: _GSetAddSort, \
    VecFloat3D*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetAddSort, \
    VecShort2D*: _GSetAddSort, \
    VecShort3D*: _GSetAddSort, \
    VecShort4D*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetAddSort, \
    Facoid*: _GSetAddSort, \
    Pyramidoid*: _GSetAddSort, \
    Spheroid*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetAddSort, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data), Value)

#define GSetInsert(Set, Data, Pos) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetInsert), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetInsert, \
    VecFloat2D*: _GSetInsert, \
    VecFloat3D*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetInsert, \
    VecShort2D*: _GSetInsert, \
    VecShort3D*: _GSetInsert, \
    VecShort4D*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetInsert, \
    Facoid*: _GSetInsert, \
    Pyramidoid*: _GSetInsert, \
    Spheroid*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetInsert, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data), Pos)

#define GSetAppend(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetAppend), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetAppend, \
    VecFloat2D*: _GSetAppend, \
    VecFloat3D*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetAppend, \
    VecShort2D*: _GSetAppend, \
    VecShort3D*: _GSetAppend, \
    VecShort4D*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetAppend, \
    Facoid*: _GSetAppend, \
    Pyramidoid*: _GSetAppend, \
    Spheroid*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetAppend, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetRemoveFirst(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetRemoveFirst), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetRemoveFirst, \
    VecFloat2D*: _GSetRemoveFirst, \
    VecFloat3D*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetRemoveFirst, \
    VecShort2D*: _GSetRemoveFirst, \
    VecShort3D*: _GSetRemoveFirst, \
    VecShort4D*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetRemoveFirst, \
    Facoid*: _GSetRemoveFirst, \
    Pyramidoid*: _GSetRemoveFirst, \
    Spheroid*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetRemoveFirst, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetRemoveLast(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetRemoveLast), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetRemoveLast, \
    VecFloat2D*: _GSetRemoveLast, \
    VecFloat3D*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetRemoveLast, \
    VecShort2D*: _GSetRemoveLast, \
    VecShort3D*: _GSetRemoveLast, \
    VecShort4D*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetRemoveLast, \
    Facoid*: _GSetRemoveLast, \
    Pyramidoid*: _GSetRemoveLast, \
    Spheroid*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetRemoveLast, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetRemoveAll(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetRemoveAll), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetRemoveAll, \
    VecFloat2D*: _GSetRemoveAll, \
    VecFloat3D*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetRemoveAll, \
    VecShort2D*: _GSetRemoveAll, \
    VecShort3D*: _GSetRemoveAll, \
    VecShort4D*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetRemoveAll, \
    Facoid*: _GSetRemoveAll, \
    Pyramidoid*: _GSetRemoveAll, \
    Spheroid*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetRemoveAll, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetGetIndexFirst(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetGetIndexFirst), \
  const GSet*: _Generic(Data, \
    default: _GSetGetIndexFirst), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetGetIndexFirst, \
    VecFloat2D*: _GSetGetIndexFirst, \
    VecFloat3D*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetGetIndexFirst, \
    VecFloat2D*: _GSetGetIndexFirst, \
    VecFloat3D*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetGetIndexFirst, \
    VecShort2D*: _GSetGetIndexFirst, \
    VecShort3D*: _GSetGetIndexFirst, \
    VecShort4D*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetGetIndexFirst, \
    VecShort2D*: _GSetGetIndexFirst, \
    VecShort3D*: _GSetGetIndexFirst, \
    VecShort4D*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetIndexFirst, \
    Facoid*: _GSetGetIndexFirst, \
    Pyramidoid*: _GSetGetIndexFirst, \
    Spheroid*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetIndexFirst, \
    Facoid*: _GSetGetIndexFirst, \
    Pyramidoid*: _GSetGetIndexFirst, \
    Spheroid*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetStr*: _Generic(Data, \
    char*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetGetIndexLast(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetGetIndexLast), \
  const GSet*: _Generic(Data, \
    default: _GSetGetIndexLast), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetGetIndexLast, \
    VecFloat2D*: _GSetGetIndexLast, \
    VecFloat3D*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetGetIndexLast, \
    VecFloat2D*: _GSetGetIndexLast, \
    VecFloat3D*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetGetIndexLast, \
    VecShort2D*: _GSetGetIndexLast, \
    VecShort3D*: _GSetGetIndexLast, \
    VecShort4D*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetGetIndexLast, \
    VecShort2D*: _GSetGetIndexLast, \
    VecShort3D*: _GSetGetIndexLast, \
    VecShort4D*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetIndexLast, \
    Facoid*: _GSetGetIndexLast, \
    Pyramidoid*: _GSetGetIndexLast, \
    Spheroid*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetIndexLast, \
    Facoid*: _GSetGetIndexLast, \
    Pyramidoid*: _GSetGetIndexLast, \
    Spheroid*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetStr*: _Generic(Data, \
    char*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetFirstElem(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetFirstElem), \
  const GSet*: _Generic(Data, \
    default: _GSetFirstElem), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetFirstElem, \
    VecFloat2D*: _GSetFirstElem, \
    VecFloat3D*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetFirstElem, \
    VecFloat2D*: _GSetFirstElem, \
    VecFloat3D*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetFirstElem, \
    VecShort2D*: _GSetFirstElem, \
    VecShort3D*: _GSetFirstElem, \
    VecShort4D*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetFirstElem, \
    VecShort2D*: _GSetFirstElem, \
    VecShort3D*: _GSetFirstElem, \
    VecShort4D*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetFirstElem, \
    Facoid*: _GSetFirstElem, \
    Pyramidoid*: _GSetFirstElem, \
    Spheroid*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetFirstElem, \
    Facoid*: _GSetFirstElem, \
    Pyramidoid*: _GSetFirstElem, \
    Spheroid*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetStr*: _Generic(Data, \
    char*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetLastElem(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetLastElem), \
  const GSet*: _Generic(Data, \
    default: _GSetLastElem), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetLastElem, \
    VecFloat2D*: _GSetLastElem, \
    VecFloat3D*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetLastElem, \
    VecFloat2D*: _GSetLastElem, \
    VecFloat3D*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetLastElem, \
    VecShort2D*: _GSetLastElem, \
    VecShort3D*: _GSetLastElem, \
    VecShort4D*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetLastElem, \
    VecShort2D*: _GSetLastElem, \
    VecShort3D*: _GSetLastElem, \
    VecShort4D*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetLastElem, \
    Facoid*: _GSetLastElem, \
    Pyramidoid*: _GSetLastElem, \
    Spheroid*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetLastElem, \
    Facoid*: _GSetLastElem, \
    Pyramidoid*: _GSetLastElem, \
    Spheroid*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTree*: _Generic(Data, \
    GenTree*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(Data, \
    char*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetStr*: _Generic(Data, \
    char*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  const GSetGenTreeStr*: _Generic(Data, \
    GenTreeStr*: _GSetLastElem, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetPrint(Set, Stream, Fun, Sep) _Generic(Set, \
  GSet*: _GSetPrint, \
  const GSet*: _GSetPrint, \
  GSetVecFloat*: _GSetPrint, \
  const GSetVecFloat*: _GSetPrint, \
  GSetVecShort*: _GSetPrint, \
  const GSetVecShort*: _GSetPrint, \
  GSetBCurve*: _GSetPrint, \
  const GSetBCurve*: _GSetPrint, \
  GSetSCurve*: _GSetPrint, \
  const GSetSCurve*: _GSetPrint, \
  GSetShapoid*: _GSetPrint, \
  const GSetShapoid*: _GSetPrint, \
  GSetKnapSackPod*: _GSetPrint, \
  const GSetKnapSackPod*: _GSetPrint, \
  GSetPBPhysParticle*: _GSetPrint, \
  const GSetPBPhysParticle*: _GSetPrint, \
  GSetGenTree*: _GSetPrint, \
  const GSetGenTree*: _GSetPrint, \
  GSetStr*: _GSetPrint, \
  const GSetStr*: _GSetPrint, \
  GSetGenTreeStr*: _GSetPrint, \
  const GSetGenTreeStr*: _GSetPrint, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Stream, Fun, Sep)

#define GSetFlush(Set) _Generic(Set, \
  GSet*: _GSetFlush, \
  GSetVecFloat*: _GSetFlush, \
  GSetVecShort*: _GSetFlush, \
  GSetBCurve*: _GSetFlush, \
  GSetSCurve*: _GSetFlush, \
  GSetShapoid*: _GSetFlush, \
  GSetKnapSackPod*: _GSetFlush, \
  GSetPBPhysParticle*: _GSetFlush, \
  GSetGenTree*: _GSetFlush, \
  GSetStr*: _GSetFlush, \
  GSetGenTreeStr*: _GSetFlush, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))

#define GSetNbElem(Set) _Generic(Set, \
  GSet*: _GSetNbElem, \
  const GSet*: _GSetNbElem, \
  GSetVecFloat*: _GSetNbElem, \
  const GSetVecFloat*: _GSetNbElem, \
  GSetVecShort*: _GSetNbElem, \
  const GSetVecShort*: _GSetNbElem, \
  GSetBCurve*: _GSetNbElem, \
  const GSetBCurve*: _GSetNbElem, \
  GSetSCurve*: _GSetNbElem, \
  const GSetSCurve*: _GSetNbElem, \
  GSetShapoid*: _GSetNbElem, \
  const GSetShapoid*: _GSetNbElem, \
  GSetKnapSackPod*: _GSetNbElem, \
  const GSetKnapSackPod*: _GSetNbElem, \
  GSetPBPhysParticle*: _GSetNbElem, \
  const GSetPBPhysParticle*: _GSetNbElem, \
  GSetGenTree*: _GSetNbElem, \
  const GSetGenTree*: _GSetNbElem, \
  GSetStr*: _GSetNbElem, \
  const GSetStr*: _GSetNbElem, \
  GSetGenTreeStr*: _GSetNbElem, \
  const GSetGenTreeStr*: _GSetNbElem, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))

#define GSetPop(Set) _Generic(Set, \
  GSet*: _GSetPop, \
  GSetVecFloat*: _GSetVecFloatPop, \
  GSetVecShort*: _GSetVecShortPop, \
  GSetBCurve*: _GSetBCurvePop, \
  GSetSCurve*: _GSetSCurvePop, \
  GSetShapoid*: _GSetShapoidPop, \
  GSetKnapSackPod*: _GSetKnapSackPodPop, \
  GSetPBPhysParticle*: _GSetPBPhysParticlePop, \
  GSetGenTree*: _GSetGenTreePop, \
  GSetStr*: _GSetStrPop, \
  GSetGenTreeStr*: _GSetGenTreeStrPop, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetDrop(Set) _Generic(Set, \
  GSet*: _GSetDrop, \
  GSetVecFloat*: _GSetVecFloatDrop, \
  GSetVecShort*: _GSetVecShortDrop, \
  GSetBCurve*: _GSetBCurveDrop, \
  GSetSCurve*: _GSetSCurveDrop, \
  GSetShapoid*: _GSetShapoidDrop, \
  GSetKnapSackPod*: _GSetKnapSackPodDrop, \
  GSetPBPhysParticle*: _GSetPBPhysParticleDrop, \
  GSetGenTree*: _GSetGenTreeDrop, \
  GSetStr*: _GSetStrDrop, \
  GSetGenTreeStr*: _GSetGenTreeStrDrop, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetRemove(Set, Pos) _Generic(Set, \
  GSet*: _GSetRemove, \
  GSetVecFloat*: _GSetVecFloatRemove, \
  GSetVecShort*: _GSetVecShortRemove, \
  GSetBCurve*: _GSetBCurveRemove, \
  GSetSCurve*: _GSetSCurveRemove, \
  GSetShapoid*: _GSetShapoidRemove, \
  GSetKnapSackPod*: _GSetKnapSackPodRemove, \
  GSetPBPhysParticle*: _GSetPBPhysParticleRemove, \
  GSetGenTree*: _GSetGenTreeRemove, \
  GSetStr*: _GSetStrRemove, \
  GSetGenTreeStr*: _GSetGenTreeStrRemove, \
  default: PBErrInvalidPolymorphism)(Set, Pos)

#define GSetRemoveElem(Set, Elem) _Generic(Set, \
  GSet*: _GSetRemoveElem, \
  GSetVecFloat*: _GSetVecFloatRemoveElem, \
  GSetVecShort*: _GSetVecShortRemoveElem, \
  GSetBCurve*: _GSetBCurveRemoveElem, \
  GSetSCurve*: _GSetSCurveRemoveElem, \
  GSetShapoid*: _GSetShapoidRemoveElem, \
  GSetKnapSackPod*: _GSetKnapSackPodRemoveElem, \
  GSetPBPhysParticle*: _GSetPBPhysParticleRemoveElem, \
  GSetGenTree*: _GSetGenTreeRemoveElem, \
  GSetStr*: _GSetStrRemoveElem, \
  GSetGenTreeStr*: _GSetGenTreeStrRemoveElem, \
  default: PBErrInvalidPolymorphism)(Set, Elem)

#define GSetGet(Set, Pos) _Generic(Set, \
  GSet*: _GSetGet, \
  const GSet*: _GSetGet, \
  GSetVecFloat*: _GSetVecFloatGet, \
  const GSetVecFloat*: _GSetVecFloatGet, \
  GSetVecShort*: _GSetVecShortGet, \
  const GSetVecShort*: _GSetVecShortGet, \
  GSetBCurve*: _GSetBCurveGet, \
  const GSetBCurve*: _GSetBCurveGet, \
  GSetSCurve*: _GSetSCurveGet, \
  const GSetSCurve*: _GSetSCurveGet, \
  GSetShapoid*: _GSetShapoidGet, \
  const GSetShapoid*: _GSetShapoidGet, \
  GSetKnapSackPod*: _GSetKnapSackPodGet, \
  const GSetKnapSackPod*: _GSetKnapSackPodGet, \
  GSetPBPhysParticle*: _GSetPBPhysParticleGet, \
  const GSetPBPhysParticle*: _GSetPBPhysParticleGet, \
  GSetGenTree*: _GSetGenTreeGet, \
  const GSetGenTree*: _GSetGenTreeGet, \
  GSetStr*: _GSetStrGet, \
  const GSetStr*: _GSetStrGet, \
  GSetGenTreeStr*: _GSetGenTreeStrGet, \
  const GSetGenTreeStr*: _GSetGenTreeStrGet, \
  default: PBErrInvalidPolymorphism)(Set, Pos)

#define GSetGetJump(Set, Pos) _Generic(Set, \
  GSet*: _GSetGetJump, \
  const GSet*: _GSetGetJump, \
  GSetVecFloat*: _GSetVecFloatGetJump, \
  const GSetVecFloat*: _GSetVecFloatGetJump, \
  GSetVecShort*: _GSetVecShortGetJump, \
  const GSetVecShort*: _GSetVecShortGetJump, \
  GSetBCurve*: _GSetBCurveGetJump, \
  const GSetBCurve*: _GSetBCurveGetJump, \
  GSetSCurve*: _GSetSCurveGetJump, \
  const GSetSCurve*: _GSetSCurveGetJump, \
  GSetShapoid*: _GSetShapoidGetJump, \
  const GSetShapoid*: _GSetShapoidGetJump, \
  GSetKnapSackPod*: _GSetKnapSackPodGetJump, \
  const GSetKnapSackPod*: _GSetKnapSackPodGetJump, \
  GSetPBPhysParticle*: _GSetPBPhysParticleGetJump, \
  const GSetPBPhysParticle*: _GSetPBPhysParticleGetJump, \
  GSetGenTree*: _GSetGenTreeGetJump, \
  const GSetGenTree*: _GSetGenTreeGetJump, \
  GSetStr*: _GSetStrGetJump, \
  const GSetStr*: _GSetStrGetJump, \
  GSetGenTreeStr*: _GSetGenTreeStrGetJump, \
  const GSetGenTreeStr*: _GSetGenTreeStrGetJump, \
  default: PBErrInvalidPolymorphism)(Set, Pos)

#define GSetHead(Set) _Generic(Set, \
  GSet*: _GSetHead, \
  const GSet*: _GSetHead, \
  GSetVecFloat*: _GSetVecFloatGetHead, \
  const GSetVecFloat*: _GSetVecFloatGetHead, \
  GSetVecShort*: _GSetVecShortGetHead, \
  const GSetVecShort*: _GSetVecShortGetHead, \
  GSetBCurve*: _GSetBCurveGetHead, \
  const GSetBCurve*: _GSetBCurveGetHead, \
  GSetSCurve*: _GSetSCurveGetHead, \
  const GSetSCurve*: _GSetSCurveGetHead, \
  GSetShapoid*: _GSetShapoidGetHead, \
  const GSetShapoid*: _GSetShapoidGetHead, \
  GSetKnapSackPod*: _GSetKnapSackPodGetHead, \
  const GSetKnapSackPod*: _GSetKnapSackPodGetHead, \
  GSetPBPhysParticle*: _GSetPBPhysParticleGetHead, \
  const GSetPBPhysParticle*: _GSetPBPhysParticleGetHead, \
  GSetGenTree*: _GSetGenTreeGetHead, \
  const GSetGenTree*: _GSetGenTreeGetHead, \
  GSetStr*: _GSetStrGetHead, \
  const GSetStr*: _GSetStrGetHead, \
  GSetGenTreeStr*: _GSetGenTreeStrGetHead, \
  const GSetGenTreeStr*: _GSetGenTreeStrGetHead, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetTail(Set) _Generic(Set, \
  GSet*: _GSetTail, \
  const GSet*: _GSetTail, \
  GSetVecFloat*: _GSetVecFloatGetTail, \
  const GSetVecFloat*: _GSetVecFloatGetTail, \
  GSetVecShort*: _GSetVecShortGetTail, \
  const GSetVecShort*: _GSetVecShortGetTail, \
  GSetBCurve*: _GSetBCurveGetTail, \
  const GSetBCurve*: _GSetBCurveGetTail, \
  GSetSCurve*: _GSetSCurveGetTail, \
  const GSetSCurve*: _GSetSCurveGetTail, \
  GSetShapoid*: _GSetShapoidGetTail, \
  const GSetShapoid*: _GSetShapoidGetTail, \
  GSetKnapSackPod*: _GSetKnapSackPodGetTail, \
  const GSetKnapSackPod*: _GSetKnapSackPodGetTail, \
  GSetPBPhysParticle*: _GSetPBPhysParticleGetTail, \
  const GSetPBPhysParticle*: _GSetPBPhysParticleGetTail, \
  GSetGenTree*: _GSetGenTreeGetTail, \
  const GSetGenTree*: _GSetGenTreeGetTail, \
  GSetStr*: _GSetStrGetTail, \
  const GSetStr*: _GSetStrGetTail, \
  GSetGenTreeStr*: _GSetGenTreeStrGetTail, \
  const GSetGenTreeStr*: _GSetGenTreeStrGetTail, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetHeadElem(Set) _Generic(Set, \
  GSet*: _GSetHeadElem, \
  const GSet*: _GSetHeadElem, \
  GSetVecFloat*: _GSetHeadElem, \
  const GSetVecFloat*: _GSetHeadElem, \
  GSetVecShort*: _GSetHeadElem, \
  const GSetVecShort*: _GSetHeadElem, \
  GSetBCurve*: _GSetHeadElem, \
  const GSetBCurve*: _GSetHeadElem, \
  GSetSCurve*: _GSetHeadElem, \
  const GSetSCurve*: _GSetHeadElem, \
  GSetShapoid*: _GSetHeadElem, \
  const GSetShapoid*: _GSetHeadElem, \
  GSetKnapSackPod*: _GSetHeadElem, \
  const GSetKnapSackPod*: _GSetHeadElem, \
  GSetPBPhysParticle*: _GSetHeadElem, \
  const GSetPBPhysParticle*: _GSetHeadElem, \
  GSetGenTree*: _GSetHeadElem, \
  const GSetGenTree*: _GSetHeadElem, \
  GSetStr*: _GSetHeadElem, \
  const GSetStr*: _GSetHeadElem, \
  GSetGenTreeStr*: _GSetHeadElem, \
  const GSetGenTreeStr*: _GSetHeadElem, \
  default: PBErrInvalidPolymorphism)((const GSet*)Set)

#define GSetTailElem(Set) _Generic(Set, \
  GSet*: _GSetTailElem, \
  const GSet*: _GSetTailElem, \
  GSetVecFloat*: _GSetTailElem, \
  const GSetVecFloat*: _GSetTailElem, \
  GSetVecShort*: _GSetTailElem, \
  const GSetVecShort*: _GSetTailElem, \
  GSetBCurve*: _GSetTailElem, \
  const GSetBCurve*: _GSetTailElem, \
  GSetSCurve*: _GSetTailElem, \
  const GSetSCurve*: _GSetTailElem, \
  GSetShapoid*: _GSetTailElem, \
  const GSetShapoid*: _GSetTailElem, \
  GSetKnapSackPod*: _GSetTailElem, \
  const GSetKnapSackPod*: _GSetTailElem, \
  GSetPBPhysParticle*: _GSetTailElem, \
  const GSetPBPhysParticle*: _GSetTailElem, \
  GSetGenTree*: _GSetTailElem, \
  const GSetGenTree*: _GSetTailElem, \
  GSetStr*: _GSetTailElem, \
  const GSetStr*: _GSetTailElem, \
  GSetGenTreeStr*: _GSetTailElem, \
  const GSetGenTreeStr*: _GSetTailElem, \
  default: PBErrInvalidPolymorphism)((const GSet*)Set)

#define GSetElement(Set, Pos) _Generic(Set, \
  GSet*: _GSetElement, \
  const GSet*: _GSetElement, \
  GSetVecFloat*: _GSetElement, \
  const GSetVecFloat*: _GSetElement, \
  GSetVecShort*: _GSetElement, \
  const GSetVecShort*: _GSetElement, \
  GSetBCurve*: _GSetElement, \
  const GSetBCurve*: _GSetElement, \
  GSetSCurve*: _GSetElement, \
  const GSetSCurve*: _GSetElement, \
  GSetShapoid*: _GSetElement, \
  const GSetShapoid*: _GSetElement, \
  GSetKnapSackPod*: _GSetElement, \
  const GSetKnapSackPod*: _GSetElement, \
  GSetPBPhysParticle*: _GSetElement, \
  const GSetPBPhysParticle*: _GSetElement, \
  GSetGenTree*: _GSetElement, \
  const GSetGenTree*: _GSetElement, \
  GSetStr*: _GSetElement, \
  const GSetStr*: _GSetElement, \
  GSetGenTreeStr*: _GSetElement, \
  const GSetGenTreeStr*: _GSetElement, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Pos)

#define GSetElementJump(Set, Pos) _Generic(Set, \
  GSet*: _GSetElementJump, \
  const GSet*: _GSetElementJump, \
  GSetVecFloat*: _GSetElementJump, \
  const GSetVecFloat*: _GSetElementJump, \
  GSetVecShort*: _GSetElementJump, \
  const GSetVecShort*: _GSetElementJump, \
  GSetBCurve*: _GSetElementJump, \
  const GSetBCurve*: _GSetElementJump, \
  GSetSCurve*: _GSetElementJump, \
  const GSetSCurve*: _GSetElementJump, \
  GSetShapoid*: _GSetElementJump, \
  const GSetShapoid*: _GSetElementJump, \
  GSetKnapSackPod*: _GSetElementJump, \
  const GSetKnapSackPod*: _GSetElementJump, \
  GSetPBPhysParticle*: _GSetElementJump, \
  const GSetPBPhysParticle*: _GSetElementJump, \
  GSetGenTree*: _GSetElementJump, \
  const GSetGenTree*: _GSetElementJump, \
  GSetStr*: _GSetElementJump, \
  const GSetStr*: _GSetElementJump, \
  GSetGenTreeStr*: _GSetElementJump, \
  const GSetGenTreeStr*: _GSetElementJump, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Pos)

#define GSetSort(Set) _Generic(Set, \
  GSet*: _GSetSort, \
  GSetVecFloat*: _GSetSort, \
  GSetVecShort*: _GSetSort, \
  GSetBCurve*: _GSetSort, \
  GSetSCurve*: _GSetSort, \
  GSetShapoid*: _GSetSort, \
  GSetKnapSackPod*: _GSetSort, \
  GSetPBPhysParticle*: _GSetSort, \
  GSetGenTree*: _GSetSort, \
  GSetStr*: _GSetSort, \
  GSetGenTreeStr*: _GSetSort, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))

#define GSetMerge(IntoSet, MergedSet) _Generic(IntoSet, \
  GSet*: _Generic(MergedSet, \
    GSet*: _GSetMerge, \
    GSetVecFloat*: _GSetMerge, \
    GSetVecShort*: _GSetMerge, \
    GSetBCurve*: _GSetMerge, \
    GSetSCurve*: _GSetMerge, \
    GSetShapoid*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetVecFloat*: _Generic(MergedSet, \
    GSetVecFloat*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(MergedSet, \
    GSetVecFloat*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(MergedSet, \
    GSetBCurve*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(MergedSet, \
    GSetSCurve*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(MergedSet, \
    GSetShapoid*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(MergedSet, \
    GSetKnapSackPod*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(MergedSet, \
    GSetPBPhysParticle*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(MergedSet, \
    GSetGenTree*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(MergedSet, \
    GSetStr*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(MergedSet, \
    GSetGenTreeStr*: _GSetMerge, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(IntoSet), \
    (GSet*)(MergedSet))

#define GSetSplit(Set, Elem) _Generic(Set, \
  GSet*: _GSetSplit, \
  GSetVecFloat*: _GSetSplit, \
  GSetVecShort*: _GSetSplit, \
  GSetBCurve*: _GSetSplit, \
  GSetSCurve*: _GSetSplit, \
  GSetShapoid*: _GSetSplit, \
  GSetKnapSackPod*: _GSetSplit, \
  GSetPBPhysParticle*: _GSetSplit, \
  GSetGenTree*: _GSetSplit, \
  GSetStr*: _GSetSplit, \
  GSetGenTreeStr*: _GSetSplit, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Elem)

#define GSetAppendSet(IntoSet, AppendSet) _Generic(IntoSet, \
  GSet*: _Generic(AppendSet, \
    GSet*: _GSetAppendSet, \
    GSetVecFloat*: _GSetAppendSet, \
    GSetVecShort*: _GSetAppendSet, \
    GSetBCurve*: _GSetAppendSet, \
    GSetSCurve*: _GSetAppendSet, \
    GSetShapoid*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetVecFloat*: _Generic(AppendSet, \
    GSetVecFloat*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(AppendSet, \
    GSetVecShort*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(AppendSet, \
    GSetBCurve*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(AppendSet, \
    GSetSCurve*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(AppendSet, \
    GSetShapoid*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(AppendSet, \
    GSetKnapSackPod*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(AppendSet, \
    GSetPBPhysParticle*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(AppendSet, \
    GSetGenTree*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(AppendSet, \
    GSetStr*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(AppendSet, \
    GSetGenTreeStr*: _GSetAppendSet, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(IntoSet), \
    (GSet*)(AppendSet))

#define GSetAppendSortedSet(IntoSet, AppendSet) _Generic(IntoSet, \
  GSet*: _Generic(AppendSet, \
    GSet*: _GSetAppendSortedSet, \
    GSetVecFloat*: _GSetAppendSortedSet, \
    GSetVecShort*: _GSetAppendSortedSet, \
    GSetBCurve*: _GSetAppendSortedSet, \
    GSetSCurve*: _GSetAppendSortedSet, \
    GSetShapoid*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetVecFloat*: _Generic(AppendSet, \
    GSetVecFloat*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(AppendSet, \
    GSetVecShort*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(AppendSet, \
    GSetBCurve*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(AppendSet, \
    GSetSCurve*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(AppendSet, \
    GSetShapoid*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(AppendSet, \
    GSetKnapSackPod*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(AppendSet, \
    GSetPBPhysParticle*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTree*: _Generic(AppendSet, \
    GSetGenTree*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetStr*: _Generic(AppendSet, \
    GSetStr*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  GSetGenTreeStr*: _Generic(AppendSet, \
    GSetGenTreeStr*: _GSetAppendSortedSet, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(IntoSet), \
    (GSet*)(AppendSet))

#define GSetSwitch(Set, PosA, PosB) _Generic(Set, \
  GSet*: _GSetSwitch, \
  GSetVecFloat*: _GSetSwitch, \
  GSetVecShort*: _GSetSwitch, \
  GSetBCurve*: _GSetSwitch, \
  GSetSCurve*: _GSetSwitch, \
  GSetShapoid*: _GSetSwitch, \
  GSetKnapSackPod*: _GSetSwitch, \
  GSetPBPhysParticle*: _GSetSwitch, \
  GSetGenTree*: _GSetSwitch, \
  GSetStr*: _GSetSwitch, \
  GSetGenTreeStr*: _GSetSwitch, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), PosA, PosB)

#define GSetMoveElem(Set, From, To) _Generic(Set, \
  GSet*: _GSetMoveElem, \
  GSetVecFloat*: _GSetMoveElem, \
  GSetVecShort*: _GSetMoveElem, \
  GSetBCurve*: _GSetMoveElem, \
  GSetSCurve*: _GSetMoveElem, \
  GSetShapoid*: _GSetMoveElem, \
  GSetKnapSackPod*: _GSetMoveElem, \
  GSetPBPhysParticle*: _GSetMoveElem, \
  GSetGenTree*: _GSetMoveElem, \
  GSetStr*: _GSetMoveElem, \
  GSetGenTreeStr*: _GSetMoveElem, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), From, To)

#define GSetCount(Set, Data) _Generic(Set, \
  GSet*: _GSetCount, \
  const GSet*: _GSetCount, \
  GSetVecFloat*: _GSetCount, \
  const GSetVecFloat*: _GSetCount, \
  GSetVecShort*: _GSetCount, \
  const GSetVecShort*: _GSetCount, \
  GSetBCurve*: _GSetCount, \
  const GSetBCurve*: _GSetCount, \
  GSetSCurve*: _GSetCount, \
  const GSetSCurve*: _GSetCount, \
  GSetShapoid*: _GSetCount, \
  const GSetShapoid*: _GSetCount, \
  GSetKnapSackPod*: _GSetCount, \
  const GSetKnapSackPod*: _GSetCount, \
  GSetPBPhysParticle*: _GSetCount, \
  const GSetPBPhysParticle*: _GSetCount, \
  GSetGenTree*: _GSetCount, \
  const GSetGenTree*: _GSetCount, \
  GSetStr*: _GSetCount, \
  const GSetStr*: _GSetCount, \
  GSetGenTreeStr*: _GSetCount, \
  const GSetGenTreeStr*: _GSetCount, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Data)

#define GSetGetBounds(Set) _Generic(Set, \
  GSetVecFloat*: _GSetVecFloatGetBounds, \
  const GSetVecFloat*: _GSetVecFloatGetBounds, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetIterForwardCreate(Set) _Generic(Set, \
  GSet*: _GSetIterForwardCreate, \
  const GSet*: _GSetIterForwardCreate, \
  GSetVecFloat*: _GSetIterForwardCreate, \
  const GSetVecFloat*: _GSetIterForwardCreate, \
  GSetVecShort*: _GSetIterForwardCreate, \
  const GSetVecShort*: _GSetIterForwardCreate, \
  GSetBCurve*: _GSetIterForwardCreate, \
  const GSetBCurve*: _GSetIterForwardCreate, \
  GSetSCurve*: _GSetIterForwardCreate, \
  const GSetSCurve*: _GSetIterForwardCreate, \
  GSetShapoid*: _GSetIterForwardCreate, \
  const GSetShapoid*: _GSetIterForwardCreate, \
  GSetKnapSackPod*: _GSetIterForwardCreate, \
  const GSetKnapSackPod*: _GSetIterForwardCreate, \
  GSetPBPhysParticle*: _GSetIterForwardCreate, \
  const GSetPBPhysParticle*: _GSetIterForwardCreate, \
  GSetGenTree*: _GSetIterForwardCreate, \
  const GSetGenTree*: _GSetIterForwardCreate, \
  GSetStr*: _GSetIterForwardCreate, \
  const GSetStr*: _GSetIterForwardCreate, \
  GSetGenTreeStr*: _GSetIterForwardCreate, \
  const GSetGenTreeStr*: _GSetIterForwardCreate, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterForwardCreateStatic(Set) _Generic(Set, \
  GSet*: _GSetIterForwardCreateStatic, \
  const GSet*: _GSetIterForwardCreateStatic, \
  GSetVecFloat*: _GSetIterForwardCreateStatic, \
  const GSetVecFloat*: _GSetIterForwardCreateStatic, \
  GSetVecShort*: _GSetIterForwardCreateStatic, \
  const GSetVecShort*: _GSetIterForwardCreateStatic, \
  GSetBCurve*: _GSetIterForwardCreateStatic, \
  const GSetBCurve*: _GSetIterForwardCreateStatic, \
  GSetSCurve*: _GSetIterForwardCreateStatic, \
  const GSetSCurve*: _GSetIterForwardCreateStatic, \
  GSetShapoid*: _GSetIterForwardCreateStatic, \
  const GSetShapoid*: _GSetIterForwardCreateStatic, \
  GSetKnapSackPod*: _GSetIterForwardCreateStatic, \
  const GSetKnapSackPod*: _GSetIterForwardCreateStatic, \
  GSetPBPhysParticle*: _GSetIterForwardCreateStatic, \
  const GSetPBPhysParticle*: _GSetIterForwardCreateStatic, \
  GSetGenTree*: _GSetIterForwardCreateStatic, \
  const GSetGenTree*: _GSetIterForwardCreateStatic, \
  GSetStr*: _GSetIterForwardCreateStatic, \
  const GSetStr*: _GSetIterForwardCreateStatic, \
  GSetGenTreeStr*: _GSetIterForwardCreateStatic, \
  const GSetGenTreeStr*: _GSetIterForwardCreateStatic, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterBackwardCreate(Set) _Generic(Set, \
  GSet*: _GSetIterBackwardCreate, \
  const GSet*: _GSetIterBackwardCreate, \
  GSetVecFloat*: _GSetIterBackwardCreate, \
  const GSetVecFloat*: _GSetIterBackwardCreate, \
  GSetVecShort*: _GSetIterBackwardCreate, \
  const GSetVecShort*: _GSetIterBackwardCreate, \
  GSetBCurve*: _GSetIterBackwardCreate, \
  const GSetBCurve*: _GSetIterBackwardCreate, \
  GSetSCurve*: _GSetIterBackwardCreate, \
  const GSetSCurve*: _GSetIterBackwardCreate, \
  GSetShapoid*: _GSetIterBackwardCreate, \
  const GSetShapoid*: _GSetIterBackwardCreate, \
  GSetKnapSackPod*: _GSetIterBackwardCreate, \
  const GSetKnapSackPod*: _GSetIterBackwardCreate, \
  GSetPBPhysParticle*: _GSetIterBackwardCreate, \
  const GSetPBPhysParticle*: _GSetIterBackwardCreate, \
  GSetGenTree*: _GSetIterBackwardCreate, \
  const GSetGenTree*: _GSetIterBackwardCreate, \
  GSetGenTreeStr*: _GSetIterBackwardCreate, \
  const GSetGenTreeStr*: _GSetIterBackwardCreate, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterBackwardCreateStatic(Set) _Generic(Set, \
  GSet*: _GSetIterBackwardCreateStatic, \
  const GSet*: _GSetIterBackwardCreateStatic, \
  GSetVecFloat*: _GSetIterBackwardCreateStatic, \
  const GSetVecFloat*: _GSetIterBackwardCreateStatic, \
  GSetVecShort*: _GSetIterBackwardCreateStatic, \
  const GSetVecShort*: _GSetIterBackwardCreateStatic, \
  GSetBCurve*: _GSetIterBackwardCreateStatic, \
  const GSetBCurve*: _GSetIterBackwardCreateStatic, \
  GSetSCurve*: _GSetIterBackwardCreateStatic, \
  const GSetSCurve*: _GSetIterBackwardCreateStatic, \
  GSetShapoid*: _GSetIterBackwardCreateStatic, \
  const GSetShapoid*: _GSetIterBackwardCreateStatic, \
  GSetKnapSackPod*: _GSetIterBackwardCreateStatic, \
  const GSetKnapSackPod*: _GSetIterBackwardCreateStatic, \
  GSetPBPhysParticle*: _GSetIterBackwardCreateStatic, \
  const GSetPBPhysParticle*: _GSetIterBackwardCreateStatic, \
  GSetGenTree*: _GSetIterBackwardCreateStatic, \
  const GSetGenTree*: _GSetIterBackwardCreateStatic, \
  GSetStr*: _GSetIterBackwardCreateStatic, \
  const GSetStr*: _GSetIterBackwardCreateStatic, \
  GSetGenTreeStr*: _GSetIterBackwardCreateStatic, \
  const GSetGenTreeStr*: _GSetIterBackwardCreateStatic, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterSetGSet(Iter, Set) _Generic(Iter, \
  GSetIterForward*: _Generic(Set, \
    GSet*: GSetIterForwardSetGSet, \
    const GSet*: GSetIterForwardSetGSet, \
    GSetVecFloat*: GSetIterForwardSetGSet, \
    const GSetVecFloat*: GSetIterForwardSetGSet, \
    GSetVecShort*: GSetIterForwardSetGSet, \
    const GSetVecShort*: GSetIterForwardSetGSet, \
    GSetBCurve*: GSetIterForwardSetGSet, \
    const GSetBCurve*: GSetIterForwardSetGSet, \
    GSetSCurve*: GSetIterForwardSetGSet, \
    const GSetSCurve*: GSetIterForwardSetGSet, \
    GSetShapoid*: GSetIterForwardSetGSet, \
    const GSetShapoid*: GSetIterForwardSetGSet, \
    GSetKnapSackPod*: GSetIterForwardSetGSet, \
    const GSetKnapSackPod*: GSetIterForwardSetGSet, \
    GSetPBPhysParticle*: GSetIterForwardSetGSet, \
    const GSetPBPhysParticle*: GSetIterForwardSetGSet, \
    GSetGenTree*: GSetIterForwardSetGSet, \
    const GSetGenTree*: GSetIterForwardSetGSet, \
    GSetStr*: GSetIterForwardSetGSet, \
    const GSetStr*: GSetIterForwardSetGSet, \
    GSetGenTreeStr*: GSetIterForwardSetGSet, \
    const GSetGenTreeStr*: GSetIterForwardSetGSet, \
    default: PBErrInvalidPolymorphism), \
  GSetIterBackward*: _Generic(Set, \
    GSet*: GSetIterBackwardSetGSet, \
    const GSet*: GSetIterBackwardSetGSet, \
    GSetVecFloat*: GSetIterBackwardSetGSet, \
    const GSetVecFloat*: GSetIterBackwardSetGSet, \
    GSetVecShort*: GSetIterBackwardSetGSet, \
    const GSetVecShort*: GSetIterBackwardSetGSet, \
    GSetBCurve*: GSetIterBackwardSetGSet, \
    const GSetBCurve*: GSetIterBackwardSetGSet, \
    GSetSCurve*: GSetIterBackwardSetGSet, \
    const GSetSCurve*: GSetIterBackwardSetGSet, \
    GSetShapoid*: GSetIterBackwardSetGSet, \
    const GSetShapoid*: GSetIterBackwardSetGSet, \
    GSetKnapSackPod*: GSetIterBackwardSetGSet, \
    const GSetKnapSackPod*: GSetIterBackwardSetGSet, \
    GSetPBPhysParticle*: GSetIterBackwardSetGSet, \
    const GSetPBPhysParticle*: GSetIterBackwardSetGSet, \
    GSetGenTree*: GSetIterBackwardSetGSet, \
    const GSetGenTree*: GSetIterBackwardSetGSet, \
    GSetStr*: GSetIterBackwardSetGSet, \
    const GSetStr*: GSetIterBackwardSetGSet, \
    GSetGenTreeStr*: GSetIterBackwardSetGSet, \
    const GSetGenTreeStr*: GSetIterBackwardSetGSet, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(Iter, (GSet*)(Set))

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

#define GSetIterStepBack(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardStepBack, \
  GSetIterBackward*: GSetIterBackwardStepBack, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterApply(Iter, Fun, Param) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardApply, \
  GSetIterBackward*: GSetIterBackwardApply, \
  default: PBErrInvalidPolymorphism)(Iter, Fun, Param)

#define GSetIterIsFirst(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardIsFirst, \
  const GSetIterForward*: GSetIterForwardIsFirst, \
  GSetIterBackward*: GSetIterBackwardIsFirst, \
  const GSetIterBackward*: GSetIterBackwardIsFirst, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterIsLast(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardIsLast, \
  const GSetIterForward*: GSetIterForwardIsLast, \
  GSetIterBackward*: GSetIterBackwardIsLast, \
  const GSetIterBackward*: GSetIterBackwardIsLast, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterGet(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardGet, \
  const GSetIterForward*: GSetIterForwardGet, \
  GSetIterBackward*: GSetIterBackwardGet, \
  const GSetIterBackward*: GSetIterBackwardGet, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterSetData(Iter, Data) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardSetData, \
  const GSetIterForward*: GSetIterForwardSetData, \
  GSetIterBackward*: GSetIterBackwardSetData, \
  const GSetIterBackward*: GSetIterBackwardSetData, \
  default: PBErrInvalidPolymorphism)(Iter, Data)

#define GSetIterGetElem(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardGetElem, \
  const GSetIterForward*: GSetIterForwardGetElem, \
  GSetIterBackward*: GSetIterBackwardGetElem, \
  const GSetIterBackward*: GSetIterBackwardGetElem, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterGetSortVal(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardGetSortVal, \
  const GSetIterForward*: GSetIterForwardGetSortVal, \
  GSetIterBackward*: GSetIterBackwardGetSortVal, \
  const GSetIterBackward*: GSetIterBackwardGetSortVal, \
  default: PBErrInvalidPolymorphism)(Iter)

#define GSetIterRemoveElem(Iter) _Generic(Iter, \
  GSetIterForward*: GSetIterForwardRemoveElem, \
  GSetIterBackward*: GSetIterBackwardRemoveElem, \
  default: PBErrInvalidPolymorphism)(Iter)

// ================ Inliner ====================

#if BUILDMODE != 0
#include "gset-inline.c"
#endif

#endif
