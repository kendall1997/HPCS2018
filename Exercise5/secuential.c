#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double evaluate(double);
double integrate(double, double, double);

int from = 0;
int to = 1;
int split = 10;
int size = 5;

int main(int argc, char *argv[]){
  double bandwidth = (to - from);
  double block = bandwidth / size;

  int index;
  for(index = 0; index < size; ++index){
    double x_0 = from + index*block;
    double x_f = from + index*block + block;
    printf("Block [%f,%f] to rank %d\n", x_0, x_f, index);
  }


  
  printf("%f\n", integrate(0,1,0.0001));
}



double integrate(double from, double to, double step){
  double sum = 0;
  double index;
  for(index = from; index <= to; index+=step){
    double tmp = evaluate(index) * step;
    sum+=tmp;
  }
  return sum;
}

double evaluate(double x){
  double bottom = pow(x,2);
  bottom += 1;
  return 4/bottom;
}