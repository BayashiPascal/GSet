# GSet

GSet is a C library providing a polymorphic set data structure and the functions to interact with it.

A GSet is a collection of element, each containing a pointer to data. These data are of type `void*` for the default `GSet` structure, but typed version of this structure can be defined in one line with a provided macro.

Available operations on a GSet are:
* push data at the head
* add data at the tail
* pop data from the head
* drop data from the tail
* iterate forward/backward on the data
* pick the current data
* shuffle the data
* sort the data with a user-defined comparison function
* foreach macro to execute a block of code on each data (available only if compiling with gcc)
* append a set at the tail of another set
* copy a GSet
* empty a GSet with/without freeing its data
* converting a GSet from/to an array

## Table Of Content

1 [Install](https://github.com/BayashiPascal/GSet/tree/master#1-install)

2 [Usage](https://github.com/BayashiPascal/GSet/tree/master#2-usage)

3 [Interface](https://github.com/BayashiPascal/GSet/tree/master#3-interface)

4 [License](https://github.com/BayashiPascal/GSet/tree/master#4-license)

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
  int val = 1;
  GSetIntPush(
    setInt,
    &val);

  // Pop the data
  int* ptrInt = GSetIntPop(setInt);
  printf("%d\n", *ptrInt);

  // Free the GSet
  GSetIntFree(&setInt);

  // Return the sucess code
  return EXIT_SUCCESS;

}
```

It can be compiled as follow:

```
gcc -std=gnu11 -c main.c
gcc main.o -lgset -lm -ltrycatchc -o main 
```

# 2.2 Define a typed GSet

To create a typed `GSet` containing data of type, for example, `struct UserData`, one can use the macro `GSETDEF(UserData, struct UserData)`. Then, all the functions defined for a `GSet` are redefined with an equivalen function named `GSetUserData...` for the type `struct UserData`. Below is an example of how it could be used:

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
  struct UserData userData = { .val = 2 };
  GSetUserDataPush(
    setUserData,
    &userData);

  // Pop the data
  struct UserData* ptrUserData = GSetUserDataPop(setUserData);
  printf("%d\n", ptrUserData->val);

  // Free the GSet
  GSetUserDataFree(&setUserData);

  // Return the sucess code
  return EXIT_SUCCESS;

}
```

Be aware that to be able to free elements in the GSetFlush, GSet requires a function `void <N>Free(T**)` to be defined before `GSETDEF(N, T)`. In the example above it could be:

```
void UserDataFree(struct UserData** const that) {
  if (that == NULL || *that == NULL) return;
  free(*that);
  *that = NULL;
}
```
# 3 Interface

Function available on non-typed GSet and typed GSet (by replacing `GSet...` by `GSet<N>...`)
```
// Create a new GSet
// Output:
//   Return the new GSet.
GSet GSetCreate(
  void);

// Allocate memory for a new GSet
// Output:
//   Return the new GSet.
GSet* GSetAlloc(
  void);

// Copy a GSet into another GSet
// Inputs:
//   that: the GSet
//    tho: the other GSet
// Output:
//   tho is first emptied and then filled with elements whose data is the
//   the data of the elements of that, in same order
void GSetCopy( 
        GSet* const that,
  GSet const* const tho);

// Empty the GSet with GSetEmpty() and free the memory it used.
// Input:
//   that: the GSet to be freed
void GSetFree(
  GSet** const that);

// Empty the GSet. Memory used by data in it is not freed.
// To empty the GSet and free data the data in it, use GSet<N>Flush() instead.
// Input:
//   that: the GSet
void GSetEmpty(
  GSet* const that);

// Add data at the head of the GSet
// Inputs:
//   that: the GSet
//   data: the data to add
void GSetPush(
  GSet* const that,
         void* const data);

// Add data at the tail of the GSet
// Inputs:
//   that: the GSet
//   data: the data to add
void GSetAdd(
  GSet* const that,
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
  GSet* const that);

// Remove and return the data at the tail of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetDrop(
  GSet* const that);

// Remove and return the data of the current element of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the data, or raise TryCatchExc_OutOfRange if there is no
//   data. If the current element is the removed one, try to move the
//   iterator to the next element, if it fails, try to the previous,
//   if it fails again, set the current element to null.
void* GSetPick(
  GSet* const that);

// Sort the elements of a GSet
// Inputs:
//   that: the GSet to sort
//   cmp: the comparison function used to sort
// It uses qsort, see man page for details. Elements are sorted in ascending
// order, relative to the comparison function cmp(a,b) which much returns
// a negative value if a<b, a positive value if a>b, and 0 if a=b
void GSetSort(
  GSet* const that,
                 int (*cmp)(void const*, void const*));

// Shuffle the elements of a GSet
// Input:
//   that: the GSet to shuffle
void GSetShuffle(
  GSet* const that);

// Convert the GSet to an array of pointers to its data
// Input:
//   that: the GSet to convert
// Output:
//   Return an array of pointers to data in the same order as the current
//   element order
void** GSetToArrayOfPtr(
  GSet* const that);

// Convert an array of pointers to a GSet
// Inputs:
//   that: the GSet
//    arr: the array to convert
//   size: the size of the array
// Output:
//   The GSet is first emptied and then filled with elements whose data is the
//   pointers in the array in the order of the array
void GSetFromArrayOfPtr(
  GSet* const that,
        void** const arr,
           int const size);

// Append a GSet at the end of another GSet
// Inputs:
//   that: the GSet
//    tho: the other GSet
// Output:
//   tho is appended at the end of that and becomes empty after this operation
void GSetAppend(
  GSet* const that,
  GSet* const tho);

// Get the data of the current element in the GSet
// Input:
//   that: the GSet
// Output:
//   Return the pointer to the data of the current element
void* GSetCurData(
  GSet const* const that);

// Get the size of the GSet
// Input:
//   that: the GSet
// Output:
//   Return the size of the data set
int GSetGetSize(
  GSet const* const that);

// Reset the current element of the iterator according to the direction
// of the iteration.
// Input:
//   that: the GSet
void GSetIterReset(
  GSet* const that);

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
  GSet* const that);

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
  GSet* const that);

// Set the iteration type of a GSet
// Inputs:
//        that: the GSet
//   iteration: the type of iteration
void GSetIterSet(
        GSet* const that,
  enum GSetIteration const iteration);

// Loop on each data Data (of type Type) of the GSet Set.
// The current data can be accessed through the variable <Data>,
// and its index with GSetIterIdx(). Uses Set's iterator, which is first
// reset, to iterate on the data.
#define GSETFOR(Data, Set)
```
Available only on typed GSet:
```
// Empty a GSet and free the data it contains
// Input:
//   that: the GSet
static inline void GSet<N>Flush(GSet<N>* const that);

// Convert a GSet to an array
// Input:
//   that: the GSet
// Output:
//   Return an array of data in the same order as the current
//   element order. The data of the array are shallow copies of the
//   data of the elements.
static inline <T>* GSet<N>ToArrayOfData(GSet<N>* const that);

// Convert an array to a GSet
// Inputs:
//   that: the GSet
//    arr: the array to convert
//   size: the size of the array
// Output:
//   The GSet is first emptied and then filled with elements whose data is a
//   a pointer to the data in the array in the order of the array
static inline void GSet<N>FromArrayOfData(GSet<N>* const that, <T>* const arr, int size);

// Release memory used by an automatically allocated GSet
// Input:
//   that: the GSet
static inline void GSet<N>Release(GSet<N>* const that);

```

# 4 License

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

