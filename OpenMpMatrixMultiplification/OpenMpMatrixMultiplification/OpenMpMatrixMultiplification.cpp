/* Mno¿enie macierzy z u¿yciem OpenMP */
#include "stdafx.h"
# include <stdlib.h>
# include <time.h>
#include <iostream>
# include <stdio.h>
# include <math.h>
# include <omp.h>
#include "MatrixOperations.h"
#include "OmpOperations.h"
int main(int argc, char *argv[])
{
	//int l = 1000, m = 2000, n = 500;

	//printf("\n  Mnozenie macierzy:\tA(%dx%d) = B(%dx%d) * C(%dx%d)\n\n", l, n, l, m, m, n);
	//printf("  Liczba dostepnych procesorow = %d\n", omp_get_num_procs());
	///* env OMP_NUM_THREADS=4 ./mxm */
	///* omp_set_num_threads(omp_get_num_procs()); */
	//printf("  Liczba zadeklarowanych watkow = %d\n", omp_get_max_threads());

	//rand_mxm(l, m, n);
	//
	std::cout <<std::endl<< "TASK 1_1" << std::endl;
	task1_1();
	std::cout << std::endl << "TASK 1_2" << std::endl;
	task1_2();
	std::cout <<std::endl<< "TASK 1_2_modified" << std::endl;
	task1_2_modified();
	std::cout << std::endl << "TASK 1_3" << std::endl;
	task1_3();
	std::cout << std::endl << "TASK 1_4" << std::endl;
	task1_4();
	std::cout << std::endl << "TASK 3" << std::endl;
	task3();
	std::cout << std::endl << "TASK 3_reduction" << std::endl;
	task3_reduction();
	std::cout << std::endl << "TASK 3_reduction" << std::endl;
	task3_exercise();
	std::cout << std::endl << "TASK 4" << std::endl;
	task4();
	std::cout << std::endl << "Exam 1" << std::endl;
	exam1(omp_get_num_procs());
	std::cout << std::endl << "Exam 2" << std::endl;
	exam2();
	std::cout << std::endl << "Exam 3" << std::endl;
	exam3();
	getchar();
	return 0;
}

