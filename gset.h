// ------------------ gset.h ------------------

// Guard against multiple inclusions
#ifndef _GSET_
#define _GSET_

// Include external modules header
#include <stdlib.h>
#include <stdbool.h>
#include <TryCatchC/trycatchc.h>

// ================== Private type declarations =========================

// Structure of a GSet
struct GSet;

// ================== Public functions declarations =========================

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

// ================== Typed GSet code auto generation  ======================

// Declare a typed GSet containing data of type Type and name GSet<Name>
#define DefineGSet(Name, Type)                                               \
  struct GSet ## Name {                                                      \
    struct GSet* s;                                                          \
    Type t;                                                                  \
  };                                                                         \
  static inline struct GSet ## Name * GSet ## Name ## Alloc(                 \
    void) {                                                                  \
    struct GSet ## Name * that = malloc(sizeof(struct GSet ## Name));        \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    *that = (struct GSet ## Name ){.s = GSetAlloc()};                        \
    return that;                                                             \
  }

DefineGSet(Char, char)
DefineGSet(UChar, unsigned char)
DefineGSet(Int, int)
DefineGSet(UInt, unsigned int)
DefineGSet(Long, long)
DefineGSet(ULong, unsigned long)
DefineGSet(Float, float)
DefineGSet(Double, double)
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
    GSetFree_(&((*PtrToPtrToSet)->s));                                       \
    free(*PtrToPtrToSet);                                                    \
    *PtrToPtrToSet = NULL;                                                   \
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
    default: GSetPush_Ptr)(PtrToSet->s, Data);                               \
  PtrToSet->t = Data

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
    default: GSetAdd_Ptr)(PtrToSet->s, Data);                                \
  PtrToSet->t = Data

#define GSetPop(PtrToSet)                                                    \
  ((PtrToSet->t =                                                            \
     _Generic((PtrToSet),                                                    \
       struct GSetChar*: GSetPop_Char,                                       \
       struct GSetUChar*: GSetPop_UChar,                                     \
       struct GSetInt*: GSetPop_Int,                                         \
       struct GSetUInt*: GSetPop_UInt,                                       \
       struct GSetLong*: GSetPop_Long,                                       \
       struct GSetULong*: GSetPop_ULong,                                     \
       struct GSetFloat*: GSetPop_Float,                                     \
       struct GSetDouble*: GSetPop_Double,                                   \
       default: GSetPop_Ptr)(PtrToSet->s)) == 0 ? 0 : PtrToSet->t)

#define GSetDrop(PtrToSet)                                                   \
  ((PtrToSet->t =                                                            \
     _Generic((PtrToSet),                                                    \
       struct GSetChar*: GSetDrop_Char,                                      \
       struct GSetUChar*: GSetDrop_UChar,                                    \
       struct GSetInt*: GSetDrop_Int,                                        \
       struct GSetUInt*: GSetDrop_UInt,                                      \
       struct GSetLong*: GSetDrop_Long,                                      \
       struct GSetULong*: GSetDrop_ULong,                                    \
       struct GSetFloat*: GSetDrop_Float,                                    \
       struct GSetDouble*: GSetDrop_Double,                                  \
       default: GSetDrop_Ptr)(PtrToSet->s)) == 0 ? 0 : PtrToSet->t)

// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
