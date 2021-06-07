// ------------------ gset.h ------------------

// Guard against multiple inclusions
#ifndef _GSET_
#define _GSET_

// Include external modules header
#include <stdlib.h>
#include <stdbool.h>
#include <TryCatchC/trycatchc.h>

// ================== Public type declarations =========================

enum GSetIterType {

  GSetIterForward,
  GSetIterBackward,

};

// ================== Private type declarations =========================

// Structure of a GSet and GSetIter
struct GSet;
struct GSetElem;
struct GSetIter;

// ================= Public functions declarations ======================

// Allocate memory for a new GSet
// Output:
//   Return the new GSet.
struct GSet* GSetAlloc(
  void);

// Empty the GSet with GSetEmpty() and free the memory it used.
// Input:
//   that: the GSet to be freed
void GSetFree_(
  struct GSet** const that);

// Push data at the head of the set
// Inputs:
//   that: the set
//   data: the data
#define GSetPush_(N, T)     \
void GSetPush_ ## N(        \
  struct GSet* const that,  \
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
  struct GSet* const that,  \
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

// Pop data from the head of the set
// Input:
//   that: the set
// Output:
//   Remove the data at the head of the set and return it
#define GSetPop_(N, T)     \
T GSetPop_ ## N(           \
  struct GSet* const that)
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
  struct GSet* const that)
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
        struct GSet* const that,
  struct GSet const* const tho);

// Return the number of element in the set
// Input:
//   that: the set
// Output:
//   Return the number of element.
size_t GSetGetSize_(
  struct GSet const* const that);

// Empty the set. Memory used by data in it is not freed.
// To empty the set and free data, use GSet<N>Flush() instead.
// Input:
//   that: the set
void GSetEmpty_(
  struct GSet* const that);

// Allocate memory for a new GSetIter
// Input:
//   type: the type of iteration
// Output:
//   Return the new GSetIter.
struct GSetIter* GSetIterAlloc(
  enum GSetIterType const type);

// Free the memory used by a GSetIter.
// Input:
//   that: the GSetIter to be freed
void GSetIterFree_(
  struct GSetIter** const that);

// Get the current data from a set
// Input:
//   that: the iterator
// Output:
//   Return the current data
#define GSetIterGet_(N, T)                                                   \
T GSetIterGet_ ## N(                                                         \
  struct GSetIter const* const that)
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
  struct GSetIter* const that,         \
  struct GSet* const set)
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
    struct GSetIter* const that,
  struct GSet const* const set);

// Move the iterator to the next element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator could move to the next element, else false
bool GSetIterNext_(
  struct GSetIter* const that);

// Move the iterator to the previous element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator could move to the previous element, else false
bool GSetIterPrev_(
  struct GSetIter* const that);

// Check if an iterator is on its first element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator is on its first element, else false
bool GSetIterIsFirst_(
  struct GSetIter* const that);

// Check if an iterator is on its last element
// Input:
//   that: the iterator
// Output:
// Return true if the iterator is on its last element, else false
bool GSetIterIsLast_(
  struct GSetIter* const that);

// Clone an iterator
// Input:
//   that: the iterator
// Output:
//   Return a clone of the iterator
struct GSetIter* GSetIterClone_(
  struct GSetIter* const that);

// ================== Typed GSet code auto generation  ======================

// Declare a typed GSet containing data of type Type and name GSet<Name>
#define DefineGSetBase(Name, Type)                                           \
  struct GSet ## Name {                                                      \
    struct GSet* s;                                                          \
    Type t;                                                                  \
  };                                                                         \
  static inline struct GSet ## Name* GSet ## Name ## Alloc(                  \
    void) {                                                                  \
    struct GSet ## Name* that = malloc(sizeof(struct GSet ## Name));         \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    Try {                                                                    \
      *that = (struct GSet ## Name ){.s = GSetAlloc()};                      \
    } CatchDefault {                                                         \
      free(that); that = NULL; Raise(TryCatchExc_MallocFailed);              \
    } EndTryWithDefault;                                                     \
    return that;                                                             \
  }                                                                          \
  struct GSetIter ## Name {                                                  \
    struct GSet ## Name* set;                                                \
    struct GSetIter* i;                                                      \
  };                                                                         \
  static inline struct GSetIter ## Name* GSetIter ## Name ## Alloc(          \
    struct GSet ## Name* const set,                                          \
       enum GSetIterType const type) {                                       \
    struct GSetIter ## Name* that = malloc(sizeof(struct GSetIter ## Name)); \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    *that = (struct GSetIter ## Name ){.set = set, .i = GSetIterAlloc(type)};\
    GSetIterReset_(that->i, set->s);                                         \
    return that;                                                             \
  }                                                                          \
  static inline struct GSetIter ## Name* GSetIter ## Name ## Clone(          \
    struct GSetIter ## Name* that) {                                         \
    struct GSetIter ## Name* clone = malloc(sizeof(struct GSetIter ## Name));\
    if (clone == NULL) Raise(TryCatchExc_MallocFailed);                      \
    Try {                                                                    \
      *clone = (struct GSetIter ## Name)                                     \
        {.set = that->set, .i = GSetIterClone_(that->i)};                    \
    } CatchDefault {                                                         \
      free(that); that = NULL; Raise(TryCatchExc_MallocFailed);              \
    } EndTryWithDefault;                                                     \
    return clone;                                                            \
  }                                                                          \

#define DefineGSet(Name, Type)                                               \
  DefineGSetBase(Name, Type)                                                 \
  void Name ## Free(Type* const that);                                       \
  static inline void GSet ## Name ## Flush(                                  \
    struct GSet ## Name* const that) {                                       \
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
DefineGSet(UCharPtr, unsigned char*)
DefineGSet(IntPtr, int*)
DefineGSet(UIntPtr, unsigned int*)
DefineGSet(LongPtr, long*)
DefineGSet(ULongPtr, unsigned long*)
DefineGSet(FloatPtr, float*)
DefineGSet(DoublePtr, double*)

// ================== Polymorphism  ======================

#define GSetFree(PtrToPtrToSet)                                              \
  if (PtrToPtrToSet != NULL && *PtrToPtrToSet != NULL) {                     \
    GSetFree_(&((*(PtrToPtrToSet))->s));                                     \
    free(*(PtrToPtrToSet));                                                  \
    *(PtrToPtrToSet) = NULL;                                                 \
  }                                                                          \

#define GSetPush(PtrToSet, Data)                                             \
  _Generic((PtrToSet),                                                       \
    struct GSetChar*: GSetPush_Char,                                         \
    struct GSetUChar*: GSetPush_UChar,                                       \
    struct GSetInt*: GSetPush_Int,                                           \
    struct GSetUInt*: GSetPush_UInt,                                         \
    struct GSetLong*: GSetPush_Long,                                         \
    struct GSetULong*: GSetPush_ULong,                                       \
    struct GSetFloat*: GSetPush_Float,                                       \
    struct GSetDouble*: GSetPush_Double,                                     \
    default: GSetPush_Ptr)((PtrToSet)->s, Data);                             \
  (PtrToSet)->t = Data

#define GSetAdd(PtrToSet, Data)                                              \
  _Generic((PtrToSet),                                                       \
    struct GSetChar*: GSetAdd_Char,                                          \
    struct GSetUChar*: GSetAdd_UChar,                                        \
    struct GSetInt*: GSetAdd_Int,                                            \
    struct GSetUInt*: GSetAdd_UInt,                                          \
    struct GSetLong*: GSetAdd_Long,                                          \
    struct GSetULong*: GSetAdd_ULong,                                        \
    struct GSetFloat*: GSetAdd_Float,                                        \
    struct GSetDouble*: GSetAdd_Double,                                      \
    default: GSetAdd_Ptr)((PtrToSet)->s, Data);                              \
  (PtrToSet)->t = Data

#define GSetPop(PtrToSet)                                                    \
  (((PtrToSet)->t =                                                          \
     _Generic((PtrToSet),                                                    \
       struct GSetChar*: GSetPop_Char,                                       \
       struct GSetUChar*: GSetPop_UChar,                                     \
       struct GSetInt*: GSetPop_Int,                                         \
       struct GSetUInt*: GSetPop_UInt,                                       \
       struct GSetLong*: GSetPop_Long,                                       \
       struct GSetULong*: GSetPop_ULong,                                     \
       struct GSetFloat*: GSetPop_Float,                                     \
       struct GSetDouble*: GSetPop_Double,                                   \
       default: GSetPop_Ptr)((PtrToSet)->s)) == 0 ? 0 : (PtrToSet)->t)

#define GSetDrop(PtrToSet)                                                   \
  (((PtrToSet)->t =                                                          \
     _Generic((PtrToSet),                                                    \
       struct GSetChar*: GSetDrop_Char,                                      \
       struct GSetUChar*: GSetDrop_UChar,                                    \
       struct GSetInt*: GSetDrop_Int,                                        \
       struct GSetUInt*: GSetDrop_UInt,                                      \
       struct GSetLong*: GSetDrop_Long,                                      \
       struct GSetULong*: GSetDrop_ULong,                                    \
       struct GSetFloat*: GSetDrop_Float,                                    \
       struct GSetDouble*: GSetDrop_Double,                                  \
       default: GSetDrop_Ptr)((PtrToSet)->s)) == 0 ? 0 : (PtrToSet)->t)

void GSetAppendInvalidType(void*, void*);
#define GSetAppend(PtrToSetDst, PtrToSetSrc)                                 \
 _Generic((PtrToSetDst),                                                     \
   struct GSetChar*:                                                         \
     _Generic((PtrToSetSrc), struct GSetChar*: GSetAppend_),                 \
   struct GSetUChar*:                                                        \
     _Generic((PtrToSetSrc), struct GSetUChar*: GSetAppend_),                \
   struct GSetInt*:                                                          \
     _Generic((PtrToSetSrc), struct GSetInt*: GSetAppend_),                  \
   struct GSetUInt*:                                                         \
     _Generic((PtrToSetSrc), struct GSetUInt*: GSetAppend_),                 \
   struct GSetLong*:                                                         \
     _Generic((PtrToSetSrc), struct GSetLong*: GSetAppend_),                 \
   struct GSetULong*:                                                        \
     _Generic((PtrToSetSrc), struct GSetULong*: GSetAppend_),                \
   struct GSetFloat*:                                                        \
     _Generic((PtrToSetSrc), struct GSetFloat*: GSetAppend_),                \
   struct GSetDouble*:                                                       \
     _Generic((PtrToSetSrc), struct GSetDouble*: GSetAppend_),               \
   default: _Generic((PtrToSetSrc),                                          \
     struct GSetChar*: GSetAppendInvalidType,                                \
     struct GSetUChar*: GSetAppendInvalidType,                               \
     struct GSetInt*: GSetAppendInvalidType,                                 \
     struct GSetUInt*: GSetAppendInvalidType,                                \
     struct GSetLong*: GSetAppendInvalidType,                                \
     struct GSetULong*: GSetAppendInvalidType,                               \
     struct GSetFloat*: GSetAppendInvalidType,                               \
     struct GSetDouble*: GSetAppendInvalidType,                              \
     default: GSetAppend_))((PtrToSetDst)->s, (PtrToSetSrc)->s)

#define GSetGetSize(PtrToSet) GSetGetSize_((PtrToSet)->s)

#define GSetIterFree(PtrToPtrToSetIter)                                      \
  if (PtrToPtrToSetIter != NULL && *(PtrToPtrToSetIter) != NULL) {           \
    GSetIterFree_(&((*(PtrToPtrToSetIter))->i));                             \
    free(*(PtrToPtrToSetIter));                                              \
    *(PtrToPtrToSetIter) = NULL;                                             \
  }                                                                          \

#define GSetIterGet(PtrToSetIter)                                            \
  (((PtrToSetIter)->set->t =                                                 \
     _Generic((PtrToSetIter),                                                \
       struct GSetIterChar*: GSetIterGet_Char,                               \
       struct GSetIterUChar*: GSetIterGet_UChar,                             \
       struct GSetIterInt*: GSetIterGet_Int,                                 \
       struct GSetIterUInt*: GSetIterGet_UInt,                               \
       struct GSetIterLong*: GSetIterGet_Long,                               \
       struct GSetIterULong*: GSetIterGet_ULong,                             \
       struct GSetIterFloat*: GSetIterGet_Float,                             \
       struct GSetIterDouble*: GSetIterGet_Double,                           \
       default: GSetIterGet_Ptr)((PtrToSetIter)->i)) == 0 ?                  \
         0 : (PtrToSetIter)->set->t)

#define GSetIterPick(PtrToSetIter)                                           \
  (((PtrToSetIter)->set->t =                                                 \
     _Generic((PtrToSetIter),                                                \
       struct GSetIterChar*: GSetIterPick_Char,                              \
       struct GSetIterUChar*: GSetIterPick_UChar,                            \
       struct GSetIterInt*: GSetIterPick_Int,                                \
       struct GSetIterUInt*: GSetIterPick_UInt,                              \
       struct GSetIterLong*: GSetIterPick_Long,                              \
       struct GSetIterULong*: GSetIterPick_ULong,                            \
       struct GSetIterFloat*: GSetIterPick_Float,                            \
       struct GSetIterDouble*: GSetIterPick_Double,                          \
       default: GSetIterPick_Ptr)(                                           \
         (PtrToSetIter)->i, (PtrToSetIter)->s)) == 0 ?                       \
           0 : (PtrToSetIter)->set->t)

#define GSetIterReset(PtrToSetIter)                                          \
  GSetIterReset_((PtrToSetIter)->i, (PtrToSetIter)->set->s)
#define GSetIterNext(PtrToSetIter) GSetIterNext_((PtrToSetIter)->i)
#define GSetIterPrev(PtrToSetIter) GSetIterPrev_((PtrToSetIter)->i)
#define GSetIterIsFirst(PtrToSetIter) GSetIterIsFirst_((PtrToSetIter)->i)
#define GSetIterIsLast(PtrToSetIter) GSetIterIsLast_((PtrToSetIter)->i)

#define GSetForEach(PtrToSetIter)                                            \
  if (GSetGetSize((PtrToSetIter)->set) > 0) for (                            \
    GSetIterReset(PtrToSetIter);                                             \
    GSetIterIsLast(PtrToSetIter) == false;                                   \
    GSetIterNext(PtrToSetIter))

// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
