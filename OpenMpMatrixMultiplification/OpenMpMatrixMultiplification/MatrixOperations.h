#pragma once
#include "stdafx.h"
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>

int random_number(int min_num, int max_num) {
	int result = 0, low_num = 0, hi_num = 0;
	if (min_num<max_num)
	{
		low_num = min_num;
		hi_num = max_num + 1; // aby domkn¹æ przedzia³ max_num na wyjœciu generatora
	}
	else {
		low_num = max_num + 1;// aby domkn¹æ przedzia³ max_num na wyjœciu generatora
		hi_num = min_num;
	}
	srand(time(NULL));
	result = (rand() % (hi_num - low_num)) + low_num;
	return result;
}
void rand_mxm(int l, int m, int n) {
	/* A(LxN) = B(LxM) * C(MxN)  */
	double *a, *b, *c;
	int i, j, k;
	double czas_obliczen;

	/* Alokacja pamiêci */
	a = (double *)malloc(l * n * sizeof(double));
	b = (double *)malloc(l * m * sizeof(double));
	c = (double *)malloc(m * n * sizeof(double));

	/* Inicjalizacja macierzy A, B i C  */
	for (k = 0; k < l * m; k++)
		b[k] = (double)(random_number(100, 1000) - 500) / 5.;
	for (k = 0; k < m * n; k++)
		c[k] = (double)(random_number(100, 1000) - 500) / 5.;
	for (k = 0; k < l * n; k++)
		c[k] = 0.0;

	/* Obliczamy A = B * C  */

	czas_obliczen = omp_get_wtime();

#pragma omp parallel for shared(a,b,c,l,m,n) private(i,j,k)
	for (j = 0; j < n; j++)
		for (i = 0; i < l; i++)
			for (k = 0; k < m; k++)
				a[i + j*l] += b[i + k*l] * c[k + j*m];
	//a[i+j*l] = a[i+j*l] + b[i+k*l] * c[k+j*m];

	czas_obliczen = omp_get_wtime() - czas_obliczen;

	printf("\n  Liczba wykonanych operacji: l * n * ( 2 * m ) = %d\n", l*n*(2 * m));
	printf("  Czas obliczen = %f s\n", czas_obliczen);
	printf("  Szybkoœæ = Liczba operacji / Czas obliczen = %f mln op/s\n\n", (double)(l*n*(2 * m) / czas_obliczen / 1000000.0));

	free(a);
	free(b);
	free(c);
}

