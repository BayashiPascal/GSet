// ------------------ gset.h ------------------

// Guard against multiple inclusions
#ifndef _GSET_
#define _GSET_

// Include external modules header
#include <stdlib.h>
#include <stdbool.h>
#include <TryCatchC/trycatchc.h>

// ================== Macros =========================

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

void GSetPush_Int(struct GSet* that, int data);
void GSetPush_UInt(struct GSet* that, unsigned int data);
void GSetPush_Ptr(struct GSet* that, void* data);

int GSetPop_Int(struct GSet* that);
unsigned int GSetPop_UInt(struct GSet* that);
void* GSetPop_Ptr(struct GSet* that);

// ================== Typed GSet code auto generation  ======================

// Declare a typed GSet containing data of type Type and name GSet<Name>
#define DefineGSet(Name, Type)                                               \
  struct GSet ## Name {                                                      \
    struct GSet* s;                                                          \
    Type t;                                                                  \
  };                                                                         \
  static struct GSet ## Name * GSet ## Name ## Alloc(                        \
    void) {                                                                  \
    struct GSet ## Name * that = malloc(sizeof(struct GSet ## Name));        \
    if (that == NULL) Raise(TryCatchExc_MallocFailed);                       \
    *that = (struct GSet ## Name ){.s = GSetAlloc()};                        \
    return that;                                                             \
  }                                                                          \
  static void GSet ## Name ## Free(                                          \
    struct GSet ## Name ** const that) {                                     \
    if (that == NULL || *that == NULL) return;                               \
    GSetFree(&((*that)->s));                                                 \
    free(*that);                                                             \
    *that = NULL;                                                            \
  }                                                                          \

DefineGSet(Int, int)
DefineGSet(UInt, unsigned int)
DefineGSet(Str, char*)

// ================== Polymorphism  ======================

#define GSetPush(Set, Data) _Generic((Set), \
  struct GSetInt*: GSetPush_Int, \
  struct GSetUInt*: GSetPush_UInt, \
  default: GSetPush_Ptr)(Set->s, Data); \
  Set->t = Data // Pushing wrong data type in the set

#define GSetPop(Set) (Set->t = _Generic((Set), \
  struct GSetInt*: GSetPop_Int, \
  struct GSetUInt*: GSetPop_UInt, \
  default: GSetPop_Ptr)(Set->s) == 0 ? 0 : Set->t)


// End of the guard against multiple inclusion
#endif

// ------------------ gset.h ------------------
