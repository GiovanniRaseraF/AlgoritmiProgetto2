CC=g++
CFLAGS=-I.
DEPS = Lambda.h Utils.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cpbst:  CalcolatoreCasoPeggioreBST.o 
	$(CC) -o casopeggiorebst  CalcolatoreCasoPeggioreBST.o
	
clean:
	rm *.o