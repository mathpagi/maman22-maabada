

mycomp :  mycomp.o complex.o input_test.o
	gcc -g -ansi -Wall -pedantic mycomp.o complex.o input_test.o -o mycomp -lm




mycomp.o:  mycomp.c complex.h
	gcc -c -ansi -Wall -pedantic mycomp.c -o mycomp.o

complex.o:  complex.c complex.h
	gcc -c -ansi -Wall -pedantic complex.c -o complex.o -lm
	
input_test.o:  input_test.c complex.h
	gcc -c -ansi -Wall -pedantic input_test.c -o input_test.o 
	

