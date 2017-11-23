#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gset.h"

#define rnd() (float)(rand())/(float)(RAND_MAX)

struct Test {
  int v;
};

void TestPrint(void *t, FILE *stream) {
  if (t == NULL) {
    fprintf(stream, "(null)");
  } else {
    fprintf(stream, "%d", ((struct Test*)t)->v);
  }
}

void TestApply(void *t, void *p) {
  struct Test *data = (struct Test*)t;
  struct Test *param = (struct Test*)p;
  printf("applying %d on %d\n", param->v, data->v);
}

int main(int argc, char **argv) {
  // Initialize the random generator
  time_t seed = time(NULL);
  srandom(seed);

  GSet *theSet = GSetCreate();
  fprintf(stdout, "Created the set, nb elem : %d\n", theSet->_nbElem);
  struct Test data[4];
  for (int i = 0; i < 4; ++i) data[i].v = i;

  GSetPush(theSet, &(data[1]));
  GSetPush(theSet, &(data[3]));
  GSetPush(theSet, &(data[2]));
  fprintf(stdout, "Pushed [1,3,2], nb elem : %d\n", theSet->_nbElem);
  fprintf(stdout, "Print GSet:\n");
  GSetPrint(theSet, stdout, &TestPrint, (char*)", ");
  fprintf(stdout, "\n");

  fprintf(stdout, "Pop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetPop(theSet);
    fprintf(stdout, "%d, ", p->v);
  }
  fprintf(stdout, "\n");

  GSetPush(theSet, &(data[1]));
  GSetPush(theSet, &(data[3]));
  GSetPush(theSet, &(data[2]));
  fprintf(stdout, "Push back and drop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetDrop(theSet);
    fprintf(stdout, "%d, ", p->v);
  }
  fprintf(stdout, "\n");

  GSetAppend(theSet, &(data[1]));
  GSetAppend(theSet, &(data[3]));
  GSetAppend(theSet, &(data[2]));
  fprintf(stdout, "Append back and pop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetPop(theSet);
    fprintf(stdout, "%d, ", p->v);
  }
  fprintf(stdout, "\n");

  GSetAppend(theSet, &(data[1]));
  GSetAppend(theSet, &(data[3]));
  GSetAppend(theSet, &(data[2]));
  fprintf(stdout, "Append back and drop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetDrop(theSet);
    fprintf(stdout, "%d, ", p->v);
  }
  fprintf(stdout, "\n");

  GSetAddSort(theSet, &(data[2]), data[2].v);
  GSetAddSort(theSet, &(data[3]), data[3].v);
  GSetAddSort(theSet, &(data[1]), data[1].v);
  fprintf(stdout, "Add sort (decreasing) [2,3,1] and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    fprintf(stdout, "%d, ", p->v);
  }
  fprintf(stdout, "\n");

  GSetSwitch(theSet, 0, 2);
  fprintf(stdout, "Switch 1st and 3rd elements:\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    fprintf(stdout, "%d, ", p->v);
  }
  fprintf(stdout, "\n");

  GSetInsert(theSet, &(data[0]), 0);
  GSetInsert(theSet, &(data[0]), 2);
  GSetInsert(theSet, &(data[0]), 8);
  fprintf(stdout, "Insert 0 at 0, 2, 8 and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    TestPrint(p, stdout);
    fprintf(stdout, ", ");
  }
  fprintf(stdout, "\n");

  fprintf(stdout, "Split the set at 1:\n");
  GSetElem *splitElem = GSetGetElem(theSet, 4);
  GSet *split = GSetSplit(theSet, splitElem);
  GSetPrint(theSet, stdout, TestPrint, ", ");
  fprintf(stdout, " and ");
  GSetPrint(split, stdout, TestPrint, ", ");
  fprintf(stdout, "\n");

  fprintf(stdout, "Merge back the set:\n");
  GSetMerge(&theSet, &split);
  GSetPrint(theSet, stdout, TestPrint, ", ");
  fprintf(stdout, "\n");
  
  GSet *clone = GSetClone(theSet);
  fprintf(stdout, "Clone the set and print it:\n");
  GSetPrint(clone, stdout, &TestPrint, (char*)", ");
  fprintf(stdout, "\n");
  GSetFree(&clone);

  fprintf(stdout, "Sort the elements, before:\n");
  GSetElem *elem = theSet->_head;
  while (elem != NULL) {
    elem->_sortVal = rnd();
    fprintf(stdout, "%.3f,", elem->_sortVal);
    elem = elem->_next;
  }
  fprintf(stdout, "\n");
  GSetSort(theSet);
  fprintf(stdout, "Sort the elements, after:\n");
  elem = theSet->_head;
  while (elem != NULL) {
    fprintf(stdout, "%.3f,", elem->_sortVal);
    elem = elem->_next;
  }
  fprintf(stdout, "\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    TestPrint(p, stdout);
    fprintf(stdout, ", ");
  }
  fprintf(stdout, "\n");

  GSetRemove(theSet, 7);
  GSetRemove(theSet, 1);
  GSetRemove(theSet, 0);
  fprintf(stdout, "Remove at 7,1,0 and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    TestPrint(p, stdout);
    fprintf(stdout, ", ");
  }
  fprintf(stdout, "\n");

  fprintf(stdout, "Index of first null data : %d\n", 
    GSetGetIndexFirst(theSet, NULL));
  fprintf(stdout, "Index of last null data : %d\n", 
    GSetGetIndexLast(theSet, NULL));

  GSetRemoveAll(theSet, NULL);
  fprintf(stdout, "Delete all null and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    TestPrint(p, stdout);
    fprintf(stdout, ", ");
  }
  fprintf(stdout, "\n");

  fprintf(stdout, "Test iterator forward\n");
  GSetIterForward *iterf = GSetIterForwardCreate(theSet);
  do {
    struct Test *p = (struct Test *)GSetIterGet(iterf);
    TestPrint(p, stdout);
    fprintf(stdout, ", ");
  } while (GSetIterStep(iterf) == true);
  fprintf(stdout, "\n");

  fprintf(stdout, "Apply a function on all elements\n");
  struct Test param;
  param.v = 2;
  GSetIterApply(iterf, TestApply, &param);
  fprintf(stdout, "\n");
  GSetIterFree(&iterf);

  fprintf(stdout, "Test iterator backward\n");
  GSetIterBackward *iterb = GSetIterBackwardCreate(theSet);
  do {
    GSetElem *e = GSetIterGetElem(iterb);
    struct Test *p = (struct Test *)(e->_data);
    TestPrint(p, stdout);
    fprintf(stdout, ", ");
  } while (GSetIterStep(iterb) == true);
  fprintf(stdout, "\n");
  GSetIterFree(&iterb);

  GSetFree(&theSet);
}
