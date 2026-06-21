#ifndef MAXHEAP_H
#define MAXHEAP_H
#include "structs.h"

struct MaxHeap
{
    SinhVien data[MAX_SV];
    int size;
};

void heapify(MaxHeap& heap, int i);

void buildMaxHeap(MaxHeap& heap);

SinhVien extractMax(MaxHeap& heap);

bool isHeapEmpty(const MaxHeap& heap);

#endif
