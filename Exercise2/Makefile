FLAGS=

all: compile

compile:
	mpicc $(FLAGS) exercise.c -o exercise

clean:
	rm -f exercise

execute:
	qsub exercise.pbs

watch:
	watch -n 5 qstat -a

run:
	mpiexec -np 3 ./exercise