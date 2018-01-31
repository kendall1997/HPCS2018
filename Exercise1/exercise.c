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

  int counter = 0;

  while (counter <= 1000) {

    //send

    if (rank == 0) {
      MPI_Send(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    else if( rank == 1 && counter != 1000) {
      MPI_Send(&counter, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
    }

    else {
      //This should not happend!
    }

    // Receive Data
    // int MPI_Recv(void *buf, int count, MPI_Datatype datatype,int source, int tag, MPI_Comm comm, MPI_Status *status)
    if (rank == 0) {
      MPI_Recv(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      counter += 1;
    }

    else if( rank == 1) {
      MPI_Recv(&counter, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    printf("Counter : %d, rank: %d\n", counter,rank);

    if(counter == 1000){
      break;
    }
  }

  MPI_Finalize();


  return 0;
}
