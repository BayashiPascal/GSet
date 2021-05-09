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

// Copy a GSet, the data in elements are not clone, they are shared by both
// the original GSet and the clone GSet
// Input:
//   that: the GSet to be cloned
// Output:
//   Return the copy of the GSet
struct GSet GSetCopy( 
  struct GSet* const that);

// Clone a GSet, the data in elements are not clone, they are shared by both
// the original GSet and the clone GSet
// Input:
//   that: the GSet to be cloned
// Output:
//   Return the clone GSet
struct GSet* GSetClone( 
  struct GSet* const that);

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

// Sort the elements of a GSet
// Inputs:
//   that: the GSet to sort
//   cmp: the comparison function used to sort
// It uses qsort, see man page for details. Elements are sorted in ascending
// order, relative to the comparison function cmp(a,b) which much returns
// a negative value if a<b, a positive value if a>b, and 0 if a=b
void GSetSort(
  struct GSet* const that,
                 int (*cmp)(void const*, void const*));

// Shuffle the elements of a GSet
// Input:
//   that: the GSet to sort
void GSetShuffle(
  struct GSet* const that);

// Convert the GSet to an array of pointers to its data
// Input:
//   that: the GSet to sort
// Output:
//   Return an array of pointers to data in the same order as the current
//   element order
void** GSetToArrayPtr(
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
// A function void <N>Free(T** d) must exists to free the data of type T in the
// GSet<N> pointed to by *d
#define DefineGSet(N, T)                                               \
  struct GSet ## N { struct GSet s; };                                 \
  static inline struct GSet ## N GSet ## N ## Create(void)             \
    {return (struct GSet ## N ){.s=GSetCreate()};}                     \
  static inline struct GSet ## N * GSet ## N ## Alloc(void)            \
    {return (struct GSet ## N *)GSetAlloc();}                          \
  static inline struct GSet ## N GSet ## N ## Copy(                    \
    struct GSet ## N * const that)                                     \
    {return (struct GSet ## N ){.s=GSetCopy((struct GSet*)that)};}     \
  static inline struct GSet ## N * GSet ## N ## Clone(                 \
    struct GSet ## N * const that)                                     \
    {return (struct GSet ## N *)GSetClone((struct GSet*)that);}        \
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
  void N ## Free(T ** const that);                                     \
  static inline void GSet ## N ## Flush(struct GSet ## N * const that) \
    {T * d=NULL; while(that->s.size>0){                                \
    d=GSet ## N ## Pop(that);N ## Free(&d);}}                          \
  static inline void GSet ## N ## Sort(                                \
    struct GSet ## N * const that,                                     \
    int (*cmp)(void const*, void const*))                              \
    {GSetSort((struct GSet*)that, cmp);}                               \
  static inline void GSet ## N ## Shuffle(                             \
    struct GSet ## N * const that)                                     \
    {GSetShuffle((struct GSet*)that);}                                 \
  static inline T ** GSet ## N ## ToArrayPtr(                          \
    struct GSet ## N * const that)                                     \
    {return (T **)GSetToArrayPtr((struct GSet*)that);}                 \
  static inline T * GSet ## N ## ToArrayData(                          \
    struct GSet ## N * const that) {                                   \
    T ** ptrs = (T**)GSetToArrayPtr((struct GSet*)that);               \
    T * arr = malloc(sizeof(T) * that->s.size);                        \
    if (arr == NULL) Raise(TryCatchExc_MallocFailed);                  \
    for (int i; i<that->s.size; ++i) arr[i] = *(ptrs[i]);              \
    free(ptrs); return arr;}                                           \

// Define some default typed GSets
DefineGSet(Int, int)
DefineGSet(Long, long)
DefineGSet(Float, float)
DefineGSet(Double, double)
DefineGSet(UInt, unsigned int)
DefineGSet(ULong, unsigned long)
DefineGSet(Str, char*)

// Comparison function for the default typed GSets
int GSetIntCmp(void const* a, void const* b);
int GSetLongCmp(void const* a, void const* b);
int GSetFloatCmp(void const* a, void const* b);
int GSetDoubleCmp(void const* a, void const* b);
int GSetUIntCmp(void const* a, void const* b);
int GSetULongCmp(void const* a, void const* b);
int GSetStrCmp(void const* a, void const* b);

// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
