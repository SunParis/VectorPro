main:
	g++ main.cpp -o main.out

create: clean
	g++ ./samples/create.cpp -o create.out
	./create.out

clean:
	rm -f *.o
	rm -f *.out
