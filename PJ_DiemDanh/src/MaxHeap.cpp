#include "maxHeap.h"
#include <iostream>

// MaxHeap
bool isHeapEmpty(const MaxHeap& heap)
{
    return heap.size <= 0;
}

void heapify(MaxHeap& heap, int i)
{
    int lonNhat = i;
    int trai = 2 * i + 1;
    int phai = 2 * i + 2;

    // So sanh voi con trai
    if(trai < heap.size && heap.data[trai].soVang > heap.data[lonNhat].soVang)
    {
        lonNhat = trai;
    }

    // So sanh voi con phai
    if(phai < heap.size && heap.data[phai].soVang > heap.data[lonNhat].soVang)
    {
        lonNhat = phai;
    }

    // Neu nut cha khong phai lon nhat, hoan doi va tiep tuc dieu chinh xuong duoi
    if(lonNhat != i)
    {
        SinhVien temp = heap.data[i];
        heap.data[i] = heap.data[lonNhat];
        heap.data[lonNhat] = temp;

        heapify(heap, lonNhat);
    }
}

void buildMaxHeap(MaxHeap& heap)
{
    // Bat dau tu nut cha cuoi cung, dieu chinh dan len goc
    for(int i = heap.size / 2 - 1; i >= 0; i--)
    {
        heapify(heap, i);
    }
}

SinhVien extractMax(MaxHeap& heap)
{
    if(isHeapEmpty(heap))
    {
        cout << "Loi: Khong the lay phan tu tu heap rong!\n";
        SinhVien rong;
        rong.mssv = -1;
        return rong;
    }

    SinhVien max = heap.data[0];
    heap.data[0] = heap.data[heap.size - 1];
    heap.size--;
    heapify(heap, 0);
    return max;
}
