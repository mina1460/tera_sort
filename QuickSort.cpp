#ifndef QUICKSORT_CPP_
#define QUICKSORT_CPP_
#include "QuickSort.h"


template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem)
{
    teraSortItem = p_teraSortItem;
}

template <class T>
void QuickSort<T>::quickSort(int64_t low, int64_t high)
{
    int64_t i = low;
    int64_t j = high;
    int64_t pi = (i+j)/2;
   // T* pivot = teraSortItem[pi];

    uint128_t pivot =  teraSortItem[pi]->key();
   // cout<<"low: "<<i<<"  high: "<<j <<"  pivot: "<<pi<<endl;

    while (i <= j)
    {
        while (teraSortItem[i]->key() < pivot)
            i++;
        while (teraSortItem[j]->key() > pivot)
            j--;

        if (i <= j)
        {
            teraSortItem[i]->swap(teraSortItem[j]);
            i++;
            j--;
        }
    }

    if (j > low)
        { quickSort(low, j); }
    if (i < high)
        {quickSort(i, high); }
}







/*
// ================================geeks for geeks============================= 


template <class T>
int64_t QuickSort<T>:: partition(int64_t l , int64_t r ){
    
    
    T* pivot = teraSortItem [r];
   //uint128_t pivot = teraSortItem[r]->getKeyValue();
    int64_t i = (l-1);
    
    for(int64_t j=l; j<= r-1; j++){
        
        if(teraSortItem[j] <= pivot){
           
            i++;
           // std::swap(teraSortItem[i],teraSortItem[j]);
            teraSortItem[i]->swap(teraSortItem[j]);
        }
        
        
    }
   // std::swap(teraSortItem[i+1],teraSortItem[r]);
    teraSortItem[i+1]->swap(teraSortItem[r]);
    return (i+1);
    
}

template <class T>
void QuickSort<T>::quickSort( int64_t l, int64_t r){
    
    
  if(l < r){

        int64_t pi = partition(l,r);
        cout<<"left: "<<l<<"   pi:  "<<pi<<"  right:  "<<r<<endl;
        quickSort(l, pi-1);
        quickSort(pi+1, r);
    }
        
}

*/













/*

------------------code aldoctor ------------------------
template <class T>
T* QuickSort<T>:: partition(int64_t left , int64_t right )
{

T** m = NULL;
int64_t center=(left+right)/2;
if(teraSortItem[center]<teraSortItem[left])
    teraSortItem[center]->swap(teraSortItem[left]);
if ( teraSortItem[right] < teraSortItem[left] )
    teraSortItem[right]->swap(teraSortItem[left]);
if ( teraSortItem[right] < teraSortItem[center] )
    teraSortItem[right]->swap(teraSortItem[left]);

teraSortItem[center]->swap(teraSortItem[right-1]);
return teraSortItem[right-1];


}


template <class T>
 void QuickSort<T>::quickSort (int64_t left, int64_t right) 
 {
    T * pivot = partition(left,right);
    int64_t i = left, j = right-1;
for (;;) 
{
    while (teraSortItem[++i] < pivot);
    while ( pivot < teraSortItem[--j]);
    
    if ( i < j ) teraSortItem[i]->swap(teraSortItem[j]); else break;
}

teraSortItem[i]->swap(teraSortItem[right-1]);

    quickSort(left,i-1);
    quickSort(i+1,right);
}


/*
template <typename T>
void quickSort (uint64_t list_size)
{
    QuickSort<T>::quickSort (0,list_size-1);
}
*/



template <class T>
QuickSort<T>::~QuickSort()
{}


#endif
