main:
	g++ main.cpp -o main.out

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

resize: clean
	g++ ./samples/resize.cpp -o resize.out
	./resize.out

modify: clean
	g++ ./samples/modify_element.cpp -o modify_element.out
	./modify_element.out

push_pop: clean
	g++ ./samples/push_pop.cpp -o push_pop.out
	./push_pop.out

insert: clean
	g++ ./samples/insert.cpp -o insert.out
	./insert.out

erase: clean
	g++ ./samples/erase.cpp -o erase.out
	./erase.out

swap: clean
	g++ ./samples/swap_merge_sort.cpp -o swap_merge_sort.out
	./swap_merge_sort.out

merge: clean
	g++ ./samples/swap_merge_sort.cpp -o swap_merge_sort.out
	./swap_merge_sort.out

sort: clean
	g++ ./samples/swap_merge_sort.cpp -o swap_merge_sort.out
	./swap_merge_sort.out



clean:
	rm -f *.o
	rm -f *.out
