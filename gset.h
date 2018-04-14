// *************** GSET.H ***************
#ifndef GSET_H
#define GSET_H

// ================= Include ==================
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pberr.h"

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
void _GSetFree(GSet** s);

// Function to empty the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetFlush(GSet* that);

// Return the number of element in the set
#if BUILDMODE != 0
inline
#endif 
int _GSetNbElem(GSet* that);

// Function to print a GSet
// Use the function 'printData' to print the data pointed to by 
// the elements, and print 'sep' between each element
// If printData is null, print the pointer value instead
void _GSetPrint(GSet* that, FILE* stream, 
  void(*printData)(void* data, FILE* stream), char* sep);

// Function to insert an element pointing toward 'data' at the 
// head of the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetPush(GSet* that, void* data);

// Function to insert an element pointing toward 'data' at the 
// position defined by 'v' sorting the set in increasing order
void _GSetAddSort(GSet* that, void* data, double v);

// Function to insert an element pointing toward 'data' at the 
// 'iElem'-th position 
// If 'iElem' is greater than or equal to the number of element
// in the GSet, elements pointing toward null data are added
// If the data is inserted inside the set, the current elements from
// the iElem-th elem are pushed 
void _GSetInsert(GSet* that, void* data, int iElem);

// Function to insert an element pointing toward 'data' at the 
// tail of the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetAppend(GSet* that, void* data);

// Function to remove the element at the head of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* _GSetPop(GSet* that);

// Function to remove the element at the tail of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* _GSetDrop(GSet* that);

// Function to remove the element at the 'iElem'-th position of the GSet
// Return the data pointed to by the removed element
#if BUILDMODE != 0
inline
#endif 
void* _GSetRemove(GSet* that, int iElem);

// Function to remove the element 'elem' of the GSet
// Return the data pointed to by the removed element
// The GSetElem is freed and *elem == NULL after calling this function
#if BUILDMODE != 0
inline
#endif 
void* _GSetRemoveElem(GSet* that, GSetElem** elem);

// Function to remove the first element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveFirst(GSet* that, void* data);

// Function to remove the last element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveLast(GSet* that, void* data);

// Function to remove all the selement of the GSet pointing to 'data'
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveAll(GSet* that, void* data);

// Function to get the data at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetGet(GSet* that, int iElem);

// Function to get the data at first position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetGetFirst(GSet* that);

// Function to get the data at last position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetGetLast(GSet* that);

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
GSetElem* _GSetGetElem(GSet* that, int iElem);

// Function to get the index of the first element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
int _GSetGetIndexFirst(GSet* that, void* data);

// Function to get the index of the last element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
int _GSetGetIndexLast(GSet* that, void* data);

// Function to get the first element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
GSetElem* _GSetGetFirstElem(GSet* that, void* data);

// Function to get the last element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
GSetElem* _GSetGetLastElem(GSet* that, void* data);

// Function to sort the element of the gset in increasing order of 
// _sortVal
void _GSetSort(GSet* that);

// Merge the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
// After calling this function 'set' is empty 
#if BUILDMODE != 0
inline
#endif 
void _GSetMerge(GSet* that, GSet* set);

// Split the GSet at the GSetElem 'e'
// 'e' must be and element of the set
// the set new end is the element before 'e', the set becomes empty if 
// 'e' was the first element
// Return a new GSet starting with 'e', or NULL if 'e' is not 
// an element of the set
#if BUILDMODE != 0
inline
#endif 
GSet* _GSetSplit(GSet* that, GSetElem* e);

// Append the element of the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void _GSetAppendSet(GSet* that, GSet* set);

// Append the element of the GSet 'that' at the end of the GSet 'set'
// Elements are kept sorted
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void _GSetAppendSortedSet(GSet* that, GSet* set);

// Switch the 'iElem'-th and 'jElem'-th element of the set
#if BUILDMODE != 0
inline
#endif 
void _GSetSwitch(GSet* that, int iElem, int jElem);

// Return the number of (GSetElem._data=='data') in the GSet 'that'
int _GSetCount(GSet* that, void* data);

// Set the sort value of the GSetElem 'that' to 'v'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetSortVal(GSetElem* that, float v);

// Move the 'iElem'-th element to the 'pos' index in the GSet
void _GSetMoveElem(GSet* that, int iElem, int pos);

// Create a new GSetIterForward for the GSet 'set'
// The iterator is reset upon creation
GSetIterForward* _GSetIterForwardCreate(GSet* set);
#if BUILDMODE != 0
inline
#endif 
GSetIterForward _GSetIterForwardCreateStatic(GSet* set);

// Create a new GSetIterBackward for the GSet 'set'
// The iterator is reset upon creation
GSetIterBackward* _GSetIterBackwardCreate(GSet* set);
#if BUILDMODE != 0
inline
#endif 
GSetIterBackward _GSetIterBackwardCreateStatic(GSet* set);

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
inline GSetVecFloat* GSetVecFloatClone(GSetVecFloat* that)
  {return (GSetVecFloat*)GSetClone((GSet*)that);}
inline VecFloat* _GSetVecFloatGet(GSetVecFloat* that, int iElem)
  {return (VecFloat*)_GSetGet((GSet*)that, iElem);}
inline VecFloat* _GSetVecFloatGetFirst(GSetVecFloat* that)
  {return (VecFloat*)_GSetGetFirst((GSet*)that);}
inline VecFloat* _GSetVecFloatGetLast(GSetVecFloat* that)
  {return (VecFloat*)_GSetGetLast((GSet*)that);}
inline VecFloat* _GSetVecFloatPop(GSetVecFloat* that)
  {return (VecFloat*)_GSetPop((GSet*)that);}
inline VecFloat* _GSetVecFloatDrop(GSetVecFloat* that)
  {return (VecFloat*)_GSetDrop((GSet*)that);}
inline VecFloat* _GSetVecFloatRemove(GSetVecFloat* that, int iElem)
  {return (VecFloat*)_GSetRemove((GSet*)that, iElem);}
inline VecFloat* _GSetVecFloatRemoveElem(GSetVecFloat* that, 
  GSetElem** elem)
  {return (VecFloat*)_GSetRemoveElem((GSet*)that, elem);}

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
inline GSetVecShort* GSetVecShortClone(GSetVecShort* that)
  {return (GSetVecShort*)GSetClone((GSet*)that);}
inline VecShort* _GSetVecShortGet(GSetVecShort* that, int iElem)
  {return (VecShort*)_GSetGet((GSet*)that, iElem);}
inline VecShort* _GSetVecShortGetFirst(GSetVecShort* that)
  {return (VecShort*)_GSetGetFirst((GSet*)that);}
inline VecShort* _GSetVecShortGetLast(GSetVecShort* that)
  {return (VecShort*)_GSetGetLast((GSet*)that);}
inline VecShort* _GSetVecShortPop(GSetVecShort* that)
  {return (VecShort*)_GSetPop((GSet*)that);}
inline VecShort* _GSetVecShortDrop(GSetVecShort* that)
  {return (VecShort*)_GSetDrop((GSet*)that);}
inline VecShort* _GSetVecShortRemove(GSetVecShort* that, int iElem)
  {return (VecShort*)_GSetRemove((GSet*)that, iElem);}
inline VecShort* _GSetVecShortRemoveElem(GSetVecShort* that, 
  GSetElem** elem)
  {return (VecShort*)_GSetRemoveElem((GSet*)that, elem);}

#ifndef BCurve
  typedef struct BCurve BCurve;
#endif
typedef struct GSetBCurve {GSet _set;} GSetBCurve;
#define GSetBCurveCreate() ((GSetBCurve*)GSetCreate())
inline GSetBCurve GSetBCurveCreateStatic(void) 
  {GSetBCurve ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetBCurve* GSetBCurveClone(GSetBCurve* that)
  {return (GSetBCurve*)GSetClone((GSet*)that);}
inline BCurve* _GSetBCurveGet(GSetBCurve* that, int iElem)
  {return (BCurve*)_GSetGet((GSet*)that, iElem);}
inline BCurve* _GSetBCurveGetFirst(GSetBCurve* that)
  {return (BCurve*)_GSetGetFirst((GSet*)that);}
inline BCurve* _GSetBCurveGetLast(GSetBCurve* that)
  {return (BCurve*)_GSetGetLast((GSet*)that);}
inline BCurve* _GSetBCurvePop(GSetBCurve* that)
  {return (BCurve*)_GSetPop((GSet*)that);}
inline BCurve* _GSetBCurveDrop(GSetBCurve* that)
  {return (BCurve*)_GSetDrop((GSet*)that);}
inline BCurve* _GSetBCurveRemove(GSetBCurve* that, int iElem)
  {return (BCurve*)_GSetRemove((GSet*)that, iElem);}
inline BCurve* _GSetBCurveRemoveElem(GSetBCurve* that, 
  GSetElem** elem)
  {return (BCurve*)_GSetRemoveElem((GSet*)that, elem);}

#ifndef SCurve
  typedef struct SCurve SCurve;
#endif
typedef struct GSetSCurve {GSet _set;} GSetSCurve;
#define GSetSCurveCreate() ((GSetSCurve*)GSetCreate())
inline GSetSCurve GSetSCurveCreateStatic(void) 
  {GSetSCurve ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetSCurve* GSetSCurveClone(GSetSCurve* that)
  {return (GSetSCurve*)GSetClone((GSet*)that);}
inline SCurve* _GSetSCurveGet(GSetSCurve* that, int iElem)
  {return (SCurve*)_GSetGet((GSet*)that, iElem);}
inline SCurve* _GSetSCurveGetFirst(GSetSCurve* that)
  {return (SCurve*)_GSetGetFirst((GSet*)that);}
inline SCurve* _GSetSCurveGetLast(GSetSCurve* that)
  {return (SCurve*)_GSetGetLast((GSet*)that);}
inline SCurve* _GSetSCurvePop(GSetSCurve* that)
  {return (SCurve*)_GSetPop((GSet*)that);}
inline SCurve* _GSetSCurveDrop(GSetSCurve* that)
  {return (SCurve*)_GSetDrop((GSet*)that);}
inline SCurve* _GSetSCurveRemove(GSetSCurve* that, int iElem)
  {return (SCurve*)_GSetRemove((GSet*)that, iElem);}
inline SCurve* _GSetSCurveRemoveElem(GSetSCurve* that, 
  GSetElem** elem)
  {return (SCurve*)_GSetRemoveElem((GSet*)that, elem);}

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
inline GSetShapoid* GSetShapoidClone(GSetShapoid* that)
  {return (GSetShapoid*)GSetClone((GSet*)that);}
inline Shapoid* _GSetShapoidGet(GSetShapoid* that, int iElem)
  {return (Shapoid*)_GSetGet((GSet*)that, iElem);}
inline Shapoid* _GSetShapoidGetFirst(GSetShapoid* that)
  {return (Shapoid*)_GSetGetFirst((GSet*)that);}
inline Shapoid* _GSetShapoidGetLast(GSetShapoid* that)
  {return (Shapoid*)_GSetGetLast((GSet*)that);}
inline Shapoid* _GSetShapoidPop(GSetShapoid* that)
  {return (Shapoid*)_GSetPop((GSet*)that);}
inline Shapoid* _GSetShapoidDrop(GSetShapoid* that)
  {return (Shapoid*)_GSetDrop((GSet*)that);}
inline Shapoid* _GSetShapoidRemove(GSetShapoid* that, int iElem)
  {return (Shapoid*)_GSetRemove((GSet*)that, iElem);}
inline Shapoid* _GSetShapoidRemoveElem(GSetShapoid* that, 
  GSetElem** elem)
  {return (Shapoid*)_GSetRemoveElem((GSet*)that, elem);}

#ifndef KnapSackPod
  typedef struct KnapSackPod KnapSackPod;
#endif
typedef struct GSetKnapSackPod {GSet _set;} GSetKnapSackPod;
#define GSetKnapSackPodCreate() ((GSetKnapSackPod*)GSetCreate())
inline GSetKnapSackPod GSetKnapSackPodCreateStatic(void) 
  {GSetKnapSackPod ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetKnapSackPod* GSetKnapSackPodClone(GSetKnapSackPod* that)
  {return (GSetKnapSackPod*)GSetClone((GSet*)that);}
inline KnapSackPod* _GSetKnapSackPodGet(GSetKnapSackPod* that, 
  int iElem)
  {return (KnapSackPod*)_GSetGet((GSet*)that, iElem);}
inline KnapSackPod* _GSetKnapSackPodGetFirst(GSetKnapSackPod* that)
  {return (KnapSackPod*)_GSetGetFirst((GSet*)that);}
inline KnapSackPod* _GSetKnapSackPodGetLast(GSetKnapSackPod* that)
  {return (KnapSackPod*)_GSetGetLast((GSet*)that);}
inline KnapSackPod* _GSetKnapSackPodPop(GSetKnapSackPod* that)
  {return (KnapSackPod*)_GSetPop((GSet*)that);}
inline KnapSackPod* _GSetKnapSackPodDrop(GSetKnapSackPod* that)
  {return (KnapSackPod*)_GSetDrop((GSet*)that);}
inline KnapSackPod* _GSetKnapSackPodRemove(GSetKnapSackPod* that, 
  int iElem)
  {return (KnapSackPod*)_GSetRemove((GSet*)that, iElem);}
inline KnapSackPod* _GSetKnapSackPodRemoveElem(GSetKnapSackPod* that, 
  GSetElem** elem)
  {return (KnapSackPod*)_GSetRemoveElem((GSet*)that, elem);}

#ifndef PBPhysParticle
  typedef struct PBPhysParticle PBPhysParticle;
#endif
typedef struct GSetPBPhysParticle {GSet _set;} GSetPBPhysParticle;
#define GSetPBPhysParticleCreate() ((GSetPBPhysParticle*)GSetCreate())
inline GSetPBPhysParticle GSetPBPhysParticleCreateStatic(void) 
  {GSetPBPhysParticle ret = {._set=GSetCreateStatic()}; return ret;}
inline GSetPBPhysParticle* GSetPBPhysParticleClone(
  GSetPBPhysParticle* that)
  {return (GSetPBPhysParticle*)GSetClone((GSet*)that);}
inline PBPhysParticle* _GSetPBPhysParticleGet(GSetPBPhysParticle* that, 
  int iElem)
  {return (PBPhysParticle*)_GSetGet((GSet*)that, iElem);}
inline PBPhysParticle* _GSetPBPhysParticleGetFirst(
  GSetPBPhysParticle* that)
  {return (PBPhysParticle*)_GSetGetFirst((GSet*)that);}
inline PBPhysParticle* _GSetPBPhysParticleGetLast(
  GSetPBPhysParticle* that)
  {return (PBPhysParticle*)_GSetGetLast((GSet*)that);}
inline PBPhysParticle* _GSetPBPhysParticlePop(GSetPBPhysParticle* that)
  {return (PBPhysParticle*)_GSetPop((GSet*)that);}
inline PBPhysParticle* _GSetPBPhysParticleDrop(GSetPBPhysParticle* that)
  {return (PBPhysParticle*)_GSetDrop((GSet*)that);}
inline 
PBPhysParticle* _GSetPBPhysParticleRemove(GSetPBPhysParticle* that, 
  int iElem)
  {return (PBPhysParticle*)_GSetRemove((GSet*)that, iElem);}
inline PBPhysParticle* _GSetPBPhysParticleRemoveElem(
  GSetPBPhysParticle* that, GSetElem** elem)
  {return (PBPhysParticle*)_GSetRemoveElem((GSet*)that, elem);}

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
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetPush, \
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
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetGetIndexFirst(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetGetIndexFirst), \
  GSetVecFloat*: _Generic(Data, \
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
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetIndexFirst, \
    Facoid*: _GSetGetIndexFirst, \
    Pyramidoid*: _GSetGetIndexFirst, \
    Spheroid*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetIndexFirst, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetGetIndexLast(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetGetIndexLast), \
  GSetVecFloat*: _Generic(Data, \
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
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetIndexLast, \
    Facoid*: _GSetGetIndexLast, \
    Pyramidoid*: _GSetGetIndexLast, \
    Spheroid*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetIndexLast, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetGetFirstElem(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetGetFirstElem), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetGetFirstElem, \
    VecFloat2D*: _GSetGetFirstElem, \
    VecFloat3D*: _GSetGetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetGetFirstElem, \
    VecShort2D*: _GSetGetFirstElem, \
    VecShort3D*: _GSetGetFirstElem, \
    VecShort4D*: _GSetGetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetFirstElem, \
    Facoid*: _GSetGetFirstElem, \
    Pyramidoid*: _GSetGetFirstElem, \
    Spheroid*: _GSetGetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetFirstElem, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetGetLastElem(Set, Data) _Generic(Set, \
  GSet*: _Generic(Data, \
    default: _GSetGetLastElem), \
  GSetVecFloat*: _Generic(Data, \
    VecFloat*: _GSetGetLastElem, \
    VecFloat2D*: _GSetGetLastElem, \
    VecFloat3D*: _GSetGetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetVecShort*: _Generic(Data, \
    VecShort*: _GSetGetLastElem, \
    VecShort2D*: _GSetGetLastElem, \
    VecShort3D*: _GSetGetLastElem, \
    VecShort4D*: _GSetGetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetBCurve*: _Generic(Data, \
    BCurve*: _GSetGetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetSCurve*: _Generic(Data, \
    SCurve*: _GSetGetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetShapoid*: _Generic(Data, \
    Shapoid*: _GSetGetLastElem, \
    Facoid*: _GSetGetLastElem, \
    Pyramidoid*: _GSetGetLastElem, \
    Spheroid*: _GSetGetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetKnapSackPod*: _Generic(Data, \
    KnapSackPod*: _GSetGetLastElem, \
    default: PBErrInvalidPolymorphism), \
  GSetPBPhysParticle*: _Generic(Data, \
    PBPhysParticle*: _GSetGetLastElem, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), (void*)(Data))

#define GSetPrint(Set, Stream, Fun, Sep) _Generic(Set, \
  GSet*: _GSetPrint, \
  GSetVecFloat*: _GSetPrint, \
  GSetVecShort*: _GSetPrint, \
  GSetBCurve*: _GSetPrint, \
  GSetSCurve*: _GSetPrint, \
  GSetShapoid*: _GSetPrint, \
  GSetKnapSackPod*: _GSetPrint, \
  GSetPBPhysParticle*: _GSetPrint, \
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
  default: PBErrInvalidPolymorphism)((GSet*)(Set))

#define GSetNbElem(Set) _Generic(Set, \
  GSet*: _GSetNbElem, \
  GSetVecFloat*: _GSetNbElem, \
  GSetVecShort*: _GSetNbElem, \
  GSetBCurve*: _GSetNbElem, \
  GSetSCurve*: _GSetNbElem, \
  GSetShapoid*: _GSetNbElem, \
  GSetKnapSackPod*: _GSetNbElem, \
  GSetPBPhysParticle*: _GSetNbElem, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))

#define GSetPop(Set) _Generic(Set, \
  GSet*: _GSetPop, \
  GSetVecFloat*: _GSetVecFloatPop, \
  GSetVecShort*: _GSetVecShortPop, \
  GSetBCurve*: _GSetBCurvePop, \
  GSetSCurve*: _GSetSCurvePop, \
  GSetShapoid*: _GSetShapoidPop, \
  GSetKnapSackPod*: _GSetShapoidPop, \
  GSetPBPhysParticle*: _GSetShapoidPop, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetDrop(Set) _Generic(Set, \
  GSet*: _GSetDrop, \
  GSetVecFloat*: _GSetVecFloatDrop, \
  GSetVecShort*: _GSetVecShortDrop, \
  GSetBCurve*: _GSetBCurveDrop, \
  GSetSCurve*: _GSetSCurveDrop, \
  GSetShapoid*: _GSetSCurveDrop, \
  GSetKnapSackPod*: _GSetSCurveDrop, \
  GSetPBPhysParticle*: _GSetSCurveDrop, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetRemove(Set, Pos) _Generic(Set, \
  GSet*: _GSetRemove, \
  GSetVecFloat*: _GSetVecFloatRemove, \
  GSetVecShort*: _GSetVecShortRemove, \
  GSetBCurve*: _GSetBCurveRemove, \
  GSetSCurve*: _GSetSCurveRemove, \
  GSetShapoid*: _GSetSCurveRemove, \
  GSetKnapSackPod*: _GSetSCurveRemove, \
  GSetPBPhysParticle*: _GSetSCurveRemove, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Pos)

#define GSetRemoveElem(Set, Elem) _Generic(Set, \
  GSet*: _GSetRemoveElem, \
  GSetVecFloat*: _GSetVecFloatRemoveElem, \
  GSetVecShort*: _GSetVecShortRemoveElem, \
  GSetBCurve*: _GSetBCurveRemoveElem, \
  GSetSCurve*: _GSetSCurveRemoveElem, \
  GSetShapoid*: _GSetSCurveRemoveElem, \
  GSetKnapSackPod*: _GSetSCurveRemoveElem, \
  GSetPBPhysParticle*: _GSetSCurveRemoveElem, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Elem)

#define GSetGet(Set, Pos) _Generic(Set, \
  GSet*: _GSetGet, \
  GSetVecFloat*: _GSetVecFloatGet, \
  GSetVecShort*: _GSetVecShortGet, \
  GSetBCurve*: _GSetBCurveGet, \
  GSetSCurve*: _GSetSCurveGet, \
  GSetShapoid*: _GSetShapoidGet, \
  GSetKnapSackPod*: _GSetKnapSackPodGet, \
  GSetPBPhysParticle*: _GSetKnapSackPodGet, \
  default: PBErrInvalidPolymorphism)(Set, Pos)

#define GSetGetFirst(Set) _Generic(Set, \
  GSet*: _GSetGetFirst, \
  GSetVecFloat*: _GSetVecFloatGetFirst, \
  GSetVecShort*: _GSetVecShortGetFirst, \
  GSetBCurve*: _GSetBCurveGetFirst, \
  GSetSCurve*: _GSetSCurveGetFirst, \
  GSetShapoid*: _GSetSCurveGetFirst, \
  GSetKnapSackPod*: _GSetSCurveGetFirst, \
  GSetPBPhysParticle*: _GSetSCurveGetFirst, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetGetLast(Set) _Generic(Set, \
  GSet*: _GSetGetLast, \
  GSetVecFloat*: _GSetVecFloatGetLast, \
  GSetVecShort*: _GSetVecShortGetLast, \
  GSetBCurve*: _GSetBCurveGetLast, \
  GSetSCurve*: _GSetSCurveGetLast, \
  GSetShapoid*: _GSetSCurveGetLast, \
  GSetKnapSackPod*: _GSetSCurveGetLast, \
  GSetPBPhysParticle*: _GSetSCurveGetLast, \
  default: PBErrInvalidPolymorphism)(Set)

#define GSetGetElem(Set, Pos) _Generic(Set, \
  GSet*: _GSetGetElem, \
  GSetVecFloat*: _GSetGetElem, \
  GSetVecShort*: _GSetGetElem, \
  GSetBCurve*: _GSetGetElem, \
  GSetSCurve*: _GSetGetElem, \
  GSetShapoid*: _GSetGetElem, \
  GSetKnapSackPod*: _GSetGetElem, \
  GSetPBPhysParticle*: _GSetGetElem, \
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
  default: PBErrInvalidPolymorphism)((GSet*)(Set), From, To)

#define GSetCount(Set, Data) _Generic(Set, \
  GSet*: _GSetCount, \
  GSetVecFloat*: _GSetCount, \
  GSetVecShort*: _GSetCount, \
  GSetBCurve*: _GSetCount, \
  GSetSCurve*: _GSetCount, \
  GSetShapoid*: _GSetCount, \
  GSetKnapSackPod*: _GSetCount, \
  GSetPBPhysParticle*: _GSetCount, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set), Data)

#define GSetIterForwardCreate(Set) _Generic(Set, \
  GSet*: _GSetIterForwardCreate, \
  GSetVecFloat*: _GSetIterForwardCreate, \
  GSetVecShort*: _GSetIterForwardCreate, \
  GSetBCurve*: _GSetIterForwardCreate, \
  GSetSCurve*: _GSetIterForwardCreate, \
  GSetShapoid*: _GSetIterForwardCreate, \
  GSetKnapSackPod*: _GSetIterForwardCreate, \
  GSetPBPhysParticle*: _GSetIterForwardCreate, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterForwardCreateStatic(Set) _Generic(Set, \
  GSet*: _GSetIterForwardCreateStatic, \
  GSetVecFloat*: _GSetIterForwardCreateStatic, \
  GSetVecShort*: _GSetIterForwardCreateStatic, \
  GSetBCurve*: _GSetIterForwardCreateStatic, \
  GSetSCurve*: _GSetIterForwardCreateStatic, \
  GSetShapoid*: _GSetIterForwardCreateStatic, \
  GSetKnapSackPod*: _GSetIterForwardCreateStatic, \
  GSetPBPhysParticle*: _GSetIterForwardCreateStatic, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterBackwardCreate(Set) _Generic(Set, \
  GSet*: _GSetIterBackwardCreate, \
  GSetVecFloat*: _GSetIterBackwardCreate, \
  GSetVecShort*: _GSetIterBackwardCreate, \
  GSetBCurve*: _GSetIterBackwardCreate, \
  GSetSCurve*: _GSetIterBackwardCreate, \
  GSetShapoid*: _GSetIterBackwardCreate, \
  GSetKnapSackPod*: _GSetIterBackwardCreate, \
  GSetPBPhysParticle*: _GSetIterBackwardCreate, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterBackwardCreateStatic(Set) _Generic(Set, \
  GSet*: _GSetIterBackwardCreateStatic, \
  GSetVecFloat*: _GSetIterBackwardCreateStatic, \
  GSetVecShort*: _GSetIterBackwardCreateStatic, \
  GSetBCurve*: _GSetIterBackwardCreateStatic, \
  GSetSCurve*: _GSetIterBackwardCreateStatic, \
  GSetShapoid*: _GSetIterBackwardCreateStatic, \
  GSetKnapSackPod*: _GSetIterBackwardCreateStatic, \
  GSetPBPhysParticle*: _GSetIterBackwardCreateStatic, \
  default: PBErrInvalidPolymorphism)((GSet*)(Set))
  
#define GSetIterSetGSet(Iter, Set) _Generic(Iter, \
  GSetIterForward*: _Generic(Set, \
    GSet*: GSetIterForwardSetGSet, \
    GSetVecFloat*: GSetIterForwardSetGSet, \
    GSetVecShort*: GSetIterForwardSetGSet, \
    GSetBCurve*: GSetIterForwardSetGSet, \
    GSetSCurve*: GSetIterForwardSetGSet, \
    GSetShapoid*: GSetIterForwardSetGSet, \
    GSetKnapSackPod*: GSetIterForwardSetGSet, \
    GSetPBPhysParticle*: GSetIterForwardSetGSet, \
    default: PBErrInvalidPolymorphism), \
  GSetIterBackward*: _Generic(Set, \
    GSet*: GSetIterBackwardSetGSet, \
    GSetVecFloat*: GSetIterBackwardSetGSet, \
    GSetVecShort*: GSetIterBackwardSetGSet, \
    GSetBCurve*: GSetIterBackwardSetGSet, \
    GSetSCurve*: GSetIterBackwardSetGSet, \
    GSetShapoid*: GSetIterBackwardSetGSet, \
    GSetKnapSackPod*: GSetIterBackwardSetGSet, \
    GSetPBPhysParticle*: GSetIterBackwardSetGSet, \
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

// ================ Inliner ====================

#if BUILDMODE != 0
#include "gset-inline.c"
#endif

#endif
