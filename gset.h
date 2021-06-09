// ------------------ gset.h ------------------

// Guard against multiple inclusions
#ifndef _GSET_
#define _GSET_

// Include external modules header
#include <stdlib.h>
#include <stdbool.h>
#include <TryCatchC/trycatchc.h>

// ================== Type declarations =========================

enum GSetIterType {

  GSetIterForward,
  GSetIterBackward,

};

// Structure of a set and its iterators
struct GSet;
struct GSetIter;
typedef struct GSet GSet;
typedef struct GSetIter GSetIter;

// ================= Public functions declarations ======================

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
#define GSetPush_(N, T)     \
void GSetPush_ ## N(        \
  GSet* const that,  \
             T const data)
GSetPush_(Char, char);
GSetPush_(UChar, unsigned char);
GSetPush_(Int, int);
GSetPush_(UInt, unsigned int);
GSetPush_(Long, long);
GSetPush_(ULong, unsigned long);
GSetPush_(Float, float);
GSetPush_(Double, double);
GSetPush_(Ptr, void*);

// Add data at the tail of the set
// Inputs:
//   that: the set
//   data: the data
#define GSetAdd_(N, T)     \
void GSetAdd_ ## N(        \
  GSet* const that,  \
             T const data)
GSetAdd_(Char, char);
GSetAdd_(UChar, unsigned char);
GSetAdd_(Int, int);
GSetAdd_(UInt, unsigned int);
GSetAdd_(Long, long);
GSetAdd_(ULong, unsigned long);
GSetAdd_(Float, float);
GSetAdd_(Double, double);
GSetAdd_(Ptr, void*);

// Add an array of data at the tail of the set
// Inputs:
//   that: the set
//   arr: the array of data
#define GSetAddArr_(N, T)     \
void GSetAddArr_ ## N(        \
  GSet* const that,  \
             size_t const size, \
             T* const arr)
GSetAddArr_(Char, char);
GSetAddArr_(UChar, unsigned char);
GSetAddArr_(Int, int);
GSetAddArr_(UInt, unsigned int);
GSetAddArr_(Long, long);
GSetAddArr_(ULong, unsigned long);
GSetAddArr_(Float, float);
GSetAddArr_(Double, double);
GSetAddArr_(Ptr, void);

// Pop data from the head of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the head of the set and return it
#define GSetPop_(N, T)     \
T GSetPop_ ## N(           \
  GSet* const that)
GSetPop_(Char, char);
GSetPop_(UChar, unsigned char);
GSetPop_(Int, int);
GSetPop_(UInt, unsigned int);
GSetPop_(Long, long);
GSetPop_(ULong, unsigned long);
GSetPop_(Float, float);
GSetPop_(Double, double);
GSetPop_(Ptr, void*);

// Drop data from the tail of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the tail of the set and return it
#define GSetDrop_(N, T)     \
T GSetDrop_ ## N(           \
  GSet* const that)
GSetDrop_(Char, char);
GSetDrop_(UChar, unsigned char);
GSetDrop_(Int, int);
GSetDrop_(UInt, unsigned int);
GSetDrop_(Long, long);
GSetDrop_(ULong, unsigned long);
GSetDrop_(Float, float);
GSetDrop_(Double, double);
GSetDrop_(Ptr, void*);

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
#define GSetSort_(N, T) \
void GSetSort_ ## N(    \
  GSet* const that,   \
          int (*cmp)(void const*, void const*), \
         bool inc)
GSetSort_(Char, char);
GSetSort_(UChar, unsigned char);
GSetSort_(Int, int);
GSetSort_(UInt, unsigned int);
GSetSort_(Long, long);
GSetSort_(ULong, unsigned long);
GSetSort_(Float, float);
GSetSort_(Double, double);
GSetSort_(Ptr, void*);

// Allocate memory for a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
GSetIter* GSetIterAlloc(
  enum GSetIterType const type);

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
#define GSetIterGet_(N, T)                                                   \
T GSetIterGet_ ## N(                                                         \
  GSetIter const* const that)
GSetIterGet_(Char, char);
GSetIterGet_(UChar, unsigned char);
GSetIterGet_(Int, int);
GSetIterGet_(UInt, unsigned int);
GSetIterGet_(Long, long);
GSetIterGet_(ULong, unsigned long);
GSetIterGet_(Float, float);
GSetIterGet_(Double, double);
GSetIterGet_(Ptr, void*);

// Pick the current data from a set
// Input:
//   that: the set
//   set: the associated set
// Output:
//   Remove the data at the head of the set and return it
#define GSetIterPick_(N, T)            \
T GSetIterPick_ ## N(                  \
  GSetIter* const that,         \
  GSet* const set)
GSetIterPick_(Char, char);
GSetIterPick_(UChar, unsigned char);
GSetIterPick_(Int, int);
GSetIterPick_(UInt, unsigned int);
GSetIterPick_(Long, long);
GSetIterPick_(ULong, unsigned long);
GSetIterPick_(Float, float);
GSetIterPick_(Double, double);
GSetIterPick_(Ptr, void*);

// Reset the iterator to its first element
// Input:
//   that: the iterator
//    set: the associated set
void GSetIterReset_(
    GSetIter* const that,
  GSet const* const set);

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
  GSetIter* const that);

// ================== Typed GSet code auto generation  ======================

// Declare a typed GSet containing data of type Type and name GSet<Name>
#define DefineGSetBase(Name, Type)                                           \
  struct GSet ## Name {                                                      \
    GSet* s;                                                          \
    Type t;                                                                  \
  };                                                                         \
  typedef struct GSet ## Name GSet ## Name;                                  \
  static inline GSet ## Name* GSet ## Name ## Alloc(                  \
    void) {                                                                  \
    GSet ## Name* that = malloc(sizeof(GSet ## Name));         \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    Try {                                                                    \
      *that = (GSet ## Name ){.s = GSetAlloc()};                      \
    } CatchDefault {                                                         \
      free(that); Raise(TryCatchExc_MallocFailed);              \
    } EndCatchDefault;                                                       \
    return that;                                                             \
  }                                                                          \
  static inline GSet ## Name* GSet ## Name ## FromArr(                       \
    size_t const size,                                                   \
    Type* const arr) {                                                    \
    GSet ## Name* that = GSet ## Name ## Alloc();                            \
    _Generic((that->t), \
      char: GSetAddArr_Char, \
      unsigned char: GSetAddArr_UChar, \
      int: GSetAddArr_Int, \
      unsigned int: GSetAddArr_UInt, \
      long: GSetAddArr_Long, \
      unsigned long: GSetAddArr_ULong, \
      float: GSetAddArr_Float, \
      double: GSetAddArr_Double, \
      default: GSetAddArr_Ptr)(that->s, size, arr);     \
    return that;                                                             \
  }                                                                          \
  static inline Type* GSet ## Name ## ToArr(                                     \
    GSet ## Name* const that) {                                               \
    if (GSetGetSize_(that->s) == 0) return NULL;                              \
    Type* arr = malloc(sizeof(Type) * GSetGetSize_(that->s));                       \
    if (arr == NULL) Raise(TryCatchExc_MallocFailed);                          \
    GSetIter* iter = NULL;                                                     \
    Try {                                                                      \
      iter = GSetIterAlloc(GSetIterForward);                                   \
      GSetIterReset_(iter, that->s);                                          \
      size_t i = 0;                                                            \
      do {                                                                     \
        arr[i] =                                           \
          _Generic((that->t), \
            char: GSetIterGet_Char, \
            unsigned char: GSetIterGet_UChar, \
            int: GSetIterGet_Int, \
            unsigned int: GSetIterGet_UInt, \
            long: GSetIterGet_Long, \
            unsigned long: GSetIterGet_ULong, \
            float: GSetIterGet_Float, \
            double: GSetIterGet_Double, \
            default: GSetIterGet_Ptr)(iter);     \
        ++i;                                                                   \
      } while(GSetIterNext_(iter));                                            \
    } CatchDefault {                                                           \
      free(arr); GSetIterFree_(&iter);                                         \
      Raise(TryCatchGetLastExc());                                             \
    } EndCatchDefault;                                                         \
    GSetIterFree_(&iter);                                                      \
    return arr;                                                                \
  } \
  struct GSetIter ## Name {                                                  \
    GSet ## Name* set;                                                \
    GSetIter* i;                                                      \
  };                                                                         \
  typedef struct GSetIter ## Name GSetIter ## Name;                          \
  static inline GSetIter ## Name* GSetIter ## Name ## Alloc(          \
    GSet ## Name* const set,                                          \
       enum GSetIterType const type) {                                       \
    GSetIter ## Name* that = malloc(sizeof(GSetIter ## Name)); \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    Try {                                                                    \
      *that =                                                                \
        (GSetIter ## Name ){.set = set, .i = GSetIterAlloc(type)};    \
    } CatchDefault {                                                         \
      free(that); Raise(TryCatchExc_MallocFailed);              \
    } EndCatchDefault;                                                       \
    GSetIterReset_(that->i, set->s);                                         \
    return that;                                                             \
  }                                                                          \
  static inline GSetIter ## Name* GSetIter ## Name ## Clone(          \
    GSetIter ## Name* that) {                                         \
    GSetIter ## Name* clone = malloc(sizeof(GSetIter ## Name));\
    if (clone == NULL) Raise(TryCatchExc_MallocFailed);                      \
    Try {                                                                    \
      *clone = (GSetIter ## Name)                                     \
        {.set = that->set, .i = GSetIterClone_(that->i)};                    \
    } CatchDefault {                                                         \
      free(that); Raise(TryCatchExc_MallocFailed);              \
    } EndCatchDefault;                                                       \
    return clone;                                                            \
  }                                                                          \

#define DefineGSet(Name, Type)                                               \
  DefineGSetBase(Name, Type)                                                 \
  void Name ## Free(Type* const that);                                       \
  static inline void GSet ## Name ## Flush(                                  \
    GSet ## Name* const that) {                                       \
    Type d = NULL;                                                           \
    while (GSetGetSize_(that->s) > 0) {                                      \
      d = GSetPop_Ptr(that->s);                                              \
      Name ## Free(&d);                                                      \
    }                                                                        \
  }                                                                          \

DefineGSetBase(Char, char)
DefineGSetBase(UChar, unsigned char)
DefineGSetBase(Int, int)
DefineGSetBase(UInt, unsigned int)
DefineGSetBase(Long, long)
DefineGSetBase(ULong, unsigned long)
DefineGSetBase(Float, float)
DefineGSetBase(Double, double)
DefineGSet(CharPtr, char*)
#define GSetStr GSetCharPtr
#define GSetStrAlloc GSetCharPtrAlloc
#define GSetStrFree GSetCharPtrFree
#define GSetStrFromArr GSetCharPtrFromArr
#define GSetStrToArr GSetCharPtrToArr
#define GSetIterStr GSetIterCharPtr
#define GSetIterStrAlloc GSetIterCharPtrAlloc
#define GSetIterStrClone GSetIterCharPtrClone
#define GSetIterStrFree GSetIterCharPtrFree
DefineGSet(UCharPtr, unsigned char*)
DefineGSet(IntPtr, int*)
DefineGSet(UIntPtr, unsigned int*)
DefineGSet(LongPtr, long*)
DefineGSet(ULongPtr, unsigned long*)
DefineGSet(FloatPtr, float*)
DefineGSet(DoublePtr, double*)

// ================== Polymorphism  ======================

#define GSetFree(PtrToPtrToSet)                                              \
  if (((PtrToPtrToSet) != NULL) && (*(PtrToPtrToSet) != NULL)) {             \
    GSetFree_(&((*(PtrToPtrToSet))->s));                                     \
    free(*(PtrToPtrToSet));                                                  \
    *(PtrToPtrToSet) = NULL;                                                 \
  }                                                                          \

#define GSetPush(PtrToSet, Data)                                             \
  _Generic((PtrToSet),                                                       \
    GSetChar*: GSetPush_Char,                                         \
    GSetUChar*: GSetPush_UChar,                                       \
    GSetInt*: GSetPush_Int,                                           \
    GSetUInt*: GSetPush_UInt,                                         \
    GSetLong*: GSetPush_Long,                                         \
    GSetULong*: GSetPush_ULong,                                       \
    GSetFloat*: GSetPush_Float,                                       \
    GSetDouble*: GSetPush_Double,                                     \
    default: GSetPush_Ptr)((PtrToSet)->s, Data);                             \
  (PtrToSet)->t = Data

#define GSetAdd(PtrToSet, Data)                                              \
  _Generic((PtrToSet),                                                       \
    GSetChar*: GSetAdd_Char,                                          \
    GSetUChar*: GSetAdd_UChar,                                        \
    GSetInt*: GSetAdd_Int,                                            \
    GSetUInt*: GSetAdd_UInt,                                          \
    GSetLong*: GSetAdd_Long,                                          \
    GSetULong*: GSetAdd_ULong,                                        \
    GSetFloat*: GSetAdd_Float,                                        \
    GSetDouble*: GSetAdd_Double,                                      \
    default: GSetAdd_Ptr)((PtrToSet)->s, Data);                              \
  (PtrToSet)->t = Data

#define GSetAddArr(PtrToSet, Size, Data)                                    \
  _Generic((PtrToSet),                                                       \
    GSetChar*: GSetAddArr_Char,                                          \
    GSetUChar*: GSetAddArr_UChar,                                        \
    GSetInt*: GSetAddArr_Int,                                            \
    GSetUInt*: GSetAddArr_UInt,                                          \
    GSetLong*: GSetAddArr_Long,                                          \
    GSetULong*: GSetAddArr_ULong,                                        \
    GSetFloat*: GSetAddArr_Float,                                        \
    GSetDouble*: GSetAddArr_Double,                                      \
    default: GSetAddArr_Ptr)((PtrToSet)->s, Size, Data);                 \
  (PtrToSet)->t = *(Data)

#define GSetPop(PtrToSet)                                                    \
  (((PtrToSet)->t =                                                          \
     _Generic((PtrToSet),                                                    \
       GSetChar*: GSetPop_Char,                                       \
       GSetUChar*: GSetPop_UChar,                                     \
       GSetInt*: GSetPop_Int,                                         \
       GSetUInt*: GSetPop_UInt,                                       \
       GSetLong*: GSetPop_Long,                                       \
       GSetULong*: GSetPop_ULong,                                     \
       GSetFloat*: GSetPop_Float,                                     \
       GSetDouble*: GSetPop_Double,                                   \
       default: GSetPop_Ptr)((PtrToSet)->s)) == 0 ? 0 : (PtrToSet)->t)

#define GSetDrop(PtrToSet)                                                   \
  (((PtrToSet)->t =                                                          \
     _Generic((PtrToSet),                                                    \
       GSetChar*: GSetDrop_Char,                                      \
       GSetUChar*: GSetDrop_UChar,                                    \
       GSetInt*: GSetDrop_Int,                                        \
       GSetUInt*: GSetDrop_UInt,                                      \
       GSetLong*: GSetDrop_Long,                                      \
       GSetULong*: GSetDrop_ULong,                                    \
       GSetFloat*: GSetDrop_Float,                                    \
       GSetDouble*: GSetDrop_Double,                                  \
       default: GSetDrop_Ptr)((PtrToSet)->s)) == 0 ? 0 : (PtrToSet)->t)

void GSetAppendInvalidType(void*, void*);
#define GSetAppend(PtrToSetDst, PtrToSetSrc)                                 \
 _Generic((PtrToSetDst),                                                     \
   GSetChar*:                                                         \
     _Generic((PtrToSetSrc), \
       GSetChar*: GSetAppend_, \
       default: GSetAppendInvalidType),                 \
   GSetUChar*:                                                        \
     _Generic((PtrToSetSrc), \
       GSetUChar*: GSetAppend_, \
       default: GSetAppendInvalidType),                \
   GSetInt*:                                                          \
     _Generic((PtrToSetSrc), \
       GSetInt*: GSetAppend_, \
       default: GSetAppendInvalidType),                  \
   GSetUInt*:                                                         \
     _Generic((PtrToSetSrc), \
       GSetUInt*: GSetAppend_, \
       default: GSetAppendInvalidType),                 \
   GSetLong*:                                                         \
     _Generic((PtrToSetSrc), \
       GSetLong*: GSetAppend_, \
       default: GSetAppendInvalidType),                 \
   GSetULong*:                                                        \
     _Generic((PtrToSetSrc), \
       GSetULong*: GSetAppend_, \
       default: GSetAppendInvalidType),                \
   GSetFloat*:                                                        \
     _Generic((PtrToSetSrc), \
       GSetFloat*: GSetAppend_, \
       default: GSetAppendInvalidType),                \
   GSetDouble*:                                                       \
     _Generic((PtrToSetSrc), \
       GSetDouble*: GSetAppend_, \
       default: GSetAppendInvalidType),               \
   default: _Generic((PtrToSetSrc),                                          \
     GSetChar*: GSetAppendInvalidType,                                \
     GSetUChar*: GSetAppendInvalidType,                               \
     GSetInt*: GSetAppendInvalidType,                                 \
     GSetUInt*: GSetAppendInvalidType,                                \
     GSetLong*: GSetAppendInvalidType,                                \
     GSetULong*: GSetAppendInvalidType,                               \
     GSetFloat*: GSetAppendInvalidType,                               \
     GSetDouble*: GSetAppendInvalidType,                              \
     default: GSetAppend_))((PtrToSetDst)->s, (PtrToSetSrc)->s)

void GSetMergeInvalidType(void*, void*);
#define GSetMerge(PtrToSetDst, PtrToSetSrc)                                 \
 _Generic((PtrToSetDst),                                                     \
   GSetChar*:                                                         \
     _Generic((PtrToSetSrc),                                      \
       GSetChar*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),                 \
   GSetUChar*:                                                        \
     _Generic((PtrToSetSrc),                                      \
       GSetUChar*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),                \
   GSetInt*:                                                          \
     _Generic((PtrToSetSrc),                                      \
       GSetInt*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),                  \
   GSetUInt*:                                                         \
     _Generic((PtrToSetSrc),                                      \
       GSetUInt*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),                 \
   GSetLong*:                                                         \
     _Generic((PtrToSetSrc),                                      \
       GSetLong*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),                 \
   GSetULong*:                                                        \
     _Generic((PtrToSetSrc),                                      \
       GSetULong*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),                \
   GSetFloat*:                                                        \
     _Generic((PtrToSetSrc),                                      \
       GSetFloat*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),                \
   GSetDouble*:                                                       \
     _Generic((PtrToSetSrc),                                      \
       GSetDouble*: GSetMerge_,                                      \
       default: GSetMergeInvalidType),               \
   default: _Generic((PtrToSetSrc),                                          \
     GSetChar*: GSetMergeInvalidType,                                \
     GSetUChar*: GSetMergeInvalidType,                               \
     GSetInt*: GSetMergeInvalidType,                                 \
     GSetUInt*: GSetMergeInvalidType,                                \
     GSetLong*: GSetMergeInvalidType,                                \
     GSetULong*: GSetMergeInvalidType,                               \
     GSetFloat*: GSetMergeInvalidType,                               \
     GSetDouble*: GSetMergeInvalidType,                              \
     default: GSetMerge_))((PtrToSetDst)->s, (PtrToSetSrc)->s)

#define GSetGetSize(PtrToSet) GSetGetSize_((PtrToSet)->s)
#define GSetEmpty(PtrToSet) GSetEmpty_((PtrToSet)->s)
#define GSetShuffle(PtrToSet) GSetShuffle_((PtrToSet)->s)

#define GSetSort(PtrToSet, CmpFun, FlagIncreasing)                           \
  _Generic((PtrToSet),                                                       \
    GSetChar*: GSetSort_Char,                                          \
    GSetUChar*: GSetSort_UChar,                                        \
    GSetInt*: GSetSort_Int,                                            \
    GSetUInt*: GSetSort_UInt,                                          \
    GSetLong*: GSetSort_Long,                                          \
    GSetULong*: GSetSort_ULong,                                        \
    GSetFloat*: GSetSort_Float,                                        \
    GSetDouble*: GSetSort_Double,                                      \
    default: GSetSort_Ptr)((PtrToSet)->s, CmpFun, FlagIncreasing);

#define GSetIterFree(PtrToPtrToSetIter)                                      \
  if (((PtrToPtrToSetIter) != NULL) && (*(PtrToPtrToSetIter) != NULL)) {     \
    GSetIterFree_(&((*(PtrToPtrToSetIter))->i));                             \
    free(*(PtrToPtrToSetIter));                                              \
    *(PtrToPtrToSetIter) = NULL;                                             \
  }                                                                          \

#define GSetIterGet(PtrToSetIter)                                            \
  (((PtrToSetIter)->set->t =                                                 \
     _Generic((PtrToSetIter),                                                \
       GSetIterChar*: GSetIterGet_Char,                               \
       GSetIterUChar*: GSetIterGet_UChar,                             \
       GSetIterInt*: GSetIterGet_Int,                                 \
       GSetIterUInt*: GSetIterGet_UInt,                               \
       GSetIterLong*: GSetIterGet_Long,                               \
       GSetIterULong*: GSetIterGet_ULong,                             \
       GSetIterFloat*: GSetIterGet_Float,                             \
       GSetIterDouble*: GSetIterGet_Double,                           \
       default: GSetIterGet_Ptr)((PtrToSetIter)->i)) == 0 ?                  \
         0 : (PtrToSetIter)->set->t)
#define GSetGet GSetIterGet

#define GSetIterPick(PtrToSetIter)                                           \
  (((PtrToSetIter)->set->t =                                                 \
     _Generic((PtrToSetIter),                                                \
       GSetIterChar*: GSetIterPick_Char,                              \
       GSetIterUChar*: GSetIterPick_UChar,                            \
       GSetIterInt*: GSetIterPick_Int,                                \
       GSetIterUInt*: GSetIterPick_UInt,                              \
       GSetIterLong*: GSetIterPick_Long,                              \
       GSetIterULong*: GSetIterPick_ULong,                            \
       GSetIterFloat*: GSetIterPick_Float,                            \
       GSetIterDouble*: GSetIterPick_Double,                          \
       default: GSetIterPick_Ptr)(                                           \
         (PtrToSetIter)->i, (PtrToSetIter)->set->s)) == 0 ?                  \
           0 : (PtrToSetIter)->set->t)
#define GSetPick GSetIterPick

#define GSetIterReset(PtrToSetIter)                                          \
  GSetIterReset_((PtrToSetIter)->i, (PtrToSetIter)->set->s)
#define GSetIterNext(PtrToSetIter) GSetIterNext_((PtrToSetIter)->i)
#define GSetIterPrev(PtrToSetIter) GSetIterPrev_((PtrToSetIter)->i)
#define GSetIterIsFirst(PtrToSetIter) GSetIterIsFirst_((PtrToSetIter)->i)
#define GSetIterIsLast(PtrToSetIter) GSetIterIsLast_((PtrToSetIter)->i)
#define GSetReset GSetIterReset
#define GSetNext GSetIterNext
#define GSetPrev GSetIterPrev
#define GSetIsFirst GSetIterIsFirst
#define GSetIsLast GSetIterIsLast

#define GSetIterForEach(PtrToSetIter)                                        \
  if (GSetGetSize((PtrToSetIter)->set) > 0) for (                            \
    GSetIterReset(PtrToSetIter);                                             \
    GSetIterIsLast(PtrToSetIter) == false;                                   \
    GSetIterNext(PtrToSetIter))
#define GSetForEach GSetIterForEach

// ===== Comparison functions for GSet<N>Sort on default typed GSet =======

int GSetCharCmp(void const* a, void const* b);
int GSetUCharCmp(void const* a, void const* b);
int GSetIntCmp(void const* a, void const* b);
int GSetUIntCmp(void const* a, void const* b);
int GSetLongCmp(void const* a, void const* b);
int GSetULongCmp(void const* a, void const* b);
int GSetFloatCmp(void const* a, void const* b);
int GSetDoubleCmp(void const* a, void const* b);
int GSetCharPtrCmp(void const* a, void const* b);
#define GSetStrCmp GSetCharPtrCmp

// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
