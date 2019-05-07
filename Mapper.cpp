#ifndef MAPPER_CPP
#define MAPPER_CPP

#include "Mapper.h"
#include "QuickSort.cpp"


template <class T, typename S>
Mapper<T,S>::Mapper (FILE * f, 
                uint64_t p_start,
                uint64_t p_count,
                uint64_t p_sample_size,
                Partitioner<T,S> * p_partitioner)
{
    input = f;
    read_count = p_count;
    read_start = p_start;
    sample_size = p_sample_size;

    dataWrapper = NULL;
    data = (S *) calloc (read_count,sizeof(S));
    fseek(input,read_start*sizeof(S),SEEK_SET);
    uint64_t read_items = fread(data,sizeof(S),read_count,f);
    partitioner = p_partitioner;
    phase = PHASE1;
}



template <class T, typename S>
void Mapper<T,S>::phase1()
{
    dataWrapper = (T **) calloc (read_count,sizeof(T *));
    sample = (T **) calloc (sample_size,sizeof(T *));
    for ( uint64_t i = 0  ; i < read_count ; i ++)
        dataWrapper[i] = new T (&data[i]);
    
 
    //Do your implementation here
    srand(time(NULL));
    uint64_t index;

/*
for (uint64_t i = 0; i < sample_size; ++i)
{
    sample[i] = new T();
}
*/
 for (uint64_t i = 0; i < sample_size; ++i)
 {
    index = rand() % read_count;
     sample[i] = new T();
     sample[i] = dataWrapper[index];
      while(sample[i]->getB1()== 1)
            {
                index = rand() % read_count;
                sample[i] = dataWrapper[index];
            }
        
            sample[i]->setB1(1);
 }


/* for (uint64_t i = 0 ; i < sample_size; i++)
        {
            index = rand() % read_count;
           
            sample[i] = dataWrapper[index];
            

            while(sample[i]->getB1()== 1)
            {
                index = rand() % read_count;
                sample[i] = dataWrapper[index];
            }
        
            sample[i]->setB1(1);
        }

*/
//now I have my samples and need to sort them in order to get my cutpoints from the sorted samples array and pass them to the partioner
	/* QuickSort<T> qs (sample);


   qs.quickSort(0, sample_size-1);*/



   //now samples are sorted

   //we should get the cutpoints now and send them to the partioner

    
uint64_t reducers_count = partitioner->getPartitionsCount();
uint64_t increment = sample_size/(reducers_count-1);
uint64_t add = increment;


for(uint64_t i=0; i<reducers_count-1; i++)
{
     partitioner->addCutpoint(i, sample[increment-10]);
     increment += add-10;
}
   //we can also send the sample pointer to the terasort which would calculate cutpoints and pass them to the partitioner
cout<<"phase 1 done"<<endl;

}
template <class T, typename S>
void Mapper<T,S>::phase2()
{
    printf ("\n \n \tStart Shuffling .....\n");
    for ( uint64_t i = 0 ; i  < read_count ; i ++)
        partitioner->addItem(dataWrapper[i]);    
    printf ("Finished Shuffling .....\n");
}


template <class T, typename S>
void Mapper<T,S>::execute ()
{
    if ( phase == PHASE1) 
    {
        phase1();
        phase = PHASE2;
    }
    else if(phase == PHASE2) phase2();
}

template <class T, typename S>
void Mapper<T,S>::start (Mapper<T,S> * me)
{
    me->execute();
}

template <class T, typename S>
void Mapper<T,S>::setThread(std::thread * p_th)
{
    th = p_th;
}

template <class T, typename S>
void Mapper<T,S>::waitForRunToFinish()
{
   // printf("waiting for thread number %s to finish executing\n","before");
    if(th->joinable()) cout<<"yes\n"; else cout<<"no\n";
    th->join();
     printf("waiting for thread number %s to finish executing\n","after");
    

}

template <class T, typename S>
Mapper<T,S>::~Mapper()
{
    if (dataWrapper != NULL)
    {
        for ( uint64_t i = 0  ; i < read_count ; i ++) delete (dataWrapper[i]);
        free(dataWrapper);
    }
    free(data);
    delete(th);
}

#endif