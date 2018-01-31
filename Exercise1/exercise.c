#include <mpi.h>
#include <stdio.h>

int main(int argc, char const *argv[]){
  //Initial set up
  int rank,size,length;
  char name[25];

  // initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(name, &length);

  //logic

  int counter = 0;

  while (counter <= 1000) {
    // Receive Data

    if (rank == 0) {
      MPI_Recv(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      counter += 1
    }

    else if( rank == 1) {
      MPI_Recv(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }


    if (rank == 0) {
      MPI_Send(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    else if( rank == 1) {
      MPI_Send(&counter, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
    }

    else {
      //This should not happend!
    }

    printf("Counter : %d, rank: %d\n", counter,rank);
  }



  return 0;
}