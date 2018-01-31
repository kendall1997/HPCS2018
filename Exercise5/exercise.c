#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double evaluate(double);
double integrate(double, double, double);

int from = 0;
int to = 1;
int split = 100000000;
int root = 0;

int main(int argc, char *argv[]){
  //Initial set up
  int rank,size,length;
  char name[25];

  // initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(name, &length);

  //logic
  double data[size];
  double bandwidth = (to - from);
  double block = bandwidth / size;
  double x_0 = from + rank*block;
  double x_f = from + rank*block + block;
  printf("Integrating block [%f,%f] to rank %d\n", x_0, x_f, rank);
  data[rank] = integrate(x_0,x_f,block/split);
  printf("Integrating block [%f,%f] to rank %d [Ready]\n", x_0, x_f, rank);
  
  //Broadcast
  int index;
  for( index = 0; index < size; ++index ){
    MPI_Bcast(&data[index], 1 , MPI_DOUBLE, index, MPI_COMM_WORLD);
  }
  //Out
  if(rank == root){
    int i;
    double pi = 0;
    for (i = 0; i < size; ++i){
      pi += data[i];
    }
    printf("Value of pi : %.16lf\n", pi);
  }

  MPI_Finalize();
  return 0;
}


double integrate(double from, double to, double step){
  double sum = 0;
  double index;
  int times = 0;
  for(index = from; index <= to; index+=step){
    double tmp = evaluate(index) * step;
    sum+=tmp;
    times+=1;
  }
  return sum;
}

double evaluate(double x){
  double bottom = pow(x,2);
  bottom += 1;
  return 4/bottom;
}
