FLAGS=

all: compile

compile: hello.c
	mpicc $(FLAGS) exercise.c -o exercise

clean:
	rm -f exercise

execute:
	qsub exercise.pbs

watch:
	watch -n 5 qstat -a