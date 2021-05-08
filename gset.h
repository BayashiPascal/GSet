// ------------------ gset.h ------------------

// Guard against multiple inclusions
#ifndef _GSET_
#define _GSET_

// Include external modules header
#include <stdlib.h>
#include <TryCatchC/trycatchc.h>

// ================== Public type definitions =========================

// Type of iteration on the set
enum GSetIteration {

  GSetIteration_forward,
  GSetIteration_backward,

};

// Structure of a GSet element
struct GSetElem;

// Structure of a GSet
struct GSet {

  // Size of the GSet (i.e. number of GSetElem currently in it)
  int size;

  // First element of the set
  struct GSetElem* first;

  // Last element of the set
  struct GSetElem* last;

  // Current element (according to iteration operations)
  struct GSetElem* elem;

  // Type of iteration
  enum GSetIteration iteration;

};

// ================== Public functions declarations =========================

// Create a new GSet
// Output:
//   Return the new GSet.
struct GSet GSetCreate(
  void);

// Allocate memory for a new GSet
// Output:
//   Return the new GSet.
struct GSet* GSetAlloc(
  void);

// Empty the GSet with GSetEmpty() and free the memory it used.
// Input:
//   that: the GSet to be freed
void GSetFree(
  struct GSet** const that);

// Empty the GSet. Memory used by data in it is not freed.
// To empty the GSet and free data the data in it, use GSet<N>Flush() instead.
// Input:
//   that: the GSet
void GSetEmpty(
  struct GSet* const that);

// Add data at the head of the GSet
// Inputs:
//   that: the GSet
//   data: the data to add
void GSetPush(
  struct GSet* const that,
         void* const data);

// Remove and return the data at the head of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data
void* GSetPop(
  struct GSet* const that);

// ================== Typed GSet  =========================

// Declare a typed GSet containing data of type T and name GSet<N>
// A function void <N>Free(T**) must exists to free the data of type T in the
// GSet<N>
#define DefineGSet(N, T)                                               \
  struct GSet ## N { struct GSet s; };                                 \
  static inline struct GSet ## N GSet ## N ## Create(void)             \
    {return (struct GSet ## N ){.s=GSetCreate()};}                     \
  static inline struct GSet ## N * GSet ## N ## Alloc(void)            \
    {return (struct GSet ## N *)GSetAlloc();}                          \
  static inline void GSet ## N ## Free(struct GSet ## N ** const that) \
    {GSetFree((struct GSet**)that);}                                   \
  static inline void GSet ## N ## Empty(struct GSet ## N * const that) \
    {GSetEmpty((struct GSet*)that);}                                   \
  static inline void GSet ## N ## Push(                                \
    struct GSet ## N * const that, T * data)                           \
    {GSetPush((struct GSet*)that, (void*)data);}                       \
  static inline T * GSet ## N ## Pop(struct GSet ## N * const that)    \
    {return (T *)GSetPop((struct GSet*)that);}                         \

// Define typed GSets
DefineGSet(Int, int)
DefineGSet(Long, long)
DefineGSet(Float, float)
DefineGSet(Double, double)
DefineGSet(UInt, unsigned int)
DefineGSet(ULong, unsigned long)
DefineGSet(Str, char*)

// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
