#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  //Initial set up
  int rank,size,length;
  char name[25];

  // initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(name, &length);

  printf("rank: %d, size %d\n",rank,size);

  //logic


  if (rank == 0){
    int counter = 0;
    while (counter < 999){
      MPI_Send(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Recv(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      counter += 1;
      printf("Count value: %d on Rank: %d\n",counter+1, rank);
    }
  }

  if (rank == 1){
    int counter = 0;
    while (counter < 998){
      MPI_Recv(&counter, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(&counter, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
      printf("Count value: %d on Rank: %d\n",counter+1, rank);
    }
  }

  MPI_Finalize();

  return 0;
}
