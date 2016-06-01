#pragma once

# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>
#include <iostream>
#include <thread>
void task1_1() {
#pragma omp parallel num_threads(2)
{
#pragma omp critical
	std::cout << "Hello World!" << std::endl;
}
}
void task1_2(){
omp_set_num_threads(3);
std::cout << "Thread in sequential part has number " << omp_get_thread_num() << " from " << omp_get_max_threads() << std::endl;
#pragma omp parallel
	{
#pragma omp critical
		std::cout << "Thread " << omp_get_thread_num() << " from " << omp_get_num_threads()<<std::endl;
	}
}
void task1_2_modified() {
	omp_set_num_threads(omp_get_num_procs());
	std::cout << "Thread in sequential part has number " << omp_get_thread_num() << " from " << omp_get_max_threads() << std::endl;
#pragma omp parallel
	{
#pragma omp critical
		std::cout << "Thread " << omp_get_thread_num() << " from " << omp_get_num_threads() << std::endl;
	}
}
void task1_3() {
#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int nthreads = omp_get_max_threads();
#pragma omp critical
		std::cout << "Thread number " << id << " from " << nthreads << std::endl;
	}
}
void task1_4() {
		int nthreads = omp_get_max_threads();
#pragma omp parallel for schedule(static,1)
		for (int i = 0; i < 16; i++)
#pragma omp critical
			std::cout << "Step " << i << ", thread number " << omp_get_thread_num() << " from " << nthreads
			<< std::endl;
}
void task1_5() {
	omp_set_num_threads(omp_get_num_procs());
	double t=omp_get_wtime();
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < 32; i++) 
		std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Execution time=" << omp_get_wtime() - t<<std::endl;
}
void task3() {
	int tab[] = { 1,2,3,4,5,6,7,8,9,10 }, threads;
	long int a = 1;
	int a_thr = 1;
	threads = omp_get_num_procs();
	omp_set_num_threads(threads);
#pragma omp parallel firstprivate(a_thr) shared(a)
	{
#pragma omp for
		for (int i = 0; i < 10; i++)
			a_thr *= tab[i];
#pragma omp critical
		a *= a_thr;
	}
	std::cout << "a= " << a << std::endl;
}
void task3_reduction() {

	int tab[] = { 1,2,3,4,5,6,7,8,9,10 }, threads;
	long int a = 1;
	threads = omp_get_num_procs();
	omp_set_num_threads(threads);
#pragma omp parallel
	{
#pragma omp for reduction(*:a)
		for (int i = 0; i < 10; i++)
			a *= tab[i];
	}
	std::cout << "a= " << a << std::endl;
}
void task3_exercise() {
	int tab[] = { 1,2,3,4,5,6,7,8,9,10 };
	long int a = 0;
	omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel
	{
#pragma omp for reduction(+:a)
		for (int i = 0; i < 10; i++)
			a += tab[i];
	}
	std::cout << "a= " << a << std::endl;
}
void task4() {
	int tab[10];
	for (int i = 0; i < 10; i++) {
		tab[i] = int((float(rand()) / RAND_MAX)*10);
	}
	long time = omp_get_wtime();
	omp_set_num_threads(omp_get_num_procs());
	int a = 0;
#pragma omp parallel for reduction(+:a)
	for (int i = 0; i < 10;i++)
	{
		a += tab[i];
	}
	std::cout << a<<std::endl <<"time="<<omp_get_wtime()-time<<std::endl;
}
void task5() {
	double result=0.0;
	double b = 3.14;
	double a=0;
	std::cout << "thread is running... " << std::endl;
	double h = (b - a) / 10;
	double s = sin(a);
#pragma omp parallel for reduction(+:s)
	for (int i = 0; i < 10; i++)
		s += 2 * sin(a + i*h);
	s += sin(b);
	result = s*h / 2;
	std::cout << "result=" << result << std::endl;
}
void exam1(int threads) {
	omp_set_num_threads(threads);
#pragma omp parallel for
	for (int i = 0; i < 15; i++)
#pragma omp critical
		std::cout << "number from " << i << " to 14" << " number=" << omp_get_thread_num() << std::endl;
}
void exam2() {
	char t1[75], t2[75];
	omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel 
	{
#pragma omp single
	{
		for (int i = 0; i < 75; i++) {
			//std::cout << omp_get_thread_num() << std::endl;
			t1[i] = (char)(33 + i);
		}
	}
#pragma omp for
			for (int i = 0; i < 75; i++) {
				//std::cout << omp_get_thread_num() << std::endl;
				t2[i] = (char)(33 + i);
			}
	}
#pragma omp single
	for (int i = 0; i < 75; i++)
		std::cout << t1[i] << " " << t2[i] << "    " << omp_get_thread_num()<<" from "<< omp_get_max_threads()<< std::endl;
}
void exam3() {
	int t1[75], t2[75];
	int a = 0;
	int i = 0;
#pragma omp parallel firstprivate(i)
	{
#pragma omp for
		for (i=0; i < 75; i++) {
			t1[i] = int((float(rand()) / RAND_MAX) * 20);;
			t2[i] = int((float(rand()) / RAND_MAX) * 20);;
		}
#pragma omp for reduction(+:a)
		for (i=0; i < 75; i++)
			a += t1[i] + t2[i];
	}
	int b = 0;
	for (i=0; i < 75; i++)
		b += t1[i] + t2[i];
	if (a != b)std::cout << "rozne" << std::endl;
	else std::cout << "takie same" << std::endl;
}
void exam2_1(int threads) {
	omp_set_num_threads(threads);
#pragma omp parallel for
	for (int i = 0; i < 10; i++) {
#pragma omp critical
		std::cout << "i=" << i << " from 9 number=" << omp_get_thread_num()<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds((int(float(rand()) / RAND_MAX) * 400) + 100));
	}
}
void exam2_2() {
	int t1[100], t2[100];
	for (int i = 0; i < 100; i++) {
		t1[i] = int((float(rand()) / RAND_MAX) * i);
	}
	omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel
	{
#pragma omp for schedule(dynamic,2)
		for (int i = 0; i < 100; i++)
			t2[i] = int((float(rand()) / RAND_MAX) * i);
#pragma omp single
		for (int i = 0; i < 100; i++)
			std::cout << t1[i] << "  " << t2[i] << std::endl;
	}
}