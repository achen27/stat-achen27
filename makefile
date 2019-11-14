all: stat.o
	gcc -o program stat.o

stat.o: stat.c stat.h
	gcc -c stat.c stat.h

run:
	./program

clean:
	rm *.o
	rm *~
