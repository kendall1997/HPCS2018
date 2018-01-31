#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  srand(time(NULL) + rank);
  //Data
  int data[3];
  data[rank] = rand() % 100;
  //Broadcast
  int index;
  for( index = 0; index < size; ++index ){
    MPI_Bcast(&data[index], 1 , MPI_INT, index, MPI_COMM_WORLD);
  }
  //Out
  
  printf("Numbers: [%d,%d,%d], Sum: %d, From Rank: %d on [%s]\n",data[0], data[1], data[2],data[0] + data[1] + data[2], rank,name);

  MPI_Finalize();
  return 0;
}