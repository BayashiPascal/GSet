// ------------------ gset.h ------------------

// Guard against multiple inclusions
#ifndef _GSET_
#define _GSET_

// Include external modules header
#include <stdlib.h>
#include <stdbool.h>
#include <TryCatchC/trycatchc.h>

// ================== Macros =========================

// Loop on each data Data (of type Type) of the GSet Set.
// The current data can be accessed through the variable <Data>,
// and its index with GSetIterIdx(). Uses Set's iterator, which is first
// reset, to iterate on the data.
// !! typeof is a gcc keyword !!
#define GSetForEach(Data, Set)                       \
  GSetIterReset((Set)->s);                           \
  if (GSetGetSize((Set)->s) > 0) for (               \
    typeof((Set)->t)* Data = GSetCurData((Set)->s);  \
    GSetIterEnded((Set)->s) == false;                \
    GSetIterNext((Set)->s),                          \
    Data = GSetCurData((Set)->s))

// ================== Private type declarations =========================

// Structure of a GSet
struct GSet;

// ================== Public type definitions =========================

// Type of iteration on the set
enum GSetIteration {

  GSetIteration_forward,
  GSetIteration_backward,

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

// Copy a GSet into another GSet
// Inputs:
//   that: the GSet
//    tho: the other GSet
// Output:
//   tho is first emptied and then filled with elements whose data is the
//   the data of the elements of that, in same order
void GSetCopy( 
        struct GSet* const that,
  struct GSet const* const tho);

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
//   that: the GSet to shuffle
void GSetShuffle(
  struct GSet* const that);

// Convert the GSet to an array of pointers to its data
// Input:
//   that: the GSet to convert
// Output:
//   Return an array of pointers to data in the same order as the current
//   element order
void** GSetToArrayOfPtr(
  struct GSet* const that);

// Convert an array of pointers to a GSet
// Inputs:
//   that: the GSet
//    arr: the array to convert
//   size: the size of the array
// Output:
//   The GSet is first emptied and then filled with elements whose data is the
//   pointers in the array in the order of the array
void GSetFromArrayOfPtr(
  struct GSet* const that,
        void** const arr,
        size_t const size);

// Append a GSet at the end of another GSet
// Inputs:
//   that: the GSet
//    tho: the other GSet
// Output:
//   tho is appended at the end of that and becomes empty after this operation
void GSetAppend(
  struct GSet* const that,
  struct GSet* const tho);

// Get the data of the current element in the GSet
// Input:
//   that: the GSet
// Output:
//   Return the pointer to the data of the current element
void* GSetCurData(
  struct GSet const* const that);

// Get the size of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the size of the data set
size_t GSetGetSize(
  struct GSet const* const that);

// Reset the current element of the iterator according to the direction
// of the iteration.
// Input:
//   that: the GSet
void GSetIterReset(
  struct GSet* const that);

// Get the index of the current element of the iterator according to the
// direction of the iteration.
// Input:
//   that: the GSet
// Output:
//   Return the index
size_t GSetIterIdx(
  struct GSet const* const that);

// Get the flag about the end of iteration.
// Input:
//   that: the GSet
// Output:
//   Return the flag
bool GSetIterEnded(
  struct GSet const* const that);

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

// Set the iteration type of a GSet
// Inputs:
//        that: the GSet
//   iteration: the type of iteration
void GSetIterSet(
        struct GSet* const that,
  enum GSetIteration const iteration);

// ================== Typed GSet  =========================

// Declare a typed GSet containing data of type T and name GSet<N>
// A function void <N>Free(T** d) must exists to free the data of type T in the
// GSet<N> pointed to by *d
// The function GSet<N>FromArrayOfData empty the GSet in argument and then
// fill it with elements whose data is a pointer to the array's element in the
//  order of the array
#define DefineGSet(N, T)                                                 \
  struct GSet ## N { struct GSet* s; T t;};                              \
  static inline struct GSet ## N GSet ## N ## Create(void)               \
    {return (struct GSet ## N ){.s=GSetAlloc()};}                        \
  static inline struct GSet ## N * GSet ## N ## Alloc(void)              \
    {struct GSet ## N * that = malloc(sizeof(struct GSet ## N));         \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                   \
    *that = GSet ## N ## Create(); return that;}                         \
  static inline void GSet ## N ## Copy(                                  \
    struct GSet ## N * const that, struct GSet ## N const* const tho)    \
    {GSetCopy(that->s, tho->s);}                                         \
  static inline void GSet ## N ## Free(struct GSet ## N ** const that)   \
    {if(that == NULL || *that == NULL) return;                           \
    GSetFree(&((*that)->s));                                             \
    free(*that); *that = NULL;}                                          \
  static inline void GSet ## N ## Release(struct GSet ## N * const that) \
    {if(that == NULL) return; GSetFree(&(that->s));}                     \
  static inline void GSet ## N ## Empty(struct GSet ## N * const that)   \
    {GSetEmpty(that->s);}                                                \
  static inline void GSet ## N ## Push(                                  \
    struct GSet ## N * const that, T * data)                             \
    {GSetPush(that->s, (void*)data);}                                    \
  static inline void GSet ## N ## Add(                                   \
    struct GSet ## N * const that, T * data)                             \
    {GSetAdd(that->s, (void*)data);}                                     \
  static inline T * GSet ## N ## Pop(struct GSet ## N * const that)      \
    {return (T *)GSetPop(that->s);}                                      \
  static inline T * GSet ## N ## Drop(struct GSet ## N * const that)     \
    {return (T *)GSetDrop(that->s);}                                     \
  static inline T * GSet ## N ## Pick(struct GSet ## N * const that)     \
    {return (T *)GSetPick(that->s);}                                     \
  static inline void GSet ## N ## IterReset(                             \
    struct GSet ## N * const that)                                       \
    {GSetIterReset(that->s);}                                            \
  static inline size_t GSet ## N ## IterIdx(                             \
    struct GSet ## N const* const that)                                  \
    {return GSetIterIdx(that->s);}                                       \
  static inline bool GSet ## N ## IterEnded(                             \
    struct GSet ## N const* const that)                                  \
    {return GSetIterEnded(that->s);}                                     \
  static inline bool GSet ## N ## IterNext(                              \
    struct GSet ## N * const that)                                       \
    {return GSetIterNext(that->s);}                                      \
  static inline bool GSet ## N ## IterPrev(                              \
    struct GSet ## N * const that)                                       \
    {return GSetIterPrev(that->s);}                                      \
  void N ## Free(T ** const that);                                       \
  static inline void GSet ## N ## Flush(struct GSet ## N * const that)   \
    {T * d=NULL; while(GSetGetSize(that->s)>0){                          \
    d=GSet ## N ## Pop(that);N ## Free(&d);}}                            \
  static inline void GSet ## N ## Sort(                                  \
    struct GSet ## N * const that,                                       \
    int (*cmp)(void const*, void const*))                                \
    {GSetSort(that->s, cmp);}                                            \
  static inline void GSet ## N ## Shuffle(                               \
    struct GSet ## N * const that)                                       \
    {GSetShuffle(that->s);}                                              \
  static inline T ** GSet ## N ## ToArrayOfPtr(                          \
    struct GSet ## N * const that)                                       \
    {return (T **)GSetToArrayOfPtr(that->s);}                            \
  static inline T * GSet ## N ## ToArrayOfData(                          \
    struct GSet ## N * const that) {                                     \
    if (GSetGetSize(that->s) == 0) return NULL;                          \
    T ** ptrs = (T**)GSetToArrayOfPtr(that->s);                          \
    T * arr = malloc(sizeof(T) * GSetGetSize(that->s));                  \
    if (arr == NULL) Raise(TryCatchExc_MallocFailed);                    \
    for (size_t i = 0; i < GSetGetSize(that->s); ++i)                    \
    {arr[i] = *(ptrs[i]);} free(ptrs); return arr;}                      \
  static inline void GSet ## N ## FromArrayOfPtr(                        \
    struct GSet ## N * const that, T** const arr, size_t size)           \
    {GSetFromArrayOfPtr(that->s, (void**)arr, size);}                    \
  static inline void GSet ## N ## FromArrayOfData(                       \
    struct GSet ## N * const that, T* const arr, size_t size)            \
    {GSetEmpty(that->s);                                                 \
    for(size_t i = 0; i < size; ++i)                                     \
    GSetAdd(that->s, arr + i);}                                          \
  static inline void GSet ## N ## Append(                                \
    struct GSet ## N * const that,                                       \
    struct GSet ## N * const tho)                                        \
    {GSetAppend(that->s, tho->s);}                                       \
  static inline T * GSet ## N ## CurData(                                \
    struct GSet ## N const * const that)                                 \
    {return (T *)GSetCurData(that->s);}                                  \
  static inline size_t GSet ## N ## GetSize(                             \
    struct GSet ## N const * const that)                                 \
    {return GSetGetSize(that->s);}                                       \
  static inline void GSet ## N ## IterSet(                               \
    struct GSet ## N * const that, enum GSetIteration const iteration)   \
    {GSetIterSet(that->s, iteration);}                                   \

// Define some default typed GSets
DefineGSet(Int, int)
DefineGSet(Long, long)
DefineGSet(Float, float)
DefineGSet(Double, double)
DefineGSet(UInt, unsigned int)
DefineGSet(ULong, unsigned long)
DefineGSet(Str, char)

// Comparison functions for the default typed GSets
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
