main:
	g++ main.cpp -o main.out

create: clean
	g++ ./samples/create.cpp -o create.out
	./create.out

resize: clean
	g++ ./samples/resize.cpp -o resize.out
	./resize.out

clean:
	rm -f *.o
	rm -f *.out
