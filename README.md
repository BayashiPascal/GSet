# GSet

GSet is a C library providing a polymorphic set data structure and the functions to interact with it.

A GSet is a collection of data, implemented as a double linked list. These data can be of any basic type, pointers to basic types, or pointers toward `struct`. A given set contains only data of the same type, and data type checking is enforced at compilation time. The user can define new GSet for its own structs with a single line macro. GSet offers a polymorphic interface covering all data types (included user-defined typed sets).

Available operations on a GSet are:
* Alloc/free/clone
* push data at the head (single data or multiple at once)
* add data at the tail (single data or multiple at once)
* pop data from the head
* drop data from the tail
* iterate forward/backward on the set (eventually using a user-defined filter function)
* pick the current data
* shuffle the data
* sort the data (using a user-defined comparison function)
* foreach and enumerate macro to execute a block of code on each data (or filtered data)
* append/merge a set at the tail of another set
* get the size of set and cound the filtered data
* empty a GSet with/without freeing its data
* converting a GSet from/to an array

## Table Of Content

1 [Install](https://github.com/BayashiPascal/GSet/tree/master#1-install)

2 [Usage](https://github.com/BayashiPascal/GSet/tree/master#2-usage)

3 [How it works](https://github.com/BayashiPascal/GSet/tree/master#3-how-it-works)

4 [Interface](https://github.com/BayashiPascal/GSet/tree/master#4-interface)

5 [License](https://github.com/BayashiPascal/GSet/tree/master#5-license)

# 1 Install

Download this repository into a folder of your choice, in the examples below I'll call it `Repos`, as follow:
```
cd Repos
wget https://github.com/BayashiPascal/GSet/archive/main.zip
unzip main.zip
mv GSet-main GSet
rm main.zip
cd GSet
make all
sudo make install
```

The [TryCatchC](https://github.com/BayashiPascal/TryCatchC) libraries will automatically be installed during installation. You may be asked for your password during installation.

# 2 Usage

## 2.1 Minimal example

Below is a minimal example of how to use a GSet.

```
#include <stdio.h>
#include <GSet/gset.h>

// Main function
int main() {

  // Create the GSet
  GSetInt* setInt = GSetIntAlloc();

  // Push a data
  int val = 42;
  GSetPush(
    setInt,
    val);

  // Pop the data
  val = GSetPop(setInt);
  printf("%d\n", val);

  // Free the GSet
  GSetFree(&setInt);

  // Return the sucess code
  return EXIT_SUCCESS;

}
```

It can be compiled as follow:

```
gcc -std=gnu11 -c main.c
gcc main.o -lgset -lm -ltrycatchc -o main 
```

# 2.2 User defined typed GSet

To create a typed `GSet` containing data of, for example, type `struct UserData`, one can use the macro `GSETDEF(UserData, struct UserData)`. Below is a basic example:

```
#include <stdio.h>
#include <GSet/gset.h>

// Dummy structure to test typed GSet
struct UserData {

  int val;

};

// Create a typed GSet for UserData
GSETDEF(UserData, struct UserData)

// Main function
int main() {

  // Example of typed GSet

  // Create the GSet
  GSetUserData* setUserData = GSetUserDataAlloc();

  // Push a data
  struct UserData userData = { .val = 42 };
  GSetPush(
    setUserData,
    &userData);

  // Pop the data
  struct UserData* ptrUserData = GSetPop(setUserData);
  printf("%d\n", ptrUserData->val);

  // Free the GSet
  GSetFree(&setUserData);

  // Return the sucess code
  return EXIT_SUCCESS;

}
```

# 3 How it works

## 3.1 Underlying untyped GSet

In the body of the library, an untyped GSet structure is implemented. It is a double linked list of elements containing data declared as an union of all basic types and pointer to void:

```
union GSetElemData {
  char Char;
  unsigned char UChar;
  int Int;
  unsigned int UInt;
  long Long;
  unsigned long ULong;
  float Float;
  double Double;
  void* Ptr;
};
struct GSetElem {
  union GSetElemData data;
  struct GSetElem* prev;
  struct GSetElem* next;
};
struct GSet {
  size_t size;
  GSetElem* first;
  GSetElem* last;
};
```

An union is preferred to several members for each type with the view to save space in memory, as only one single type will ever be used for a given GSetElem, and to allow the manipulation of the data independantly of its type.

Functions on GSet, if they need access to the data, are defined for each data type. Macro are used to commonalise the code. For example, to pop a data:

```
#define GSETPOP__(N, T)                                \
T GSetPop_ ## N(                                       \
  GSet* const that) {                                  \
  if (that->size == 0) Raise(TryCatchExc_OutOfRange);  \
  GSetElem* elem = GSetPopElem(that);                  \
  T data = elem->data.N;                               \
  GSetElemFree(&elem);                                 \
  return data;                                         \
}
GSETPOP__(Char, char)
GSETPOP__(UChar, unsigned char)
GSETPOP__(Int, int)
...
GSETPOP__(Ptr, void*)
```

which gives us the functions:

```
char GSetPop_Char(GSet* const that);
unsigned char GSetPop_UChar(GSet* const that);
int GSetPop_Int(GSet* const that);
...
void* GSetPop_Ptr(GSet* const that);
```

At this level, all the pointers are considered to be pointers to void.

## 3.2 Typed GSet with polymorphism and type checking

Typed GSet used by the user are defined in the header of the library. Here again, macro is used to commonalise code.

```
// Declare a typed GSet containing data of type Type and name GSet<Name>
#define DEFINEGSETBASE(Name, Type)                                           \
  struct GSet ## Name {                                                      \
    GSet* s;                                                                 \
    Type t;                                                                  \
  };                                                                         \
  ...
DEFINEGSETBASE(Char, char)
DEFINEGSETBASE(UChar, unsigned char)
DEFINEGSETBASE(Int, int)
...
```

The user can declare its own typed GSet with a single line of code as follow: `GSETDEF(Name, Type)` where `Name` is an idenitifer for the new type of GSet and `Type` is the type of the data in the GSet. For example, `GSETDEF(Int, int)` declare a typed GSet called `GSetInt` and containing data of type `int`. Typed GSet provided by default by the library are:

```
GSetChar,      data type: char
GSetUChar,     data type: unsigned char
GSetInt,       data type: int
GSetUInt,      data type: unsigned int
GSetLong,      data type: long
GSetULong,     data type: unsigned long
GSetFloat,     data type: float
GSetDouble,    data type: double
GSetCharPtr,   data type: char*
GSetUCharPtr,  data type: unsigned char*
GSetIntPtr,    data type: int*
GSetUIntPtr,   data type: unsigned int*
GSetLongPtr,   data type: long*
GSetULongPtr,  data type: unsigned long*
GSetFloatPtr,  data type: float*
GSetDoublePtr, data type: double*

GSetStr, alias of GSetCharPtr
```

A typed GSet is simply an untyped GSet and a member `t`. This member's purpose is explained below.

Functions on typed GSet which do not depend on the type of data are simple macro calling the equivalent functions on the untyped GSet member. For example, to get the size of the set:

```
#define GSetGetSize(PtrToSet) GSetGetSize_((PtrToSet)->s)
```

Functions on typed GSet which do depend on the type of data uses the generic selection to call the appropriate function on the untyped GSet member. For example, to push data:
```
#define GSetPush(PtrToSet, Data)                                             \
  _Generic((PtrToSet),                                                       \
    GSetChar*: GSetPush_Char,                                                \
    GSetUChar*: GSetPush_UChar,                                              \
    ...
    GSetDouble*: GSetPush_Double,                                            \
    default: GSetPush_Ptr)((PtrToSet)->s, Data);
```

However the above code has the inconvenient that, due to pointers being stored as pointers to void, type checking is not inforced. This is where the member `t` is used. By adding an assignment of the data to `t`, the type of the data will be properly checked against the intended type of the GSet.

```
#define GSetPush(PtrToSet, Data)                                             \
  _Generic((PtrToSet),                                                       \
    GSetChar*: GSetPush_Char,                                                \
    GSetUChar*: GSetPush_UChar,                                              \
    ...
    GSetDouble*: GSetPush_Double,                                            \
    default: GSetPush_Ptr)((PtrToSet)->s, Data);                             \
  (PtrToSet)->t = Data
```

Trying to compile the following code:
```
GSetIntPtr* set = GSetIntPtrAlloc();
double* v = NULL;
GSetPush(set, v);
```
gives:
```
gset.h:530:17: warning: assignment to ‘int *’ from incompatible pointer type ‘double *’ [-Wincompatible-pointer-types]
  530 |   (PtrToSet)->t = Data
      |                 ^
main.c:273:1: note: in expansion of macro ‘GSetPush’
  273 | GSetPush(set, v);
      | ^~~~~~~~
```

To check the type of the returned value instead of an argument, member `t` is used as follow:

```
#define GSetPop(PtrToSet)                                                    \
  (((PtrToSet)->t =                                                          \
     _Generic((PtrToSet),                                                    \
       GSetChar*: GSetPop_Char,                                              \
       GSetUChar*: GSetPop_UChar,                                            \
       ...
       GSetDouble*: GSetPop_Double,                                          \
       default: GSetPop_Ptr)((PtrToSet)->s)) == 0 ? 0 : (PtrToSet)->t)
```
which allows to write:
```
GSetIntPtr* set = GSetIntPtrAlloc();
int* v = GSetPop(set); 
```
with again proper type checking at compilation:
```
GSetIntPtr* set = GSetIntPtrAlloc();
double* v = GSetPop(set); 
```
gives:
```
gset.h:559:3: warning: initialization of ‘double *’ from incompatible pointer type ‘int *’ [-Wincompatible-pointer-types]
  559 |   (((PtrToSet)->t =                                                          \
      |   ^
main.c:272:13: note: in expansion of macro ‘GSetPop’
  272 | double* v = GSetPop(set);
```

These tricks come at the expense of otherwise useless assignments and tests plus the memory cost of the member `t`, and the user should ponder the loss in performance against the gain in security.

## 3.3 Iterators

Manipulation of typed GSet is done through GSetIter structures. They are typed as their corresponding typed GSet and created by the same macro that creates this typed GSet. An iterator allows the user to traverse the data in a GSet backward or forward, eventually jumping over elements with a user-defined filter function.

A macro is available to loop simply on data with an iterator. For example, to print the data of a set:

```
GSetInt* set = GSetIntAlloc();
GSetPush(set, 1);
GSetPush(set, 2);
GSetIterInt* iter = GSetIterIntAlloc(set);
GSETFOR(iter) {
  printf("%d ", GSetGet(iter));
}
```

If the user needs the loop step (as a `size_t`), an enumeration can be used instead:

```
GSetInt* set = GSetIntAlloc();
GSetPush(set, 1);
GSetPush(set, 2);
GSetIterInt* iter = GSetIterIntAlloc(set);
GSETENUM(iter, step) {
  printf("%zu-th data: %d\n", step, GSetGet(iter));
}
```

Filtering is a powerful functionality of iterators. A user defined function can be assigned to an iterator, it will then act as if only data matching that filtering function were in the set. The interface of the filter function is `bool (*fun)(void *a, void *b)`, where `a` will be a pointer to the data and `b` contains eventual parameters for the filtering function. For example, if you want an iterator on positive value in a GSetInt:

```
bool FilterPositive(void* val, void* params) {
  (void)params;
  return (*(int*)val % 2 == 0);
}
...
GSetInt* set = GSetIntAlloc();
GSetPush(set, 1);
GSetPush(set, 2);
GSetIterInt* iter = GSetIterIntAlloc(set);
GSetIterSetFilter(iter, FilterPositive, NULL);
GSETFOR(iter) {
  printf("%d ", GSetGet(iter));
}
```

# 4 Interface

In the functions below `<N>` is to be replaced by the GSet identifier (`Name`) and `<T>` by the data type `Type` used in `GSETDEF(Name, Type)`

## 4.1 GSet<N>

static inline GSet<N>* GSet<N>Alloc(void);
static inline GSet<N>* GSet<N>FromArr(size_t const size, <T> const* const arr);
static inline <T>* GSet<N>ToArr(GSet<N> const* const that)
static inline void GSet<N>Flush(GSet<N>* const that);
void GSetFree(GSet<N>** const that);
void GSetPush(GSet<N>* const that, <T> const data);
void GSetAdd(GSet<N>* that, <T> const data);
void GSetAddArr(GSet<N>* that, size_t const size, <T> const* const data);
<T> GSetPop(GSet<N>* const that);
<T> GSetDrop(GSet<N>* const that);
void GSetAppend(GSet<N>* const dst, GSet<N> const* const src);
void GSetMerge(GSet<N>* const dst, GSet<N>* const src);
size_t GSetGetSize(GSet<N> const* const that);
void GSetEmpty(GSet<N>* const that);
void GSetShuffle(GSet<N>* const that)
void GSetSort(GSet<N>* const that, CmpFun, bool const inc);

## 4.2 GSetIter<N>

static inline GSetIter<N>* GSetIter<N>Alloc(GSet<N>* const set);
static inline GSetIter<N>* GSetIter<N>Clone(GSetIter<N> const* const that);
void GSetIterFree(PtrToPtrToSetIter);
<T> GSetIterGet(GSetIter<N> const* const that);
GSetGet is an alias for GSetIterGet
<T> GSetIterPick(GSetIter<N>* const that);
GSetPick is an alias for GSetIterPick
void GSetIterReset(GSetIter<N>* const that);
GSetReset is an alias for GSetIterReset
bool GSetIterNext(GSetIter<N>* const that);
GSetNext is an alias for GSetIterNext
bool GSetIterPrev(GSetIter<N>* const that);
GSetPrev is an alias for GSetIterPrev
bool GSetIterIsFirst(GSetIter<N> const* const that);
GSetIsFirst is an alias for GSetIterIsFirst
bool GSetIterIsLast(GSetIter<N> const* const that);
GSetIsLast is an alias for GSetIterIsLast
void GSetIterSetType(GSetIter<N>* const that, GSetIterType const type);
GSetIterType GSetIterGetType(GSetIter<N> const* const that)
void GSetIterSetFilter(GSetIter<N>* const that, PtrToFun, PtrToParams);
GSetSetFilter is an alias for GSetIterSetFilter
void* GSetIterGetFilterParam(GSetIter<N> const* const that);
GSetGetFilterParam is an alias for GSetIterGetFilterParam
size_t GSetIterCount(GSetIter<N> const* const that);
GSetCount is an alias for GSetIterCount

# 5 License

GSet, a C library providing a polymorphic set data structure and the functions to interact with it.
Copyright (C) 2021  Pascal Baillehache

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

