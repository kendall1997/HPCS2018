FLAGS=

all: compile

compile:
	mpicc $(FLAGS) exercise.c -o exercise -lm

clean:
	rm -f exercise

execute:
	qsub exercise.pbs

watch:
	watch -n 5 qstat -a

run:
	mpiexec -np 2 ./exercise