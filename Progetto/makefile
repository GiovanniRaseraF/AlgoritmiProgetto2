CC=g++
CFLAGS=-I.
DEPS = Lambda.h Utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

calcmake:  Calcolatore.o 
	$(CC) -o calcolare  Calcolatore.o

vscalc:  CalcolatoreVisualStudio.o 
	$(CC) -o vscalcolatore  CalcolatoreVisualStudio.o
	

clean:
	rm *.o