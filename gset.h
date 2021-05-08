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

// Add data at the tail of the GSet
// Inputs:
//   that: the GSet
//   data: the data to add
void GSetAdd(
  struct GSet* const that,
         void* const data);

// Remove and return the data at the head of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetPop(
  struct GSet* const that);

// Remove and return the data at the tail of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetDrop(
  struct GSet* const that);

// Remove and return the data of the current element of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetPick(
  struct GSet* const that);

// Reset the current element of the iterator according to the direction
// of the iteration.
// Input:
//   that: the GSet
void GSetIterReset(
  struct GSet* const that);

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
  struct GSet* const that);

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
  static inline void GSet ## N ## Add(                                 \
    struct GSet ## N * const that, T * data)                           \
    {GSetAdd((struct GSet*)that, (void*)data);}                        \
  static inline T * GSet ## N ## Pop(struct GSet ## N * const that)    \
    {return (T *)GSetPop((struct GSet*)that);}                         \
  static inline T * GSet ## N ## Drop(struct GSet ## N * const that)   \
    {return (T *)GSetDrop((struct GSet*)that);}                        \
  static inline T * GSet ## N ## Pick(struct GSet ## N * const that)   \
    {return (T *)GSetPick((struct GSet*)that);}                        \
  static inline void GSet ## N ## IterReset(                           \
    struct GSet ## N * const that)                                     \
    {GSetIterReset((struct GSet*)that);}                               \
  static inline bool GSet ## N ## IterNext(                            \
    struct GSet ## N * const that)                                     \
    {return GSetIterNext((struct GSet*)that);}                         \
  static inline bool GSet ## N ## IterPrev(                            \
    struct GSet ## N * const that)                                     \
    {return GSetIterPrev((struct GSet*)that);}                         \
  static inline void GSet ## N ## Flush(struct GSet ## N * const that) \
    {T * d=NULL; while(that->s.size>0){                                \
    d=GSet ## N ## Pop(that);N ## Free(&d);}}                          \

// Define typed GSets
static inline void IntFree(int** const that) {
  if (that == NULL || *that == NULL) {return;} free(*that); *that = NULL;
}
DefineGSet(Int, int)
static inline void LongFree(long** const that) {
  if (that == NULL || *that == NULL) {return;} free(*that); *that = NULL;
}
DefineGSet(Long, long)
static inline void FloatFree(float** const that) {
  if (that == NULL || *that == NULL) {return;} free(*that); *that = NULL;
}
DefineGSet(Float, float)
static inline void DoubleFree(double** const that) {
  if (that == NULL || *that == NULL) {return;} free(*that); *that = NULL;
}
DefineGSet(Double, double)
static inline void UIntFree(unsigned int** const that) {
  if (that == NULL || *that == NULL) {return;} free(*that); *that = NULL;
}
DefineGSet(UInt, unsigned int)
static inline void ULongFree(unsigned long** const that) {
  if (that == NULL || *that == NULL) {return;} free(*that); *that = NULL;
}
DefineGSet(ULong, unsigned long)
static inline void StrFree(char*** const that) {
  if (that == NULL || *that == NULL) {return;} free(*that); *that = NULL;
}
DefineGSet(Str, char*)

// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
