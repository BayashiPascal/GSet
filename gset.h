// ------------------ gset.h ------------------

// Guard against multiple inclusions
#ifndef GSET_H
#define GSET_H

// Include external modules header
#include <stdlib.h>
#include <stdbool.h>
#include <TryCatchC/trycatchc.h>

// ================== Type declarations =========================

enum GSetIterType {

  GSetIterForward,
  GSetIterBackward,

};
typedef enum GSetIterType GSetIterType;

// Structure of a set and its iterators
struct GSet;
struct GSetIter;
typedef struct GSet GSet;
typedef struct GSetIter GSetIter;

// ================= Public functions declarations ======================

// Function to get the commit id of the library
// Output:
//   Return a string containing the result of `git rev-parse HEAD` at
//   compilation time
char const* GSetGetCommitId(
  void);

// Allocate memory for a new GSet
// Output:
//   Return the new GSet.
GSet* GSetAlloc(
  void);

// Empty the GSet with GSetEmpty() and free the memory it used.
// Input:
//   that: the GSet to be freed
void GSetFree_(
  GSet** const that);

// Push data at the head of the set
// Inputs:
//   that: the set
//   data: the data
#define GSETPUSH_(N, T)     \
void GSetPush_ ## N(        \
  GSet* const that,         \
             T const data)
GSETPUSH_(Char, char);
GSETPUSH_(UChar, unsigned char);
GSETPUSH_(Int, int);
GSETPUSH_(UInt, unsigned int);
GSETPUSH_(Long, long);
GSETPUSH_(ULong, unsigned long);
GSETPUSH_(Float, float);
GSETPUSH_(Double, double);
GSETPUSH_(Ptr, void*);

// Push an array of data at the head of the set
// Inputs:
//   that: the set
//   arr: the array of data
#define GSETPUSHARR_(N, T)    \
void GSetPushArr_ ## N(       \
     GSet* const that,        \
    size_t const size,        \
  T const* const arr)
GSETPUSHARR_(Char, char);
GSETPUSHARR_(UChar, unsigned char);
GSETPUSHARR_(Int, int);
GSETPUSHARR_(UInt, unsigned int);
GSETPUSHARR_(Long, long);
GSETPUSHARR_(ULong, unsigned long);
GSETPUSHARR_(Float, float);
GSETPUSHARR_(Double, double);
GSETPUSHARR_(Ptr, void);

// Add data at the tail of the set
// Inputs:
//   that: the set
//   data: the data
#define GSETADD_(N, T)     \
void GSetAdd_ ## N(        \
  GSet* const that,        \
      T const data)
GSETADD_(Char, char);
GSETADD_(UChar, unsigned char);
GSETADD_(Int, int);
GSETADD_(UInt, unsigned int);
GSETADD_(Long, long);
GSETADD_(ULong, unsigned long);
GSETADD_(Float, float);
GSETADD_(Double, double);
GSETADD_(Ptr, void*);

// Add an array of data at the tail of the set
// Inputs:
//   that: the set
//   arr: the array of data
#define GSETADDARR_(N, T)        \
void GSetAddArr_ ## N(           \
     GSet* const that,           \
    size_t const size,           \
  T const* const arr)
GSETADDARR_(Char, char);
GSETADDARR_(UChar, unsigned char);
GSETADDARR_(Int, int);
GSETADDARR_(UInt, unsigned int);
GSETADDARR_(Long, long);
GSETADDARR_(ULong, unsigned long);
GSETADDARR_(Float, float);
GSETADDARR_(Double, double);
GSETADDARR_(Ptr, void);

// Add data before the current position of an iterator
// Inputs:
//   that: the set iterator
//   data: the data
#define GSETITERADDBEFORE_(N, T)                \
void GSetIterAddBefore_ ## N(                   \
  GSetIter* const that,                         \
          T const data,                         \
      GSet* const set)
GSETITERADDBEFORE_(Char, char);
GSETITERADDBEFORE_(UChar, unsigned char);
GSETITERADDBEFORE_(Int, int);
GSETITERADDBEFORE_(UInt, unsigned int);
GSETITERADDBEFORE_(Long, long);
GSETITERADDBEFORE_(ULong, unsigned long);
GSETITERADDBEFORE_(Float, float);
GSETITERADDBEFORE_(Double, double);
GSETITERADDBEFORE_(Ptr, void*);

// Pop data from the head of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the head of the set and return it
#define GSETPOP_(N, T)     \
T GSetPop_ ## N(           \
  GSet* const that)
GSETPOP_(Char, char);
GSETPOP_(UChar, unsigned char);
GSETPOP_(Int, int);
GSETPOP_(UInt, unsigned int);
GSETPOP_(Long, long);
GSETPOP_(ULong, unsigned long);
GSETPOP_(Float, float);
GSETPOP_(Double, double);
GSETPOP_(Ptr, void*);

// Drop data from the tail of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the tail of the set and return it
#define GSETDROP_(N, T)     \
T GSetDrop_ ## N(           \
  GSet* const that)
GSETDROP_(Char, char);
GSETDROP_(UChar, unsigned char);
GSETDROP_(Int, int);
GSETDROP_(UInt, unsigned int);
GSETDROP_(Long, long);
GSETDROP_(ULong, unsigned long);
GSETDROP_(Float, float);
GSETDROP_(Double, double);
GSETDROP_(Ptr, void*);

// Append data from a set to the end of another
// Input:
//   that: the set where data are added
//   tho: the set containing data to add
void GSetAppend_(
        GSet* const that,
  GSet const* const tho);

// Merge a set into another. The merged set is empty after this operation
// Input:
//   that: the extended set
//   tho: the merged set
void GSetMerge_(
  GSet* const that,
  GSet* const tho);

// Return the number of element in the set
// Input:
//   that: the set
// Output:
//   Return the number of element.
size_t GSetGetSize_(
  GSet const* const that);

// Empty the set. Memory used by data in it is not freed.
// To empty the set and free data, use GSet<N>Flush() instead.
// Input:
//   that: the set
void GSetEmpty_(
  GSet* const that);

// Shuffle the set
// Input:
//   that: the set
void GSetShuffle_(
  GSet* const that);

// Sort the elements of a GSet
// Inputs:
//   that: the set to sort
//    cmp: the comparison function used to sort
//    inc: if true the set is sort in increasing order, else in decreasing
//         order
// It uses qsort, see man page for details. Elements are sorted in ascending
// order, relative to the comparison function cmp(a,b) which much returns
// a negative value if a<b, a positive value if a>b, and 0 if a=b
#define GSETSORT_(N, T)                                 \
void GSetSort_ ## N(                                    \
  GSet* const that,                                     \
          int (* const cmp)(void const*, void const*),  \
         bool const inc)
GSETSORT_(Char, char);
GSETSORT_(UChar, unsigned char);
GSETSORT_(Int, int);
GSETSORT_(UInt, unsigned int);
GSETSORT_(Long, long);
GSETSORT_(ULong, unsigned long);
GSETSORT_(Float, float);
GSETSORT_(Double, double);
GSETSORT_(Ptr, void*);

// Allocate memory for a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
GSetIter* GSetIterAlloc(
  GSetIterType const type);

// Free the memory used by a GSetIter.
// Input:
//   that: the GSetIter to be freed
void GSetIterFree_(
  GSetIter** const that);

// Get the current data from a set
// Input:
//   that: the iterator
// Output:
//   Return the current data
#define GSETITERGET_(N, T)     \
T GSetIterGet_ ## N(           \
  GSetIter const* const that)
GSETITERGET_(Char, char);
GSETITERGET_(UChar, unsigned char);
GSETITERGET_(Int, int);
GSETITERGET_(UInt, unsigned int);
GSETITERGET_(Long, long);
GSETITERGET_(ULong, unsigned long);
GSETITERGET_(Float, float);
GSETITERGET_(Double, double);
GSETITERGET_(Ptr, void*);

// Pick the current data from a set
// Input:
//   that: the set
//   set: the associated set
// Output:
//   Remove the data at the head of the set and return it
#define GSETITERPICK_(N, T)    \
T GSetIterPick_ ## N(          \
  GSetIter* const that,        \
  GSet* const set)
GSETITERPICK_(Char, char);
GSETITERPICK_(UChar, unsigned char);
GSETITERPICK_(Int, int);
GSETITERPICK_(UInt, unsigned int);
GSETITERPICK_(Long, long);
GSETITERPICK_(ULong, unsigned long);
GSETITERPICK_(Float, float);
GSETITERPICK_(Double, double);
GSETITERPICK_(Ptr, void*);

// Reset the iterator to its first element
// Input:
//   that: the iterator
//    set: the associated set
void GSetIterReset_(
    GSetIter* const that,
  GSet const* const set);

// Check if the iterator is ready
// Input:
//   that: the iterator
// Output:
//   Return true if the iterator is on an element of its set, false else
//   (either it's because the set is empty, or the iterator's filter has
//   no matching element in the set)
bool GSetIterIsReady_(
    GSetIter* const that);

// Move the iterator to the next element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator could move to the next element, else false
bool GSetIterNext_(
  GSetIter* const that);

// Move the iterator to the previous element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator could move to the previous element, else false
bool GSetIterPrev_(
  GSetIter* const that);

// Check if an iterator is on its first element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator is on its first element, else false
bool GSetIterIsFirst_(
  GSetIter* const that);

// Check if an iterator is on its last element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator is on its last element, else false
bool GSetIterIsLast_(
  GSetIter* const that);

// Clone an iterator
// Input:
//   that: the iterator
// Output:
//   Return a clone of the iterator
GSetIter* GSetIterClone_(
  GSetIter const* const that);

// Set the type of an iterator
// Input:
//   that: the iterator
//   type: the type
void GSetIterSetType_(
     GSetIter* const that,
  GSetIterType const type);

// Get the type of an iterator
// Input:
//   that: the iterator
// Return the type of the iterator
GSetIterType GSetIterGetType_(
  GSetIter const* const that);

// Set the filter of an iterator
// Inputs:
//     that: the iterator
//      fun: the filter's function
//   params: the parameters of the filter's function
typedef bool (*GSetIterFilterFun)(
  void*,
  void*);
void GSetIterSetFilter_(
    GSetIter* const that,
  GSetIterFilterFun fun,
              void* params);

// Get the filter's function parameters
// Input:
//     that: the iterator
// Output:
//   Return the parameters of the filter's function
void* GSetIterGetFilterParam_(
  GSetIter* const that);

// Count the number of elements enumerated by an iterator
// Inputs:
//   that: the iterator
//    set: the set
// Output:
//   Return the number of elements
size_t GSetIterCount_(
  GSetIter const* const that,
      GSet const* const set);

// ================== Typed GSet code auto generation  ======================

// Declare a typed GSet containing data of type Type and name GSet<Name>
#define DEFINEGSETBASE(Name, Type)                                           \
  struct GSet ## Name {                                                      \
    GSet* s;                                                                 \
    Type t;                                                                  \
  };                                                                         \
  typedef struct GSet ## Name GSet ## Name;                                  \
  static inline GSet ## Name* GSet ## Name ## Alloc(                         \
    void) {                                                                  \
    GSet ## Name* that = malloc(sizeof(GSet ## Name));                       \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    Try {                                                                    \
      *that = (GSet ## Name ) { .s = GSetAlloc() };                          \
    } CatchDefault {                                                         \
      free(that); Raise(TryCatchExc_MallocFailed);                           \
    } EndCatchDefault;                                                       \
    return that;                                                             \
  }                                                                          \
  static inline GSet ## Name* GSet ## Name ## FromArr(                       \
    size_t const size,                                                       \
    Type const* const arr) {                                                 \
    GSet ## Name* that = GSet ## Name ## Alloc();                            \
    _Generic((that->t),                                                      \
      char: GSetAddArr_Char,                                                 \
      unsigned char: GSetAddArr_UChar,                                       \
      int: GSetAddArr_Int,                                                   \
      unsigned int: GSetAddArr_UInt,                                         \
      long: GSetAddArr_Long,                                                 \
      unsigned long: GSetAddArr_ULong,                                       \
      float: GSetAddArr_Float,                                               \
      double: GSetAddArr_Double,                                             \
      char const: GSetAddArr_Char,                                           \
      unsigned char const: GSetAddArr_UChar,                                 \
      int const: GSetAddArr_Int,                                             \
      unsigned int const: GSetAddArr_UInt,                                   \
      long const: GSetAddArr_Long,                                           \
      unsigned long const: GSetAddArr_ULong,                                 \
      float const: GSetAddArr_Float,                                         \
      double const: GSetAddArr_Double,                                       \
      default: GSetAddArr_Ptr)(that->s, size, arr);                          \
    return that;                                                             \
  }                                                                          \
  struct GSetIter ## Name {                                                  \
    GSet ## Name* set;                                                       \
    GSetIter* i;                                                             \
  };                                                                         \
  typedef struct GSetIter ## Name GSetIter ## Name;                          \
  static inline GSetIter ## Name* GSetIter ## Name ## Alloc(                 \
    GSet ## Name* const set) {                                               \
    GSetIter ## Name* that = malloc(sizeof(GSetIter ## Name));               \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    Try {                                                                    \
      *that =                                                                \
        (GSetIter ## Name ) {                                                \
          .set = set, .i = GSetIterAlloc(GSetIterForward)                    \
        };                                                                   \
    } CatchDefault {                                                         \
      free(that); Raise(TryCatchExc_MallocFailed);                           \
    } EndCatchDefault;                                                       \
    GSetIterReset_(that->i, set->s);                                         \
    return that;                                                             \
  }                                                                          \
  static inline GSetIter ## Name* GSetIter ## Name ## Clone(                 \
    GSetIter ## Name const* const that) {                                    \
    GSetIter ## Name* clone = malloc(sizeof(GSetIter ## Name));              \
    if (clone == NULL) Raise(TryCatchExc_MallocFailed);                      \
    Try {                                                                    \
      *clone = (GSetIter ## Name)                                            \
        { .set = that->set, .i = GSetIterClone_(that->i) };                  \
    } CatchDefault {                                                         \
      free(clone); Raise(TryCatchExc_MallocFailed);                          \
    } EndCatchDefault;                                                       \
    return clone;                                                            \
  }                                                                          \
  static inline Type* GSetIter ## Name ## ToArr(                             \
    GSetIter ## Name const* const that) {                                    \
    size_t size = GSetIterCount_(that->i, that->set->s);                     \
    if (size == 0) return NULL;                                              \
    Type* arr = malloc(sizeof(Type) * size);                                 \
    if (arr == NULL) Raise(TryCatchExc_MallocFailed);                        \
    GSetIter* iter = NULL;                                                   \
    Try {                                                                    \
      iter = GSetIterClone_(that->i);                                        \
      GSetIterReset_(iter, that->set->s);                                    \
      size_t i = 0;                                                          \
      do {                                                                   \
        arr[i] =                                                             \
          _Generic((that->set->t),                                           \
            char: GSetIterGet_Char,                                          \
            unsigned char: GSetIterGet_UChar,                                \
            int: GSetIterGet_Int,                                            \
            unsigned int: GSetIterGet_UInt,                                  \
            long: GSetIterGet_Long,                                          \
            unsigned long: GSetIterGet_ULong,                                \
            float: GSetIterGet_Float,                                        \
            double: GSetIterGet_Double,                                      \
            default: GSetIterGet_Ptr)(iter);                                 \
        ++i;                                                                 \
      } while(GSetIterNext_(iter));                                          \
    } CatchDefault {                                                         \
      free(arr); GSetIterFree_(&iter);                                       \
      Raise(TryCatchGetLastExc());                                           \
    } EndCatchDefault;                                                       \
    GSetIterFree_(&iter);                                                    \
    return arr;                                                              \
  }

#define GSETDEF(Name, Type)                                                  \
  DEFINEGSETBASE(Name, Type)                                                 \
  void Name ## Free(Type* const that);                                       \
  static inline void GSet ## Name ## Flush(                                  \
    GSet ## Name* const that) {                                              \
    Type d = NULL;                                                           \
    while (GSetGetSize_(that->s) > 0) {                                      \
      d = GSetPop_Ptr(that->s);                                              \
      Name ## Free(&d);                                                      \
    }                                                                        \
  }

DEFINEGSETBASE(Char, char)
DEFINEGSETBASE(UChar, unsigned char)
DEFINEGSETBASE(Int, int)
DEFINEGSETBASE(UInt, unsigned int)
DEFINEGSETBASE(Long, long)
DEFINEGSETBASE(ULong, unsigned long)
DEFINEGSETBASE(Float, float)
DEFINEGSETBASE(Double, double)
GSETDEF(CharPtr, char*)
#define GSetStr GSetCharPtr
#define GSetStrAlloc GSetCharPtrAlloc
#define GSetStrFree GSetCharPtrFree
#define GSetStrFromArr GSetCharPtrFromArr
#define GSetStrFlush GSetCharPtrFlush
#define GSetIterStr GSetIterCharPtr
#define GSetIterStrAlloc GSetIterCharPtrAlloc
#define GSetIterStrClone GSetIterCharPtrClone
#define GSetIterStrFree GSetIterCharPtrFree
#define GSetIterStrToArr GSetIterCharPtrToArr
GSETDEF(UCharPtr, unsigned char*)
GSETDEF(IntPtr, int*)
GSETDEF(UIntPtr, unsigned int*)
GSETDEF(LongPtr, long*)
GSETDEF(ULongPtr, unsigned long*)
GSETDEF(FloatPtr, float*)
GSETDEF(DoublePtr, double*)

// ================== Polymorphism  ======================

#define GSetGetSize(PtrToSet) GSetGetSize_((PtrToSet)->s)
#define GSetShuffle(PtrToSet) GSetShuffle_((PtrToSet)->s)
#define GSetEmpty(PtrToSet) GSetEmpty_((PtrToSet)->s)

#define GSetFree(PtrToPtrToSet)                                              \
  if (((PtrToPtrToSet) != NULL) && (*(PtrToPtrToSet) != NULL)) {             \
    GSetFree_(&((*(PtrToPtrToSet))->s));                                     \
    free(*(PtrToPtrToSet));                                                  \
    *(PtrToPtrToSet) = NULL;                                                 \
  }

#define GSetPush(PtrToSet, Data)                                             \
  do {                                                                       \
    _Generic((PtrToSet),                                                     \
      GSetChar*: GSetPush_Char,                                              \
      GSetUChar*: GSetPush_UChar,                                            \
      GSetInt*: GSetPush_Int,                                                \
      GSetUInt*: GSetPush_UInt,                                              \
      GSetLong*: GSetPush_Long,                                              \
      GSetULong*: GSetPush_ULong,                                            \
      GSetFloat*: GSetPush_Float,                                            \
      GSetDouble*: GSetPush_Double,                                          \
      default: GSetPush_Ptr)((PtrToSet)->s, Data);                           \
    (PtrToSet)->t = Data;                                                    \
  } while (false)

#define GSetPushArr(PtrToSet, Size, Arr)                                     \
  do {                                                                       \
    _Generic((PtrToSet),                                                     \
      GSetChar*: GSetPushArr_Char,                                           \
      GSetUChar*: GSetPushArr_UChar,                                         \
      GSetInt*: GSetPushArr_Int,                                             \
      GSetUInt*: GSetPushArr_UInt,                                           \
      GSetLong*: GSetPushArr_Long,                                           \
      GSetULong*: GSetPushArr_ULong,                                         \
      GSetFloat*: GSetPushArr_Float,                                         \
      GSetDouble*: GSetPushArr_Double,                                       \
      default: GSetPushArr_Ptr)((PtrToSet)->s, Size, Arr);                   \
    (PtrToSet)->t = *(Arr);                                                  \
  } while (false)

#define GSetAdd(PtrToSet, Data)                                              \
  do {                                                                       \
    _Generic((PtrToSet),                                                     \
      GSetChar*: GSetAdd_Char,                                               \
      GSetUChar*: GSetAdd_UChar,                                             \
      GSetInt*: GSetAdd_Int,                                                 \
      GSetUInt*: GSetAdd_UInt,                                               \
      GSetLong*: GSetAdd_Long,                                               \
      GSetULong*: GSetAdd_ULong,                                             \
      GSetFloat*: GSetAdd_Float,                                             \
      GSetDouble*: GSetAdd_Double,                                           \
      default: GSetAdd_Ptr)((PtrToSet)->s, Data);                            \
    (PtrToSet)->t = Data;                                                    \
  } while (false)

#define GSetAddArr(PtrToSet, Size, Arr)                                      \
  do {                                                                       \
    _Generic((PtrToSet),                                                     \
      GSetChar*: GSetAddArr_Char,                                            \
      GSetUChar*: GSetAddArr_UChar,                                          \
      GSetInt*: GSetAddArr_Int,                                              \
      GSetUInt*: GSetAddArr_UInt,                                            \
      GSetLong*: GSetAddArr_Long,                                            \
      GSetULong*: GSetAddArr_ULong,                                          \
      GSetFloat*: GSetAddArr_Float,                                          \
      GSetDouble*: GSetAddArr_Double,                                        \
      default: GSetAddArr_Ptr)((PtrToSet)->s, Size, Arr);                    \
    (PtrToSet)->t = *(Arr);                                                  \
  } while (false)

#define GSetPop(PtrToSet)                                                    \
  (((PtrToSet)->t =                                                          \
     _Generic((PtrToSet),                                                    \
       GSetChar*: GSetPop_Char,                                              \
       GSetUChar*: GSetPop_UChar,                                            \
       GSetInt*: GSetPop_Int,                                                \
       GSetUInt*: GSetPop_UInt,                                              \
       GSetLong*: GSetPop_Long,                                              \
       GSetULong*: GSetPop_ULong,                                            \
       GSetFloat*: GSetPop_Float,                                            \
       GSetDouble*: GSetPop_Double,                                          \
       default: GSetPop_Ptr)((PtrToSet)->s)) == 0 ? 0 : (PtrToSet)->t)

#define GSetDrop(PtrToSet)                                                   \
  (((PtrToSet)->t =                                                          \
     _Generic((PtrToSet),                                                    \
       GSetChar*: GSetDrop_Char,                                             \
       GSetUChar*: GSetDrop_UChar,                                           \
       GSetInt*: GSetDrop_Int,                                               \
       GSetUInt*: GSetDrop_UInt,                                             \
       GSetLong*: GSetDrop_Long,                                             \
       GSetULong*: GSetDrop_ULong,                                           \
       GSetFloat*: GSetDrop_Float,                                           \
       GSetDouble*: GSetDrop_Double,                                         \
       default: GSetDrop_Ptr)((PtrToSet)->s)) == 0 ? 0 : (PtrToSet)->t)

void GSetAppendInvalidType(
  void*,
  void*);
#define GSetAppend(PtrToSetDst, PtrToSetSrc)                                 \
 _Generic((PtrToSetDst),                                                     \
   GSetChar*:                                                                \
     _Generic((PtrToSetSrc),                                                 \
       GSetChar*: GSetAppend_,                                               \
       GSetChar const*: GSetAppend_,                                         \
       default: GSetAppendInvalidType),                                      \
   GSetUChar*:                                                               \
     _Generic((PtrToSetSrc),                                                 \
       GSetUChar*: GSetAppend_,                                              \
       GSetUChar const*: GSetAppend_,                                        \
       default: GSetAppendInvalidType),                                      \
   GSetInt*:                                                                 \
     _Generic((PtrToSetSrc),                                                 \
       GSetInt*: GSetAppend_,                                                \
       GSetInt const*: GSetAppend_,                                          \
       default: GSetAppendInvalidType),                                      \
   GSetUInt*:                                                                \
     _Generic((PtrToSetSrc),                                                 \
       GSetUInt*: GSetAppend_,                                               \
       GSetUInt const*: GSetAppend_,                                         \
       default: GSetAppendInvalidType),                                      \
   GSetLong*:                                                                \
     _Generic((PtrToSetSrc),                                                 \
       GSetLong*: GSetAppend_,                                               \
       GSetLong const*: GSetAppend_,                                         \
       default: GSetAppendInvalidType),                                      \
   GSetULong*:                                                               \
     _Generic((PtrToSetSrc),                                                 \
       GSetULong*: GSetAppend_,                                              \
       GSetULong const*: GSetAppend_,                                        \
       default: GSetAppendInvalidType),                                      \
   GSetFloat*:                                                               \
     _Generic((PtrToSetSrc),                                                 \
       GSetFloat*: GSetAppend_,                                              \
       GSetFloat const*: GSetAppend_,                                        \
       default: GSetAppendInvalidType),                                      \
   GSetDouble*:                                                              \
     _Generic((PtrToSetSrc),                                                 \
       GSetDouble*: GSetAppend_,                                             \
       GSetDouble const*: GSetAppend_,                                       \
       default: GSetAppendInvalidType),                                      \
   default: _Generic((PtrToSetSrc),                                          \
     GSetChar*: GSetAppendInvalidType,                                       \
     GSetUChar*: GSetAppendInvalidType,                                      \
     GSetInt*: GSetAppendInvalidType,                                        \
     GSetUInt*: GSetAppendInvalidType,                                       \
     GSetLong*: GSetAppendInvalidType,                                       \
     GSetULong*: GSetAppendInvalidType,                                      \
     GSetFloat*: GSetAppendInvalidType,                                      \
     GSetDouble*: GSetAppendInvalidType,                                     \
     GSetChar const*: GSetAppendInvalidType,                                 \
     GSetUChar const*: GSetAppendInvalidType,                                \
     GSetInt const*: GSetAppendInvalidType,                                  \
     GSetUInt const*: GSetAppendInvalidType,                                 \
     GSetLong const*: GSetAppendInvalidType,                                 \
     GSetULong const*: GSetAppendInvalidType,                                \
     GSetFloat const*: GSetAppendInvalidType,                                \
     GSetDouble const*: GSetAppendInvalidType,                               \
     default: GSetAppend_))((PtrToSetDst)->s, (PtrToSetSrc)->s)

void GSetMergeInvalidType(
  void*,
  void*);
#define GSetMerge(PtrToSetDst, PtrToSetSrc)                                  \
 _Generic((PtrToSetDst),                                                     \
   GSetChar*:                                                                \
     _Generic((PtrToSetSrc),                                                 \
       GSetChar*: GSetMerge_,                                                \
       default: GSetMergeInvalidType),                                       \
   GSetUChar*:                                                               \
     _Generic((PtrToSetSrc),                                                 \
       GSetUChar*: GSetMerge_,                                               \
       default: GSetMergeInvalidType),                                       \
   GSetInt*:                                                                 \
     _Generic((PtrToSetSrc),                                                 \
       GSetInt*: GSetMerge_,                                                 \
       default: GSetMergeInvalidType),                                       \
   GSetUInt*:                                                                \
     _Generic((PtrToSetSrc),                                                 \
       GSetUInt*: GSetMerge_,                                                \
       default: GSetMergeInvalidType),                                       \
   GSetLong*:                                                                \
     _Generic((PtrToSetSrc),                                                 \
       GSetLong*: GSetMerge_,                                                \
       default: GSetMergeInvalidType),                                       \
   GSetULong*:                                                               \
     _Generic((PtrToSetSrc),                                                 \
       GSetULong*: GSetMerge_,                                               \
       default: GSetMergeInvalidType),                                       \
   GSetFloat*:                                                               \
     _Generic((PtrToSetSrc),                                                 \
       GSetFloat*: GSetMerge_,                                               \
       default: GSetMergeInvalidType),                                       \
   GSetDouble*:                                                              \
     _Generic((PtrToSetSrc),                                                 \
       GSetDouble*: GSetMerge_,                                              \
       default: GSetMergeInvalidType),                                       \
   default: _Generic((PtrToSetSrc),                                          \
     GSetChar*: GSetMergeInvalidType,                                        \
     GSetUChar*: GSetMergeInvalidType,                                       \
     GSetInt*: GSetMergeInvalidType,                                         \
     GSetUInt*: GSetMergeInvalidType,                                        \
     GSetLong*: GSetMergeInvalidType,                                        \
     GSetULong*: GSetMergeInvalidType,                                       \
     GSetFloat*: GSetMergeInvalidType,                                       \
     GSetDouble*: GSetMergeInvalidType,                                      \
     default: GSetMerge_))((PtrToSetDst)->s, (PtrToSetSrc)->s)

#define GSetSort(PtrToSet, CmpFun, FlagIncreasing)                           \
  _Generic((PtrToSet),                                                       \
    GSetChar*: GSetSort_Char,                                                \
    GSetUChar*: GSetSort_UChar,                                              \
    GSetInt*: GSetSort_Int,                                                  \
    GSetUInt*: GSetSort_UInt,                                                \
    GSetLong*: GSetSort_Long,                                                \
    GSetULong*: GSetSort_ULong,                                              \
    GSetFloat*: GSetSort_Float,                                              \
    GSetDouble*: GSetSort_Double,                                            \
    default: GSetSort_Ptr)((PtrToSet)->s, CmpFun, FlagIncreasing)

#define GSetIterFree(PtrToPtrToSetIter)                                      \
  if (((PtrToPtrToSetIter) != NULL) && (*(PtrToPtrToSetIter) != NULL)) {     \
    GSetIterFree_(&((*(PtrToPtrToSetIter))->i));                             \
    free(*(PtrToPtrToSetIter));                                              \
    *(PtrToPtrToSetIter) = NULL;                                             \
  }                                                                          \

#define GSetIterGet(PtrToSetIter)                                            \
  (((PtrToSetIter)->set->t =                                                 \
     _Generic((PtrToSetIter),                                                \
       GSetIterChar*: GSetIterGet_Char,                                      \
       GSetIterUChar*: GSetIterGet_UChar,                                    \
       GSetIterInt*: GSetIterGet_Int,                                        \
       GSetIterUInt*: GSetIterGet_UInt,                                      \
       GSetIterLong*: GSetIterGet_Long,                                      \
       GSetIterULong*: GSetIterGet_ULong,                                    \
       GSetIterFloat*: GSetIterGet_Float,                                    \
       GSetIterDouble*: GSetIterGet_Double,                                  \
       GSetIterChar const*: GSetIterGet_Char,                                \
       GSetIterUChar const*: GSetIterGet_UChar,                              \
       GSetIterInt const*: GSetIterGet_Int,                                  \
       GSetIterUInt const*: GSetIterGet_UInt,                                \
       GSetIterLong const*: GSetIterGet_Long,                                \
       GSetIterULong const*: GSetIterGet_ULong,                              \
       GSetIterFloat const*: GSetIterGet_Float,                              \
       GSetIterDouble const*: GSetIterGet_Double,                            \
       default: GSetIterGet_Ptr)((PtrToSetIter)->i)) == 0 ?                  \
         0 : (PtrToSetIter)->set->t)
#define GSetGet GSetIterGet

#define GSetIterPick(PtrToSetIter)                                           \
  (((PtrToSetIter)->set->t =                                                 \
     _Generic((PtrToSetIter),                                                \
       GSetIterChar*: GSetIterPick_Char,                                     \
       GSetIterUChar*: GSetIterPick_UChar,                                   \
       GSetIterInt*: GSetIterPick_Int,                                       \
       GSetIterUInt*: GSetIterPick_UInt,                                     \
       GSetIterLong*: GSetIterPick_Long,                                     \
       GSetIterULong*: GSetIterPick_ULong,                                   \
       GSetIterFloat*: GSetIterPick_Float,                                   \
       GSetIterDouble*: GSetIterPick_Double,                                 \
       default: GSetIterPick_Ptr)(                                           \
         (PtrToSetIter)->i, (PtrToSetIter)->set->s)) == 0 ?                  \
           0 : (PtrToSetIter)->set->t)
#define GSetPick GSetIterPick

#define GSetIterAddBefore(PtrToSetIter, Data)                                \
  do {                                                                       \
    _Generic((PtrToSetIter),                                                 \
      GSetIterChar*: GSetIterAddBefore_Char,                                 \
      GSetIterUChar*: GSetIterAddBefore_UChar,                               \
      GSetIterInt*: GSetIterAddBefore_Int,                                   \
      GSetIterUInt*: GSetIterAddBefore_UInt,                                 \
      GSetIterLong*: GSetIterAddBefore_Long,                                 \
      GSetIterULong*: GSetIterAddBefore_ULong,                               \
      GSetIterFloat*: GSetIterAddBefore_Float,                               \
      GSetIterDouble*: GSetIterAddBefore_Double,                             \
      default: GSetIterAddBefore_Ptr)((PtrToSetIter)->i, Data,               \
        (PtrToSetIter)->set->s);                                             \
    (PtrToSetIter)->set->t = Data;                                           \
  } while (false)
#define GSetAddBefore GSetIterAddBefore

#define GSetIterReset(PtrToSetIter) \
  GSetIterReset_((PtrToSetIter)->i, (PtrToSetIter)->set->s)
#define GSetIterIsReady(PtrToSetIter) GSetIterIsReady_((PtrToSetIter)->i)
#define GSetIterNext(PtrToSetIter) GSetIterNext_((PtrToSetIter)->i)
#define GSetIterPrev(PtrToSetIter) GSetIterPrev_((PtrToSetIter)->i)
#define GSetIterIsFirst(PtrToSetIter) GSetIterIsFirst_((PtrToSetIter)->i)
#define GSetIterIsLast(PtrToSetIter) GSetIterIsLast_((PtrToSetIter)->i)
#define GSetIterSetType(PtrToSetIter, Type) \
  GSetIterSetType_(PtrToSetIter->i, Type)
#define GSetIterGetType(PtrToSetIter) GSetIterGetType_(PtrToSetIter->i)
#define GSetIterSetFilter(PtrToSetIter, PtrToFun, PtrToParams) \
  GSetIterSetFilter_((PtrToSetIter)->i, PtrToFun, PtrToParams)
#define GSetIterGetFilterParam(PtrToSetIter) \
  GSetIterGetFilterParam_((PtrToSetIter)->i)
#define GSetIterCount(PtrToSetIter) \
  GSetIterCount_((PtrToSetIter)->i, (PtrToSetIter)->set->s)
#define GSetReset GSetIterReset
#define GSetIsReady GSetIterIsReady
#define GSetNext GSetIterNext
#define GSetPrev GSetIterPrev
#define GSetIsFirst GSetIterIsFirst
#define GSetIsLast GSetIterIsLast
#define GSetSetFilter GSetIterSetFilter
#define GSetGetFilterParam GSetIterGetFilterParam
#define GSetCount GSetIterCount

#define GSetIterForEach(PtrToSetIter)                                        \
  GSetIterReset(PtrToSetIter);                                               \
  if (GSetGetSize((PtrToSetIter)->set) > 0) for (                            \
    bool hasEnded = false;                                                   \
    hasEnded == false;                                                       \
    hasEnded = !GSetIterNext(PtrToSetIter))
#define GSETFOR GSetIterForEach

#define GSetIterEnumerate(PtrToSetIter, Idx)                                 \
  GSetIterReset(PtrToSetIter);                                               \
  if (GSetGetSize((PtrToSetIter)->set) > 0) for (                            \
    size_t hasEnded = 0, Idx = 0;                                            \
    hasEnded == false;                                                       \
    hasEnded = !GSetIterNext(PtrToSetIter), ++Idx)
#define GSETENUM GSetIterEnumerate

// ===== Comparison functions for GSet<N>Sort on default typed GSet =======

int GSetCharCmp(
  void const* a,
  void const* b);
int GSetUCharCmp(
  void const* a,
  void const* b);
int GSetIntCmp(
  void const* a,
  void const* b);
int GSetUIntCmp(
  void const* a,
  void const* b);
int GSetLongCmp(
  void const* a,
  void const* b);
int GSetULongCmp(
  void const* a,
  void const* b);
int GSetFloatCmp(
  void const* a,
  void const* b);
int GSetDoubleCmp(
  void const* a,
  void const* b);
int GsetCharPtrCmp(
  void const* a,
  void const* b);
#define GSetStrCmp GsetCharPtrCmp

// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
