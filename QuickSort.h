#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "TeraSortItem.h"

template <class T>
class QuickSort{
    private:
       T ** teraSortItem;
       
    public:

        
        QuickSort(T ** p_teraSortItem);
        
        void quickSort(int64_t low, int64_t high);

        //int64_t partition(int64_t l, int64_t r);
      //  T* partition(int64_t l, int64_t r);
        //void quickSort(int64_t l, int64_t r);
       // void quickSort (int64_t list_size);
        ~QuickSort();
};

#endif