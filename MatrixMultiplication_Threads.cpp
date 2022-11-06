// CPP Program to multiply two matrix using pthreads
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

// maximum size of matrix
#define MAX 32

// Number of threads
#define MAX_THREAD 1

int matA[MAX][MAX];
int matB[MAX][1];
int matC[MAX][1];
int thread_no = 0;

void* multi(void* arg)
{
	int thrd_no = thread_no++;
	for (int j = 0; j < (MAX/MAX_THREAD); j++){
		for (int k = 0; k < MAX; k++){
			matC[thrd_no * MAX/MAX_THREAD + j][0] += matA[thrd_no * MAX/MAX_THREAD + j][k] * matB[k][0];
		}
		cout << "thread no: "<< thrd_no << " matC[" << thrd_no * MAX/MAX_THREAD + j << "][0] = "	<< matC[thrd_no * MAX/MAX_THREAD + j][0] << endl;
	}
}

// Driver Code
int main()
{
	// Generating random values in matA and matB
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matA[i][j] = rand() % 10;
		}
	}

	// Generating random values in matA and matB
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < 1; j++) {
			matB[i][j] = rand() % 10;
		}
	}

	// Displaying matA
	// cout << endl << "Matrix A" << endl;
	// for (int i = 0; i < MAX; i++) {
	// 	for (int j = 0; j < MAX; j++)
	// 		cout << matA[i][j] << " ";
	// 	cout << endl;
	// }
	//
	// // Displaying matB
	// cout << endl << "Matrix B" << endl;
	// for (int i = 0; i < MAX; i++) {
	// 	for (int j = 0; j < 1; j++)
	// 		cout << matB[i][j] << " ";
	// 	cout << endl;
	// }

	// declaring threads array
	pthread_t threads[MAX_THREAD];

  clock_t begin = clock();

	// Creating threads, each evaluating its own part
	for (int i = 0; i < MAX_THREAD; i++) {
		int* p;
		pthread_create(&threads[i], NULL, multi, (void*)(p));
	}

	// joining and waiting for all threads to complete
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

 	clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	// Displaying the result matrix
	cout << endl << "Multiplication of A and B" << endl;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < 1; j++)
			cout << matC[i][j] << " ";
		cout << endl;
	}

	cout << "Elapsed time (ms): " << elapsed_secs * 1000;
	return 0;
}
