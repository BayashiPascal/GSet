#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include "pberr.h"
#include "gset.h"
#include "pbmath.h"

#define RANDOMSEED 0
#define rnd() (float)(rand())/(float)(RAND_MAX)

void UnitTestGSetElemGetSet() {
  GSetElem elem;
  GSetElem elemNext;
  GSetElem elemPrev;
  float val = 1.0;
  char data = ' ';
  elem._next = &elemNext;
  elem._prev = &elemPrev;
  elem._sortVal = val;
  elem._data = &data;
  if (GSetElemNext(&elem) != &elemNext) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemNext failed");
    PBErrCatch(GSetErr);
  }
  if (GSetElemPrev(&elem) != &elemPrev) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemPrev failed");
    PBErrCatch(GSetErr);
  }
  if (GSetElemData(&elem) != &data) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemData failed");
    PBErrCatch(GSetErr);
  }
  if (!ISEQUALF(GSetElemGetSortVal(&elem), val)) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemGetSortVal failed");
    PBErrCatch(GSetErr);
  }
  float valb = 2.0;
  char datab = ' ';
  GSetElem elemNextb;
  GSetElem elemPrevb;
  GSetElemSetData(&elem, &datab);
  GSetElemSetSortVal(&elem, valb);
  GSetElemSetNext(&elem, &elemNextb);
  GSetElemSetPrev(&elem, &elemPrevb);
  if (GSetElemData(&elem) != &datab) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemSetData failed");
    PBErrCatch(GSetErr);
  }
  if (!ISEQUALF(GSetElemGetSortVal(&elem), valb)) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemSetSortVal failed");
    PBErrCatch(GSetErr);
  }
  if (GSetElemNext(&elem) != &elemNextb) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemSetNext failed");
    PBErrCatch(GSetErr);
  }
  if (GSetElemPrev(&elem) != &elemPrevb) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetElemSetPrev failed");
    PBErrCatch(GSetErr);
  }
  
  printf("UnitTestGSetElemGetSet OK\n");
}

void UnitTestGSetElem() {
  UnitTestGSetElemGetSet();
  printf("UnitTestGSetElem OK\n");
}

void UnitTestGSetCreateFree() {
  GSet* set = GSetCreate();
  if (set == NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "set is null");
    PBErrCatch(GSetErr);
  }
  if (set->_nbElem != 0) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_nbElem is invalid (%ld==0)", set->_nbElem);
    PBErrCatch(GSetErr);
  }
  if (set->_head != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_head is not null");
    PBErrCatch(GSetErr);
  }
  if (set->_tail != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_tail is not null");
    PBErrCatch(GSetErr);
  }
  GSetFree(&set);
  if (set != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "set is not null after free");
    PBErrCatch(GSetErr);
  }
  set = GSetCreate();
  GSetPush(set, NULL);
  GSetFree(&set);
  if (set != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "set is not null after free");
    PBErrCatch(GSetErr);
  }
  GSet setstatic = GSetCreateStatic();
  if (setstatic._nbElem != 0) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_nbElem is invalid (%ld==0)", 
      setstatic._nbElem);
    PBErrCatch(GSetErr);
  }
  if (setstatic._head != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_head is not null");
    PBErrCatch(GSetErr);
  }
  if (setstatic._tail != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_tail is not null");
    PBErrCatch(GSetErr);
  }
  printf("UnitTestGSetCreateFree OK\n");
}

void UnitTestGSetClone() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSet* clone = GSetClone(&set);
  if (clone->_nbElem != 5) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetClone NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterForward iter = GSetIterForwardCreateStatic(clone);
  int i = 0;
  do {
    if (a + i != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetClone NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetFree(&clone);
  GSetFlush(&set);
  printf("UnitTestGSetClone OK\n");
}

void UnitTestGSetFlush() {
  GSet* set = GSetCreate();
  for (int i = 5; i--;)
    GSetPush(set, NULL);
  GSetFlush(set);
  if (set->_head != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_head is not null after flush");
    PBErrCatch(GSetErr);
  }
  if (set->_tail != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_tail is not null after flush");
    PBErrCatch(GSetErr);
  }
  if (set->_nbElem != 0) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "_nbElem is not 0 after flush");
    PBErrCatch(GSetErr);
  }
  GSetFree(&set);
  printf("UnitTestGSetFlush OK\n");
}

void printData(const void* const data, FILE* const stream) {
  fprintf(stream, "%d", *(int*)data);
}

void UnitTestGSetPrint() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetPrint(&set, stdout, printData, ", ");
  printf("\n");
  GSetFlush(&set);
  printf("UnitTestGSetPrint OK\n");
}

void UnitTestGSetPushPopAppendDrop() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;) {
    GSetPush(&set, a + i);
    GSetPrint(&set, stdout, printData, ", ");
    printf("\n");
  }
  if (set._nbElem != 5) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetPushPopAppendDrop NOK");
    PBErrCatch(GSetErr);
  }
  for (int i = 5; i--;) {
    while (GSetPop(&set) == NULL);
    GSetPrint(&set, stdout, printData, ", ");
    printf("\n");
  }
  if (set._nbElem != 0) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetPushPopAppendDrop NOK");
    PBErrCatch(GSetErr);
  }
  for (int i = 5; i--;) {
    GSetAppend(&set, a + i);
    GSetPrint(&set, stdout, printData, ", ");
    printf("\n");
  }
  if (set._nbElem != 5) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetPushPopAppendDrop NOK");
    PBErrCatch(GSetErr);
  }
  for (int i = 5; i--;) {
    while (GSetDrop(&set) == NULL);
    GSetPrint(&set, stdout, printData, ", ");
    printf("\n");
  }
  if (set._nbElem != 0) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetPushPopAppendDrop NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetPushPopAppendDrop OK\n");
}

void UnitTestGSetAddSort() {
  srandom(RANDOMSEED);
  int a[5] = {-2, -1, 0, 1, 2};
  int nbTest = 1000;
  GSet set = GSetCreateStatic();
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  for (int iTest = nbTest; iTest--;) {
    for (int i = 10; i--;) {
      int j = (int)floor(rnd() * 5);
      GSetAddSort(&set, a + j, a[j]);
    }
    GSetIterReset(&iter);
    int v = *(int*)GSetIterGet(&iter);
    GSetIterStep(&iter);
    do {
      int w = *(int*)GSetIterGet(&iter);
      if (w < v) {
        GSetErr->_type = PBErrTypeUnitTestFailed;
        sprintf(GSetErr->_msg, "GSetAddSort NOK");
        PBErrCatch(GSetErr);
      }
      v = w;
    } while (GSetIterStep(&iter));
    GSetFlush(&set);
  }
  printf("UnitTestGSetAddSort OK\n");
}

void UnitTestGSetInsertRemove() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  GSetInsert(&set, a, 2);
  int *checka[3] = {NULL, NULL, a};
  int i = 0;
  GSetIterReset(&iter);
  do {
    if (checka[i] != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetInsert NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetFlush(&set);
  GSetInsert(&set, a, 0);
  GSetInsert(&set, a + 1, 1);
  GSetInsert(&set, a + 2, 1);
  GSetInsert(&set, a + 3, 1);
  GSetInsert(&set, a + 4, 3);
  int *checkb[5] = {a, a + 3, a + 2, a + 4, a + 1};
  i = 0;
  GSetIterReset(&iter);
  do {
    if (checkb[i] != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetInsert NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetRemove(&set, 0);
  int *checkc[4] = {a + 3, a + 2, a + 4, a + 1};
  i = 0;
  GSetIterReset(&iter);
  do {
    if (checkc[i] != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetRemove NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetRemove(&set, 3);
  int *checkd[3] = {a + 3, a + 2, a + 4};
  i = 0;
  GSetIterReset(&iter);
  do {
    if (checkd[i] != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetRemove NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetRemove(&set, 1);
  int *checke[2] = {a + 3, a + 4};
  i = 0;
  GSetIterReset(&iter);
  do {
    if (checke[i] != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetRemove NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetRemove(&set, 1);
  int *checkf[1] = {a + 3};
  i = 0;
  GSetIterReset(&iter);
  do {
    if (checkf[i] != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetRemove NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetRemove(&set, 0);
  if (set._nbElem != 0 || set._head != NULL || set._tail != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetRemove NOK");
    PBErrCatch(GSetErr);
  }
  printf("UnitTestGSetInsertRemove OK\n");
}

void UnitTestGSetNbElemGet() {
  int a[5] = {0, 1, 2, 3, 4};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;) {
    GSetPush(&set, a + i);
    if (5 - i != GSetNbElem(&set)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetNbElem NOK");
      PBErrCatch(GSetErr);
    }
  }
  for (int i = 5; i--;)
    if (i != *(int*)GSetGet(&set, i)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetGet NOK");
      PBErrCatch(GSetErr);
    }
  if (*(int*)GSetHead(&set) != 0) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetGetFirst NOK");
    PBErrCatch(GSetErr);
  }
  if (*(int*)GSetTail(&set) != 4) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetGetLast NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetNbElemGet OK\n");
}

void UnitTestGSetGetIndex() {
  int a[5] = {0, 1, 2, 3, 4};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  for (int i = 5; i--;)
    GSetAppend(&set, a + i);
  for (int i = 5; i--;) {
    if (i != GSetGetIndexFirst(&set, a + i)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetGetIndexFirst NOK");
      PBErrCatch(GSetErr);
    }
    if (9 - i != GSetGetIndexLast(&set, a + i)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetGetIndexLast NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetFlush(&set);
  printf("UnitTestGSetGetIndex OK\n");
}

void UnitTestGSetSort() {
  srandom(RANDOMSEED);
  int a[5] = {-2, -1, 0, 1, 2};
  int nbTest = 1000;
  GSet set = GSetCreateStatic();
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  for (int iTest = nbTest; iTest--;) {
    for (int i = 10; i--;) {
      int j = (int)floor(rnd() * 5);
      GSetPush(&set, a + j);
      GSetElemSetSortVal((GSetElem*)GSetHeadElem(&set), a[j]);
    }
    GSetSort(&set);
    GSetIterReset(&iter);
    int v = *(int*)GSetIterGet(&iter);
    GSetIterStep(&iter);
    do {
      int w = *(int*)GSetIterGet(&iter);
      if (w < v) {
        GSetErr->_type = PBErrTypeUnitTestFailed;
        sprintf(GSetErr->_msg, "GSetSort NOK");
        PBErrCatch(GSetErr);
      }
      v = w;
    } while (GSetIterStep(&iter));
    GSetFlush(&set);
  }
  printf("UnitTestGSetSort OK\n");
}

int compare_floats(const void* a, const void* b)
{
  float arg1 = *(const float*)a;
  float arg2 = *(const float*)b;
  return (arg1 > arg2) - (arg1 < arg2);
}

void UnitTestGSetSortBig() {
  srandom(RANDOMSEED);
  int nbTest = 10;
  float sumTime = 0.0;
  float minTime = 100000.0;
  float maxTime = 0.0;
  #define sizeSet 1000000l
  for (int iTest = 0; iTest < nbTest; ++iTest) {
    GSet set = GSetCreateStatic();
    for (long i = 0; i < sizeSet; ++i) {
      GSetPush(&set, NULL);
      GSetElemSetSortVal((GSetElem*)GSetHeadElem(&set), 
        rnd() * 100000.0);
    }
    clock_t clockBefore = clock();
    GSetSort(&set);
    clock_t clockAfter = clock();
    float delayMs = ((double)(clockAfter - clockBefore)) / 
      CLOCKS_PER_SEC * 1000.0;
    if (minTime > delayMs)
      minTime = delayMs;
    if (maxTime < delayMs)
      maxTime = delayMs;
    sumTime += delayMs;
    GSetFlush(&set);
  }
  printf("Min/Avg/Max time to sort %li elements: %.1f/%.1f/%.1fms\n", 
    sizeSet, minTime, sumTime / (float)nbTest, maxTime);

  float floats[sizeSet];
  sumTime = 0.0;
  minTime = 100000.0;
  maxTime = 0.0;
  for (int iTest = 0; iTest < nbTest; ++iTest) {
    for (long i = 0; i < sizeSet; ++i) {
      floats[i] = rnd() * 100000.0;
    }
    clock_t clockBefore = clock();
    qsort(floats, sizeSet, sizeof(int), compare_floats);
    clock_t clockAfter = clock();
    float delayMs = ((double)(clockAfter - clockBefore)) / 
      CLOCKS_PER_SEC * 1000.0;
    if (minTime > delayMs)
      minTime = delayMs;
    if (maxTime < delayMs)
      maxTime = delayMs;
    sumTime += delayMs;
  }
  printf("For comparison, using qsort on an array of %li floats:\n",
    sizeSet);
  printf("  Min/Avg/Max time : %.1f/%.1f/%.1fms\n", 
    minTime, sumTime / (float)nbTest, maxTime);

  printf("UnitTestGSetSortBig OK\n");
}

void UnitTestGSetSplitMerge() {
  int a[5] = {0, 1, 2, 3, 4};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  for (int i = 5; i--;)
    GSetAppend(&set, a + i);
  GSet* split = GSetSplit(&set, (GSetElem*)GSetElement(&set, 5));
  if (split->_nbElem != 5 || set._nbElem != 5) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetSplit NOK");
    PBErrCatch(GSetErr);
  }
  for (int i = 5; i--;) {
    if (a[i] != *(int*)GSetGet(&set, i)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetSplit NOK");
      PBErrCatch(GSetErr);
    }
    if (a[i] != *(int*)GSetGet(split, 4 - i)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetSplit NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetMerge(&set, split);
  if (split->_nbElem != 0 || set._nbElem != 10) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetMerge NOK");
    PBErrCatch(GSetErr);
  }
  for (int i = 5; i--;) {
    if (i != GSetGetIndexFirst(&set, a + i)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetMerge NOK");
      PBErrCatch(GSetErr);
    }
    if (9 - i != GSetGetIndexLast(&set, a + i)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetMerge NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetFlush(&set);
  GSetFree(&split);
  printf("UnitTestGSetSplitMerge OK\n");
}

void UnitTestGSetSwitch() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetSwitch(&set, 0, 4);
  GSetSwitch(&set, 1, 3);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  int *checka[5] = {a + 4, a + 3, a + 2, a + 1, a};
  int i = 0;
  GSetIterReset(&iter);
  do {
    if (checka[i] != GSetIterGet(&iter)) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetSwitch NOK");
      PBErrCatch(GSetErr);
    }
    ++i;
  } while (GSetIterStep(&iter));
  GSetFlush(&set);
  printf("UnitTestGSetSwitch OK\n");
}

void UnitTestGSetMoveElem() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetMoveElem(&set, 3, 1);
  int checka[5] = {1, 4, 2, 3, 5};
  for (int i = 5; i--;) {
    if (checka[i] != *((int*)GSetGet(&set, i))) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetMoveElem NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetMoveElem(&set, 1, 3);
  int checkb[5] = {1, 2, 3, 4, 5};
  for (int i = 5; i--;) {
    if (checkb[i] != *((int*)GSetGet(&set, i))) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetMoveElem NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetMoveElem(&set, 0, 3);
  int checkc[5] = {2, 3, 4, 1, 5};
  for (int i = 5; i--;) {
    if (checkc[i] != *((int*)GSetGet(&set, i))) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetMoveElem NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetMoveElem(&set, 4, 1);
  int checkd[5] = {2, 5, 3, 4, 1};
  for (int i = 5; i--;) {
    if (checkd[i] != *((int*)GSetGet(&set, i))) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetMoveElem NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetFlush(&set);
  printf("UnitTestGSetMoveElem OK\n");
}

void UnitTestGSetMergeSet() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet setA = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&setA, a + i);
  GSet setB = GSetCreateStatic();
  for (int i = 2; i--;)
    GSetPush(&setB, a + i + 3);
  GSetAppendSet(&setA, &setB);
  for (int i = 5; i--;) {
    if (a[i] != *((int*)GSetGet(&setA, i))) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetAppendSet NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetFlush(&setA);
  GSetFlush(&setB);
  for (int i = 3; i--;)
    GSetAddSort(&setB, a + i, i);
  for (int i = 2; i--;)
    GSetAddSort(&setA, a + i + 3, i + 3);
  GSetAppendSortedSet(&setA, &setB);
  for (int i = 5; i--;) {
    if (a[i] != *((int*)GSetGet(&setA, i))) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetAppendSortedSet NOK");
      PBErrCatch(GSetErr);
    }
  }
  GSetFlush(&setA);
  GSetFlush(&setB);
  printf("UnitTestGSetMergeSet OK\n");
}

void UnitTestGSetCount() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    for (int j = i; j--;)
      GSetPush(&set, a + i);
  for (int i = 5; i--;)
    if (GSetCount(&set, a + i) != i) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetCount NOK");
      PBErrCatch(GSetErr);
    }
  GSetFlush(&set);
  printf("UnitTestGSetMergeSet OK\n");
}

void UnitTestGSetShuffle() {
  srandom(1);
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetShuffle(&set);
  int b[5] = {2, 3, 4, 1, 5};
  for (int i = 0; i < 5; ++i) {
    int* j = GSetPop(&set);
    if (*j != b[i]) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetSuffle NOK");
      PBErrCatch(GSetErr);
    }
  }
  printf("UnitTestGSetShuffle OK\n");
}

void UnitTestGSet() {
  UnitTestGSetCreateFree();
  UnitTestGSetClone();
  UnitTestGSetFlush();
  UnitTestGSetPrint();
  UnitTestGSetPushPopAppendDrop();
  UnitTestGSetAddSort();
  UnitTestGSetInsertRemove();
  UnitTestGSetNbElemGet();
  UnitTestGSetGetIndex();
  UnitTestGSetSort();
  UnitTestGSetSortBig();
  UnitTestGSetSplitMerge();
  UnitTestGSetSwitch();
  UnitTestGSetMoveElem();
  UnitTestGSetMergeSet();
  UnitTestGSetCount();
  UnitTestGSetShuffle();
  printf("UnitTestGSet OK\n");
}

void UnitTestGSetIteratorForwardCreateFree() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterForward* iter = GSetIterForwardCreate(&set);
  if (iter->_set != &set || iter->_curElem != set._head) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardCreateFree NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterFree(&iter);
  if (iter != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "iter is not NULL after free");
    PBErrCatch(GSetErr);
  }
  GSetIterForward iterb = GSetIterForwardCreateStatic(&set);
  if (iterb._set != &set || iterb._curElem != set._head) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardCreateFree NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorForwardCreateFree OK\n");
}

void UnitTestGSetIteratorForwardClone() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  GSetIterForward* iterb = GSetIterClone(&iter);
  if (iter._set != iterb->_set || iter._curElem != iterb->_curElem) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardClone NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterFree(&iterb);
  GSetFlush(&set);
  printf("UnitTestGSetIteratorForwardClone OK\n");
}

void UnitTestGSetIteratorForwardReset() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  GSetIterStep(&iter);
  GSetIterReset(&iter);
  if (iter._curElem != set._head) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardReset NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorForwardReset OK\n");
}

void UnitTestGSetIteratorForwardStepGetGetElem() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  GSetElem* elem = set._head->_next;
  GSetIterStep(&iter);
  if (iter._curElem != elem) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterStep NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetIterGetElem(&iter) != elem) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterGetElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetIterGet(&iter) != a + 1) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterGet NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterStepBack(&iter);
  if (iter._curElem != set._head) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterStepBack NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorForwardStepGetGetElem OK\n");
}

void FunInc(void* data, void* param) {
  (void)param;
  ++(*(int*)data);
}

void UnitTestGSetIteratorForwardApply() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  GSetIterApply(&iter, &FunInc, NULL);
  for (int i = 5; i--;)
    if (a[i] != i + 2) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardApply NOK");
      PBErrCatch(GSetErr);
    }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorForwardApply OK\n");
}

void UnitTestGSetIteratorForwardIsFirstIsLast() {
  int a[3] = {1, 2, 3};
  GSet set = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&set, a + i);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  if (GSetIterIsFirst(&iter) == false || GSetIterIsLast(&iter) == true) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, 
      "UnitTestGSetIteratorForwardIsFirstIsLast NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterStep(&iter);
  if (GSetIterIsFirst(&iter) == true || GSetIterIsLast(&iter) == true) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, 
      "UnitTestGSetIteratorForwardIsFirstIsLast NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterStep(&iter);
  if (GSetIterIsFirst(&iter) == true || GSetIterIsLast(&iter) == false) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, 
      "UnitTestGSetIteratorForwardIsFirstIsLast NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorForwardIsFirstIsLast OK\n");
}

void UnitTestGSetIteratorForwardSet() {
  int a[3] = {1, 2, 3};
  GSet set = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&set, a + i);
  int b[3] = {1, 2, 3};
  GSet setb = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&setb, b + i);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  GSetIterSetGSet(&iter, &setb);
  if (iter._set != &setb || iter._curElem != setb._head) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterSetGSet NOK");
    PBErrCatch(GSetErr);
  }
  char c = ' ';
  GSetIterSetData(&iter, &c);
  if (GSetIterGet(&iter) != &c) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterSetData NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  GSetFlush(&setb);
  printf("UnitTestGSetIteratorForwardSet OK\n");
}

void UnitTestGSetIteratorForwardRemoveElem() {
  int a[3] = {1, 2, 3};
  GSet set = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&set, a + i);
  GSetIterForward iter = GSetIterForwardCreateStatic(&set);
  GSetIterStep(&iter);
  if (GSetIterRemoveElem(&iter) == false) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetNbElem(&set) != 2) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (iter._curElem != set._head->_next) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetIterRemoveElem(&iter) == true) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetNbElem(&set) != 1) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorForwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorForwardRemoveElem OK\n");
}

void UnitTestGSetIteratorForward() {
  UnitTestGSetIteratorForwardCreateFree();
  UnitTestGSetIteratorForwardClone();
  UnitTestGSetIteratorForwardReset();
  UnitTestGSetIteratorForwardStepGetGetElem();
  UnitTestGSetIteratorForwardApply();
  UnitTestGSetIteratorForwardIsFirstIsLast();
  UnitTestGSetIteratorForwardSet();
  UnitTestGSetIteratorForwardRemoveElem();
  printf("UnitTestGSetIteratorForward OK\n");
}

void UnitTestGSetIteratorBackwardCreateFree() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterBackward* iter = GSetIterBackwardCreate(&set);
  if (iter->_set != &set || iter->_curElem != set._tail) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardCreateFree NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterFree(&iter);
  if (iter != NULL) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "iter is not NULL after free");
    PBErrCatch(GSetErr);
  }
  GSetIterBackward iterb = GSetIterBackwardCreateStatic(&set);
  if (iterb._set != &set || iterb._curElem != set._tail) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardCreateFree NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorBackwardCreateFree OK\n");
}

void UnitTestGSetIteratorBackwardClone() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterBackward iter = GSetIterBackwardCreateStatic(&set);
  GSetIterBackward* iterb = GSetIterClone(&iter);
  if (iter._set != iterb->_set || iter._curElem != iterb->_curElem) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardClone NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterFree(&iterb);
  GSetFlush(&set);
  printf("UnitTestGSetIteratorBackwardClone OK\n");
}

void UnitTestGSetIteratorBackwardReset() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterBackward iter = GSetIterBackwardCreateStatic(&set);
  GSetIterStep(&iter);
  GSetIterReset(&iter);
  if (iter._curElem != set._tail) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardReset NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorBackwardReset OK\n");
}

void UnitTestGSetIteratorBackwardStepGetGetElem() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterBackward iter = GSetIterBackwardCreateStatic(&set);
  GSetElem* elem = set._tail->_prev;
  GSetIterStep(&iter);
  if (iter._curElem != elem) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterStep NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetIterGetElem(&iter) != elem) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterGetElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetIterGet(&iter) != a + 3) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterGet NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterStepBack(&iter);
  if (iter._curElem != set._tail) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterStepBack NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorBackwardStepGetGetElem OK\n");
}

void UnitTestGSetIteratorBackwardApply() {
  int a[5] = {1, 2, 3, 4, 5};
  GSet set = GSetCreateStatic();
  for (int i = 5; i--;)
    GSetPush(&set, a + i);
  GSetIterBackward iter = GSetIterBackwardCreateStatic(&set);
  GSetIterApply(&iter, &FunInc, NULL);
  for (int i = 5; i--;)
    if (a[i] != i + 2) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardApply NOK");
      PBErrCatch(GSetErr);
    }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorBackwardApply OK\n");
}

void UnitTestGSetIteratorBackwardIsFirstIsLast() {
  int a[3] = {1, 2, 3};
  GSet set = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&set, a + i);
  GSetIterBackward iter = GSetIterBackwardCreateStatic(&set);
  if (GSetIterIsFirst(&iter) == false || GSetIterIsLast(&iter) == true) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, 
      "UnitTestGSetIteratorBackwardIsFirstIsLast NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterStep(&iter);
  if (GSetIterIsFirst(&iter) == true || GSetIterIsLast(&iter) == true) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, 
      "UnitTestGSetIteratorBackwardIsFirstIsLast NOK");
    PBErrCatch(GSetErr);
  }
  GSetIterStep(&iter);
  if (GSetIterIsFirst(&iter) == true || GSetIterIsLast(&iter) == false) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, 
      "UnitTestGSetIteratorBackwardIsFirstIsLast NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorBackwardIsFirstIsLast OK\n");
}

void UnitTestGSetIteratorBackwardSet() {
  int a[3] = {1, 2, 3};
  GSet set = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&set, a + i);
  int b[3] = {1, 2, 3};
  GSet setb = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&setb, b + i);
  GSetIterBackward iter = GSetIterBackwardCreateStatic(&set);
  GSetIterSetGSet(&iter, &setb);
  if (iter._set != &setb || iter._curElem != setb._tail) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterSetGSet NOK");
    PBErrCatch(GSetErr);
  }
  char c = ' ';
  GSetIterSetData(&iter, &c);
  if (GSetIterGet(&iter) != &c) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetIterSetData NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  GSetFlush(&setb);
  printf("UnitTestGSetIteratorBackwardSet OK\n");
}

void UnitTestGSetIteratorBackwardRemoveElem() {
  int a[3] = {1, 2, 3};
  GSet set = GSetCreateStatic();
  for (int i = 3; i--;)
    GSetPush(&set, a + i);
  GSetIterBackward iter = GSetIterBackwardCreateStatic(&set);
  GSetIterStep(&iter);
  if (GSetIterRemoveElem(&iter) == false) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetNbElem(&set) != 2) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (iter._curElem != set._head) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetIterRemoveElem(&iter) == true) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  if (GSetNbElem(&set) != 1) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "UnitTestGSetIteratorBackwardRemoveElem NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetIteratorBackwardRemoveElem OK\n");
}

void UnitTestGSetIteratorBackward() {
  UnitTestGSetIteratorBackwardCreateFree();
  UnitTestGSetIteratorBackwardClone();
  UnitTestGSetIteratorBackwardReset();
  UnitTestGSetIteratorBackwardStepGetGetElem();
  UnitTestGSetIteratorBackwardApply();
  UnitTestGSetIteratorBackwardIsFirstIsLast();
  UnitTestGSetIteratorBackwardSet();
  printf("UnitTestGSetIteratorBackward OK\n");
}

void UnitTestSpeedShuffle() {
  GSet set = GSetCreateStatic();
  long setSizeMin = 100;
  long setSizeMax = 10000;
  int nbRun = 100;
  printf("Start speed test for shuffling algorithms\n\n");
  for (long setSize = setSizeMin; setSize <= setSizeMax; setSize *= 2) {
    for (long i = setSize; i--;)
      GSetPush(&set, i);
    /*for (int run = 10; run--;) {
      GSetShuffle(&set);
      GSetShuffleA(&set);
      GSetShuffleB(&set);
      GSetShuffleC(&set);
    }*/
    clock_t clockBefore = clock();
    for (int run = nbRun; run--;)
      GSetShuffleA(&set);
    clock_t clockAfter = clock();
    float delayMsA = 1.0 / ((double)nbRun) * ((double)(clockAfter - clockBefore)) / 
      CLOCKS_PER_SEC * 1000.0;
    printf("Delay to shuffle %ld elements with GSetShuffleA: %fms\n", 
      setSize, delayMsA);
    clockBefore = clock();
    for (int run = nbRun; run--;)
      GSetShuffleB(&set);
    clockAfter = clock();
    float delayMsB = 1.0 / ((double)nbRun) * ((double)(clockAfter - clockBefore)) / 
      CLOCKS_PER_SEC * 1000.0;
    printf("Delay to shuffle %ld elements with GSetShuffleB: %fms\n", 
      setSize, delayMsB);
    clockBefore = clock();
    for (int run = nbRun; run--;)
      GSetShuffleC(&set);
    clockAfter = clock();
    float delayMsC = 1.0 / ((double)nbRun) * ((double)(clockAfter - clockBefore)) / 
      CLOCKS_PER_SEC * 1000.0;
    printf("Delay to shuffle %ld elements with GSetShuffleC: %fms\n", 
      setSize, delayMsC);
    clockBefore = clock();
    for (int run = nbRun; run--;)
      GSetShuffle(&set);
    clockAfter = clock();
    float delayMs = 1.0 / ((double)nbRun) * ((double)(clockAfter - clockBefore)) / 
      CLOCKS_PER_SEC * 1000.0;
    printf("Delay to shuffle %ld elements with GSetShuffle: %fms\n", 
      setSize, delayMs);
    printf("\n");
    if (delayMs > 1.1 * MIN(delayMsA, MIN(delayMsB, delayMsC))) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "UnitTestSpeedShuffle NOK");
      PBErrCatch(GSetErr);
    }
    GSetFlush(&set);
  }
  printf("UnitTestSpeedShuffle OK\n");
}

void UnitTestGSetJump() {
  GSet set = GSetCreateStatic();
  const long nb = 100000;
  long check[nb];
  for (long i = 0; i < nb; ++i) {
    check[i] = i;
    GSetAppend(&set, check + i);
  }
  clock_t clockBefore = clock();
  for (long i = 0; i < nb; ++i) {
    long* v = GSetGet(&set, i);
    if (*v != check[i]) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetGet NOK");
      PBErrCatch(GSetErr);
    }
  }
  clock_t clockAfter = clock();
  float delayMsA = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  clockBefore = clock();
  (void)GSetGet(&set, 0);
  for (long i = 0; i < nb; ++i) {
    long* v = GSetGetJump(&set, i);
    if (*v != check[i]) {
      GSetErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GSetErr->_msg, "GSetGetJump NOK");
      PBErrCatch(GSetErr);
    }
  }
  clockAfter = clock();
  float delayMsB = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("Delay to access %ld elements with GSet: %fms\n", 
    nb, delayMsA);
  printf("Delay to access %ld elements with GSetJump: %fms\n", 
    nb, delayMsB);
  if (delayMsA < 1.1 * delayMsB) {
    GSetErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GSetErr->_msg, "GSetGetJump NOK");
    PBErrCatch(GSetErr);
  }
  GSetFlush(&set);
  printf("UnitTestGSetJump OK\n");
}

void UnitTestAll() {
  UnitTestGSetElem();
  UnitTestGSet();
  UnitTestGSetIteratorForward();
  UnitTestGSetIteratorBackward();
  UnitTestSpeedShuffle();
  UnitTestGSetJump();
  printf("UnitTestAll OK\n");
}

int main() {
  UnitTestAll();
  // Return success code
  return 0;
}

