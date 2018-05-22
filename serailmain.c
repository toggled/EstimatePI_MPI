//
// Created by Naheed Anjum Arafat on 5/22/18.
//

#include <stdio.h>
#include <math.h>
#include <sys/time.h>

int main() {

    double pi_25decimal = 3.141592653589793238462643;

    double totalPI; // final value of PI computed
    int n = 2000;
    double x,h;
    int i;
    struct timeval start;
    struct timeval end;
    long timeusecs;

    totalPI = 0.0;


    // My solution

    gettimeofday(&start, NULL);

    h = 1.0 / n ;
    for (i = 0 ; i< n ; i++){
        x =  h* ((double)i + 0.5);
//        printf("from %.2f \n",x);
        totalPI += (h*(4.0 / (1.0 + x*x)));
    }

    gettimeofday(&end, NULL);

//    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        printf("pi is approximately %.16f, Error is %.16f\n",
               totalPI, fabs(totalPI - pi_25decimal));

    timeusecs = ((end.tv_sec * 1000000 + end.tv_usec)
     - (start.tv_sec * 1000000 + start.tv_usec));

//    printf("Runtime (microsecs) %ld \n", timeusecs );
    printf("Runtime (milli secs) %.4f \n", timeusecs/1000.0 );
    return 0;
}