// *************** GSET-INLINE.C ***************

// ================ Functions implementation ====================

// Static constructors for GSet
#if BUILDMODE != 0
inline
#endif 
GSet GSetCreateStatic(void) {
  // Declare a GSet and set the properties
  GSet s = {._head = NULL, ._tail = NULL, ._nbElem = 0};
  // Return the GSet
  return s;
}

// Function to empty the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetFlush(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Pop element until the GSet is null
  while (GSetPop(that) || that->_nbElem > 0); 
}

// Function to insert an element pointing toward 'data' at the 
// head of the GSet
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void _GSetPush(GSet* const that, void* const data) {
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
  // By default set the sorting value to 0.0
  GSetElemSetSortVal(e, 0.0);
  // Add the element at the head of the GSet 
  GSetElemSetPrev(e, NULL);
  if (GSetHeadElem(that) != NULL) 
    GSetElemSetPrev((GSetElem*)GSetHeadElem(that), e);
  GSetElemSetNext(e, (GSetElem*)GSetHeadElem(that));
  that->_head = e;
  if (GSetTailElem(that) == NULL) 
    that->_tail = e;
  // Increment the number of elements in the GSet
  ++(that->_nbElem);
}

// Function to insert an element pointing toward 'data' at the 
// tail of the GSet
#if BUILDMODE != 0
inline
#endif 
void _GSetAppend(GSet* const that, void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  GSetElem* e = PBErrMalloc(GSetErr, sizeof(GSetElem));
  if (e != NULL) {
    GSetElemSetData(e, data);
    GSetElemSetSortVal(e, 0.0);
    GSetElemSetPrev(e, (GSetElem*)GSetTailElem(that));
    GSetElemSetNext(e, NULL);
    if (GSetTailElem(that) != NULL) 
      GSetElemSetNext((GSetElem*)GSetTailElem(that), e);
    that->_tail = e;
    if (GSetHeadElem(that) == NULL) 
      that->_head = e;
    ++(that->_nbElem);
  }
}

// Function to remove the element at the head of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* _GSetPop(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  void* ret = NULL;
  GSetElem* p = (GSetElem*)GSetHeadElem(that);
  if (p != NULL) {
    ret = GSetElemData(p);
    that->_head = (GSetElem*)GSetElemNext(p);
    if (GSetElemNext(p) != NULL) 
      GSetElemSetPrev((GSetElem*)GSetElemNext(p), NULL);
    GSetElemSetNext(p, NULL);
    GSetElemSetData(p, NULL);
    if (GSetTailElem(that) == p) 
      that->_tail = NULL;
    free(p);
    --(that->_nbElem);
  }
  return ret;
}

// Function to remove the element at the tail of the GSet
// Return the data pointed to by the removed element, or null if the 
// GSet is empty
#if BUILDMODE != 0
inline
#endif 
void* _GSetDrop(GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  void* ret = NULL;
  GSetElem* p = (GSetElem*)GSetTailElem(that);
  if (p != NULL) {
    ret = GSetElemData(p);
    that->_tail = (GSetElem*)GSetElemPrev(p);
    if (GSetElemPrev(p) != NULL) 
      GSetElemSetNext((GSetElem*)GSetElemPrev(p), NULL);
    GSetElemSetPrev(p, NULL);
    GSetElemSetData(p, NULL);
    if (GSetHeadElem(that) == p) 
      that->_head = NULL;
    free(p);
    --(that->_nbElem);
  }
  return ret;
}

// Function to remove the element 'elem' of the GSet
// Return the data pointed to by the removed element
// The GSetElem is freed and *elem == NULL after calling this function
#if BUILDMODE != 0
inline
#endif 
void* _GSetRemoveElem(GSet* const that, GSetElem** elem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (elem == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'elem' is null");
    PBErrCatch(GSetErr);
  }
  if (*elem == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'*elem' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Variable to memorize the return value
  void* ret = NULL;
  // Memorize the data at iElem-th position
  ret = GSetElemData(*elem);
  // Remove the element
  if (GSetElemNext(*elem) != NULL) 
    GSetElemSetPrev((GSetElem*)GSetElemNext(*elem), 
      (GSetElem*)GSetElemPrev(*elem));
  if (GSetElemPrev(*elem) != NULL) 
    GSetElemSetNext((GSetElem*)GSetElemPrev(*elem), 
      (GSetElem*)GSetElemNext(*elem));
  if (GSetHeadElem(that) == *elem) 
    that->_head = (GSetElem*)GSetElemNext(*elem);
  if (that->_tail == (*elem)) 
    that->_tail = (GSetElem*)GSetElemPrev(*elem);
  GSetElemSetNext(*elem, NULL);
  GSetElemSetPrev(*elem, NULL);
  GSetElemSetData(*elem, NULL);
  free((*elem));
  *elem = NULL;
  // Decrement the number of elements
  --(that->_nbElem);
  // Return the data
  return ret;
}

// Function to remove the first element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveFirst(GSet* const that, const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Get the first element pointing to 'data'
  GSetElem* elem = (GSetElem*)GSetFirstElem(that, data);
  // If we could find an element
  if (elem != NULL)
    // Remove this element
    GSetRemoveElem(that, &elem);
}

// Function to remove the last element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveLast(GSet* const that, const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Get the last element pointing to 'data'
  GSetElem* elem = (GSetElem*)GSetLastElem(that, data);
  // If we could find an element
  if (elem != NULL)
    // Remove this element
    GSetRemoveElem(that, &elem);
}

// Function to remove the element at the 'iElem'-th position of the GSet
// Return the data pointed to by the removed element
#if BUILDMODE != 0
inline
#endif 
void* _GSetRemove(GSet* const that, const long iElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%ld<%ld)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Variable to memorize the return value
  void* ret = NULL;
  // Set a pointer to the head of the Gset
  GSetElem* p = (GSetElem*)GSetHeadElem(that);
  // Move the pointer to the iElem-th element
  for (long i = iElem; i > 0 && p != NULL; 
    --i, p = (GSetElem*)GSetElemNext(p));
  // Memorize the data at iElem-th position
  ret = GSetElemData(p);
  // Remove the element
  if (GSetElemNext(p) != NULL) 
    GSetElemSetPrev((GSetElem*)GSetElemNext(p), 
      (GSetElem*)GSetElemPrev(p));
  if (GSetElemPrev(p) != NULL) 
    GSetElemSetNext((GSetElem*)GSetElemPrev(p), 
      (GSetElem*)GSetElemNext(p));
  if (GSetHeadElem(that) == p) 
    that->_head = (GSetElem*)GSetElemNext(p);
  if (that->_tail == p) 
    that->_tail = (GSetElem*)GSetElemPrev(p);
  GSetElemSetNext(p, NULL);
  GSetElemSetPrev(p, NULL);
  GSetElemSetData(p, NULL);
  free(p);
  // Decrement the number of elements
  --(that->_nbElem);
  // Return the data
  return ret;
}

// Function to remove all the selement of the GSet pointing to 'data'
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void _GSetRemoveAll(GSet* const that, const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the tail of the GSet
  GSetElem* p = (GSetElem*)GSetTailElem(that);
  // Loop on elements until we reached the head of the list
  while (p != NULL) {
    // If the element points toward data
    if (GSetElemData(p) == data) {
      // Memorize the previous element before deleting
      GSetElem* prev = (GSetElem*)GSetElemPrev(p);
      // Remove the element
      GSetRemoveElem(that, &p);
      // Continue with previous element
      p = prev;
    // Else, the element doesn't point toward data
    } else {
      // Continue with previous element
      p = (GSetElem*)GSetElemPrev(p);
    }
  }
}

// Function to get the data at the GSetElem
#if BUILDMODE != 0
inline
#endif 
void* GSetElemData(const GSetElem* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return that->_data;
}

// Function to get the data at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetGet(const GSet* const that, const long iElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%ld<%ld)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data of the iElem-th element
  return GSetElemData(GSetElement(that, iElem));
}

// Function to get the data at first position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetHead(const GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data of the first element
  return GSetElemData(GSetHeadElem(that));
}

// Function to get the data at last position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* _GSetTail(const GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data of the last element
  return GSetElemData(GSetTailElem(that));
}

// Function to get the GSetElem at first position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetHeadElem(const GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the first element
  return that->_head;
}

// Function to get the GSetElem at last position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetTailElem(const GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the last element
  return that->_tail;
}

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetElement(const GSet* const that, const long iElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeInvalidArg;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%ld<%ld)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer for the return value
  GSetElem* ret = NULL;
  // Set the pointer to the head of the GSet
  ret = (GSetElem*)GSetHeadElem(that);
  // Move to the next element iElem times
  for (long i = iElem; i > 0 && ret != NULL; 
    --i, ret = (GSetElem*)GSetElemNext(ret));
  // Return the element
  return ret;
}

// Function to get the index of the first element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
long _GSetGetIndexFirst(const GSet* const that, const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the head of the GSet
  GSetElem* p = (GSetElem*)GSetHeadElem(that);
  // Set a variable to memorize index
  long index = 0;
  // Loop on elements until we have found the 
  // requested data or reached the end of the list
  while (p != NULL && GSetElemData(p) != data) {
    ++index;
    p = (GSetElem*)GSetElemNext(p);
  }
  // If the pointer is null it means the data wasn't in the GSet
  if (p == NULL)
    index = -1;
  // Return the index
  return index;
}

// Function to get the index of the last element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
long _GSetGetIndexLast(const GSet* const that, const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the tail of the GSet
  GSetElem* p = (GSetElem*)GSetTailElem(that);
  // Set a variable to memorize index
  long index = that->_nbElem - 1;
  // Loop on elements until we have found the 
  // requested data or reached the head of the list
  while (p != NULL && GSetElemData(p) != data) {
    --index;
    p = (GSetElem*)GSetElemPrev(p);
  }
  // Return the index
  return index;
}

// Function to get the first element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetFirstElem(const GSet* const that, 
  const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the head of the GSet
  GSetElem* p = (GSetElem*)GSetHeadElem(that);
  // Loop on elements until we have found the 
  // requested data or reached the end of the list
  while (p != NULL && GSetElemData(p) != data)
    p = (GSetElem*)GSetElemNext(p);
  // Return the pointer
  return p;
}

// Function to get the last element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
const GSetElem* _GSetLastElem(const GSet* const that, 
  const void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the head of the GSet
  GSetElem* p = (GSetElem*)GSetTailElem(that);
  // Loop on elements until we have found the 
  // requested data or reached the end of the list
  while (p != NULL && GSetElemData(p) != data)
    p = (GSetElem*)GSetElemPrev(p);
  // Return the pointer
  return p;
}

// Merge the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
// After calling this function 'set' is empty 
#if BUILDMODE != 0
inline
#endif 
void _GSetMerge(GSet* const that, GSet* const set) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // If 'set' is not empty
  if (set->_nbElem != 0) {
    // If 'that' is empty
    if (that->_nbElem == 0) {
      // Copy 'set' into 'that'
      memcpy(that, set, sizeof(GSet));
      // Empty 'set'
      set->_head = NULL;
      set->_tail = NULL;
      set->_nbElem = 0;
    // Else, if 'that' is not empty
    } else {
      // Add 'set' to the tail of 'that'
      GSetElemSetNext((GSetElem*)GSetTailElem(that), 
        (GSetElem*)GSetHeadElem(set));
      // Add 'that' to the head of 'set'
      GSetElemSetPrev((GSetElem*)GSetHeadElem(set), 
        (GSetElem*)GSetTailElem(that));
      // Update the tail of 'that'
      that->_tail = (GSetElem*)GSetTailElem(set);
      // Update the number of element of 'that'
      that->_nbElem += set->_nbElem;
      // Empty 'set'
      set->_head = NULL;
      set->_tail = NULL;
      set->_nbElem = 0;
    }
  }
}

// Split the GSet at the GSetElem 'e'
// 'e' must be and element of the set
// the set new end is the element before 'e', the set becomes empty if 
// 'e' was the first element
// Return a new GSet starting with 'e', or NULL if 'e' is not 
// an element of the set
#if BUILDMODE != 0
inline
#endif 
GSet* _GSetSplit(GSet* const that, GSetElem* const e) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (e == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'e' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Check that e is an element of that
  // Declare a variable to count element before e in that
  long nb = 0;
  // If e is not the head of that 
  if (GSetHeadElem(that) != e) {
    GSetElem* ptr = e;
    // While there is an element before e
    do {
      // Increment the number of element
      ++nb;
      // Move to the previous element
      ptr = (GSetElem*)GSetElemPrev(ptr);
    } while (ptr != NULL && ptr != GSetHeadElem(that));
    // If we have reached an element without previous element, this
    // element is not the head of that, meaning e is not in the set 
    if (ptr == NULL)
      // Stop here
      return NULL;
  }
  // Allocate memory for the result
  GSet* res = GSetCreate();
  // Set the head of res
  res->_head = e;
  // Set the tail of res
  res->_tail = (GSetElem*)GSetTailElem(that);
  // Set the number of element of res
  res->_nbElem = that->_nbElem - nb;
  // Set the tail of s
  that->_tail = (GSetElem*)GSetElemPrev(e);
  // Set the number of element of that
  that->_nbElem = nb;
  // If that is empty
  if (nb == 0)
    // Update head
    that->_head = NULL;
  // Else, that is not empty
  else
    // Disconnect the tail of that
    GSetElemSetNext((GSetElem*)GSetTailElem(that), NULL);
  // Disconnect the head of res
  GSetElemSetPrev((GSetElem*)GSetHeadElem(res), NULL);
  // Return the result
  return res;
}

// Switch the 'iElem'-th and 'jElem'-th element of the set
#if BUILDMODE != 0
inline
#endif 
void _GSetSwitch(GSet* const that, const long iElem, const long jElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%ld<%ld)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
  if (jElem < 0 || jElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'jElem' is invalid (0<=%ld<%ld)", 
      jElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Get the two elements
  GSetElem* iPtr = (GSetElem*)GSetElement(that, iElem);
  GSetElem* jPtr = (GSetElem*)GSetElement(that, jElem);
  // Switch the elements
  float v = GSetElemGetSortVal(iPtr);
  GSetElemSetSortVal(iPtr, GSetElemGetSortVal(jPtr));
  GSetElemSetSortVal(jPtr, v);
  void* dat = GSetElemData(iPtr);
  GSetElemSetData(iPtr, GSetElemData(jPtr));
  GSetElemSetData(jPtr, dat);
}

// Set the sort value of the GSetElem 'that' to 'v'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetSortVal(GSetElem* const that, const float v) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_sortVal = v;
}

// Set the data of the GSetElem 'that' to 'd'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetData(GSetElem* const that, void* const d) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_data = d;
}

// Set the previous element of the GSetElem 'that' to 'e'
// Do not set the link back in 'e'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetPrev(GSetElem* const that, GSetElem* const e) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_prev = e;
}

// Set the next element of the GSetElem 'that' to 'e'
// Do not set the link back in 'e'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetNext(GSetElem* const that, GSetElem* const e) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_next = e;
}

// Create a new GSetIterForward for the GSet 'set'
// The iterator is reset upon creation
#if BUILDMODE != 0
inline
#endif 
GSetIterForward _GSetIterForwardCreateStatic(GSet* const set) {
#if BUILDMODE == 0
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Create the iterator
  GSetIterForward ret = {._set = set, ._curElem = set->_head};
  // Return the new iterator
  return ret;
}

// Create a new GSetIterBackward for the GSet 'set'
// The iterator is reset upon creation
#if BUILDMODE != 0
inline
#endif 
GSetIterBackward _GSetIterBackwardCreateStatic(GSet* const set) {
#if BUILDMODE == 0
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Create the iterator
  GSetIterBackward ret = {._set = set, ._curElem = set->_tail};
  // Return the new iterator
  return ret;
}

// Reset the GSetIterForward to its starting position
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardReset(GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset
  that->_curElem = (GSetElem*)GSetHeadElem(that->_set);
}

// Reset the GSetIterBackward to its starting position
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardReset(GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset
  that->_curElem = (GSetElem*)GSetTailElem(that->_set);
}

// Step the GSetIterForward
// Return false if arguments are invalid or we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardStep(GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Step
  if (that->_curElem != NULL && GSetElemNext(that->_curElem) != NULL)
    that->_curElem = (GSetElem*)GSetElemNext(that->_curElem);
  else
    return false;
  return true;
}

// Step the GSetIterBackward
// Return false if arguments are invalid or we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardStep(GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Step
  if (that->_curElem != NULL && GSetElemPrev(that->_curElem) != NULL)
    that->_curElem = (GSetElem*)GSetElemPrev(that->_curElem);
  else
    return false;
  return true;
}

// Step the GSetIterForward
// Return false if arguments are invalid or we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardStepBack(GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Step back
  if (that->_curElem != NULL && GSetElemPrev(that->_curElem) != NULL)
    that->_curElem = (GSetElem*)GSetElemPrev(that->_curElem);
  else
    return false;
  return true;
}

// Step the GSetIterBackward
// Return false if arguments are invalid or we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardStepBack(GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Step back
  if (that->_curElem != NULL && GSetElemNext(that->_curElem) != NULL)
    that->_curElem = (GSetElem*)GSetElemNext(that->_curElem);
  else
    return false;
  return true;
}

// Apply a function to all elements of the GSet of the GSetIterForward
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardApply(GSetIterForward* const that, 
  void(*fun)(void* data, void* param), void* param) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (fun == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'fun' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset the iterator
  GSetIterReset(that);
  // If the set is not empty
  if (that->_curElem != NULL)
    // Loop on element
    do {
      // Apply the user function
      fun(GSetElemData(that->_curElem), param);
    } while (GSetIterStep(that));
}

// Apply a function to all elements of the GSet of the GSetIterBackward
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardApply(GSetIterBackward* const that, 
  void(*fun)(void* data, void* param), void* param) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (fun == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'fun' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset the iterator
  GSetIterReset(that);
  // If the set is not empty
  if (that->_curElem != NULL)
    // Loop on element
    do {
      // Apply the user function
      fun(GSetElemData(that->_curElem), param);
    } while (GSetIterStep(that) == true);
}

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardIsFirst(const GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == GSetHeadElem(that->_set))
    return true;
  else
    return false;
}

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardIsFirst(const GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == GSetTailElem(that->_set))
    return true;
  else
    return false;
}

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardIsLast(const GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == GSetTailElem(that->_set))
    return true;
  else
    return false;
}

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardIsLast(const GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == GSetHeadElem(that->_set))
    return true;
  else
    return false;
}

// Change the attached set of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardSetGSet(GSetIterForward* const that, 
  GSet* const set) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the GSet
  that->_set = set;
  // Reset the iterator
  GSetIterReset(that);
}

// Change the attached set of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardSetGSet(GSetIterBackward* const that, 
  GSet* const set) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the GSet
  that->_set = set;
  // Reset the iterator
  GSetIterReset(that);
}

// Return the data currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* GSetIterForwardGet(const GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return GSetElemData(that->_curElem);
}

// Return the data currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* GSetIterBackwardGet(const GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return GSetElemData(that->_curElem);
}

// Return the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetIterForwardGetElem(
  const GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return that->_curElem;
}

// Return the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetIterBackwardGetElem(
  const GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return that->_curElem;
}

// Return the number of element in the set
#if BUILDMODE != 0
inline
#endif 
long _GSetNbElem(const GSet* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return that->_nbElem;
}

// Remove the element currently pointed to by the iterator
// The iterator is moved forward to the next element
// Return false if we couldn't move
// Return true else
// It's the responsibility of the user to delete the content of the 
// element prior to calling this function
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardRemoveElem(GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  GSetElem *next = (GSetElem*)GSetElemNext(that->_curElem);
  GSetRemoveElem(that->_set, &(that->_curElem));
  that->_curElem = next;
  if (next != NULL)
    return true;
  else 
    return false;
}

// Remove the element currently pointed to by the iterator
// The iterator is moved backward to the next element
// Return false if we couldn't move
// Return true else
// It's the responsibility of the user to delete the content of the 
// element prior to calling this function
#if BUILDMODE != 0
inline
#endif 
bool GSetIterBackwardRemoveElem(GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  GSetElem *prev = (GSetElem*)GSetElemPrev(that->_curElem);
  GSetRemoveElem(that->_set, &(that->_curElem));
  that->_curElem = prev;
  if (prev != NULL)
    return true;
  else 
    return false;
}

// Append the element of the GSet 'set' at the end of the GSet 'that'
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void _GSetAppendSet(GSet* const that, const GSet* const set) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // If there are elements in the set to append
  if (GSetNbElem(set) > 0) {
    // Declare an iterator on the set to append
    GSetIterForward iter = GSetIterForwardCreateStatic(set);
    // Loop on element to append
    do {
      // Get the data to append
      void* data = GSetIterGet(&iter);
      // Append the data to the end of the set
      GSetAppend(that, data);
    } while (GSetIterStep(&iter));
  }
}

// Append the element of the GSet 'that' at the end of the GSet 'set'
// Elements are kept sorted
// 'that' and 'set' can be empty
#if BUILDMODE != 0
inline
#endif 
void _GSetAppendSortedSet(GSet* const that, const GSet* const set) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (set == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'set' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // If there are elements in the set to append
  if (GSetNbElem(set) > 0) {
    // Declare an iterator on the set to append
    GSetIterForward iter = GSetIterForwardCreateStatic(set);
    // Loop on element to append
    do {
      // Get the element to append
      GSetElem* elem = (GSetElem*)GSetIterGetElem(&iter);
      // Append the data of the element according to the sorting value
      GSetAddSort(that, GSetElemData(elem), GSetElemGetSortVal(elem));
    } while (GSetIterStep(&iter));
  }
}

// Return the sort value of GSetElem 'that'
#if BUILDMODE != 0
inline
#endif 
float GSetElemGetSortVal(const GSetElem* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif  
  return that->_sortVal;
}

// Return the next element of GSetElem 'that'
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetElemNext(const GSetElem* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif  
  return that->_next;
}

// Return the previous element of GSetElem 'that'
#if BUILDMODE != 0
inline
#endif 
const GSetElem* GSetElemPrev(const GSetElem* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif  
  return that->_prev;
}

// Set the data of the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardSetData(const GSetIterForward* const that, 
  void* data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif  
  GSetElemSetData((GSetElem*)GSetIterGetElem(that), data);
}

// Set the data of the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardSetData(const GSetIterBackward* const that,
  void* data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif  
  GSetElemSetData((GSetElem*)GSetIterGetElem(that), data);
}

// Return the sort value of the element currently pointed to by the 
// iterator
#if BUILDMODE != 0
inline
#endif 
float GSetIterForwardGetSortVal(const GSetIterForward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif  
  return GSetElemGetSortVal(GSetIterGetElem(that));
}

// Return the sort value of the element currently pointed to by the 
// iterator
#if BUILDMODE != 0
inline
#endif 
float GSetIterBackwardGetSortVal(const GSetIterBackward* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif  
  return GSetElemGetSortVal(GSetIterGetElem(that));
}

