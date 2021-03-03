CC = gcc

all: bubble_sort quick_sort merge_sort insertion_sort selection_sort

bubble_sort: bubble_sort.c pattern.c
	$(CC) -Wall $< -o $@

quick_sort: quick_sort.c pattern.c
	$(CC) -Wall $< -o $@

merge_sort: merge_sort.c pattern.c
	$(CC) -Wall $< -o $@

insertion_sort: insertion_sort.c pattern.c
	$(CC) -Wall $< -o $@

selection_sort: selection_sort.c pattern.c
	$(CC) -Wall $< -o $@

clean:
	rm -f bubble_sort quick_sort merge_sort insertion_sort selection_sort
