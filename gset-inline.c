 // ============ GSET-INLINE.C ================

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
void GSetFlush(GSet *that) {
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
void GSetPush(GSet *that, void* data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Allocate memory for the new element
  GSetElem *e = PBErrMalloc(GSetErr, sizeof(GSetElem));
  // Memorize the pointer toward data
  e->_data = data;
  // By default set the sorting value to 0.0
  e->_sortVal = 0.0;
  // Add the element at the head of the GSet 
  e->_prev = NULL;
  if (that->_head != NULL) 
    that->_head->_prev = e;
  e->_next = that->_head;
  that->_head = e;
  if (that->_tail == NULL) 
    that->_tail = e;
  // Increment the number of elements in the GSet
  ++(that->_nbElem);
}

// Function to insert an element pointing toward 'data' at the 
// tail of the GSet
#if BUILDMODE != 0
inline
#endif 
void GSetAppend(GSet *that, void* data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  GSetElem *e = PBErrMalloc(GSetErr, sizeof(GSetElem));
  if (e != NULL) {
    e->_data = data;
    e->_sortVal = 0.0;
    e->_prev = that->_tail;
    e->_next = NULL;
    if (that->_tail != NULL) 
      that->_tail->_next = e;
    that->_tail = e;
    if (that->_head == NULL) 
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
void* GSetPop(GSet *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  void *ret = NULL;
  GSetElem *p = that->_head;
  if (p != NULL) {
    ret = p->_data;
    that->_head = p->_next;
    if (p->_next != NULL) 
      p->_next->_prev = NULL;
    p->_next = NULL;
    p->_data = NULL;
    if (that->_tail == p) 
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
void* GSetDrop(GSet *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  void *ret = NULL;
  GSetElem *p = that->_tail;
  if (p != NULL) {
    ret = p->_data;
    that->_tail = p->_prev;
    if (p->_prev != NULL) 
      p->_prev->_next = NULL;
    p->_prev = NULL;
    p->_data = NULL;
    if (that->_head == p) 
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
void* GSetRemoveElem(GSet *that, GSetElem **elem) {
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
  void *ret = NULL;
  // Memorize the data at iElem-th position
  ret = (*elem)->_data;
  // Remove the element
  if ((*elem)->_next != NULL) 
    (*elem)->_next->_prev = (*elem)->_prev;
  if ((*elem)->_prev != NULL) 
    (*elem)->_prev->_next = (*elem)->_next;
  if (that->_head == (*elem)) 
    that->_head = (*elem)->_next;
  if (that->_tail == (*elem)) 
    that->_tail = (*elem)->_prev;
  (*elem)->_next = NULL;
  (*elem)->_prev = NULL;
  (*elem)->_data = NULL;
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
void GSetRemoveFirst(GSet *that, void *data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Get the first element pointing to 'data'
  GSetElem *elem = GSetGetFirstElem(that, data);
  // If we could find an element
  if (elem != NULL)
    // Remove this element
    while (GSetRemoveElem(that, &elem) && false);
}

// Function to remove the last element of the GSet pointing to 'data'
// If there is no element pointing to 'data' do nothing
#if BUILDMODE != 0
inline
#endif 
void GSetRemoveLast(GSet *that, void *data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Get the last element pointing to 'data'
  GSetElem *elem = GSetGetLastElem(that, data);
  // If we could find an element
  if (elem != NULL)
    // Remove this element
    while (GSetRemoveElem(that, &elem) && false);
}

// Function to remove the element at the 'iElem'-th position of the GSet
// Return the data pointed to by the removed element
#if BUILDMODE != 0
inline
#endif 
void* GSetRemove(GSet *that, int iElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%d<%d)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Variable to memorize the return value
  void *ret = NULL;
  // Set a pointer to the head of the Gset
  GSetElem *p = that->_head;
  // Move the pointer to the iElem-th element
  for (int i = iElem; i > 0 && p != NULL; --i, p = p->_next);
  // Memorize the data at iElem-th position
  ret = p->_data;
  // Remove the element
  if (p->_next != NULL) 
    p->_next->_prev = p->_prev;
  if (p->_prev != NULL) 
    p->_prev->_next = p->_next;
  if (that->_head == p) 
    that->_head = p->_next;
  if (that->_tail == p) 
    that->_tail = p->_prev;
  p->_next = NULL;
  p->_prev = NULL;
  p->_data = NULL;
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
void GSetRemoveAll(GSet *that, void *data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the tail of the GSet
  GSetElem *p = that->_tail;
  // Loop on elements until we reached the head of the list
  while (p != NULL) {
    // If the element points toward data
    if (p->_data == data) {
      // Memorize the previous element before deleting
      GSetElem *prev = p->_prev;
      // Remove the element
      GSetRemoveElem(that, &p);
      // Continue with previous element
      p = prev;
    // Else, the element doesn't point toward data
    } else {
      // Continue with previous element
      p = p->_prev;
    }
  }
}

// Function to get the data at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
void* GSetGet(GSet *that, int iElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%d<%d)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer for the return value
  void *ret = NULL;
  // Get the iElem-th element
  GSetElem* e = GSetGetElem(that, iElem);
  // Get the data of the element
  ret = e->_data;
  // Return the data
  return ret;
}

// Function to get the element at the 'iElem'-th position of the GSet
// without removing it
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetGetElem(GSet *that, int iElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%d<%d)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer for the return value
  GSetElem *ret = NULL;
  // Set the pointer to the head of the GSet
  ret = that->_head;
  // Move to the next element iElem times
  for (int i = iElem; i > 0 && ret != NULL; --i, ret = ret->_next);
  // Return the element
  return ret;
}

// Function to get the index of the first element of the GSet
// which point to 'data'
// Return -1 if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
int GSetGetIndexFirst(GSet *that, void *data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the head of the GSet
  GSetElem *p = that->_head;
  // Set a variable to memorize index
  int index = 0;
  // Loop on elements until we have found the 
  // requested data or reached the end of the list
  while (p != NULL && p->_data != data) {
    ++index;
    p = p->_next;
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
int GSetGetIndexLast(GSet *that, void *data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the tail of the GSet
  GSetElem *p = that->_tail;
  // Set a variable to memorize index
  int index = that->_nbElem - 1;
  // Loop on elements until we have found the 
  // requested data or reached the head of the list
  while (p != NULL && p->_data != data) {
    --index;
    p = p->_prev;
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
GSetElem* GSetGetFirstElem(GSet *that, void *data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the head of the GSet
  GSetElem *p = that->_head;
  // Loop on elements until we have found the 
  // requested data or reached the end of the list
  while (p != NULL && p->_data != data)
    p = p->_next;
  // Return the pointer
  return p;
}

// Function to get the last element of the GSet
// which point to 'data'
// Return NULL if 'data' is not in the set
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetGetLastElem(GSet *that, void *data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set a pointer toward the head of the GSet
  GSetElem *p = that->_tail;
  // Loop on elements until we have found the 
  // requested data or reached the end of the list
  while (p != NULL && p->_data != data)
    p = p->_prev;
  // Return the pointer
  return p;
}

// Merge the GSet 'r' at the end of the GSet 's'
// 'r' and 's' can be empty
// After calling this function r is empty 
#if BUILDMODE != 0
inline
#endif 
void GSetMerge(GSet *s, GSet *r) {
#if BUILDMODE == 0
  if (s == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'*s' is null");
    PBErrCatch(GSetErr);
  }
  if (r == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'*r' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // If the set r is not empty
  if (r->_nbElem != 0) {
    // If the set s is empty
    if (s->_nbElem == 0) {
      // Copy r into s
      memcpy(s, r, sizeof(GSet));
      // Empty r
      r->_head = NULL;
      r->_tail = NULL;
      r->_nbElem = 0;
    // Else, if the set s is not empty
    } else {
      // Add r to the tail of s
      s->_tail->_next = r->_head;
      // Add s to the head of r
      r->_head->_prev = s->_tail;
      // Update the tail of s
      s->_tail = r->_tail;
      // Update the number of element of s
      s->_nbElem += r->_nbElem;
      // Empty r
      r->_head = NULL;
      r->_tail = NULL;
      r->_nbElem = 0;
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
GSet* GSetSplit(GSet *that, GSetElem *e) {
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
  int nb = 0;
  // If e is not the head of that 
  if (that->_head != e) {
    GSetElem *ptr = e;
    // While there is an element before e
    do {
      // Increment the number of element
      ++nb;
      // Move to the previous element
      ptr = ptr->_prev;
    } while (ptr != NULL && ptr != that->_head);
    // If we have reached an element without previous element, this
    // element is not the head of that, meaning e is not in the set 
    if (ptr == NULL)
      // Stop here
      return NULL;
  }
  // Allocate memory for the result
  GSet *res = GSetCreate();
  // Set the head of res
  res->_head = e;
  // Set the tail of res
  res->_tail = that->_tail;
  // Set the number of element of res
  res->_nbElem = that->_nbElem - nb;
  // Set the tail of s
  that->_tail = e->_prev;
  // Set the number of element of that
  that->_nbElem = nb;
  // If that is empty
  if (nb == 0)
    // Update head
    that->_head = NULL;
  // Else, that is not empty
  else
    // Disconnect the tail of that
    that->_tail->_next = NULL;
  // Disconnect the head of res
  res->_head->_prev = NULL;
  // Return the result
  return res;
}

// Switch the 'iElem'-th and 'jElem'-th element of the set
#if BUILDMODE != 0
inline
#endif 
void GSetSwitch(GSet *that, int iElem, int jElem) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iElem < 0 || iElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iElem' is invalid (0<=%d<%d)", 
      iElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
  if (jElem < 0 || jElem >= that->_nbElem) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'jElem' is invalid (0<=%d<%d)", 
      jElem, that->_nbElem);
    PBErrCatch(GSetErr);
  }
#endif
  // Get the two elements
  GSetElem *iPtr = GSetGetElem(that, iElem);
  GSetElem *jPtr = GSetGetElem(that, jElem);
  // Switch the elements
  float v = iPtr->_sortVal;
  iPtr->_sortVal = jPtr->_sortVal;
  jPtr->_sortVal = v;
  void *dat = iPtr->_data;
  iPtr->_data = jPtr->_data;
  jPtr->_data = dat;
}

// Set the sort value of the GSetElem 'that' to 'v'
#if BUILDMODE != 0
inline
#endif 
void GSetElemSetSortVal(GSetElem *that, float v) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_sortVal = v;
}

// Create a new GSetIterForward for the GSet 'set'
// The iterator is reset upon creation
#if BUILDMODE != 0
inline
#endif 
GSetIterForward GSetIterForwardCreateStatic(GSet *set) {
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
GSetIterBackward GSetIterBackwardCreateStatic(GSet *set) {
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
void GSetIterForwardReset(GSetIterForward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset
  that->_curElem = that->_set->_head;
}

// Reset the GSetIterBackward to its starting position
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void GSetIterBackwardReset(GSetIterBackward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset
  that->_curElem = that->_set->_tail;
}

// Step the GSetIterForward
// Return false if arguments are invalid or we couldn't step
// Return true else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardStep(GSetIterForward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Step
  if (that->_curElem->_next != NULL)
    that->_curElem = that->_curElem->_next;
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
bool GSetIterBackwardStep(GSetIterBackward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Step
  if (that->_curElem->_prev != NULL)
    that->_curElem = that->_curElem->_prev;
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
void GSetIterForwardApply(GSetIterForward *that, 
  void(*fun)(void *data, void *param), void *param) {
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
      fun(that->_curElem->_data, param);
    } while (GSetIterStep(that) == true);
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
void GSetIterBackwardApply(GSetIterBackward *that, 
  void(*fun)(void *data, void *param), void *param) {
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
      fun(that->_curElem->_data, param);
    } while (GSetIterStep(that) == true);
}

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GSet)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool GSetIterForwardIsFirst(GSetIterForward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == that->_set->_head)
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
bool GSetIterBackwardIsFirst(GSetIterBackward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == that->_set->_tail)
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
bool GSetIterForwardIsLast(GSetIterForward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == that->_set->_tail)
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
bool GSetIterBackwardIsLast(GSetIterBackward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curElem == that->_set->_head)
    return true;
  else
    return false;
}

// Change the attached set of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void GSetIterForwardSetGSet(GSetIterForward *that, GSet *set) {
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
void GSetIterBackwardSetGSet(GSetIterBackward *that, GSet *set) {
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
void* GSetIterForwardGet(GSetIterForward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return that->_curElem->_data;
}

// Return the data currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* GSetIterBackwardGet(GSetIterBackward *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GSetErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Return the data
  return that->_curElem->_data;
}

// Return the element currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GSetElem* GSetIterForwardGetElem(GSetIterForward *that) {
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
GSetElem* GSetIterBackwardGetElem(GSetIterBackward *that) {
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
int GSetNbElem(GSet *that) {
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