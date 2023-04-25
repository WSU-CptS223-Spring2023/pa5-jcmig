#include "ChainingHash.h"
#include "ProbingHash.h"
//#include "ParallelProbingHash.h" 
#include <omp.h>

#define NUM_THREADS 2  // update this value with the number of cores in your system. 

int main()
{
	/*Task I (a)- ChainingHash table*/

		//  create an object of type ChainingHash 
		ChainingHash<int, int> hashTable;

		// In order, insert values with keys 1 – 1,000,000. For simplicity, the key and value stored are the same. 
		double startTime = omp_get_wtime();
		for (int i = 1; i < 1000000; i++) {
			hashTable.insert(i, i);
		}
		double endTime = omp_get_wtime();

		// Report the total amount of time, in seconds, required to insert the values to ChainingHash table. Write the results to a file called “HashAnalysis.txt”. 
		std::ofstream outfile("HashAnalysis.txt");
		double insertTime = endTime - startTime;
		outfile << "Chaining insertion time: " << insertTime << " seconds" << std::endl;

		// Search for the value with key 177 in ChainingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		startTime = omp_get_wtime();
		int val = hashTable.find(177);
		endTime = omp_get_wtime();
		double searchTime = endTime - startTime;
		outfile << "Chaining search time: " << searchTime << " seconds" << std::endl;	

		// Search for the value with key 2,000,000 in ChainingHash table. Report the time required to find the value in each table by writing it to the file.  
		startTime = omp_get_wtime();
		val = hashTable.find(2000000);
		endTime = omp_get_wtime();
		double failedSearchTime = endTime - startTime;
		outfile << "Chaining failed search time: " << failedSearchTime << " seconds" << std::endl;

		// Remove the value with key 177 from ChainingHash table. Report the time required to remove the value with in each table by writing it to the file.  
		startTime = omp_get_wtime();
		hashTable.remove(177);
		endTime = omp_get_wtime();
		double removeTime = endTime - startTime;
		outfile << "Chaining deletion time: " << removeTime << " seconds" << std::endl;

		// Also, write to the file the final size, bucket count, and load factor of the hash for ChainingHash table. 
		outfile << "Table size: " << hashTable.size() << std::endl;
		outfile << "Bucket count: " << hashTable.bucket_count() << std::endl;
		outfile << "Load factor: " << hashtTable.load_factor() << std::endl;

		/* Example output template:
			Chaining insertion time: 
			Chaining search time: 
			Chaining failed search time: 
			Chaining deletion time: 
			Table size: 
			Bucket count: 
			Load factor: 
		*/

	/*Task I (b) - ProbingHash table (using Linear Probing) */

		//  create an object of type ProbingHash 
		ProbingHash<int, int> hashTable2;

		// In order, insert values with keys 1 – 1,000,000. For simplicity, the key and value stored are the same.
		startTime = omp_get_wtime();
		for (int i = 1; i < 1000000; i++) {
			hashTable2.insert(i, i);
		}
		endTime = omp_get_wtime();

		// Report the total amount of time, in seconds, required to insert the values to ProbingHash table. Write the results to a file called “HashAnalysis.txt”. 
		double insertTime2 = endTime - startTime;
		outfile << "Linear Probing insertion time: " << insertTime2 << " seconds" << std::endl;

		// Search for the value with key 177 in ProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		startTime = omp_get_wtime();
		val = hashTable2.search(177);
		end_time = omp_get_wtime();
		double searchTime2 = endTime - startTime;
		outfile << "Linear Probing search time: " << searchTime2 << " seconds" << std::endl;

		// Search for the value with key 2,000,000 in ProbingHash table. Report the time required to find the value in each table by writing it to the file.  
		startTime = omp_get_wtime();
		val = hashTable2.search(2000000);
		endTime = omp_get_wtime();
		double failedSearchTime2 = endTime - startTime;
		outfile << "Linear Probing failed search time: " << failedSearchTime2 << " seconds" << std::endl;

		// Remove the value with key 177 from ProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  
		startTime = omp_get_wtime();
		hashTable2.remove(177);
		endTime = omp_get_wtime();
		double removeTime2 = endTime - startTime;
		outfile << "Linear Probing deletion time: " << removeTime2 << " seconds" << std::endl;

		// Also, write to the file the final size, bucket count, and load factor of the hash for ProbingHash table. 
		outfile << "Table size: " << hashTable2.size() << std::endl;
		outfile << "Bucket count: " << hashTable2.bucket_count() << std::endl;
		outfile << "Load factor: " << hashTable2.load_factor() << std::endl;
		
		/* Example output template:
			Linear Probing insertion time: 
			Linear Probing search time: 
			Linear Probing failed search time: 
			Linear Probing deletion time: 
			Table size: 
			Bucket count: 
			Load factor: 
		*/
	
	/*Task II -  ParallelProbingHash table (using Linear Probing) */
      
	  // (a) Using a single thread:  
		//  create an object of type ParallelProbingHash 

		// Set the number of threads (omp_set_num_threads()) to 1 

		/* In an OpenMP parallel region (#pragma omp parallel), in order, insert values with keys 1 – 1,000,000. 
		Inside the parallel region make sure that the value for the iteration number of the loop is shared among all threads. 
		For simplicity, the key and value stored are the same.
        */
		// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

		// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		
		// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

		// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 

		/* Example output template:
			Parallel Probing insertion time: 
			Parallel Probing search time: 
			Parallel Probing failed search time: 
			Parallel Probing deletion time: 
			Table size: 
			Bucket count: 
			Load factor: 
		*/

	// (b) Using multiple threads:  
		//  create an object of type ParallelProbingHash 

		// i.	Change the number of threads to match the number of cores on your system 

		/* In an OpenMP parallel region (#pragma omp parallel), in order, insert values with keys 1 – 1,000,000. 
		Inside the parallel region make sure that the value for the iteration number of the loop is shared among all threads. 
		For simplicity, the key and value stored are the same.
        */
		// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

		// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		
		// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

		// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 

		/* Example output template:
			Parallel Probing insertion time: 
			Parallel Probing search time: 
			Parallel Probing failed search time: 
			Parallel Probing deletion time: 
			Table size: 
			Bucket count: 
			Load factor: 
		*/
	return 0;
}