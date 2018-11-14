#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

/* COMPILO CON mpicc sample.c -o sample -lm Y EJECUTO CON mpiexec -n 4 ./sample 1000 2.5 3.5 */



double randn (double mu, double sigma)
{
	double U1, U2, W, mult;
	static double X1, X2;
	static int call = 0;
	double X_mu_sigma; 

	if (call == 1)
	{
	call = !call;
	return (mu + sigma * (double) X2);
	}

	do
	{
	U1 = -1 + ((double) rand () / RAND_MAX) * 2;
	U2 = -1 + ((double) rand () / RAND_MAX) * 2;
	W = pow (U1, 2) + pow (U2, 2);
	}
	while (W >= 1 || W == 0);

	mult = sqrt ((-2 * log (W)) / W);
	X1 = U1 * mult;
	X2 = U2 * mult;

	call = !call;

	X_mu_sigma = mu + sigma * (double) X1;

	return (X_mu_sigma);
}

void* generator (int N, double mu, double sigma)
{
	double* values; 
	values = malloc(sizeof(double *)*N);

	int i; 
	for ( i = 0; i < N; i++)
	{
		values[i] = randn(mu, sigma);
	}

	FILE *sample = fopen("sample.dat", "w");
		
	for(int i = 0; i < N; i++)
	{
            	fprintf(sample, "%f", values[i]);
        	fprintf(sample, "\n");
    	}
	fclose(sample);
}

int main(int argc, char *argv[])
{

	int N = atoi(argv[1]);
	double mu = atof(argv[2]);
	double sigma = atof(argv[3]);

	int rank, size;

	/* starts MPI */
	MPI_Init (&argc, &argv);
	/* get current process rank */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	/* get number of processes */
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	/* print the rank and number of processes */
	generator(N/size, mu, sigma);
	/* ends MPI */
	MPI_Finalize();


}


