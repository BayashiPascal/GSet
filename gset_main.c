#include <stdlib.h>
#include <stdio.h>
#include "gset.h"

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

int main(int argc, char **argv) {
  GSet *theSet = GSetCreate();
  fprintf(stderr, "Created the set, nb elem : %d\n", theSet->_nbElem);
  struct Test data[4];
  for (int i = 0; i < 4; ++i) data[i].v = i;

  GSetPush(theSet, &(data[1]));
  GSetPush(theSet, &(data[3]));
  GSetPush(theSet, &(data[2]));
  fprintf(stderr, "Pushed [1,3,2], nb elem : %d\n", theSet->_nbElem);
  fprintf(stderr, "Print GSet:\n");
  GSetPrint(theSet, stdout, &TestPrint, (char*)", ");
  fprintf(stderr, "\n");

  fprintf(stderr, "Pop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetPop(theSet);
    fprintf(stderr, "%d, ", p->v);
  }
  fprintf(stderr, "\n");

  GSetPush(theSet, &(data[1]));
  GSetPush(theSet, &(data[3]));
  GSetPush(theSet, &(data[2]));
  fprintf(stderr, "Push back and drop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetDrop(theSet);
    fprintf(stderr, "%d, ", p->v);
  }
  fprintf(stderr, "\n");

  GSetAppend(theSet, &(data[1]));
  GSetAppend(theSet, &(data[3]));
  GSetAppend(theSet, &(data[2]));
  fprintf(stderr, "Append back and pop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetPop(theSet);
    fprintf(stderr, "%d, ", p->v);
  }
  fprintf(stderr, "\n");

  GSetAppend(theSet, &(data[1]));
  GSetAppend(theSet, &(data[3]));
  GSetAppend(theSet, &(data[2]));
  fprintf(stderr, "Append back and drop elements :\n");
  while (theSet->_nbElem > 0) {
    struct Test *p = (struct Test *)GSetDrop(theSet);
    fprintf(stderr, "%d, ", p->v);
  }
  fprintf(stderr, "\n");

  GSetAddSort(theSet, &(data[2]), data[2].v);
  GSetAddSort(theSet, &(data[3]), data[3].v);
  GSetAddSort(theSet, &(data[1]), data[1].v);
  fprintf(stderr, "Add sort [2,3,1] and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    fprintf(stderr, "%d, ", p->v);
  }
  fprintf(stderr, "\n");

  GSetInsert(theSet, &(data[0]), 0);
  GSetInsert(theSet, &(data[0]), 2);
  GSetInsert(theSet, &(data[0]), 8);
  fprintf(stderr, "Insert 0 at 0, 2, 8 and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    TestPrint(p, stderr);
    fprintf(stderr, ", ");
  }
  fprintf(stderr, "\n");

  GSet *clone = GSetClone(theSet);
  fprintf(stderr, "Clone the set and print it:\n");
  GSetPrint(clone, stdout, &TestPrint, (char*)", ");
  fprintf(stderr, "\n");
  GSetFree(&clone);

  GSetRemove(theSet, 7);
  GSetRemove(theSet, 1);
  GSetRemove(theSet, 0);
  fprintf(stderr, "Remove at 7,1,0 and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    TestPrint(p, stderr);
    fprintf(stderr, ", ");
  }
  fprintf(stderr, "\n");

  fprintf(stderr, "Index of first null data : %d\n", 
    GSetGetIndexFirst(theSet, NULL));
  fprintf(stderr, "Index of last null data : %d\n", 
    GSetGetIndexLast(theSet, NULL));

  GSetRemoveAll(theSet, NULL);
  fprintf(stderr, "Delete all null and get elements :\n");
  for (int i = 0; i < theSet->_nbElem; ++i) {
    struct Test *p = (struct Test *)GSetGet(theSet, i);
    TestPrint(p, stderr);
    fprintf(stderr, ", ");
  }
  fprintf(stderr, "\n");

  GSetFree(&theSet);
}
