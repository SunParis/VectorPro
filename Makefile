main: clean
	g++ main.cpp -o main.out
	./main.out

create: clean
	g++ ./samples/create.cpp -o create.out
	./create.out

assign: clean
	g++ ./samples/assign.cpp -o assign.out
	./assign.out

at: clean
	g++ ./samples/at.cpp -o at.out
	./at.out

back: clean
	g++ ./samples/back.cpp -o back.out
	./back.out

begin: clean
	g++ ./samples/begin.cpp -o begin.out
	./begin.out

capacity: clean
	g++ ./samples/capacity.cpp -o capacity.out
	./capacity.out

cbegin: clean
	g++ ./samples/cbegin.cpp -o cbegin.out
	./cbegin.out

cend: clean
	g++ ./samples/cend.cpp -o cend.out
	./cend.out

clear: clean
	g++ ./samples/clear.cpp -o clear.out
	./clear.out

crbegin: clean
	g++ ./samples/crbegin.cpp -o crbegin.out
	./crbegin.out

crend: clean
	g++ ./samples/crend.cpp -o crend.out
	./crend.out

emplace: clean
	g++ ./samples/emplace.cpp -o emplace.out
	./emplace.out

emplace_back: clean
	g++ ./samples/emplace_back.cpp -o emplace_back.out
	./emplace_back.out

empty: clean
	g++ ./samples/empty.cpp -o empty.out
	./empty.out

erase: clean
	g++ ./samples/erase.cpp -o erase.out
	./erase.out

find: clean
	g++ ./samples/find.cpp -o find.out
	./find.out

front: clean
	g++ ./samples/front.cpp -o front.out
	./front.out

insert: clean
	g++ ./samples/insert.cpp -o insert.out
	./insert.out

max_size: clean
	g++ ./samples/max_size.cpp -o max_size.out
	./max_size.out

merge: clean
	g++ ./samples/merge.cpp -o merge.out
	./merge.out

not_empty: clean
	g++ ./samples/not_empty.cpp -o not_empty.out
	./not_empty.out

operator[]: clean
	g++ ./samples/operator[].cpp -o operator[].out
	./operator[].out

operator_assign: clean
	g++ ./samples/operator=.cpp -o operator=.out
	./operator=.out

ostream: clean
	g++ ./samples/ostream.cpp -o ostream.out
	./ostream.out

pop_back: clean
	g++ ./samples/pop_back.cpp -o pop_back.out
	./pop_back.out

pop: clean
	g++ ./samples/pop.cpp -o pop.out
	./pop.out

print: clean
	g++ ./samples/print.cpp -o print.out
	./print.out

push_back: clean
	g++ ./samples/push_back.cpp -o push_back.out
	./push_back.out

push: clean
	g++ ./samples/push.cpp -o push.out
	./push.out

rbegin: clean
	g++ ./samples/rbegin.cpp -o rbegin.out
	./rbegin.out

rend: clean
	g++ ./samples/rend.cpp -o rend.out
	./rend.out

reserve: clean
	g++ ./samples/reserve.cpp -o reserve.out
	./reserve.out

resize: clean
	g++ ./samples/resize.cpp -o resize.out
	./resize.out

reverse: clean
	g++ ./samples/reverse.cpp -o reverse.out
	./reverse.out

shrink_to_fit: clean
	g++ ./samples/shrink_to_fit.cpp -o shrink_to_fit.out
	./shrink_to_fit.out

size: clean
	g++ ./samples/size.cpp -o size.out
	./size.out

sort: clean
	g++ ./samples/sort.cpp -o sort.out
	./sort.out

swap: clean
	g++ ./samples/swap.cpp -o swap.out
	./swap.out

clean:
	rm -f *.o
	rm -f *.out
