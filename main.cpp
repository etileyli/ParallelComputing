
// Ozcan Tilki
// g++ -g -o main main.cpp -pthread -std=c++11; ./main

#include <bits/stdc++.h>
#include <chrono>
#include <vector>
using namespace std;

/*
#define MAX 32

#define MAX_THREAD 4
*/
int thread_count = 1;
int matrix_size = 512;

std::vector<std::vector<int>> matA(matrix_size, vector<int>(matrix_size));//[MAX][MAX];;//[MAX][MAX];
std::vector<std::vector<int>> matB(matrix_size, vector<int>(1));//[MAX][1];;//[MAX][1];
std::vector<std::vector<int>> matC(matrix_size, vector<int>(1));//[MAX][1];;//[MAX][1];
int step_i = 0;


void print_left_matrix(){

    std::cout << "Matrix B\n";

	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++)
			std::cout << matA[i][j] << " ";
	std::cout << endl;
	}
}

void print_right_matrix(){
        std::cout << "Matrix A\n";

		for (int i = 0; i < matrix_size; i++){
			std::cout << matB[i][0] << " ";
	std::cout << endl;
	}
}

void print_result_matrix(){
    	std::cout << "\nMultiplication of A and B" << std::endl;
	for (int i = 0; i < matrix_size; i++) {
			cout << matC[i][0] << " ";
		cout << endl;
	}
}

void fill_matrix(){



	for (int i = 0; i < matrix_size; i++) {
        	matB[i][0] = rand() % 100;
		for (int j = 0; j < matrix_size; j++) {
			matA[i][j] = rand() % 100;

		}
	}
}

void* multi(void* arg)
{
	int i = step_i++;

	for (int k = 0; k < matrix_size; k++)
		matC[i][0] += matA[i][k] * matB[k][0];
}

long long process(int _thread_count, int _matrix_size){


    thread_count = _thread_count;
    matrix_size = _matrix_size;

    if(thread_count > matrix_size)
    	thread_count = 32;
   long long elapsed =0;

     fill_matrix();

     //print_left_matrix();
     //print_right_matrix();

   for(int t = 0; t < 10; t++){
         step_i = 0;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    for (int r = 0; r < (matrix_size/thread_count); r++) {

        std::vector<pthread_t> threads(thread_count);//[MAX_THREAD];

        int* p;
        for (int i = 0; i < thread_count; i++) {
            pthread_create(&threads[i], NULL, multi, (void*)(p));
        }


        for (int i = 0; i < thread_count; i++)
            pthread_join(threads[i], NULL);

    }

     std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      elapsed += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

 }


     //std::cout << "Elapsed Time : " << elapsed << std::endl;

     //print_result_matrix();

    return elapsed/10;

}


int main(int argc, char *argv[])
{

/*
     if(argc > 1){
     thread_count = atoi(argv[1]);
     matrix_size = atoi(argv[2]);
     }
     std::cout << "----------------------------" << std::endl;
     std::cout << "thread count : " << thread_count <<  std::endl;
     std::cout << "matrix size : " << matrix_size <<  std::endl;
*/

  std::cout << "[32x32][1 thread] : " << process(1, 32) << " microseconds" << std::endl;
  std::cout << "[32x32][2 thread] : " << process(2, 32) << " microseconds" << std::endl;
  std::cout << "[32x32][4 thread] : " << process(4, 32) << " microseconds" << std::endl;
  std::cout << "[32x32][8 thread] : " << process(8, 32) << " microseconds" << std::endl;
  std::cout << "[32x32][16 thread] : " << process(16, 32) << " microseconds" << std::endl;
  std::cout << "[32x32][32 thread] : " << process(32, 32) << " microseconds" << std::endl;
  std::cout << "[32x32][64 thread] : " << process(32, 32) << " microseconds" << std::endl;

  std::cout << "[128x128][1 thread] : " << process(1, 128) << " microseconds" << std::endl;
  std::cout << "[128x128][2 thread] : " << process(2, 128) << " microseconds" << std::endl;
  std::cout << "[128x128][4 thread] : " << process(4, 128) << " microseconds" << std::endl;
  std::cout << "[128x128][8 thread] : " << process(8, 128) << " microseconds" << std::endl;
  std::cout << "[128x128][16 thread] : " << process(16, 128) << " microseconds" << std::endl;
	std::cout << "[128x128][32 thread] : " << process(32, 128) << " microseconds" << std::endl;
  std::cout << "[128x128][64 thread] : " << process(64, 128) << " microseconds" << std::endl;

  std::cout << "[512x512][1 thread] : " << process(1, 512) << " microseconds" << std::endl;
  std::cout << "[512x512][2 thread] : " << process(2, 512) <<" microseconds" << std::endl;
  std::cout << "[512x512][4 thread] : " << process(4, 512) <<" microseconds" << std::endl;
  std::cout << "[512x512][8 thread] : " << process(8, 512) <<" microseconds" << std::endl;
  std::cout << "[512x512][16 thread] : " << process(16, 512) <<" microseconds" << std::endl;
	std::cout << "[512x512][32 thread] : " << process(32, 512) <<" microseconds" << std::endl;
  std::cout << "[512x512][64 thread] : " << process(64, 512) <<" microseconds" << std::endl;


	return 0;
}
