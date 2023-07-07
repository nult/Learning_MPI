#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <time.h>
#include <mpi.h>

#define XI 0.01745329252

double pi_cal(int num,double length,double width,double needle);

int main(int argc, char *argv[])
{
    int i,num_procs,my_rank;
    int Ni=1000000;
    double ai=1,bi=1,li=1;
    double pi=0,pi_temp;
    struct timespec starttime,endtime;
    long usetime,d_nsec;
    time_t d_sec;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&starttime);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,  &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD,  &my_rank);
    //if(my_rank==0){
    //    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&starttime);
    //}
    pi_temp=pi_cal(Ni/num_procs,ai,bi,li);
    MPI_Reduce(&pi_temp,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(my_rank==0){
        pi=pi/num_procs;
    }
    MPI_Finalize();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&endtime);
    d_sec = endtime.tv_sec - starttime.tv_sec;
    d_nsec = endtime.tv_nsec - starttime.tv_nsec;
    usetime = d_sec*1E9 + d_nsec;
    printf("N = %d, pi = %f ,time cost is %d ns\n",Ni,pi,usetime);

    return 0;
}

double pi_cal(int N,double a,double b,double l)
{
    int B,i;
    double r_x,r_y,angle;
    double P,pi;
    double p1_x,p1_y,p2_x,p2_y;

    if(l>=sqrt(a*a+b*b)){
        printf("l is larger than sqrt(a*a+b*b),wrong!");
        exit(1);
    }

    srand(time(NULL));
    B=0;
    for(i=0;i<N;i++){
        r_x=((double)rand())*100000/((double)RAND_MAX);
        r_y=((double)rand())*100000/((double)RAND_MAX);
        angle=((double)rand())*360/((double)RAND_MAX);
        p1_x=r_x-0.5*l*cos(XI*angle);p1_x=p1_x/a;
        p2_x=r_x+0.5*l*cos(XI*angle);p2_x=p2_x/a;
        p1_y=r_y-0.5*l*sin(XI*angle);p1_y=p1_y/b;
        p2_y=r_y+0.5*l*sin(XI*angle);p2_y=p2_y/b;
        if(ceil(p1_x)!=ceil(p2_x) || ceil(p1_y)!=ceil(p2_y)){
            B++;
        }
    }
    P=((double)B)/((double)N);
    pi=(2.0*l*(a+b)-l*l)/(P*a*b);
    return pi;
}
