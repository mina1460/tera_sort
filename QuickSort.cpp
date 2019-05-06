#ifndef QUICKSORT_CPP_
#define QUICKSORT_CPP_
#include "QuickSort.h"


template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem)
{
    teraSortItem = p_teraSortItem;
}

template <class T>
int64_t QuickSort<T>:: partition(int64_t l , int64_t r ){
    
  /*  T* pivot = teraSortItem[r];
    int64_t i = (l-1);
    
    for(int64_t j=l; j<= r-1; j++){
        
        if(teraSortItem[j] <= pivot ){
            i++;
           // std::swap(teraSortItem[i],teraSortItem[j]);

            teraSortItem[j]->swap(teraSortItem[i]);
        }
        
        
    }
    //std::swap(teraSortItem[i+1],teraSortItem[r]);
    teraSortItem[i+1]->swap(teraSortItem[r]);
    return (i+1);*/
    
    cout<<"partition"<<endl;
}


template <class T>
void QuickSort<T>::quickSort( int64_t l, int64_t r){
    
    
/*    if(l < r){
        int64_t pi = partition(l,r);
        quickSort(l, pi-1);
        quickSort(pi+1, r);
    }*/
    cout<<"5alst"<<endl;
          
}


template <typename T>
void quickSort (uint64_t list_size)
{
    QuickSort<T>::quickSort (0,list_size-1);
}


template <class T>
QuickSort<T>::~QuickSort()
{

}


#endif