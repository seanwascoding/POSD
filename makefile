all: dirs bin/ut_all

# src/dfs_iterator.h test/dfsIterator_test.h

bin/ut_all: test/ut_all.cpp test/Iterator_test.h  test/bfsIterator_test.h test/dfsIterator_test.h src/node.h src/folder.h src/file.h src/null_iterator.h iterator.o
	g++ -std=c++11 test/ut_all.cpp obj/iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o: src/iterator.cpp src/iterator.h src/dfs_iterator.h
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

dirs:
	mkdir -p bin obj

clean:
	rm -rf bin obj

.PHONY: clean dirs