// *************** GSET.C ***************

// ================= Include ==================
#include "gset.h"
#if BUILDMODE == 0
#include "gset-inline.c"
#endif

#define rnd() (float)(rand())/(float)(RAND_MAX)

// ================ Functions implementation ==================

// Function to create a new GSet,
// Return a pointer toward the new GSet
GSet* GSetCreate(void) {
  // Allocate memory for the GSet
  GSet* s = PBErrMalloc(GSetErr, sizeof(GSet));
  // Set the pointer to head and tail, and the number of element
  s->_head = NULL;
  s->_tail = NULL;
  s->_nbElem = 0;
  s->_indexLastGot = 0;
  s->_lastGot = NULL;
  // Return the new GSet
  return s;
}

// Function to clone a GSet,
// Return a pointer toward the new GSet
GSet* GSetClone(const GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Create the clone
  GSet* c = GSetCreate();
  // Set a pointer to the head of the set
  GSetElem* ptr = (GSetElem*)GSetHeadElem(that);
  // While the pointer is not at the end of the set
  while (ptr != NULL) {
    // Append the data of the current pointer to the clone
    GSetAppend(c, GSetElemData(ptr));
    // Copy the sort value
    GSetElemSetSortVal((GSetElem*)GSetTailElem(c), 
      GSetElemGetSortVal(ptr));
    // Move the pointer to the next element
    ptr = (GSetElem*)GSetElemNext(ptr);
  }
  // Return the clone
  return c;
}

// Function to free the memory used by the GSet
void _GSetFree(GSet** that) {
  if (that == NULL || *that == NULL) return;
  // Empty the GSet
  GSetFlush(*that);
  // Free the memory
  free(*that);
  // Set the pointer to null
  *that = NULL;
}

// Function to print a GSet
// Use the function 'printData' to print the data pointed to by 
// the elements, and print 'sep' between each element
// If printData is null, print the pointer value instead
// Do nothing if arguments are invalid
void _GSetPrint(GSet* const that, FILE* const stream, 
  void(*printData)(const void* const data, FILE* const stream), 
  const char* const sep) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (stream == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'stream' is null");
    PBErrCatch(GSetErr);
  }
  if (sep == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'sep' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer to the head element
  GSetElem* p = (GSetElem*)GSetHeadElem(that);
  // While the pointer hasn't reach the end
  while (p != NULL) {
    // If there is a print function for the data
    if (printData != NULL) {
      // Use the argument function to print the data of the 
      // current element
      (*printData)(GSetElemData(p), stream);
    // Else, there is no print function for the data
    } else {
      // Print the pointer value instead
      fprintf(stream, "%p", GSetElemData(p));
    }
    // Move to the next element
    p = (GSetElem*)GSetElemNext(p);
    // If there is a next element
    if (p != NULL)
      // Print the separator
      fprintf(stream, "%s", sep);
  }
  // Flush the stream
  fflush(stream);
}

// Function to insert an element pointing toward 'data' at the 
// position defined by 'v' sorting the set in increasing order
void _GSetAddSort(GSet* const that, void* const data, 
  const double v) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Allocate memory for the new element
  GSetElem* e = PBErrMalloc(GSetErr, sizeof(GSetElem));
  // Memorize the pointer toward data
  GSetElemSetData(e, data);
  // Memorize the sorting value
  GSetElemSetSortVal(e, v);
  // If the GSet is empty
  if (that->_nbElem == 0) {
    // Add the element at the head of the GSet
    that->_head = e;
    that->_tail = e;
    GSetElemSetNext(e, NULL);
    GSetElemSetPrev(e, NULL);
  } else {
    // Set a pointer to the head of the GSet
    GSetElem* p = (GSetElem*)GSetHeadElem(that);
    // While the pointed element has a lower value than the 
    // new element, move the pointer to the next element
    while (p != NULL && GSetElemGetSortVal(p) <= v) 
      p = (GSetElem*)GSetElemNext(p);
    // Set the next element of the new element to the current element
    GSetElemSetNext(e, p);
    // If the current element is not null
    if (p != NULL) {
      // Insert the new element inside the list of elements before p
      GSetElemSetPrev(e, (GSetElem*)GSetElemPrev(p));
      if (GSetElemPrev(p) != NULL) 
        GSetElemSetNext((GSetElem*)GSetElemPrev(p), e);
      else
        that->_head = e;
      GSetElemSetPrev(p, e);
    // Else, if the current element is null
    } else {
      // Insert the new element at the tail of the GSet
      GSetElemSetPrev(e, (GSetElem*)GSetTailElem(that));
      if (GSetTailElem(that) != NULL) 
        GSetElemSetNext((GSetElem*)GSetTailElem(that), e);
      that->_tail = e;
      if (GSetHeadElem(that) == NULL) 
        that->_head = e;
    }
  }
  // Increment the number of elements
  ++(that->_nbElem);
}

// Function to insert an element pointing toward 'data' at the 
// 'iElem'-th position 
// If 'iElem' is greater than or equal to the number of element
// in the GSet, elements pointing toward null data are added
// If the data is inserted inside the set, the current elements from
// the iElem-th elem are pushed 
void _GSetInsert(GSet* const that, void* const data, 
  const long iElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0) {
    GSetErr->_type = PBErrTypeInvalidArg;
    sprintf(GSetErr->_msg, "'iElem' is invalid (%ld>=0)", iElem);
    PBErrCatch(GSetErr);
  }
#endif
  // If iElem is greater than the number of elements, append
  // elements pointing toward null data to fill in the gap
  while (iElem > that->_nbElem)
    GSetAppend(that, NULL);
  // If iElem is in the list of element or at the tail
  if (iElem <= that->_nbElem + 1) {
    // If the insert position is the head
    if (iElem == 0) {
      // Push the data
      GSetPush(that, data);
    // Else, if the insert position is the tail
    } else if (iElem == that->_nbElem) {
      // Append data
      GSetAppend(that, data);
    // Else, the insert position is inside the list
    } else {
      // Allocate memory for the new element
      GSetElem* e = PBErrMalloc(GSetErr, sizeof(GSetElem));
      // Memorize the pointer toward data
      GSetElemSetData(e, data);
      // By default set the sorting value to 0.0
      GSetElemSetSortVal(e, 0.0);
      // Set a pointer toward the head of the GSet
      GSetElem* p = (GSetElem*)GSetHeadElem(that);
      // Move the pointer to the iElem-th element
      for (long i = iElem; i > 0 && p != NULL; 
        --i, p = (GSetElem*)GSetElemNext(p));
      // Insert the element before the pointer
      GSetElemSetNext(e, p);
      GSetElemSetPrev(e, (GSetElem*)GSetElemPrev(p));
      GSetElemSetPrev(p, e);
      GSetElemSetNext((GSetElem*)GSetElemPrev(e), e);
      // Increment the number of elements
      ++(that->_nbElem);
    }
  }
}

// Function to sort the element of the gset in increasing order of 
// _sortVal
// Do nothing if arguments are invalid or the sort failed
static GSet* GSetSortRec(GSet** s);
void _GSetSort(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Create a clone of the original set
  GSet* clone = GSetClone(that);
  // Create recursively the sorted set
  GSet* res = GSetSortRec(&clone);
  // If we could sort the set
  if (res != NULL) {
    // Update the original set with the result one
    GSetFlush(that);
    memcpy(that, res, sizeof(GSet));
    // Free the memory used by the result set
    free(res);
    res = NULL;
  }
}
GSet* GSetSortRec(GSet** s) {
  // Declare a variable for the result
  GSet* res = NULL;
  // If the set contains no element or one element
  if ((*s)->_nbElem == 0 || (*s)->_nbElem == 1) {
    // Return the set
    res = *s;
  // Else, the set contains several elements
  } else {
    // Create two sets, one for elements lower than the pivot
    // one for elements greater or equal than the pivot
    GSet* lower = GSetCreate();
    GSet* greater = GSetCreate();
    res = GSetCreate();
    
    // --------------------------
    // Selecting the pivot as the middle element seemed to me better
    // but test with UnitTestGSetSortBig proved me wrong: 1492/2060/2554
    // --------------------------
    
    // Declare a variable to memorize the pivot, which is equal
    // to the sort value of the first element of the set
    float pivot = GSetElemGetSortVal(GSetHeadElem(*s));
    // Pop the pivot and put it in the result
    void* data = GSetPop(*s);
    GSetAppend(res, data);
    GSetElemSetSortVal((GSetElem*)GSetHeadElem(res), pivot);
    // Pop all the elements one by one from the set
    while ((*s)->_nbElem != 0) {
      // Declare a variable to memorize the sort value of the head
      // element
      float val = GSetElemGetSortVal((GSetElem*)GSetHeadElem(*s));
      // Pop the head element
      data = GSetPop(*s);
      // If the poped element has a sort value equal to the pivot
      if (fabs(val - pivot) < GSET_EPSILON) {
        // Insert it in the result set
        GSetAppend(res, data);
        // Copy the sort value
        GSetElemSetSortVal((GSetElem*)GSetTailElem(res), val);
      // If the poped element has a sort value lower than the pivot
      } else if (val < pivot) {

        // --------------------------
        // The following seemed to me a good idea but test with 
        // UnitTestGSetSortBig proved me wrong: 1496/2054/2626
        // Insert at the beginning if the sort value is lower or equal
        // than the sort value of the head of the lower set, or if it's 
        // empty
        // Else, insert at the end of the lower set
        // --------------------------

        // Insert it in the lower set
        GSetAppend(lower, data);
        // Copy the sort value
        GSetElemSetSortVal((GSetElem*)GSetTailElem(lower), val);
      // Else, the poped element has a sort value greater than  
      // the pivot
      } else {

        // --------------------------
        // The following seemed to me a good idea but test with 
        // UnitTestGSetSortBig proved me wrong: 1496/2054/2626
        // Insert at the beginning if the sort value is lower or equal
        // than the sort value of the head of the greater set, or if it's 
        // empty
        // Else, insert at the end of the greater set
        // --------------------------

        // Insert it in the greater set
        GSetAppend(greater, data);
        // Copy the sort value
        GSetElemSetSortVal((GSetElem*)GSetTailElem(greater), val);
      }
    }
    // At the end of the loop the original set is empty and we 
    // don't need it anymore
    GSetFree(s);
    // Sort the two half
    GSet* sortedLower = GSetSortRec(&lower);
    GSet* sortedGreater = GSetSortRec(&greater);
    // Merge back the sorted two halves and the pivot
    GSetMerge(sortedLower, res);
    GSetMerge(sortedLower, sortedGreater);
    GSetFree(&res);
    res = sortedLower;
    GSetFree(&sortedGreater);
  }
  // Return the result
  return res;
}

// Move the 'iElem'-th element to the 'pos' index in the GSet
void _GSetMoveElem(GSet* const that, const long iElem, const long pos) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenBrushErr->_type = PBErrTypeNullPointer;
    sprintf(GenBrushErr->_msg, "'that' is null");
    PBErrCatch(GenBrushErr);
  }
  if (iElem < 0 || iElem >= GSetNbElem(that)) {
    GenBrushErr->_type = PBErrTypeInvalidArg;
    sprintf(GenBrushErr->_msg, "'iElem' is invalid (0<=%ld<%ld)",
      iElem, GSetNbElem(that));
    PBErrCatch(GenBrushErr);
  }
  if (pos < 0 || pos >= GSetNbElem(that)) {
    GenBrushErr->_type = PBErrTypeInvalidArg;
    sprintf(GenBrushErr->_msg, "'pos' is invalid (0<=%ld<%ld)",
      pos, GSetNbElem(that));
    PBErrCatch(GenBrushErr);
  }
#endif
  // If the origin and destination position are the same
  // there is nothing to do
  if (iElem == pos)
    return;
  // Get a pointer to the moved element
  GSetElem* elem = (GSetElem*)GSetElement(that, iElem);
  //Declare two variables to memorize the sort value and data
  // of the moved element
  float sortVal = GSetElemGetSortVal(elem);
  void* data = GSetElemData(elem);
  // Remove the moved element
  GSetRemove(that, iElem);
  // Insert  new element
  GSetInsert(that, data, pos);
  // Get a pointer to the newly inserted element
  elem = (GSetElem*)GSetElement(that, pos);
  // Correct the sorted value with the original value
  GSetElemSetSortVal(elem, sortVal);
}

// Return the number of (GSetElem._data=='data') in the GSet 'that'
long _GSetCount(const GSet* const that, const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare a variable to memorize the result
  long nb = 0;
  // If the set is not empty
  if (GSetNbElem(that) > 0) {
    // Loop on the set's elements
    GSetIterForward iter = GSetIterForwardCreateStatic(that);
    do {
      // If the current element's data is the searched data
      if (GSetIterGet(&iter) == data)
        // Increment the result
        ++nb;
    } while (GSetIterStep(&iter));
  }
  // return the result
  return nb;
}

// Create a new GSetIterForward for the GSet 'set'
// The iterator is reset upon creation
GSetIterForward* _GSetIterForwardCreate(GSet* const set) {
#if BUILDMODE == 0
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Allocate memory
  GSetIterForward* ret = 
    PBErrMalloc(GSetErr, sizeof(GSetIterForward));
  // Set properties
  ret->_set = set;
  ret->_curElem = (GSetElem*)GSetHeadElem(set);
  // Return the new iterator
  return ret;
}

// Create a new GSetIterBackward for the GSet 'set'
// The iterator is reset upon creation
GSetIterBackward* _GSetIterBackwardCreate(GSet* const set) {
#if BUILDMODE == 0
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Allocate memory
  GSetIterBackward* ret = 
    PBErrMalloc(GSetErr, sizeof(GSetIterBackward));
  // Set properties
  ret->_set = set;
  ret->_curElem = set->_tail;
  // Return the new iterator
  return ret;
}

// Free the memory used by a GSetIterForward (not by its attached GSet)
// Do nothing if arguments are invalid
void GSetIterForwardFree(GSetIterForward** that) {
  // Check arguments
  if (that == NULL || *that == NULL)
    return;
  (*that)->_set = NULL;
  (*that)->_curElem = NULL;
  free(*that);
  *that = NULL;
}

// Free the memory used by a GSetIterBackward (not by its attached GSet)
// Do nothing if arguments are invalid
void GSetIterBackwardFree(GSetIterBackward** that) {
  // Check arguments
  if (that == NULL || *that == NULL)
    return;
  (*that)->_set = NULL;
  (*that)->_curElem = NULL;
  free(*that);
  *that = NULL;
}

// Clone a GSetIterForward
GSetIterForward* GSetIterForwardClone(
  const GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Create the clone
  GSetIterForward* ret = GSetIterForwardCreate(that->_set);
  ret->_curElem = that->_curElem;
  // return the clone
  return ret;
}

// Clone a GSetIterBackward
GSetIterBackward* GSetIterBackwardClone(
  const GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Create the clone
  GSetIterBackward* ret = GSetIterBackwardCreate(that->_set);
  ret->_curElem = that->_curElem;
  // return the clone
  return ret;
}

// Shuffle the GSet 'that'
// The random generator must have been initialized before calling 
// this function
// This function modifies the _sortVal of each elements in 'that'
void GSetShuffle(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // If the set is empty there is nothing to do
#if BUILDMODE == 0
  if (GSetNbElem(that) <= 800)
#else
  if (GSetNbElem(that) <= 650)
#endif
    GSetShuffleB(that);
  else 
    GSetShuffleA(that);
}

void GSetShuffleA(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the sort value randomly then sort the GSet
  // If the set is empty there is nothong to do
  if (GSetNbElem(that) == 0)
    return;
  // Create an iterator on the set
  GSetIterForward iter = GSetIterForwardCreateStatic(that);
  // Loop on the set
  do {
    // Set a random value to the element
    GSetElemSetSortVal((GSetElem*)GSetIterGetElem(&iter), rnd());
  } while (GSetIterStep(&iter));
  // Sort the set
  GSetSort(that);
}

void GSetShuffleB(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // AddSort each element with a random value in a new GSet 
  // Create a temporary set
  GSet shuffled = GSetCreateStatic();
  // Append all the elements of the initial set, sorted with a random
  // value
  while (GSetNbElem(that) > 0) {
    void* data = GSetPop(that);
    GSetAddSort(&shuffled, data, rnd());
  }
  // put back the shuffled set into the original set
  GSetMerge(that, &shuffled);
}

void GSetShuffleC(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Fischer-Yates algorithm
  for (long i = GSetNbElem(that); i--;) {
     long j = (long)round(rnd() * (float)i);
     GSetSwitch(that, i, j);
  }
}

