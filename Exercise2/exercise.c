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

  printf("rank: %d, size %d\n",rank,size);

  //logic

  if (rank == 0 ){
    srand(time(NULL));
    //Data
    int myRandom = rand() % 100;
    int random0, random1, random2;
    //Out
    MPI_Send(&myRandom, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&myRandom, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    //In
    random0 = myRandom;
    MPI_Recv(&random1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&random2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Numbers: [%d,%d,%d], Sum: %d, From Rank: %d\n",random0, random1, random2,random0 + random1 + random2, rank);
  }

  else if (rank == 1 ){
    srand(time(NULL));
    //Data
    int myRandom = rand() % 100 + rand() % 100;
    int random0, random1, random2;
    //Out
    MPI_Send(&myRandom, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&myRandom, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    //In
    random1 = myRandom;
    MPI_Recv(&random0, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&random2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Numbers: [%d,%d,%d], Sum: %d, From Rank: %d\n",random0, random1, random2,random0 + random1 + random2, rank);
  }

  else if( rank == 2 ){
    srand(time(NULL));
    //Data
    int myRandom = rand() % 100 +rand() % 100 + rand() % 100;
    int random0, random1, random2;
    //Out
    MPI_Send(&myRandom, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&myRandom, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    //In
    random2 = myRandom;
    MPI_Recv(&random0, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&random1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Numbers: [%d,%d,%d], Sum: %d, From Rank: %d\n",random0, random1, random2,random0 + random1 + random2, rank);
  }

  MPI_Finalize();

  return 0;
}