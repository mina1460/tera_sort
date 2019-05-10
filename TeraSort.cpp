#ifndef TERASORT_CPP
#define TERASORT_CPP

#include "TeraSort.h"

template <class T, typename S>
TeraSort<T,S>::TeraSort (char * p_input_file_name,char * p_output_file_name,
                            uint16_t p_mappers, uint16_t p_reducers,uint64_t p_sample_size)
{
    input = fopen (p_input_file_name,"rb");
    output = fopen (p_output_file_name,"wb");
    file_byte_size = 0 ;
    file_record_size = 0 ;
    mappers = p_mappers;
    reducers = p_reducers;
    sample_size = p_sample_size;
    map_engines = NULL;
    partitioner=NULL;
    if ( input != NULL && output != NULL)
    {
       //Do your implementation here
        //sets the file pointer to the end of the file
        fseek(input,0,SEEK_END);
        //stores the size of the program in the file_byte_size
        file_byte_size = ftell(input);
        rewind(input);
        file_record_size = 100; //each line is 100 bytes
        //stores the number of lines by dividing the file size by the size of each line
        uint64_t records_count = file_byte_size / file_record_size;
        uint64_t rem = records_count % mappers; //the remainder is the value which shall be passed to last thread more than the others.
        uint64_t start = records_count / mappers ; //the starting position for all threads
//partitioner<T,S>::Partitioner (FILE * f,uint16_t p_partitions_count,uint64_t p_partition_expected_size)
        uint64_t partition_expected_size = (file_byte_size/100) / reducers;
        partitioner = new Partitioner <T,S> (output, reducers, partition_expected_size);

        int i;

        map_engines = new Mapper <T,S> *[mappers];
        reduce_engines = new Reducer <T,S> *[reducers];

        for (i = 0; i<mappers -1; i++)
        {
            //Mapper<T,S>::Mapper (FILE * f, uint64_t p_start, uint64_t p_count, uint64_t p_sample_size, Partitioner<T,S> * p_partitioner)
            map_engines[i] = new Mapper <T,S> (input, i*start, records_count / mappers, sample_size, partitioner);
        }

        map_engines[mappers-1] = new Mapper <T,S> (input, i*start, ((records_count / mappers)+ rem), sample_size, partitioner);


        for (int j = 0; j < reducers; j++)
        {
            reduce_engines[j]= new Reducer <T,S> (partitioner->getPartition(j)); 
        }

    }
    else perror("opening input or output files has failed");
}

template <class T, typename S>
void TeraSort<T,S>::execute()
{
    printf ("Terasort Start Execute\n");
    

    for ( uint16_t i = 0 ; i  < mappers; i++)
    {
        std::thread * th = new std::thread(Mapper<T,S>::start, map_engines[i]);    
        map_engines[i]->setThread(th);
    }

	//Do your implementation here
    for (int i=0; i<mappers; i++)
    {
          printf("waiting for thread number %d to finish executing\n",i+1);
        map_engines[i]->waitForRunToFinish(); 
    }

//now I should calculate the Cutpoints so that they can be used in phase 2
        partitioner->calcCutpointsAverage(mappers);
        
    

    //this would be resposnible for calling phase 2

     for ( uint16_t i = 0 ; i  < mappers; i++)
    {
        std::thread * th2 = new std::thread(Mapper<T,S>::start, map_engines[i]);
        map_engines[i]->setThread(th2);
    }

                //Do your implementation here
      for (int x=0; x<mappers; x++)
        {
             map_engines[x]->waitForRunToFinish();
        }

    printf("phase 1 and 2 are now done\n");

for ( uint16_t j = 0 ; j  < reducers; j++)
            {
                std::thread * th = new std::thread(Reducer<T,S>::start, reduce_engines[j]);
                reduce_engines[j]->setThread(th);
            }

 for (int x=0; x<reducers; x++)   
   reduce_engines[x]->waitForRunToFinish();
 

 for ( uint16_t i = 0 ; i  < reducers; i++)
     partitioner->getPartition(i)->dump();
 cout<<"almafrod 3mlt dump\n";


}


template <class T, typename S>
TeraSort<T,S>::~TeraSort()
{
    if ( input != NULL) fclose (input);
    if ( output != NULL) fclose (output);
    if ( map_engines != NULL)
    {
        for ( uint16_t i = 0 ; i  < mappers; i++)
            delete (map_engines[i]);
        free(map_engines);
    }
    if ( partitioner != NULL ) delete(partitioner);
}

#endif
