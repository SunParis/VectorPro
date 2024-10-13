main:
	g++ main.cpp -o main.out

create: clean
	g++ ./samples/create.cpp -o create.out
	./create.out

resize: clean
	g++ ./samples/resize.cpp -o resize.out
	./resize.out

clear: clean
	g++ ./samples/clear.cpp -o clear.out
	./clear.out

access: clean
	g++ ./samples/access_element.cpp -o access_element.out
	./access_element.out

clean:
	rm -f *.o
	rm -f *.out
