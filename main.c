#include <stdio.h>
#include <math.h>
#include <mpi.h>


int main(int argc, char* argv[]) {
    int myid, numprocs; // id of this process,  global number_of_processes spawned.
    double pi_25decimal = 3.141592653589793238462643;

    double myvalueofPI; // final value of PI i computed
    double totalPI; // final value of PI computed by master
    int n = 20;
    double h,x;
    int i;
    double temp_sum;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    h = 1.0 / (double) n;
    myvalueofPI = 0.0;

    // Solution in the book

//    for ( i = myid ; i < n; i += numprocs) {
//        x = h * ((double)i + 0.5);
//        printf("%.2f from %d\n",x,myid);
//        temp_sum += (4.0 / (1.0 + x*x));
//    }
//
//    myvalueofPI = h * temp_sum;

    // My solution

    for (i = myid* n / numprocs ; i< (myid+1)* n / numprocs ; i++){
        x = h * ((double)i + 0.5);
        printf("%.2f from %d\n",x,myid);
        myvalueofPI += (h*(4.0 / (1.0 + x*x)));
    }

    MPI_Reduce(&myvalueofPI, &totalPI, 1, MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (myid == 0){
        printf("pi is approximately %.16f, Error is %.16f\n",
               totalPI, fabs(totalPI - pi_25decimal));
    }

    MPI_Finalize();
    return 0;
}