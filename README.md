# Tera_sort
This is an implementation of the Hadoop Map Reduce model to solve the Tera sort problem. 

What is the Tera Sort problem?
The Tera Sort problem is a benchmark for evaluating the performance of large-scale sorting algorithms. It involves sorting a very large dataset, typically in the range of terabytes (hence the name "Tera Sort"). The goal is to sort the data as efficiently as possible, in terms of both time and resources used.

The dataset for the Tera Sort problem is usually generated randomly, and the sorting is performed on the keys of the records. The keys are typically integers or strings, and the records may include additional data fields.

Solving the Tera Sort problem requires the use of efficient algorithms and data structures, as well as the ability to scale the sorting process to large distributed systems. The Map Reduce architecture is often used for this purpose, as it allows for parallelization of the sorting process across multiple machines.

In this project, we have implemented a solution to the Tera Sort problem using the Map Reduce architecture and multithreading in C++. The program is able to sort large datasets efficiently and quickly, making it a useful tool for sorting very large datasets.

Ideally, the code can be changed very easily to do any sort of Map reduce functions by replacing the action hooks to any function other than the quick sort; however, you still need to define the merge process. 
