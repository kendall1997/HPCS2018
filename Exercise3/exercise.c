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
    srand(time(NULL) + rank);
    //Data
    int myRandom = rand() % 100;
    int random0, random1, random2;
    //Requests
    MPI_Request request1;
    MPI_Request request2;
    MPI_Request request11;
    MPI_Request request22;
    //Out
    MPI_Isend(&myRandom, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request1);
    MPI_Isend(&myRandom, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &request2);
    //In
    random0 = myRandom;
    MPI_Irecv(&random1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request11);
    MPI_Irecv(&random2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &request22);
    //Wait
    MPI_Wait(&request11, MPI_SUCCESS);
    MPI_Wait(&request22, MPI_SUCCESS);
    //Out
    printf("Numbers: [%d,%d,%d], Sum: %d, From Rank: %d\n",random0, random1, random2,random0 + random1 + random2, rank);
  }

  else if (rank == 1 ){
    srand(time(NULL) + rank);
    //Data
    int myRandom = rand() % 100;
    int random0, random1, random2;
    //Requests
    MPI_Request request1;
    MPI_Request request2;
    MPI_Request request11;
    MPI_Request request22;
    //Out
    MPI_Isend(&myRandom, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request1);
    MPI_Isend(&myRandom, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &request2);
    //In
    random1 = myRandom;
    MPI_Irecv(&random0, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request11);
    MPI_Irecv(&random2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &request22);
    //Wait
    MPI_Wait(&request11, MPI_SUCCESS);
    MPI_Wait(&request22, MPI_SUCCESS);
    //Out
    printf("Numbers: [%d,%d,%d], Sum: %d, From Rank: %d\n",random0, random1, random2,random0 + random1 + random2, rank);
  }

  else if( rank == 2 ){
    srand(time(NULL) + rank);
    //Data
    int myRandom = rand() % 100;
    int random0, random1, random2;
    //Requests
    MPI_Request request1;
    MPI_Request request2;
    MPI_Request request11;
    MPI_Request request22;
    //Out
    MPI_Isend(&myRandom, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request1);
    MPI_Isend(&myRandom, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request2);
    //In
    random2 = myRandom;
    MPI_Irecv(&random0, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request11);
    MPI_Irecv(&random1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request22);
    //Wait
    MPI_Wait(&request11, MPI_SUCCESS);
    MPI_Wait(&request22, MPI_SUCCESS);
    //Out
    printf("Numbers: [%d,%d,%d], Sum: %d, From Rank: %d\n",random0, random1, random2,random0 + random1 + random2, rank);
  }

  MPI_Finalize();

  return 0;
}