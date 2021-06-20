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
gcc -std=c17 -c main.c
gcc main.o -lgset -lm -ltrycatchc -o main 
```

## 2.2 User defined typed GSet

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

It is not possible to create a set of pointer to functions, but there is a work-around: define a structure with a member as the pointer to function and create a set for this structure.

## 2.3 Unit tests

The file `main.c` contains unit test for the library, which can be compiled as follow:

```
gcc -std=c17 -I./ -pedantic -Wall -Wextra -Wno-clobbered -Og -ggdb -g3 -DBUILDMODE=0 -c main.c 
gcc main.o gset.o -lm -ltrycatchc -o main 
``` 

It has been checked that the compilation generates no warning, as well as running the unit test through `valgrind` generates no warning.

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
  struct GSetElem* first;
  struct GSetElem* last;
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

`static inline GSet<N>* GSet<N>Alloc(void);`

Create a new instance of `GSet<N>`.

`static inline GSet<N>* GSet<N>FromArr(size_t const size, <T> const* const arr);`

Create a new instance of `GSet<N>` filled with the data in the array `arr` of size `size`.

`void GSetFree(GSet<N>** const that);`

Free the memory used by the set `*that` and set `*that` to `NULL`. The memory used by the data in the set is not freed, use `GSetFlush` instead if you want to free the data too (cf below).

`void GSetPush(GSet<N>* const that, <T> const data);`

Push the `data` at the head of the set `that`.

`void GSetPushArr(GSet<N>* that, size_t const size, <T> const* const arr);`

Push the data in the array `arr`, containing `size` data, at the head of the set `that`.

`void GSetAdd(GSet<N>* that, <T> const data);`

Add the `data` at the tail of the set `that`.

`void GSetAddArr(GSet<N>* that, size_t const size, <T> const* const arr);`

Add the data in the array `arr`, containing `size` data, at the tail of the set `that`.

`<T> GSetPop(GSet<N>* const that);`

Remove and return the data at the head of the set `that`. Raise the exception `TryCatchExc_OutOfRange` if there is no data.

`<T> GSetDrop(GSet<N>* const that);`

Remove and return the data at the tail of the set `that`. Raise the exception `TryCatchExc_OutOfRange` if there is no data.

`void GSetEmpty(GSet<N>* const that);`

Remove all the data in the set `that`. The memory used by the data is not freed.

`static inline void GSet<N>Flush(GSet<N>* const that);`

Remove all the data in the set `that`. The memory used by the data is freed by calling the user defined function `<N>Free(<T>* const)`. `GSet<N>Flush` is only available if `<T>` is a pointer. The library provides the following `<N>Free` functions:

```
CharPtrFree(char** const that);
UCharPtrFree(unsigned char** const that);
IntPtrFree(int** const that);
UIntPtrFree(unsigned int** const that);
LongPtrFree(long** const that);
ULongPtrFree(unsigned long** const that);
FloatPtrFree(float** const that);
DoublePtrFree(double** const that);
StrFree(char** const that);
```

The user can define a `<N>Free` function as follow:

```
struct Dummy {
  ...
};
void DummyFree(struct Dummy** const that) {
  if (that == NULL || *that == NULL) return;
  // Free the members of struct Dummy here
  free(*that); *that = NULL;
}
```

`void GSetAppend(GSet<N>* const dst, GSet<N> const* const src);`

Add the data in the set `src` at the tail of the set `dst`.

`void GSetMerge(GSet<N>* const dst, GSet<N>* const src);`

Remove the data in the set `src` and add them at the tail of the set `dst`.

`size_t GSetGetSize(GSet<N> const* const that);`

Get the number of data in the set `that`.

`void GSetShuffle(GSet<N>* const that)`

Shuffle the data in the set `that`.

`void GSetSort(GSet<N>* const that, int (* const cmp)(void const*, void const*), bool const inc);`

Sort the data in the set `that` according to the sorting function `cmp`, in increasing order if `inc` is true, in decreasing order else. The sorting function takes two arguments `a` and `b` which are two pointers to data in the set, and returns an integer lower than 0 if `a<b`, greater than 0 if `a>b`, and equal to 0 if `a=b`. The library provides the following default sorting function for basic types:

```
int GSetCharCmp(void const* a, void const* b) {
  return (*(char const*)a < *(char const*)b ? -1 :
          *(char const*)a > *(char const*)b ? 1 : 0);
}
int GSetUCharCmp( void const* a, void const* b) {
  return (*(unsigned char const*)a < *(unsigned char const*)b ? -1 :
          *(unsigned char const*)a > *(unsigned char const*)b ? 1 : 0);
}
int GSetIntCmp(void const* a, void const* b) {
  return (*(int const*)a < *(int const*)b ? -1 :
          *(int const*)a > *(int const*)b ? 1 : 0);
}
int GSetUIntCmp(void const* a, void const* b) {
  return (*(unsigned int const*)a < *(unsigned int const*)b ? -1 :
          *(unsigned int const*)a > *(unsigned int const*)b ? 1 : 0);
}
int GSetLongCmp(void const* a, void const* b) {
  return (*(long const*)a < *(long const*)b ? -1 :
          *(long const*)a > *(long const*)b ? 1 : 0);
}
int GSetULongCmp(void const* a, void const* b) {
  return (*(unsigned long const*)a < *(unsigned long const*)b ? -1 :
          *(unsigned long const*)a > *(unsigned long const*)b ? 1 : 0);
}
int GSetFloatCmp(void const* a, void const* b) {
  float x = *(float*)a;
  float y = *(float*)b;
  if ((x - y) > DBL_EPSILON) return 1;
  else if ((x - y) < -DBL_EPSILON) return -1;
  else return 0;
}
int GSetDoubleCmp(void const* a, void const* b) {
  double x = *(double*)a;
  double y = *(double*)b;
  if ((x - y) > DBL_EPSILON) return 1;
  else if ((x - y) < -DBL_EPSILON) return -1;
  else return 0;
}
int GsetCharPtrCmp(void const* a, void const* b) {
  char const* sa = *(char* const*)a;
  char const* sb = *(char* const*)b;
  if (sa == NULL && sb == NULL) return 0;
  if (sa == NULL && sb != NULL) return -1;
  if (sa != NULL && sb == NULL) return 1;
  return strcmp(sa, sb);
}
```

## 4.2 GSetIter<N>

`static inline GSetIter<N>* GSetIter<N>Alloc(GSet<N>* const set);`

Create a new instance of `GSetIter<N>` to iterate on the set `set` of default type `GSetIterForward`, and default filtering function `NULL` (i.e. no filtering).

`static inline GSetIter<N>* GSetIter<N>Clone(GSetIter<N> const* const that);`

Create a clone of the iterator `that` (new instance with same type, set, current position, filtering function).

`void GSetIterFree(GSetIter<N>** const that);`

Free the memory used by the iterator `*that` and set `*that` to `NULL`.

`<T> GSetIterGet(GSetIter<N> const* const that);`

Return the current data. Raise the exception `TryCatchExc_OutOfRange` if there is no data.

`<T> GSetIterPick(GSetIter<N>* const that);`

Remove and return the current data. Raise the exception `TryCatchExc_OutOfRange` if there is no data.

`void GSetIterReset(GSetIter<N>* const that);`

Reset the iterator, i.e. it's current data becomes the first one according to its type and filter function.

`bool GSetIterNext(GSetIter<N>* const that);`

Move the iterator to the next data according to its type and filter function and return true if there was a next data, or let the current data unchanged and return false if there was no next data.

`bool GSetIterPrev(GSetIter<N>* const that);`

Move the iterator to the previous data according to its type and filter function and return true if there was a previous data, or let the current data unchanged and return false if there was no previous data.

`bool GSetIterIsFirst(GSetIter<N> const* const that);`

Return true if the current data is the first data according to the iterator's type and filter function, else return false, unless there is no current data in which case raise the exception `TryCatchExc_OutOfRange`.

`bool GSetIterIsLast(GSetIter<N> const* const that);`

Return true if the current data is the last data according to the iterator's type and filter function, else return false, unless there is no current data in which case raise the exception `TryCatchExc_OutOfRange`.

`void GSetIterSetType(GSetIter<N>* const that, GSetIterType const type);`

Set the type of iteration (forward/backward) of the iterator `that` to `type`.

`GSetIterType GSetIterGetType(GSetIter<N> const* const that);`

Get the type of iteration (forward/backward) of the iterator `that`.

`void GSetIterSetFilter(GSetIter<N>* const that, GSetIterFilterFun fun, void* params);`

Set the filter function of the iterator `that` to `fun` and the filter function's second argument to `params`. `fun` interface is `typedef bool (*GSetIterFilterFun)(void*, void*);`, cf 3.3 for details.

`void* GSetIterGetFilterParam(GSetIter<N> const* const that);`

Return the filter function's second argument for the iterator `that`.

`size_t GSetIterCount(GSetIter<N> const* const that);`

Return the number of data traversed by the iterator given its filter function.

`static inline <T>* GSet<N>ToArr(GSet<N> const* const that)`

Return the data traversed by the iterator given its filter function as an array of type `<T>`.

The following alias are declared as shortcuts:
```
GSetGet is an alias for GSetIterGet
GSetPick is an alias for GSetIterPick
GSetReset is an alias for GSetIterReset
GSetNext is an alias for GSetIterNext
GSetPrev is an alias for GSetIterPrev
GSetIsFirst is an alias for GSetIterIsFirst
GSetIsLast is an alias for GSetIterIsLast
GSetSetFilter is an alias for GSetIterSetFilter
GSetGetFilterParam is an alias for GSetIterGetFilterParam
GSetCount is an alias for GSetIterCount
```

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

