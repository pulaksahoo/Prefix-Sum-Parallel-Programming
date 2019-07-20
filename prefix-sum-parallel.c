

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/resource.h>
#include <time.h>
#include <omp.h>

void display(int * t, int length_t)
{
	int i = 0;

	for (; i < length_t; ++i)
	{
		printf("%d ", t[i]);
	}
	printf("\n");
}

void prefix_sum(int* T, int n, int th)
{
	// omp_set_num_threads(4);
	printf("No of threads: %d\n",th );
	printf("hello %d\n",th);
	if (n > 1)
	{
		int i;
		int j;
		int l,k;
		// printf("hello %d\n",n/th);
		int * new_arr = (int *) malloc ((th+1)*sizeof(int));
		// printf("hello %d\n",n/th);
		if (n==2)
		{
			T[1] += T[0];
		}
		else
		{
			// printf("hello1 %d\n",n/th);
			#pragma omp parallel num_threads(th) private(j,k)
			{
				k=omp_get_thread_num();	
				// j=k*(n/th);
				// printf("%d %d\n",k*(n/th),(k+1)*n/th);
				for(j=k*(n/th);j<(k+1)*n/th;j++)
				{
					// printf("%d %d\n",j,k);
					new_arr[k]+=T[j];
				}
			#pragma omp barrier
			}

			// display(new_arr,th);
			#pragma omp parallel num_threads(th) private(i)
			for(i=2; i <= th; i*=2)
			{
				// printf("No of threads: %d\n",omp_get_num_threads() );
				// printf("No of threads: %d\n",omp_get_thread_num() );
				if ((omp_get_thread_num() % i) == (i - 1))
				{
					new_arr[omp_get_thread_num()] += new_arr[omp_get_thread_num() - i/2];
					// printf("%d\t%d\n",omp_get_thread_num(),i );
					// display(T,n);
				}
				#pragma omp barrier
			}
			display(new_arr,th);

			// for(i=i/2; i >1; i/=2)
			// {
			// 	if ((omp_get_thread_num() % i) == (i/2 - 1))
			// 	{
			// 		if (!(omp_get_thread_num() < (i/2 - 1)))
			// 		{
			// 			T[omp_get_thread_num()] += T[omp_get_thread_num() - i/2];
			// 		}
			// 	}
			// 	#pragma omp barrier
			// }
		}
	}
}


int main(int argc, char const *argv[])
{
	/*ARGUMENT CHECKING*/
	if (argc < 3)
	{
		// printf("USAGE : %s <N>\n", argv[0]);
		printf("Enter size of array and threads as ARGUMENT");
		exit(1);
	}

	/*INITIALIZATION*/
	/*sizes of table*/
	int n = atoi(argv[1]);
	int th = atoi(argv[2]);
	if(n%th!=0){
		print("n must be divisible by threads");
		exit(1);
	}

	/*tables creation*/
	int * tab = (int *) malloc ((n+1)*sizeof(int));

	/*indices*/
	int i = 0;

	double start;
	double end;

	/*initialize rng*/
	srand (time(NULL));

	/*initialization of tables*/
	for (; i < n; ++i)
	{
		tab[i] = rand()%10;
		// tab[i]=i+1;
	}
	// tab[9]={1,2,3,4,5,6,7,8,0};
	tab[n+1] = 0;

	display(tab, n);
	printf("start SP2 with n = %d\n", n);

	start = omp_get_wtime();

    prefix_sum(tab, n,th);

	end = omp_get_wtime();

	/*DISPLAY*/
    // display(tab, n);


	printf("user time used for SP2 : %f\n", end - start);
	printf("-----------------------------------------------------------------\n");



	/*FREE RESOURCES*/
	free(tab);

	return 0;
}
