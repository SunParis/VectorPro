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

modify: clean
	g++ ./samples/modify_element.cpp -o modify_element.out
	./modify_element.out

assign: clean
	g++ ./samples/assign.cpp -o assign.out
	./assign.out

push_pop: clean
	g++ ./samples/push_pop.cpp -o push_pop.out
	./push_pop.out

clean:
	rm -f *.o
	rm -f *.out
